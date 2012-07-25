int32_t soc_init = 0;
int32_t volatile soc_cc = 0;

int32_t soc_by_ocv(int32_t v_bat) {

  float params[6] = {SOC_OCV_C0, SOC_OCV_C1, SOC_OCV_C2, SOC_OCV_C3, SOC_OCV_C4, SOC_OCV_C5};
  float soc_ocv = 0;
  float current_term = 0;

  if (v_bat < SOC_OCV_V_MIN) v_bat = SOC_OCV_V_MIN;
  if (v_bat > SOC_OCV_V_MAX) v_bat = SOC_OCV_V_MAX;

  for(int i=0;i<6;i++) {
    current_term = params[i];
    for(int j=0;j<i;j++) {
      current_term = current_term*((v_bat-SOC_OCV_V_OFFSET)/SOC_OCV_V_SCALE);
    }
    soc_ocv += current_term;
  }

  return roundf(soc_ocv*5);
}

void soc_by_cc_count() {
  int32_t i_bat = i_battery();

  if (i_bat < 0) {
    // charging
    soc_cc += int32_t(roundf(float(i_bat)*SOC_CC_I_TO_CAP_C*SOC_CC_CHARGE_EFF));
  } else {
      // discharging
    soc_cc += int32_t(roundf(float(i_bat)*SOC_CC_I_TO_CAP_C/SOC_CC_DISCHA_EFF));
  }
}

void soc_by_cc_start(int32_t init) {
  soc_cc = init;
  soc_init = init;
  Timer1.initialize(SOC_CC_INTERVAL);
  Timer1.attachInterrupt(soc_by_cc_count);
}

void soc_by_cc_stop() {
  Timer1.detachInterrupt();
}

int32_t soc_init_val() {
  return roundf(soc_init/1e3);
}

int32_t soc_current_charge() {
  return soc_cc/1e3;
}

int soc_percentage(int32_t charge) {
  return 100-charge*100/SOC_CAPACITY;
}

void soc_estimation_ritual() {

  int32_t soc_v_bat = 0;

  // Put message on screen
  lcd.setCursor(0,0);
  lcd.print("SOC: estimating ");
  lcd.setCursor(0,1);
  lcd.print("                ");

  // Stop state of charge estimation
  soc_by_cc_stop();

  // Set fc control output to 0 minimizing the fc current
  i_control_output(0);

  // Turn off motor and motor fan if they're on
  fan_motor_off();
  solenoid_motor_off();

  // Wait a while
  delay(1000);

  // Average battery voltage over 2 seconds
  for (int i=0;i<10;i++) {
    // Measure voltage
    soc_v_bat += v_battery();
    delay(200);
  }
  soc_v_bat = roundf(soc_v_bat/10);

  // Estimate soc by ocv and restart coulomb counting
  soc_by_cc_start(soc_by_ocv(soc_v_bat));

  // set fc control output to the value determined by the power controller
  i_control_output(p_controller_output());

}
