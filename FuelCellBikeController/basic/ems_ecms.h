int32_t ecms_options_power[ECMS_OPTION_COUNT] = {
  ECMS_0_FC_POWER,  ECMS_1_FC_POWER,  ECMS_2_FC_POWER,  ECMS_3_FC_POWER,  ECMS_4_FC_POWER,
  ECMS_5_FC_POWER,  ECMS_6_FC_POWER,  ECMS_7_FC_POWER,  ECMS_8_FC_POWER,  ECMS_9_FC_POWER,
  ECMS_10_FC_POWER, ECMS_11_FC_POWER, ECMS_12_FC_POWER, ECMS_13_FC_POWER, ECMS_14_FC_POWER
};

float ecms_options_cost[ECMS_OPTION_COUNT] = {
  ECMS_0_FC_COST,  ECMS_1_FC_COST,  ECMS_2_FC_COST,  ECMS_3_FC_COST,  ECMS_4_FC_COST,
  ECMS_5_FC_COST,  ECMS_6_FC_COST,  ECMS_7_FC_COST,  ECMS_8_FC_COST,  ECMS_9_FC_COST,
  ECMS_10_FC_COST, ECMS_11_FC_COST, ECMS_12_FC_COST, ECMS_13_FC_COST, ECMS_14_FC_COST
};

int ecms_penalty_soc[ECMS_PENALTY_COUNT] = {
  ECMS_P0_SOC, ECMS_P1_SOC, ECMS_P2_SOC, ECMS_P3_SOC, ECMS_P4_SOC, ECMS_P5_SOC
};

int ecms_penalty_val[ECMS_PENALTY_COUNT] = {
  ECMS_P0_VAL, ECMS_P1_VAL, ECMS_P2_VAL, ECMS_P3_VAL, ECMS_P4_VAL, ECMS_P5_VAL
};

int32_t ecms_option_fc_power(int option_id) {
  // return fc power corresponding to the option specified
  return ecms_options_power[option_id];
}

float ecms_option_fc_cost(int option_id) {
  // return fc cost corresponding to the option specified
  return ecms_options_cost[option_id];
}

float ecms_bat_equivalent_cost(int32_t bat_power) {
  // calculate battery cost by power
  if (bat_power > 0) {
    // discharging
    return bat_power*ECMS_BAT_SC/ECMS_BAT_D_EFF;
  } else {
    // charging
    return bat_power*ECMS_BAT_SC*ECMS_BAT_C_EFF;
  }

}

float ecms_battery_penalty(int soc_percentage) {

  int p_left = 0;
  int p_right = 1;

  // return 0 if input is out of range
  if (soc_percentage < ecms_penalty_soc[0] || soc_percentage > ecms_penalty_soc[(ECMS_PENALTY_COUNT-1)]) return 0;

  // search for the penalty function points right and left of the input soc
  for (int i=1;i<ECMS_PENALTY_COUNT;i++) {
    if (soc_percentage < ecms_penalty_soc[i]) {
      p_right = i;
      p_left = i-1;
      break;
    }
  }

  // linear interpolation of penalty function, y = y_left + dy/dx*(x - x_left)
  return (
    ecms_penalty_val[p_left]) + (
      float(ecms_penalty_val[p_right] - ecms_penalty_val[p_left])/
      float(ecms_penalty_soc[p_right] - ecms_penalty_soc[p_left])*
      (soc_percentage-ecms_penalty_soc[p_left])
  );

}



float ecms_option_total_cost(int option_id, int32_t motor_power, float bat_penalty) {
  // calculate battery power
  int32_t bat_power = motor_power-ecms_option_fc_power(option_id);
  // return sum of fc and battery cost
  return ecms_bat_equivalent_cost(bat_power)*bat_penalty + ecms_option_fc_cost(option_id);
}

int ecms_optimal_option(int32_t motor_power, float bat_penalty) {

  // define var to store current option's cost
  float cur_option_cost = 0;

  // start with option 0 as optimal option
  float opt_option_cost = ecms_option_total_cost(0, motor_power, bat_penalty);
  int opt_option_id = 0;

  // cycle through options 1 and up
  for (int i=1;i<ECMS_OPTION_COUNT;i++) {

    // calculate cost of the current option
    cur_option_cost = ecms_option_total_cost(i, motor_power, bat_penalty);

    if (cur_option_cost < opt_option_cost) {
      // the current option is better
      opt_option_cost = cur_option_cost;
      opt_option_id = i;
    }

  }

  // all options evaluated, return option with lowest cost
  return opt_option_id;

}

bool ecms_is_option(int option_id) {
  return (option_id > -1 && option_id < ECMS_OPTION_COUNT);
}
