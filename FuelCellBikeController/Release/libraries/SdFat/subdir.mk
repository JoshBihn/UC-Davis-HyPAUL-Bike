################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../libraries/SdFat/Sd2Card.cpp \
../libraries/SdFat/SdBaseFile.cpp \
../libraries/SdFat/SdFat.cpp \
../libraries/SdFat/SdFatUtil.cpp \
../libraries/SdFat/SdFile.cpp \
../libraries/SdFat/SdStream.cpp \
../libraries/SdFat/SdVolume.cpp \
../libraries/SdFat/istream.cpp \
../libraries/SdFat/ostream.cpp 

OBJS += \
./libraries/SdFat/Sd2Card.o \
./libraries/SdFat/SdBaseFile.o \
./libraries/SdFat/SdFat.o \
./libraries/SdFat/SdFatUtil.o \
./libraries/SdFat/SdFile.o \
./libraries/SdFat/SdStream.o \
./libraries/SdFat/SdVolume.o \
./libraries/SdFat/istream.o \
./libraries/SdFat/ostream.o 

CPP_DEPS += \
./libraries/SdFat/Sd2Card.d \
./libraries/SdFat/SdBaseFile.d \
./libraries/SdFat/SdFat.d \
./libraries/SdFat/SdFatUtil.d \
./libraries/SdFat/SdFile.d \
./libraries/SdFat/SdStream.d \
./libraries/SdFat/SdVolume.d \
./libraries/SdFat/istream.d \
./libraries/SdFat/ostream.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/SdFat/%.o: ../libraries/SdFat/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"C:\SPB_Data\git\Fuel-Cell-Bike-Controller-new\ArduinoCore" -I"C:\SPB_Data\git\Fuel-Cell-Bike-Controller-new\FuelCellBikeController\libraries\SdFat" -I"C:\SPB_Data\git\Fuel-Cell-Bike-Controller-new\FuelCellBikeController\libraries\BufferedWriter" -w -Os -ffunction-sections -fdata-sections -fno-exceptions -DARDUINO=22 -g -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


