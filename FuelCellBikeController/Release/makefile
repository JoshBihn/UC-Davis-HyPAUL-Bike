################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include libraries/TimerOne/subdir.mk
-include libraries/SdFat/subdir.mk
-include libraries/OneWire/subdir.mk
-include libraries/LiquidCrystal/subdir.mk
-include libraries/DallasTemperature/subdir.mk
-include libraries/BufferedWriter/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
FLASH_IMAGE += \
FuelCellBikeController.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: FuelCellBikeController.elf secondary-outputs

# Tool invocations
FuelCellBikeController.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-g++ -s -Os -Wl,--gc-sections -o"FuelCellBikeController.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lm -Wl,-Map,FuelCellBikeController.map,--cref -L../../ArduinoCore/Release/ -mmcu=atmega2560
	@echo 'Finished building target: $@'
	@echo ' '

FuelCellBikeController.hex: FuelCellBikeController.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex FuelCellBikeController.elf  "FuelCellBikeController.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: FuelCellBikeController.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega2560 FuelCellBikeController.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: FuelCellBikeController.elf
	@echo 'Invoking: AVRDude'
	C:\WinAVR-20100110\bin\avrdude -pm2560 -cwiring -PCOM5 -b115200 -Uflash:w:FuelCellBikeController.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ELFS)$(FLASH_IMAGE)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(AVRDUDEDUMMY)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) FuelCellBikeController.elf
	-@echo ' '

secondary-outputs: $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
