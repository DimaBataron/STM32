################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SX12xxDrivers-V2.1.0/src/RxTx/DataProcess.c \
../Drivers/SX12xxDrivers-V2.1.0/src/RxTx/LinkIndication.c 

O_SRCS += \
../Drivers/SX12xxDrivers-V2.1.0/src/RxTx/DataProcess.o \
../Drivers/SX12xxDrivers-V2.1.0/src/RxTx/LinkIndication.o 

OBJS += \
./Drivers/SX12xxDrivers-V2.1.0/src/RxTx/DataProcess.o \
./Drivers/SX12xxDrivers-V2.1.0/src/RxTx/LinkIndication.o 

C_DEPS += \
./Drivers/SX12xxDrivers-V2.1.0/src/RxTx/DataProcess.d \
./Drivers/SX12xxDrivers-V2.1.0/src/RxTx/LinkIndication.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SX12xxDrivers-V2.1.0/src/RxTx/%.o Drivers/SX12xxDrivers-V2.1.0/src/RxTx/%.su Drivers/SX12xxDrivers-V2.1.0/src/RxTx/%.cyclo: ../Drivers/SX12xxDrivers-V2.1.0/src/RxTx/%.c Drivers/SX12xxDrivers-V2.1.0/src/RxTx/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/console" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/UART_Terminal" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/BrushedDC" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/SX12xxDrivers-V2.1.0/src/radio" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/SX12xxDrivers-V2.1.0/src/RxTx" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/ChaeburatorIT_Proc" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Core/Inc" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/STM32F1xx_HAL_Driver/Inc" -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/STM32F1xx_HAL_Driver/Src" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I"D:/East23/Project/CubeIDE/ChaeburlatorBase/Drivers/UART_Output" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-SX12xxDrivers-2d-V2-2e-1-2e-0-2f-src-2f-RxTx

clean-Drivers-2f-SX12xxDrivers-2d-V2-2e-1-2e-0-2f-src-2f-RxTx:
	-$(RM) ./Drivers/SX12xxDrivers-V2.1.0/src/RxTx/DataProcess.cyclo ./Drivers/SX12xxDrivers-V2.1.0/src/RxTx/DataProcess.d ./Drivers/SX12xxDrivers-V2.1.0/src/RxTx/DataProcess.o ./Drivers/SX12xxDrivers-V2.1.0/src/RxTx/DataProcess.su ./Drivers/SX12xxDrivers-V2.1.0/src/RxTx/LinkIndication.cyclo ./Drivers/SX12xxDrivers-V2.1.0/src/RxTx/LinkIndication.d ./Drivers/SX12xxDrivers-V2.1.0/src/RxTx/LinkIndication.o ./Drivers/SX12xxDrivers-V2.1.0/src/RxTx/LinkIndication.su

.PHONY: clean-Drivers-2f-SX12xxDrivers-2d-V2-2e-1-2e-0-2f-src-2f-RxTx

