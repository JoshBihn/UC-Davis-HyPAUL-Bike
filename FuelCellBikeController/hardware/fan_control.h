void fan_battery_on() {
  digitalWrite(FAN_BAT, HIGH);
}

void fan_battery_off() {
  digitalWrite(FAN_BAT, LOW);
}

void fan_motor_on() {
  digitalWrite(FAN_MOTOR, HIGH);
}

void fan_motor_off() {
  digitalWrite(FAN_MOTOR, LOW);
}
