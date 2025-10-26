################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SX12xxDrivers-V2.1.0/src/radio/radio.c \
../SX12xxDrivers-V2.1.0/src/radio/spi.c \
../SX12xxDrivers-V2.1.0/src/radio/sx1276-Hal.c \
../SX12xxDrivers-V2.1.0/src/radio/sx1276-LoRaMisk.c \
../SX12xxDrivers-V2.1.0/src/radio/sx1276-Lora.c \
../SX12xxDrivers-V2.1.0/src/radio/sx1276.c 

O_SRCS += \
../SX12xxDrivers-V2.1.0/src/radio/radio.o \
../SX12xxDrivers-V2.1.0/src/radio/spi.o \
../SX12xxDrivers-V2.1.0/src/radio/sx1276-Hal.o \
../SX12xxDrivers-V2.1.0/src/radio/sx1276-LoRaMisk.o \
../SX12xxDrivers-V2.1.0/src/radio/sx1276-LoRaProces.o \
../SX12xxDrivers-V2.1.0/src/radio/sx1276-Lora.o \
../SX12xxDrivers-V2.1.0/src/radio/sx1276.o 

OBJS += \
./SX12xxDrivers-V2.1.0/src/radio/radio.o \
./SX12xxDrivers-V2.1.0/src/radio/spi.o \
./SX12xxDrivers-V2.1.0/src/radio/sx1276-Hal.o \
./SX12xxDrivers-V2.1.0/src/radio/sx1276-LoRaMisk.o \
./SX12xxDrivers-V2.1.0/src/radio/sx1276-Lora.o \
./SX12xxDrivers-V2.1.0/src/radio/sx1276.o 

C_DEPS += \
./SX12xxDrivers-V2.1.0/src/radio/radio.d \
./SX12xxDrivers-V2.1.0/src/radio/spi.d \
./SX12xxDrivers-V2.1.0/src/radio/sx1276-Hal.d \
./SX12xxDrivers-V2.1.0/src/radio/sx1276-LoRaMisk.d \
./SX12xxDrivers-V2.1.0/src/radio/sx1276-Lora.d \
./SX12xxDrivers-V2.1.0/src/radio/sx1276.d 


# Each subdirectory must supply rules for building sources it contributes
SX12xxDrivers-V2.1.0/src/radio/%.o SX12xxDrivers-V2.1.0/src/radio/%.su SX12xxDrivers-V2.1.0/src/radio/%.cyclo: ../SX12xxDrivers-V2.1.0/src/radio/%.c SX12xxDrivers-V2.1.0/src/radio/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/East23/Project/CubeIDE/Palenish_RC/ADC_Stick" -I"D:/East23/Project/CubeIDE/Palenish_RC/display" -I"D:/East23/Project/CubeIDE/Palenish_RC/display/Inc" -I"D:/East23/Project/CubeIDE/Palenish_RC/display/Src" -I"D:/East23/Project/CubeIDE/Palenish_RC/display/fonts" -I"D:/East23/Project/CubeIDE/Palenish_RC/IT_Process_0.2.1" -I"D:/East23/Project/CubeIDE/Palenish_RC/KeyPad" -I"D:/East23/Project/CubeIDE/Palenish_RC/SX12xxDrivers-V2.1.0/src/radio" -I"D:/East23/Project/CubeIDE/Palenish_RC/SX12xxDrivers-V2.1.0/src/RxTx" -I"D:/East23/Project/CubeIDE/Palenish_RC/LoRa_MenuV2" -I"D:/East23/Project/CubeIDE/Palenish_RC/ProgMem" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-SX12xxDrivers-2d-V2-2e-1-2e-0-2f-src-2f-radio

clean-SX12xxDrivers-2d-V2-2e-1-2e-0-2f-src-2f-radio:
	-$(RM) ./SX12xxDrivers-V2.1.0/src/radio/radio.cyclo ./SX12xxDrivers-V2.1.0/src/radio/radio.d ./SX12xxDrivers-V2.1.0/src/radio/radio.o ./SX12xxDrivers-V2.1.0/src/radio/radio.su ./SX12xxDrivers-V2.1.0/src/radio/spi.cyclo ./SX12xxDrivers-V2.1.0/src/radio/spi.d ./SX12xxDrivers-V2.1.0/src/radio/spi.o ./SX12xxDrivers-V2.1.0/src/radio/spi.su ./SX12xxDrivers-V2.1.0/src/radio/sx1276-Hal.cyclo ./SX12xxDrivers-V2.1.0/src/radio/sx1276-Hal.d ./SX12xxDrivers-V2.1.0/src/radio/sx1276-Hal.o ./SX12xxDrivers-V2.1.0/src/radio/sx1276-Hal.su ./SX12xxDrivers-V2.1.0/src/radio/sx1276-LoRaMisk.cyclo ./SX12xxDrivers-V2.1.0/src/radio/sx1276-LoRaMisk.d ./SX12xxDrivers-V2.1.0/src/radio/sx1276-LoRaMisk.o ./SX12xxDrivers-V2.1.0/src/radio/sx1276-LoRaMisk.su ./SX12xxDrivers-V2.1.0/src/radio/sx1276-Lora.cyclo ./SX12xxDrivers-V2.1.0/src/radio/sx1276-Lora.d ./SX12xxDrivers-V2.1.0/src/radio/sx1276-Lora.o ./SX12xxDrivers-V2.1.0/src/radio/sx1276-Lora.su ./SX12xxDrivers-V2.1.0/src/radio/sx1276.cyclo ./SX12xxDrivers-V2.1.0/src/radio/sx1276.d ./SX12xxDrivers-V2.1.0/src/radio/sx1276.o ./SX12xxDrivers-V2.1.0/src/radio/sx1276.su

.PHONY: clean-SX12xxDrivers-2d-V2-2e-1-2e-0-2f-src-2f-radio

