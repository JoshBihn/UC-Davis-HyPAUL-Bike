int32_t p_tank() {
  return int32_t(analogRead(P_TANK))*P_TANK_C;
}
