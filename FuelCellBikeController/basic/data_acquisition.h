unsigned int daq_measurement_id_val = 0; // changed to int not long
int daq_state = 0;

void daq_schedule_start() {
  daq_state = 1;
}

bool daq_start_scheduled() {
  return (daq_state == 1);
}

void daq_start_now() {
  daq_state = 2;
}

bool daq_started() {
  return (daq_state > 1);
}

bool daq_on() {
  return (daq_state > 0);
}

void daq_schedule_stop() {
  daq_state = 3;
}

bool daq_stop_scheduled() {
  return (daq_state == 3);
}

void daq_stop_now() {
  daq_state = 0;
  daq_measurement_id_val = 0;
}

unsigned int daq_measurement_id() { // changed to long
  return daq_measurement_id_val;
}

void daq_measurement_increment() {
  daq_measurement_id_val++;
}
