################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../calendar.cpp \
../calendarUtil.cpp \
../compositeCalendar.cpp \
../simpleCalendar.cpp 

OBJS += \
./calendar.o \
./calendarUtil.o \
./compositeCalendar.o \
./simpleCalendar.o 

CPP_DEPS += \
./calendar.d \
./calendarUtil.d \
./compositeCalendar.d \
./simpleCalendar.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/vishist/IRDConnect/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


