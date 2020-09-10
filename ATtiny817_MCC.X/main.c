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

//uint8_t SW0_flag = 1;
//
//void mySW0_ISR (void) {
//    SW0_flag ^= 1;
//}
void toggle_LED0(void) {
    LED0_Toggle();
}


/*
    Main application
*/
int main(void)
{
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();

    
    SS_SetLow();
    SPI0_ExchangeByte(0x06);
    SS_SetHigh();
    _delay_ms(100);
    
    SS_SetLow();
    SPI0_ExchangeByte(0x02);
    SPI0_ExchangeByte(0x01);
    SPI0_ExchangeByte(0xFA);
    SPI0_ExchangeByte(0xCC);
    SS_SetHigh();
    _delay_ms(100);
    
    SS_SetLow();
    SPI0_ExchangeByte(0x03);
    SPI0_ExchangeByte(0x01);
    SPI0_ExchangeByte(0xFA);
    SPI0_ExchangeByte(0x00);
    SS_SetHigh();
    _delay_ms(100);
        
    
    TCA0_SetOVFIsrCallback(toggle_LED0);
    
    /* Replace with your application code */
    while (1){
        

//        USART0_Write(USART0_Read());
        printf("Hello World!\n\r");

        
        _delay_ms(500);
        
    }
}
/**
    End of File
*/