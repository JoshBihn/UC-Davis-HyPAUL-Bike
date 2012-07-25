// Loop iteration time
#define ITER_INTERVAL    100        // [ms]

// Daq config
#define DAQ_CSV_SEPARATOR ";"

// LCD config
#define LCD_COLS          16
#define LCD_ROWS           2

// Button config
#define BUTTON_DEAD_TIME 300        // [ms]

#define BUTTON_NEXT        1
#define BUTTON_PREVIOUS    2
#define BUTTON_ACTION      3
#define BUTTON_UNUSED_1    4
#define BUTTON_UNUSED_2    5

// Menu config
#define MENU_REFR_TIME   500        // [ms]
#define MENU_PAGE_COUNT   10
#define PAGE_DAQ           1
#define PAGE_SOC           2
#define PAGE_EM            3
#define PAGE_VELOCITY      4
#define PAGE_FC            5
#define PAGE_BATTERY       6
#define PAGE_MOTOR         7
#define PAGE_TEMP          8
#define PAGE_HYDROGEN      9
#define PAGE_STATS        10

// Fan control config
#define FAN_BAT_T_THRES   30        //  [deg C]
#define FAN_MOT_T_THRES   30        //  [deg C]

// voltage sensor calibration
#define V_BAT_C           87.59     // [mV/step]
#define V_FC_C            88.55     // [mV/step]
#define V_BAT_ZERO       142
#define V_FC_ZERO        179

// current sensor calibration
// C [amps / step] = 5 [volts] / 1023 [steps] * Ir [rated milliAmps] / 0.625 [volts / Ir amps] / amplifier_gain
#define I_FC_C            57 //55.86     // 5/1023*50e3/0.625/7.0 [mA/step]
#define I_BAT_LOW_C      392        // 5/1023*50e3/0.625/1   [mA/step]
#define I_BAT_HIGH_C    1564        // 5/1023*200e3/0.625/1  [mA/step]
#define I_MOTOR_C       1564        // 5/1023*200e3/0.625/1  [mA/step]

#define I_FC_ZERO          7  // -6
#define I_BAT_LOW_ZERO   509
#define I_BAT_HIGH_ZERO  508
#define I_MOTOR_ZERO     506

#define I_BAT_CROSSOVER  150e3

// Pressure sensor calibration
#define P_TANK_C          20.8067   // 6.894*617.5*5/1023 [kPa]

// Hydrogen mass estimation
#define M_HYDROGEN_C       2.885     // V_tanks [m^3] * M_h2 [g/mol] / R [J/mol K] * 10^3 [Pa/kPa] = 5.95e-3*2 * 2.016 / 8.3145 * 1e3 = 2.885

// General SOC config
#define SOC_CAPACITY       15e3     // [mAh] original ten pack capacity   25e3

// SOC by OCV estimation
// Fitted data measured at a 2A load to account for the 12v system still drawing power
// SOC_OCV = SOC_OCV_C0 + SOC_OCV_C1*(v_bat-SOC_V_OFFSET)^1 + ... + SOC_OCV_Cn*(v_bat-SOC_V_OFFSET)^n
#define SOC_OCV_V_MIN      4.322e4  // [mV]
#define SOC_OCV_V_MAX      5.019e4  // [mV]
#define SOC_OCV_V_OFFSET   4.605e4  // [mV]
#define SOC_OCV_V_SCALE    1.767e3
#define SOC_OCV_C5         4.546e4
#define SOC_OCV_C4        -1.396e5
#define SOC_OCV_C3        -7.084e4
#define SOC_OCV_C2         5.947e5
#define SOC_OCV_C1        -1.356e6
#define SOC_OCV_C0         1.821e6

// SOC by coulomb counting
#define SOC_CC_INTERVAL    1e4      // [us]
#define SOC_CC_CHARGE_EFF  1.00     // Impossible, but follows from calibration. Could result from a problem with the current sensor.
#define SOC_CC_DISCHA_EFF  1.00     //0.85
#define SOC_CC_I_TO_CAP_C  1/360    // 1/360 [uAh/mA] = 1e3 [uA/mA] * 1/3600 [h/s] * 1e-6 [s/us] * 1e4 [us]

/* // Current controller
#define I_CONTROLLER_C     5.1e-3   // [steps/mA]
#define I_CONTROLLER_FB_ON true     // feedback on?
#define I_CONTROLLER_FB_C  2.0e-3   // [steps/mA] */

// FC power controller
#define P_CONTROLLER_FB_C  0.3      // [steps/W]

// Velocity
#define VELOCITY_C       220        // 1760 [mm wheel circumference] / 8 [pulses] = 220 [mm/pulse]

// Fuel cell state config
#define FC_STATE_VOLTAGE_THRESHOLD 10e3

// EM states
#define EM_ECMS_ON        -1

// ECMS
#define ECMS_BC_EFF        1.00      // boost converter efficiency
#define ECMS_BAT_D_EFF     0.95      // battery discharge efficiency
#define ECMS_BAT_C_EFF     0.90      // battery charge efficiency
#define ECMS_FC_SC         2.0225e-2 // fuel cell estimated average specific fuel consumption [g/J]
#define ECMS_BAT_SC        (ECMS_FC_SC/(ECMS_BAT_C_EFF*ECMS_BC_EFF)) // battery average specific fuel consumption [g/J]

#define ECMS_OPTION_COUNT 15

#define ECMS_0_FC_POWER   200
#define ECMS_0_FC_COST      3.868

#define ECMS_1_FC_POWER   300
#define ECMS_1_FC_COST      5.780

#define ECMS_2_FC_POWER   400
#define ECMS_2_FC_COST      7.678

#define ECMS_3_FC_POWER   500
#define ECMS_3_FC_COST      9.631

#define ECMS_4_FC_POWER   600
#define ECMS_4_FC_COST     11.668

#define ECMS_5_FC_POWER   700
#define ECMS_5_FC_COST     13.774

#define ECMS_6_FC_POWER   800
#define ECMS_6_FC_COST     15.910

#define ECMS_7_FC_POWER   900
#define ECMS_7_FC_COST     18.045

#define ECMS_8_FC_POWER 1000
#define ECMS_8_FC_COST    20.179

#define ECMS_9_FC_POWER 1100
#define ECMS_9_FC_COST    22.350

#define ECMS_10_FC_POWER 1200
#define ECMS_10_FC_COST    24.621

#define ECMS_11_FC_POWER 1300
#define ECMS_11_FC_COST    27.048

#define ECMS_12_FC_POWER 1400
#define ECMS_12_FC_COST    29.652

#define ECMS_13_FC_POWER 1500
#define ECMS_13_FC_COST    32.465

#define ECMS_14_FC_POWER 1600
#define ECMS_14_FC_COST    35.272

// Penalty function
#define ECMS_PENALTY_COUNT  6

#define ECMS_P0_SOC         0
#define ECMS_P0_VAL         2

#define ECMS_P1_SOC        40
#define ECMS_P1_VAL         2

#define ECMS_P2_SOC        50
#define ECMS_P2_VAL         1

#define ECMS_P3_SOC        70
#define ECMS_P3_VAL         1

#define ECMS_P4_SOC        80
#define ECMS_P4_VAL         0

#define ECMS_P5_SOC       100
#define ECMS_P5_VAL         0


