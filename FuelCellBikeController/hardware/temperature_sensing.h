//Temperature Sensors in battery
OneWire t_bat_onewire(T_BAT);
DallasTemperature dt_bat(&t_bat_onewire);

//Temperature sensor in motor
OneWire t_motor_onewire(T_MOTOR);
DallasTemperature dt_motor(&t_motor_onewire);

//Temperature sensor on tank
OneWire t_tank_onewire(T_TANK);
DallasTemperature dt_tank(&t_tank_onewire);

DeviceAddress at_motor;
DeviceAddress at_tank;
DeviceAddress at_battery;

void t_battery_request() {
  dt_bat.requestTemperatures();
}

void t_motor_request() {
  dt_motor.requestTemperatures();
}

void t_tank_request() {
  dt_tank.requestTemperatures();
}

float t_battery() {
  return dt_bat.getTempC(at_battery);
}

float t_motor() {
  return dt_motor.getTempC(at_motor);
}

float t_tank() {
  return dt_tank.getTempC(at_tank);
}

void t_setup() {
  dt_bat.begin();
  dt_bat.setWaitForConversion(false);
  dt_bat.getAddress(at_battery, 0);
  dt_motor.begin();
  dt_motor.setWaitForConversion(false);
  dt_motor.getAddress(at_motor, 0);
  dt_tank.begin();
  dt_tank.setWaitForConversion(false);
  dt_tank.getAddress(at_tank, 0);
}
