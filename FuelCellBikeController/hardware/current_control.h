void i_control_output(int value) {
  analogWrite(I_CONTROL, value);
}

void i_control_setup() {

  // set pwm mode: only first output, no prescale, 8 bit fast pwm (see datasheet pages 159, 148 and 133)
  TCCR3A = 0b10000001; // com3a1 com3a0 com3b1 com3b0 com3c1 com3c0 wgm31 wgm30
  TCCR3B = 0b00001001; // icnc3  ices3  -      wgm33  wgm32  cs32   cs31  cs30

  // set output low
  i_control_output(0);

}

