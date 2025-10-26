################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SX12xxDrivers-V2.1.0/src/radio/radio.c \
../Drivers/SX12xxDrivers-V2.1.0/src/radio/spi.c \
../Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-Hal.c \
../Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-LoRaMisk.c \
../Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-Lora.c \
../Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276.c 

O_SRCS += \
../Drivers/SX12xxDrivers-V2.1.0/src/radio/radio.o \
../Drivers/SX12xxDrivers-V2.1.0/src/radio/spi.o \
../Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-Hal.o \
../Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-LoRaMisk.o \
../Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-LoRaProces.o \
../Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-Lora.o \
../Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276.o 

OBJS += \
./Drivers/SX12xxDrivers-V2.1.0/src/radio/radio.o \
./Drivers/SX12xxDrivers-V2.1.0/src/radio/spi.o \
./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-Hal.o \
./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-LoRaMisk.o \
./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-Lora.o \
./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276.o 

C_DEPS += \
./Drivers/SX12xxDrivers-V2.1.0/src/radio/radio.d \
./Drivers/SX12xxDrivers-V2.1.0/src/radio/spi.d \
./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-Hal.d \
./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-LoRaMisk.d \
./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-Lora.d \
./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SX12xxDrivers-V2.1.0/src/radio/%.o Drivers/SX12xxDrivers-V2.1.0/src/radio/%.su Drivers/SX12xxDrivers-V2.1.0/src/radio/%.cyclo: ../Drivers/SX12xxDrivers-V2.1.0/src/radio/%.c Drivers/SX12xxDrivers-V2.1.0/src/radio/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/console" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/UART_Terminal" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/BrushedDC" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/SX12xxDrivers-V2.1.0/src/radio" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/SX12xxDrivers-V2.1.0/src/RxTx" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/ChaeburatorIT_Proc" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Core/Inc" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/STM32F1xx_HAL_Driver/Inc" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/STM32F1xx_HAL_Driver/Src" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/UART_Output" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-SX12xxDrivers-2d-V2-2e-1-2e-0-2f-src-2f-radio

clean-Drivers-2f-SX12xxDrivers-2d-V2-2e-1-2e-0-2f-src-2f-radio:
	-$(RM) ./Drivers/SX12xxDrivers-V2.1.0/src/radio/radio.cyclo ./Drivers/SX12xxDrivers-V2.1.0/src/radio/radio.d ./Drivers/SX12xxDrivers-V2.1.0/src/radio/radio.o ./Drivers/SX12xxDrivers-V2.1.0/src/radio/radio.su ./Drivers/SX12xxDrivers-V2.1.0/src/radio/spi.cyclo ./Drivers/SX12xxDrivers-V2.1.0/src/radio/spi.d ./Drivers/SX12xxDrivers-V2.1.0/src/radio/spi.o ./Drivers/SX12xxDrivers-V2.1.0/src/radio/spi.su ./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-Hal.cyclo ./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-Hal.d ./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-Hal.o ./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-Hal.su ./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-LoRaMisk.cyclo ./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-LoRaMisk.d ./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-LoRaMisk.o ./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-LoRaMisk.su ./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-Lora.cyclo ./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-Lora.d ./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-Lora.o ./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276-Lora.su ./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276.cyclo ./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276.d ./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276.o ./Drivers/SX12xxDrivers-V2.1.0/src/radio/sx1276.su

.PHONY: clean-Drivers-2f-SX12xxDrivers-2d-V2-2e-1-2e-0-2f-src-2f-radio

