################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/UART_Terminal/Console_Func.c \
../Drivers/UART_Terminal/UART_Terminal.c 

OBJS += \
./Drivers/UART_Terminal/Console_Func.o \
./Drivers/UART_Terminal/UART_Terminal.o 

C_DEPS += \
./Drivers/UART_Terminal/Console_Func.d \
./Drivers/UART_Terminal/UART_Terminal.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/UART_Terminal/%.o Drivers/UART_Terminal/%.su Drivers/UART_Terminal/%.cyclo: ../Drivers/UART_Terminal/%.c Drivers/UART_Terminal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/console" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/UART_Terminal" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/BrushedDC" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/SX12xxDrivers-V2.1.0/src/radio" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/SX12xxDrivers-V2.1.0/src/RxTx" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/ChaeburatorIT_Proc" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Core/Inc" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/STM32F1xx_HAL_Driver/Inc" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/STM32F1xx_HAL_Driver/Src" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/UART_Output" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/Servo" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/ADC_LoadCell" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-UART_Terminal

clean-Drivers-2f-UART_Terminal:
	-$(RM) ./Drivers/UART_Terminal/Console_Func.cyclo ./Drivers/UART_Terminal/Console_Func.d ./Drivers/UART_Terminal/Console_Func.o ./Drivers/UART_Terminal/Console_Func.su ./Drivers/UART_Terminal/UART_Terminal.cyclo ./Drivers/UART_Terminal/UART_Terminal.d ./Drivers/UART_Terminal/UART_Terminal.o ./Drivers/UART_Terminal/UART_Terminal.su

.PHONY: clean-Drivers-2f-UART_Terminal

