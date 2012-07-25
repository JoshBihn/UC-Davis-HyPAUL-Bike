bool kickstand_out() {
  return digitalRead(SW_KICKSTAND) == HIGH;
}
