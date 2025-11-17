################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LoRa_MenuV2/LoRaMenuV2.c 

OBJS += \
./LoRa_MenuV2/LoRaMenuV2.o 

C_DEPS += \
./LoRa_MenuV2/LoRaMenuV2.d 


# Each subdirectory must supply rules for building sources it contributes
LoRa_MenuV2/%.o LoRa_MenuV2/%.su LoRa_MenuV2/%.cyclo: ../LoRa_MenuV2/%.c LoRa_MenuV2/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/East23/Project/CubeIDE/Palenish_RC/ADC_Stick" -I"D:/East23/Project/CubeIDE/Palenish_RC/display" -I"D:/East23/Project/CubeIDE/Palenish_RC/display/Inc" -I"D:/East23/Project/CubeIDE/Palenish_RC/display/Src" -I"D:/East23/Project/CubeIDE/Palenish_RC/display/fonts" -I"D:/East23/Project/CubeIDE/Palenish_RC/IT_Process_0.2.1" -I"D:/East23/Project/CubeIDE/Palenish_RC/KeyPad" -I"D:/East23/Project/CubeIDE/Palenish_RC/SX12xxDrivers-V2.1.0/src/radio" -I"D:/East23/Project/CubeIDE/Palenish_RC/SX12xxDrivers-V2.1.0/src/RxTx" -I"D:/East23/Project/CubeIDE/Palenish_RC/LoRa_MenuV2" -I"D:/East23/Project/CubeIDE/Palenish_RC/ProgMem" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-LoRa_MenuV2

clean-LoRa_MenuV2:
	-$(RM) ./LoRa_MenuV2/LoRaMenuV2.cyclo ./LoRa_MenuV2/LoRaMenuV2.d ./LoRa_MenuV2/LoRaMenuV2.o ./LoRa_MenuV2/LoRaMenuV2.su

.PHONY: clean-LoRa_MenuV2

