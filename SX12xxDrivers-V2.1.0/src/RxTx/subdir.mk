################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/East23/Project/STM32BatLib/SX12xxDrivers-V2.1.0/src/RxTx/DataProcess.c \
D:/East23/Project/STM32BatLib/SX12xxDrivers-V2.1.0/src/RxTx/LinkIndication.c 

OBJS += \
./SX12xxDrivers-V2.1.0/src/RxTx/DataProcess.o \
./SX12xxDrivers-V2.1.0/src/RxTx/LinkIndication.o 

C_DEPS += \
./SX12xxDrivers-V2.1.0/src/RxTx/DataProcess.d \
./SX12xxDrivers-V2.1.0/src/RxTx/LinkIndication.d 


# Each subdirectory must supply rules for building sources it contributes
SX12xxDrivers-V2.1.0/src/RxTx/DataProcess.o: D:/East23/Project/STM32BatLib/SX12xxDrivers-V2.1.0/src/RxTx/DataProcess.c SX12xxDrivers-V2.1.0/src/RxTx/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/East23/Project/CubeIDE/UnityTestStart/TestUnityProject/TestUSART/Inc" -I"D:/East23/Project/CubeIDE/UnityTestStart/Unity/src" -I"D:/East23/Project/CubeIDE/UnityTestStart/TestUnityProject/TestSPI" -I"D:/East23/Project/CubeIDE/UnityTestStart/TestUnityProject/TestGPIO" -I"D:/East23/Project/STM32BatLib/SX12xxDrivers-V2.1.0/src/radio" -I"D:/East23/Project/STM32BatLib/SX12xxDrivers-V2.1.0/src/RxTx" -I"D:/East23/Project/CubeIDE/UnityTestStart/TestUnityProject/TestSX1278" -I"D:/East23/Project/CubeIDE/UnityTestStart/TestUnityProject" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
SX12xxDrivers-V2.1.0/src/RxTx/LinkIndication.o: D:/East23/Project/STM32BatLib/SX12xxDrivers-V2.1.0/src/RxTx/LinkIndication.c SX12xxDrivers-V2.1.0/src/RxTx/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/East23/Project/CubeIDE/UnityTestStart/TestUnityProject/TestUSART/Inc" -I"D:/East23/Project/CubeIDE/UnityTestStart/Unity/src" -I"D:/East23/Project/CubeIDE/UnityTestStart/TestUnityProject/TestSPI" -I"D:/East23/Project/CubeIDE/UnityTestStart/TestUnityProject/TestGPIO" -I"D:/East23/Project/STM32BatLib/SX12xxDrivers-V2.1.0/src/radio" -I"D:/East23/Project/STM32BatLib/SX12xxDrivers-V2.1.0/src/RxTx" -I"D:/East23/Project/CubeIDE/UnityTestStart/TestUnityProject/TestSX1278" -I"D:/East23/Project/CubeIDE/UnityTestStart/TestUnityProject" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-SX12xxDrivers-2d-V2-2e-1-2e-0-2f-src-2f-RxTx

clean-SX12xxDrivers-2d-V2-2e-1-2e-0-2f-src-2f-RxTx:
	-$(RM) ./SX12xxDrivers-V2.1.0/src/RxTx/DataProcess.cyclo ./SX12xxDrivers-V2.1.0/src/RxTx/DataProcess.d ./SX12xxDrivers-V2.1.0/src/RxTx/DataProcess.o ./SX12xxDrivers-V2.1.0/src/RxTx/DataProcess.su ./SX12xxDrivers-V2.1.0/src/RxTx/LinkIndication.cyclo ./SX12xxDrivers-V2.1.0/src/RxTx/LinkIndication.d ./SX12xxDrivers-V2.1.0/src/RxTx/LinkIndication.o ./SX12xxDrivers-V2.1.0/src/RxTx/LinkIndication.su

.PHONY: clean-SX12xxDrivers-2d-V2-2e-1-2e-0-2f-src-2f-RxTx

