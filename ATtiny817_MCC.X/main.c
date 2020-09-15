/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "util/delay.h"
#include <math.h>

#define WREN_CMD    0x06
#define BYTE_WR_CMD 0x02
#define RD_CMD      0x03
#define RDSR_CMD    0x05

volatile uint8_t SW0_flag = 1;
adc_result_t adcVal;

void mySW0_ISR (void) {
    SW0_flag ^= 1;
}

void toggle_LED0(void) {
    LED0_Toggle();
}

double readThermistor(uint16_t rawAdc) {
  double temp;
  temp = log(10000.0*((256.0/rawAdc-1))); 
  temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp ))* temp );
  temp = temp - 273.15;            // Convert Kelvin to Celcius
   //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
   return temp;
}

//WREN command
void writeEnable_EEPROM(void){
    SS_SetLow();
    SPI0_ExchangeByte(WREN_CMD);
    SS_SetHigh();
    _delay_ms(100);
}

 //WRITE command
void writeByte_EEPROM(uint16_t address, uint8_t dataByte) {
    SS_SetLow();
    SPI0_ExchangeByte(BYTE_WR_CMD);
    SPI0_ExchangeByte((address >> 8) & 0xFF);
    SPI0_ExchangeByte((address & 0xFF));
    SPI0_ExchangeByte(dataByte);
    SS_SetHigh();
    _delay_ms(100);
}

//READ command
uint8_t readByte_EEPROM(uint16_t address) {
    uint8_t readBuffer = 0;
    SS_SetLow();
    SPI0_ExchangeByte(RD_CMD);
    SPI0_ExchangeByte((address >> 8) & 0xFF);
    SPI0_ExchangeByte((address & 0xFF));
    SPI0_ExchangeByte(0x00);
    readBuffer = SPI0.DATA;
    SS_SetHigh();
    _delay_ms(100);
    return readBuffer;
}
    

/*
    Main application
*/
int main(void)
{
    /* Initializes MCU, drivers and middleware */
    uint8_t var = 0;
    SYSTEM_Initialize();
    

    writeEnable_EEPROM();
    writeByte_EEPROM(0x2311, 0xAB);
    var = readByte_EEPROM(0x2311);
    readByte_EEPROM(0x01FA);
        
    TCA0_SetOVFIsrCallback(toggle_LED0);
    
    
    /* Replace with your application code */
    while (1){
        printf("Hello World!\n\r");
        _delay_ms(500);
        
        adcVal = ADC0_GetConversion(ADC_MUXPOS_AIN10_gc);
//        USART0_Write(adcVal);
        printf("ADC: %d\n\r", adcVal);
        
        _delay_ms(10);
    }
}
/**
    End of File
*/