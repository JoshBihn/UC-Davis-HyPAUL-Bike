uint32_t daq_start, iter_start = 0;
int32_t bike_velocity, bike_distance, soc_charge, i_fc, i_bat, i_mot, v_fc, v_bat, p_fc, p_bat, p_mot, p_mot_avg, p_mot_avg_tmp, prs_h2, m_h2 = 0;
int prev_iter_time, iter_usage, iter_counter, soc_perc = 0;
int em_mode = EM_ECMS_ON;
float t_h2, t_mot, t_bat, em_bat_penalty = 0;
bool soc_reset_due, temp_fahrenheit, vel_mph, lcd_claimed = false;
bool browsing_menu = true;

void loop() {

  // Wait until iteration start is due, meanwhile act on button presses
  while (millis() % ITER_INTERVAL) {

    switch (button_down()) {
    case BUTTON_NEXT:
      if (browsing_menu) {
        menu_next();
      } else {
        switch (menu_page()) {

        case PAGE_EM:
          if (ecms_is_option(em_mode+1)) {
            // user defined fuel cell power option
            em_mode++;
          }
          break;

        }
      }
      break;

    case BUTTON_PREVIOUS:
      if (browsing_menu) {
        menu_prev();
      } else {
        switch (menu_page()) {

        case PAGE_EM:
          if (ecms_is_option(em_mode-1)) {
            // user selected fc power option
            em_mode--;
          } else {
            // ECMS on
            em_mode = EM_ECMS_ON;
          }
          break;

        }
      }
      break;

    case BUTTON_ACTION:
      switch(menu_page()) {

      case PAGE_DAQ:
        if (daq_on()) {
          // Daq is on, schedule stop
          daq_schedule_stop();
        } else {
          // Daq is off, schedule start
          if (sd_new_file()) {
            daq_schedule_start();
          }
        }
        break;

      case PAGE_SOC:
        // If daq is off schedule soc reset
        if (!daq_on()) {
          soc_reset_due = true;
        }
        break;

      case PAGE_EM:
        if (fc_on()) {
          // Toggle menu browsing or setpoint choosing
          browsing_menu = !browsing_menu;
        } else {
          // fc is off, start it
          solenoid_fc_toggle_schedule();
        }
        break;

      case PAGE_VELOCITY:
        // Toggle mph or kph
        vel_mph = !vel_mph;
        break;

      case PAGE_TEMP:
        // Toggle Fahrenheit or Celsius
        temp_fahrenheit = !temp_fahrenheit;
        break;

      }
      // When a button is pushed the lcd is updated
      menu_refresh_due_now();
      break;
    }
  }

  // Iteration start, save time
  iter_start = millis();

  // Velocity measurement, updated once every second
  if (iter_counter == 0) {
    bike_velocity = vel_bike();
  }

  // Reset odometer if daq is gonna start
  if (daq_start_scheduled() && iter_counter == 0) vel_bike_odo_reset();

  // Traveled distance
  bike_distance = vel_bike_odo();

  // Save current SOC
  soc_charge = soc_current_charge();
  soc_perc = soc_percentage(soc_charge);

  // EM: calculate battery penalty function value
  if (iter_counter == 0) em_bat_penalty = ecms_battery_penalty(soc_perc);

  // Current measurements
  i_fc = i_fuel_cell();
  i_bat = i_battery();
  i_mot = i_motor();

  // Voltage measurements
  v_fc = v_fuel_cell();
  v_bat = v_battery();

  // Power estimation
  p_fc = roundf((v_fc/1e3)*(i_fc/1e3));
  p_bat = roundf((v_bat/1e3)*(i_bat/1e3));
  p_mot = roundf((v_bat/1e3)*(i_mot/1e3));

  // Pressure measurement
  prs_h2 = p_tank();

  // Hydrogen mass estimation
  m_h2 = hydrogen_mass(t_h2, prs_h2);

  // When daq start is scheduled and the iteration counter passes 0
  if (daq_start_scheduled() && iter_counter == 0) {

    // Start daq
    daq_start_now();

    // Save time
    daq_start = iter_start;

    // Write CSV header line
    sd_bw.putStr("id");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("timestamp (ms)");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("prev iter time (ms)");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("velocity (mm/s)");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("distance (mm)");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("Bat SOC (mAh)");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("Bat SOC (%)");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("i_fc (mA)");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("i_bat (mA)");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("i_mot (mA)");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("v_fc (mV)");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("v_bat (mV)");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("p_fc_setpoint (W)");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("p_fc (W)");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("p_bat (W)");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("p_mot (W)");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("t_h2 (deg C)");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("t_bat (10^-2 deg C)");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("t_mot (deg C)");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("prs_h2 (kPa)");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("m_h2_tank (g)");
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putStr("\r\n");
    sd_bw.writeBuf();

  }

  // If the daq has been started
  if (daq_started()) {

    // Write CSV line
    sd_bw.putNum(daq_measurement_id()); //changed daq_measurement_id to unsigned int now 1/2 the limit of daq
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum((iter_start-daq_start));
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(prev_iter_time);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(bike_velocity);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(bike_distance);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(soc_charge);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(soc_perc);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(i_fc);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(i_bat);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(i_mot);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(v_fc);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(v_bat);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(p_controller_setpoint());
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(p_fc);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(p_bat);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(p_mot);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum((int)(t_h2*100));  // note 1; removed roundf and cast to int. data out put is understood by the
    sd_bw.putStr(DAQ_CSV_SEPARATOR); //reader to have a decimal in front of the last two digits
    sd_bw.putNum((int)(t_bat*100)); // see note one
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum((int)(t_mot*100)); // see note one
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(prs_h2);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(m_h2);
    sd_bw.putStr("\r\n");
    sd_bw.writeBuf();

    daq_measurement_increment();

  }

  // If a daq stop has been scheduled and the iteration counter hits 9
  if (daq_stop_scheduled() && iter_counter == 9) {
    daq_stop_now();
    sd_close_file();
  }

  // Determine if fuel cell is on
  fc_determine_state(v_fc);

  // Toggle FC solenoid if scheduled
  solenoid_fc_toggle_control();

  // Calculate average motor power over a second before the iteration counter hits 0
    if (iter_counter == 9) {
      p_mot_avg = roundf(p_mot_avg_tmp/10);
      p_mot_avg_tmp = 0;
    }
    p_mot_avg_tmp += p_mot;

  if (fc_on()) {
    // Fuel cell is on
    if (em_mode == EM_ECMS_ON) {
      // ECMS is on, set power controller setpoint to the optimal ECMS option before the iteration counter hits 0
      if (iter_counter == 9) {
        p_controller_setpoint(ecms_option_fc_power(ecms_optimal_option(p_mot_avg, em_bat_penalty)));
      }
    } else {
      // User selected fc power, set power controller setpoint to the ECMS option specified in em_mode
      p_controller_setpoint(ecms_option_fc_power(em_mode));
    }
  } else {
    // Fuel cell is off, set power controller setpoint to zero
    p_controller_setpoint(0);
  }

  // Input measured fuel cell power into power controller
  p_controller_input(p_fc);

  // write power controller output value to the boost converter current control input
  i_control_output(p_controller_output());

  // Alternate temperature measurements, do this last because it can be slow..
  switch(iter_counter) {
    case 1:
      t_tank_request();
      break;
    case 2:
      t_h2 = t_tank();
      break;
    case 3:
      t_motor_request();
      break;
    case 4:
      t_mot = t_motor();
      break;
    case 6:
      t_battery_request();
      break;
    case 7:
      t_bat = t_battery();
      break;
  }

  /* // Turn battery fan on when temperature is too high or sensor is absent
  if (t_bat > FAN_BAT_T_THRES || t_bat == DEVICE_DISCONNECTED) {
    fan_battery_on();
  } else {
    fan_battery_off();
  } */

  // OCV is very dependent on temperature, so keep battery fan always on to keep temperature as low as possible
  fan_battery_on();

  // Turn motor fan on when temperature is too high or sensor is absent
  if (t_mot > FAN_MOT_T_THRES || t_mot == DEVICE_DISCONNECTED) {
    fan_motor_on();
  } else {
    fan_motor_off();
  }

  // Turn on motor controller when nothing is wrong
  if (!kickstand_out() && soc_perc > 20) {
    solenoid_motor_on();
    warning_led_off();
  } else {
    solenoid_motor_off();
    // led: flash when kickstand is out, light when soc is too low
    if (iter_counter < 5 || soc_perc <= 20) {
      warning_led_on();
    } else {
      warning_led_off();
    }
  }

  if (soc_perc > 90) {
    // When SOC is too high
    if (fc_on()) {
      // Turn off FC controller when it's on
      solenoid_fc_toggle_schedule();
    }
    // led constantly on
    warning_led_on();
}

  // SOC reset due? SOC reset disrupts the iteration flow as it takes about 6 seconds
  if (soc_reset_due) {
    // do a bunch of stuff, takes long
    soc_estimation_ritual();
    // SOC reset done
    soc_reset_due = false;
  }

  // Refresh menu if needed
  if (menu_refresh_due()) {

    // Output menu
    lcd.setCursor(0,0);
    switch (menu_page()) {

    // Daq page
    case PAGE_DAQ:
      lcd.print("Daq: ");
      if (daq_on()) {
        lcd.print("stop?      ");
      } else {
        lcd.print("start?     ");
      }

      lcd.setCursor(0,1);
      switch (sd_error()) {
      case 0:
        lcd.print(sd_file_name);
        lcd.print("                ");
        break;
      case 1:
        lcd.print("SD init error   ");
        break;
      case 2:
        lcd.print("SD open error   ");
        break;
      }
      break;

      // SOC page
      case PAGE_SOC:
        lcd.print("SOC: ");
        if (!daq_on()) {
          lcd.print("reset?      ");
        } else {
          lcd.print("            ");
        }
        lcd.setCursor(0,1);
        if (soc_reset_due) {
          lcd.print("                ");
        } else {
          lcd.print(soc_init_val());
          lcd.print("");
          if ((soc_charge-soc_init_val()) >= 0) lcd.print("+");
          lcd.print((soc_charge-soc_init_val()));
          lcd.print(" ");
          lcd.print(soc_perc);
          lcd.print("% ");
          lcd.print(em_bat_penalty, 1);
          lcd.print("     ");
        }
        break;

      // Energy management page
      case PAGE_EM:
        lcd.print("EM: ");
        if (fc_on()) {
          if (browsing_menu) {
            switch (p_controller_state()) {
            case 0:
              lcd.print("set mode?  ");
              break;
            case 1:
              lcd.print("bc ctrl min");
              break;
            case 2:
              lcd.print("bc ctrl max");
              break;
            }
          } else {
            // choosing energy management mode
            if (em_mode == EM_ECMS_ON) {
              lcd.print("ECMS");
            } else {
              lcd.print(ecms_option_fc_power(em_mode));
              lcd.print(" W");
            }
            lcd.print(", ok?   ");
          }
        } else {
          lcd.print("start fc?   ");
        }

        lcd.setCursor(0,1);
        if (browsing_menu || em_mode == EM_ECMS_ON) {
          lcd.print("FC:");
          lcd.print((p_fc/1e3), 1);
          lcd.print(" Set:");
          lcd.print((p_controller_setpoint()/1e3), 1);
          lcd.print("kW");
        } else {
          // user defined ecms option
          lcd.print("ec:");
          lcd.print(ecms_option_total_cost(em_mode, p_mot_avg, em_bat_penalty), 1);
          lcd.print(" mg/s    ");
        }
        break;

    // Velocity page
    case PAGE_VELOCITY:
      lcd.print("Speed: ");
      if (vel_mph) {
        lcd.print("to km/h? ");
      } else {
        lcd.print("to mph?  ");
      }
      lcd.setCursor(0,1);
      if (vel_mph) {
        if (daq_on()) {
          lcd.print((bike_distance*0.6214e-6), 1);
          lcd.print(" mi ");
        }
        lcd.print((bike_velocity*2.23e-3), 1);
        lcd.print(" mph         ");
      } else {
        if (daq_on()) {
          lcd.print((bike_distance*1e-6), 1);
          lcd.print(" km ");
        }
        lcd.print((bike_velocity*3.6e-3), 1);
        lcd.print(" kmh         ");
      }
      break;

    // Fuel cell measurements page
    case PAGE_FC:
      if (fc_on()) {
        lcd.print("FC (on): ");
      } else {
        lcd.print("FC (off): ");
      }
      lcd.print(p_fc);
      lcd.print(" W     ");
      lcd.setCursor(0,1);
      lcd.print((v_fc/1e3), 2);
      lcd.print(" V  ");
      if (v_fc < 1e4) lcd.print(" ");
      if (!fc_on()) lcd.print(" ");
      lcd.print((i_fc/1e3), 1);
      lcd.print(" A ");
      break;

    // Battery measurements page
    case PAGE_BATTERY:
      lcd.print("Battery: ");
      lcd.print(p_bat);
      lcd.print(" W    ");
      lcd.setCursor(0,1);
      lcd.print((v_bat/1e3), 2);
      lcd.print(" V  ");
      if (v_bat < 1e4) lcd.print(" ");
      lcd.print((i_bat/1e3), 1);
      lcd.print(" A   ");
      break;

    // Battery measurements page
    case PAGE_MOTOR:
      lcd.print("Motor:  ");
      lcd.print(p_mot);
      lcd.print(" W     ");
      lcd.setCursor(0,1);
      lcd.print((v_bat/1e3), 2);
      lcd.print(" V ");
      if (v_bat < 1e4) lcd.print(" ");
      lcd.print((i_mot/1e3), 1);
      lcd.print(" A    ");
      break;

    // Temperature page
    case PAGE_TEMP:
      lcd.print("Temp: ");
      if (temp_fahrenheit) {
        lcd.print("to C?     ");
      } else {
        lcd.print("to F?     ");
      }
      lcd.setCursor(0,1);
      if (temp_fahrenheit) {
        lcd.print("Bat:");
        lcd.print((t_bat*9/5+32), 0);
        lcd.print("F Mot:");
        lcd.print((t_mot*9/5+32), 0);
        lcd.print("F ");
      } else {
        lcd.print("Bat:");
        lcd.print(t_bat, 0);
        lcd.print("C Mot:");
        lcd.print(t_mot, 0);
        lcd.print("C ");
      }
        break;

    // Hydrogen supply page
    case PAGE_HYDROGEN:
      lcd.print("H2: ");
      lcd.print(m_h2);
      lcd.print(" g left    ");
      lcd.setCursor(0,1);
      lcd.print("P:");
      lcd.print(roundf(prs_h2/100));
      lcd.print(" b T:");
      lcd.print(t_h2,1);
      lcd.print("C    ");
      break;

    // Stats page
    case PAGE_STATS:
      lcd.print("Stats:          ");
      lcd.setCursor(0,1);
      lcd.print("Up:");
      lcd.print((millis()/1000/60));
      lcd.print(" m Us:");
      lcd.print((prev_iter_time*100/ITER_INTERVAL));
      lcd.print("%    ");
      break;

    }
  }

  // Iteration counter
  iter_counter++;
  if (iter_counter == 10) iter_counter = 0;

  // Iteration end, save iteration time
  prev_iter_time = millis()-iter_start;

}
