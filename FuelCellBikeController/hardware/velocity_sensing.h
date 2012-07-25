uint32_t volatile vel_first_pulse_id, vel_first_pulse_time, vel_last_pulse_time, vel_total_pulse_count, vel_signal_low_at, vel_signal_high_at = 0;

void vel_pulse() {

  if (digitalRead(VEL_BIKE) == LOW) {
    vel_signal_low_at = micros();
  }

  if (digitalRead(VEL_BIKE) == HIGH) {
  // If the signal has been low long enough this is an actual pulse
    if (vel_signal_low_at > 0 && (micros()-vel_signal_low_at) > 3000) {

      // Reset low timer
      vel_signal_low_at = 0;

      // Increment pulse counter
      vel_total_pulse_count++;

      // If this is the first pulse of a measurement
      if (vel_first_pulse_id == 0) {
        // Save pulse time and id
        vel_first_pulse_id = vel_total_pulse_count;
        vel_first_pulse_time = millis();
      }

      // Save pulse time
      vel_last_pulse_time = millis();
    }
  }
}

void vel_begin() {
  attachInterrupt(4, vel_pulse, CHANGE);
}

int vel_bike() {

  // if the first pulse id hasn't been set return 0
  if (vel_first_pulse_id == 0) return 0;

  // pulses since last measurement
  int meas_pulses = vel_total_pulse_count-vel_first_pulse_id;

  // time since last measurement
  int meas_time = vel_last_pulse_time-vel_first_pulse_time;

  // reset first pulse id so it will be set on the next pulse
  vel_first_pulse_id = 0;

  // return 0 if not enough pulses are counted
  if (meas_pulses < 2) return 0;

  // calculate velocity
  int vel = roundf(meas_pulses*1e3/meas_time*VELOCITY_C); // mm / s

  // if float rounding determines velocity to be < 0, return 0
  if (vel < 0) return 0;

  // return velocity
  return vel;

}

int32_t vel_bike_odo() {
  return roundf(vel_total_pulse_count*VELOCITY_C); // mm
}

void vel_bike_odo_reset() {
  vel_total_pulse_count = 0;
}

