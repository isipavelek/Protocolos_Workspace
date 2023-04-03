################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/src/API_Init.c \
../Drivers/API/src/API_debounce.c \
../Drivers/API/src/API_delay.c \
../Drivers/API/src/API_enc_port.c \
../Drivers/API/src/API_encoder.c \
../Drivers/API/src/API_lcd.c \
../Drivers/API/src/API_lcd_port.c \
../Drivers/API/src/API_reloj.c \
../Drivers/API/src/API_rtc.c \
../Drivers/API/src/API_uart.c 

OBJS += \
./Drivers/API/src/API_Init.o \
./Drivers/API/src/API_debounce.o \
./Drivers/API/src/API_delay.o \
./Drivers/API/src/API_enc_port.o \
./Drivers/API/src/API_encoder.o \
./Drivers/API/src/API_lcd.o \
./Drivers/API/src/API_lcd_port.o \
./Drivers/API/src/API_reloj.o \
./Drivers/API/src/API_rtc.o \
./Drivers/API/src/API_uart.o 

C_DEPS += \
./Drivers/API/src/API_Init.d \
./Drivers/API/src/API_debounce.d \
./Drivers/API/src/API_delay.d \
./Drivers/API/src/API_enc_port.d \
./Drivers/API/src/API_encoder.d \
./Drivers/API/src/API_lcd.d \
./Drivers/API/src/API_lcd_port.d \
./Drivers/API/src/API_reloj.d \
./Drivers/API/src/API_rtc.d \
./Drivers/API/src/API_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/src/%.o Drivers/API/src/%.su Drivers/API/src/%.cyclo: ../Drivers/API/src/%.c Drivers/API/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F429ZITx -DSTM32F4 -DNUCLEO_F429ZI -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Inc -I"C:/Users/ipave/Documents/GitHub/Protocolos_workspace/LCD_Hola_Mundo/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/ipave/Documents/GitHub/Protocolos_workspace/LCD_Hola_Mundo/Drivers/CMSIS/Include" -I"C:/Users/ipave/Documents/GitHub/Protocolos_workspace/LCD_Hola_Mundo/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/ipave/Documents/GitHub/Protocolos_workspace/LCD_Hola_Mundo/Drivers/BSP/STM32F4xx_Nucleo_144" -I"C:/Users/ipave/Documents/GitHub/Protocolos_workspace/LCD_Hola_Mundo/Drivers/Core/Inc" -I"C:/Users/ipave/Documents/GitHub/Protocolos_workspace/LCD_Hola_Mundo/Drivers/API/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-src

clean-Drivers-2f-API-2f-src:
	-$(RM) ./Drivers/API/src/API_Init.cyclo ./Drivers/API/src/API_Init.d ./Drivers/API/src/API_Init.o ./Drivers/API/src/API_Init.su ./Drivers/API/src/API_debounce.cyclo ./Drivers/API/src/API_debounce.d ./Drivers/API/src/API_debounce.o ./Drivers/API/src/API_debounce.su ./Drivers/API/src/API_delay.cyclo ./Drivers/API/src/API_delay.d ./Drivers/API/src/API_delay.o ./Drivers/API/src/API_delay.su ./Drivers/API/src/API_enc_port.cyclo ./Drivers/API/src/API_enc_port.d ./Drivers/API/src/API_enc_port.o ./Drivers/API/src/API_enc_port.su ./Drivers/API/src/API_encoder.cyclo ./Drivers/API/src/API_encoder.d ./Drivers/API/src/API_encoder.o ./Drivers/API/src/API_encoder.su ./Drivers/API/src/API_lcd.cyclo ./Drivers/API/src/API_lcd.d ./Drivers/API/src/API_lcd.o ./Drivers/API/src/API_lcd.su ./Drivers/API/src/API_lcd_port.cyclo ./Drivers/API/src/API_lcd_port.d ./Drivers/API/src/API_lcd_port.o ./Drivers/API/src/API_lcd_port.su ./Drivers/API/src/API_reloj.cyclo ./Drivers/API/src/API_reloj.d ./Drivers/API/src/API_reloj.o ./Drivers/API/src/API_reloj.su ./Drivers/API/src/API_rtc.cyclo ./Drivers/API/src/API_rtc.d ./Drivers/API/src/API_rtc.o ./Drivers/API/src/API_rtc.su ./Drivers/API/src/API_uart.cyclo ./Drivers/API/src/API_uart.d ./Drivers/API/src/API_uart.o ./Drivers/API/src/API_uart.su

.PHONY: clean-Drivers-2f-API-2f-src

