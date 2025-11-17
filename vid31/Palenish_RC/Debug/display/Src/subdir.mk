################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../display/Src/disp1color.c \
../display/Src/f10x16f.c \
../display/Src/f6x8m.c \
../display/Src/font.c \
../display/Src/ssd1306.c 

OBJS += \
./display/Src/disp1color.o \
./display/Src/f10x16f.o \
./display/Src/f6x8m.o \
./display/Src/font.o \
./display/Src/ssd1306.o 

C_DEPS += \
./display/Src/disp1color.d \
./display/Src/f10x16f.d \
./display/Src/f6x8m.d \
./display/Src/font.d \
./display/Src/ssd1306.d 


# Each subdirectory must supply rules for building sources it contributes
display/Src/%.o display/Src/%.su display/Src/%.cyclo: ../display/Src/%.c display/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/East23/Project/CubeIDE/Palenish_RC/ADC_Stick" -I"D:/East23/Project/CubeIDE/Palenish_RC/display" -I"D:/East23/Project/CubeIDE/Palenish_RC/display/Inc" -I"D:/East23/Project/CubeIDE/Palenish_RC/display/Src" -I"D:/East23/Project/CubeIDE/Palenish_RC/display/fonts" -I"D:/East23/Project/CubeIDE/Palenish_RC/IT_Process_0.2.1" -I"D:/East23/Project/CubeIDE/Palenish_RC/KeyPad" -I"D:/East23/Project/CubeIDE/Palenish_RC/SX12xxDrivers-V2.1.0/src/radio" -I"D:/East23/Project/CubeIDE/Palenish_RC/SX12xxDrivers-V2.1.0/src/RxTx" -I"D:/East23/Project/CubeIDE/Palenish_RC/LoRa_MenuV2" -I"D:/East23/Project/CubeIDE/Palenish_RC/ProgMem" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-display-2f-Src

clean-display-2f-Src:
	-$(RM) ./display/Src/disp1color.cyclo ./display/Src/disp1color.d ./display/Src/disp1color.o ./display/Src/disp1color.su ./display/Src/f10x16f.cyclo ./display/Src/f10x16f.d ./display/Src/f10x16f.o ./display/Src/f10x16f.su ./display/Src/f6x8m.cyclo ./display/Src/f6x8m.d ./display/Src/f6x8m.o ./display/Src/f6x8m.su ./display/Src/font.cyclo ./display/Src/font.d ./display/Src/font.o ./display/Src/font.su ./display/Src/ssd1306.cyclo ./display/Src/ssd1306.d ./display/Src/ssd1306.o ./display/Src/ssd1306.su

.PHONY: clean-display-2f-Src

