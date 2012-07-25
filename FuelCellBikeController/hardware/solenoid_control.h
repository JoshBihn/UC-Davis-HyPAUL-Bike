uint32_t solenoid_fc_off_due = 0;

void solenoid_motor_on() {
  digitalWrite(SOL_MOTOR, HIGH);
}

void solenoid_motor_off() {
  digitalWrite(SOL_MOTOR, LOW);
}

void solenoid_contactor_on() {
  digitalWrite(SOL_CONTACT, HIGH);
}

void solenoid_contactor_off() {
  digitalWrite(SOL_CONTACT, LOW);
}

void solenoid_fc_on() {
  digitalWrite(SOL_FC, HIGH);
}

void solenoid_fc_off() {
  digitalWrite(SOL_FC, LOW);
}

void solenoid_fc_toggle_wait() {
  solenoid_fc_on();
  delay(2000);
  solenoid_fc_off();
}

void solenoid_fc_toggle_schedule() {
  solenoid_fc_on();
  if (solenoid_fc_off_due == 0) solenoid_fc_off_due = millis()+2000;
}

void solenoid_fc_toggle_control() {
  if (solenoid_fc_off_due > 0 && millis() > solenoid_fc_off_due) {
    solenoid_fc_off();
    solenoid_fc_off_due = 0;
  }
}
