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
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"D:/East23/Project/CubeIDE/ChaeburatorTest/Drivers/Servo" -I"D:/East23/Project/CubeIDE/ChaeburatorTest/Drivers/BrushedDC" -I"D:/East23/Project/CubeIDE/ChaeburatorTest/SX12xxDrivers-V2.1.0/src/radio" -I"D:/East23/Project/CubeIDE/Palenish_RC/SX12xxDrivers-V2.1.0/src" -I"D:/East23/Project/CubeIDE/ChaeburatorTest/SX12xxDrivers-V2.1.0/src/RxTx" -I"D:/East23/Project/CubeIDE/ChaeburatorTest/ChaeburatorIT_Proc" -I"D:/East23/Project/CubeIDE/ChaeburatorTest/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/East23/Project/CubeIDE/ChaeburatorTest/UART_Output" -I"D:/East23/Project/CubeIDE/ChaeburatorTest/ADC_LoadCell" -I"D:/East23/Project/CubeIDE/ChaeburatorTest/Drivers/Chaeburator" -I"D:/East23/Project/CubeIDE/ChaeburatorTest/Drivers/TestChaeburator" -I"D:/East23/Project/CubeIDE/ChaeburatorTest/Drivers/UART_Terminal" -I"D:/East23/Project/CubeIDE/ChaeburatorTest/Drivers/console" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-UART_Terminal

clean-Drivers-2f-UART_Terminal:
	-$(RM) ./Drivers/UART_Terminal/Console_Func.cyclo ./Drivers/UART_Terminal/Console_Func.d ./Drivers/UART_Terminal/Console_Func.o ./Drivers/UART_Terminal/Console_Func.su ./Drivers/UART_Terminal/UART_Terminal.cyclo ./Drivers/UART_Terminal/UART_Terminal.d ./Drivers/UART_Terminal/UART_Terminal.o ./Drivers/UART_Terminal/UART_Terminal.su

.PHONY: clean-Drivers-2f-UART_Terminal

