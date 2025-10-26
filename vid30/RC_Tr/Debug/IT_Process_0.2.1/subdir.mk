################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../IT_Process_0.2.1/PalenishIT_Proc.c 

OBJS += \
./IT_Process_0.2.1/PalenishIT_Proc.o 

C_DEPS += \
./IT_Process_0.2.1/PalenishIT_Proc.d 


# Each subdirectory must supply rules for building sources it contributes
IT_Process_0.2.1/%.o IT_Process_0.2.1/%.su IT_Process_0.2.1/%.cyclo: ../IT_Process_0.2.1/%.c IT_Process_0.2.1/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/East23/Project/CubeIDE/Palenish_RC/ADC_Stick" -I"D:/East23/Project/CubeIDE/Palenish_RC/display" -I"D:/East23/Project/CubeIDE/Palenish_RC/display/Inc" -I"D:/East23/Project/CubeIDE/Palenish_RC/display/Src" -I"D:/East23/Project/CubeIDE/Palenish_RC/display/fonts" -I"D:/East23/Project/CubeIDE/Palenish_RC/IT_Process_0.2.1" -I"D:/East23/Project/CubeIDE/Palenish_RC/KeyPad" -I"D:/East23/Project/CubeIDE/Palenish_RC/SX12xxDrivers-V2.1.0/src/radio" -I"D:/East23/Project/CubeIDE/Palenish_RC/SX12xxDrivers-V2.1.0/src/RxTx" -I"D:/East23/Project/CubeIDE/Palenish_RC/LoRa_MenuV2" -I"D:/East23/Project/CubeIDE/Palenish_RC/ProgMem" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-IT_Process_0-2e-2-2e-1

clean-IT_Process_0-2e-2-2e-1:
	-$(RM) ./IT_Process_0.2.1/PalenishIT_Proc.cyclo ./IT_Process_0.2.1/PalenishIT_Proc.d ./IT_Process_0.2.1/PalenishIT_Proc.o ./IT_Process_0.2.1/PalenishIT_Proc.su

.PHONY: clean-IT_Process_0-2e-2-2e-1

