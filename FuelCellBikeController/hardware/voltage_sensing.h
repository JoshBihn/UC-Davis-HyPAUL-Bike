int32_t v_battery() {
  int32_t reading = int32_t(analogRead(V_BAT));
  if (reading < V_BAT_ZERO) return 0;
  else return roundf((reading-V_BAT_ZERO)*V_BAT_C);
}

int32_t v_fuel_cell() {
  int32_t reading = int32_t(analogRead(V_FC));
  if (reading < V_FC_ZERO) return 0;
  else return roundf((reading-V_FC_ZERO)*V_FC_C);
}
