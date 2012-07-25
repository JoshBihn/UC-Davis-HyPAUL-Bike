################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../libraries/DallasTemperature/DallasTemperature.cpp 

OBJS += \
./libraries/DallasTemperature/DallasTemperature.o 

CPP_DEPS += \
./libraries/DallasTemperature/DallasTemperature.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/DallasTemperature/%.o: ../libraries/DallasTemperature/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"C:\SPB_Data\git\Fuel-Cell-Bike-Controller-new\ArduinoCore" -I"C:\SPB_Data\git\Fuel-Cell-Bike-Controller-new\FuelCellBikeController\libraries\SdFat" -I"C:\SPB_Data\git\Fuel-Cell-Bike-Controller-new\FuelCellBikeController\libraries\BufferedWriter" -w -Os -ffunction-sections -fdata-sections -fno-exceptions -DARDUINO=22 -g -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


