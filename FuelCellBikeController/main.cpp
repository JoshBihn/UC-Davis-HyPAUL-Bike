// Standard C libs
#include <math.h>

// Arduino stuff
#include <WProgram.h>
#include "arduino_error_handling.h"

// External libraries
#include "libraries/LiquidCrystal/LiquidCrystal.h"
#include "libraries/OneWire/OneWire.h"
#include "libraries/DallasTemperature/DallasTemperature.h"
#include "libraries/TimerOne/TimerOne.h"
#include "libraries/SdFat/SdFat.h"
#include "libraries/SdFat/SdFatUtil.h"
#include "libraries/BufferedWriter/BufferedWriter.h"

// Arduino pinout
#include "constants_pinout.h"

// Config
#include "constants_config.h"

// Global lcd object
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7); //go fix the lcd lib first
//LiquidCrystal = new lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// Hardware abstraction
#include "hardware/button_input.h"
#include "hardware/pot_input.h"
#include "hardware/kickstand_input.h"
#include "hardware/led_output.h"
#include "hardware/solenoid_control.h"
#include "hardware/fan_control.h"
#include "hardware/current_control.h"
#include "hardware/voltage_sensing.h"
#include "hardware/current_sensing.h"
#include "hardware/pressure_sensing.h"
#include "hardware/temperature_sensing.h"
#include "hardware/sd_storage.h"

// Basic functionality
#include "basic/menu.h"
#include "basic/data_acquisition.h"
#include "basic/hydrogen_mass.h"
//#include "basic/current_controller.h"
#include "basic/fc_power_controller.h"
#include "basic/fc_state.h"
#include "basic/soc.h"
#include "basic/ems_ecms.h"

#include "hardware/velocity_sensing.h"


// General setup function
#include "setup.h"

// Timer interrupt function
#include "timer_interrupt.h"

// Loop function, include "main_loop.h" or any test like "tests/fans.h" here to run it
#include "main_loop.h"
//#include "tests/velocity_pulses.h"
//#include "tests/current_fc_mot.h"

// Let's roll!
int main(void) {

  // arduino init
  init();

  // setup function
  setup();

  // tests can do additional setup
  #ifdef ADDITIONAL_SETUP_PRESENT
    additional_setup();
  #endif

  // loop forever
  for (;;)
    loop();

  return 0;
}
