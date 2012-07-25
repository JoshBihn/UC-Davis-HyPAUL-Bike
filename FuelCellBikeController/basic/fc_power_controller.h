int32_t p_controller_setpoint_value, p_controller_state_id = 0;
int p_controller_output_value;

void p_controller_input(int32_t p_controller_input_value) {

  // calculate new output value using feedback
  p_controller_state_id = 0;
  p_controller_output_value += roundf((p_controller_setpoint_value-p_controller_input_value)*P_CONTROLLER_FB_C);

  // lower limit control value
  if (p_controller_output_value < 0) {
    p_controller_state_id = 1;
    p_controller_output_value = 0;
  }

  // upper limit control value
  if (p_controller_output_value > 255) {
    p_controller_state_id = 2;
    p_controller_output_value = 255;
  }

}

int32_t p_controller_setpoint(int32_t setpoint = -1) {
  if (setpoint > -1) {
    p_controller_setpoint_value = setpoint;
  }
  return p_controller_setpoint_value;
}

int p_controller_state() {
  return p_controller_state_id;
}

int p_controller_output() {
  return p_controller_output_value;
}
