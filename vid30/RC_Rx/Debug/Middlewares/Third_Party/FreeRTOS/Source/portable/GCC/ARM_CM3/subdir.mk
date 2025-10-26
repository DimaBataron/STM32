################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/port.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/port.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/port.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/%.o Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/%.su Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/%.cyclo: ../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/%.c Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/console" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/UART_Terminal" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/BrushedDC" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/SX12xxDrivers-V2.1.0/src/radio" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/SX12xxDrivers-V2.1.0/src/RxTx" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/ChaeburatorIT_Proc" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Core/Inc" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/STM32F1xx_HAL_Driver/Inc" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/STM32F1xx_HAL_Driver/Src" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/UART_Output" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM3

clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM3:
	-$(RM) ./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/port.cyclo ./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/port.d ./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/port.o ./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/port.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM3

