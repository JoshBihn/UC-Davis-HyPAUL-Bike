int pot_value() {
  int value = analogRead(POT);
  if (value > 1010) {
    return 1023;
  } else {
    return value;
  }
}
