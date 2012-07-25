void setup () {

  // set output pins, the rest default to inputs
  pinMode(FAN_MOTOR,   OUTPUT);
  pinMode(FAN_BAT,     OUTPUT);
  pinMode(SOL_CONTACT, OUTPUT);
  pinMode(SOL_MOTOR,   OUTPUT);
  pinMode(SOL_FC,      OUTPUT);
  pinMode(I_CONTROL,   OUTPUT);
  pinMode(LED_WARNING, OUTPUT);

  // set pullup resistors
  digitalWrite(BUTTON_1, HIGH);
  digitalWrite(BUTTON_2, HIGH);
  digitalWrite(BUTTON_3, HIGH);
  digitalWrite(BUTTON_4, HIGH);
  digitalWrite(BUTTON_5, HIGH);
  digitalWrite(SW_KICKSTAND, HIGH);
  digitalWrite(VEL_BIKE,  HIGH);

  // Turn contactor on      // why now?
  solenoid_contactor_on();
  delay(100);               // can this be done after t_setup()?

  // setup lcd
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.print("UCD Hybrid Bike ");

  // Setup temp sensors
  t_setup();

  // Setup current control output
  i_control_setup();

  // Turn fuel cell controller on
  lcd.setCursor(0,1);
  lcd.print("FC ctrl on..    ");
  solenoid_fc_toggle_wait();

  // Estimate initial SOC, takes a while
  soc_estimation_ritual();

  // start velocity measurement
  vel_begin();

}
