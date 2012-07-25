bool fc_state_on = false;
uint32_t fc_state_dead_time;

void fc_determine_state(int32_t v_fc) {

  bool fc_inst_state = (v_fc > FC_STATE_VOLTAGE_THRESHOLD);

  if (fc_state_on != fc_inst_state) {
    if (fc_state_dead_time == 0) {
      fc_state_dead_time = millis()+1e3;
    } else if (millis() > fc_state_dead_time) {
      fc_state_dead_time = 0;
      fc_state_on = fc_inst_state;
    }
  }

  if (fc_state_on == fc_inst_state) {
    fc_state_dead_time = 0;
  }

}

bool fc_on() {
  return fc_state_on;
}
