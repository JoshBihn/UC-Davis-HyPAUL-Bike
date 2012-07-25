/* this file was commented out of the include list in main.cpp
 * the function i_controller_input is therefore commented out below to resolve compiler errors
 * stemming from the associated constants being commented out in the config.h file
 *
 * */

//#include <math.h>
int32_t i_controller_setpoint_value, i_controller_state_id = 0;
int i_controller_output_value;
/*
void i_controller_input(int32_t i_controller_input_value) {

  if (I_CONTROLLER_FB_ON) {
    // calculate new output value using feedback
    i_controller_state_id = 0;
    i_controller_output_value += roundf((i_controller_setpoint_value-i_controller_input_value)*I_CONTROLLER_FB_C);
  } else {
    // calculate new output value without feedback
    i_controller_state_id = 0;
    i_controller_output_value = roundf(i_controller_setpoint_value*I_CONTROLLER_C);
  }

  // lower limit control value
  if (i_controller_output_value < 0) {
    i_controller_state_id = 1;
    i_controller_output_value = 0;
  }

  // upper limit control value
  if (i_controller_output_value > 255) {
    i_controller_state_id = 2;
    i_controller_output_value = 255;
  }

}
*/

int32_t i_controller_setpoint(int32_t setpoint = -1) {
  if (setpoint > -1 && setpoint <= 5e4) {
    i_controller_setpoint_value = setpoint;
  }
  return i_controller_setpoint_value;
}

int i_controller_state() {
  return i_controller_state_id;
}

int i_controller_output() {
  return i_controller_output_value;
}
