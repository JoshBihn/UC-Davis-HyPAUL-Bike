int32_t i_battery_low() {
  return roundf((int32_t(analogRead(I_BAT_LOW))-I_BAT_LOW_ZERO)*I_BAT_LOW_C);
}

int32_t i_battery_high() {
  return roundf((int32_t(analogRead(I_BAT_HIGH))-I_BAT_HIGH_ZERO)*I_BAT_HIGH_C);
}

int32_t i_battery() {
  int32_t i_bat_l = i_battery_low();
  if (i_bat_l < I_BAT_CROSSOVER) {
    return i_bat_l;
  } else {
    return i_battery_high();
  }
}

int32_t i_fuel_cell() {
  int reading = analogRead(I_FC);
  if (reading == 0) return 0;
  else return roundf((int32_t(reading)-I_FC_ZERO)*I_FC_C);
}

int32_t i_motor() {
  int reading = analogRead(I_MOTOR);
  if (reading < I_MOTOR_ZERO) return 0;
  else return roundf((int32_t(reading)-I_MOTOR_ZERO)*I_MOTOR_C);
}
