# avr_on_mcc
Source code for demonstration of using Microchip Code Configurator (MCC) to configure peripherals and develop a project in ATtiny817

**Hardware used are:**
ATtiny817 Xplained Mini Board
Microchip Serial PIM SPI EEPROM
Analog Joystick as potentiometer

**Software:**
MPLAB X 5.40
XC8 2.20
MCC 3.95.0



Pin Configuration:

1. SPI0
   1. MOSI - PA1
   2. MISO - PA2
   3. SCK - PA3
   4. SS - PB0 (as GPIO)
2. UART
   1. TX - PB2
   2. RX - PB3
3. ADC
   1. AINx or AIN10 - PB1
4. Analog Comparator
   1. OUT pin - PA5
   2. AINPx (or Positive Reference) - PA7
5. LED0 - PC0
6. SW0 - PC5

**Optional:**

7. PWM pin for RGB LED Driver
   1. R - PC4
   2. G - PB6
   3. B - PB7



UART Baudrate: 38400