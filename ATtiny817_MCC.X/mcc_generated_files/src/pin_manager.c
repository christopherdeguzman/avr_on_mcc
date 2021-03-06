/**
  @Company
    Microchip Technology Inc.

  @Description
    This Source file provides APIs.
    Generation Information :
    Driver Version    :   1.0.0
*/
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


#include "../include/pin_manager.h"
static void (*PORTA_PA2_InterruptHandler)(void);
static void (*PORTB_PB3_InterruptHandler)(void);
static void (*PORTC_IO_PC4_R_InterruptHandler)(void);
static void (*PORTA_PA1_InterruptHandler)(void);
static void (*PORTB_PB2_InterruptHandler)(void);
static void (*PORTC_SW0_InterruptHandler)(void);
static void (*PORTA_PA3_InterruptHandler)(void);
static void (*PORTB_IO_PB7_B_InterruptHandler)(void);
static void (*PORTA_PA5_InterruptHandler)(void);
static void (*PORTB_IO_PB6_G_InterruptHandler)(void);
static void (*PORTA_PA7_InterruptHandler)(void);
static void (*PORTC_LED0_InterruptHandler)(void);
static void (*PORTB_PB1_InterruptHandler)(void);
static void (*PORTB_SS_InterruptHandler)(void);

void PORT_Initialize(void);

void PIN_MANAGER_Initialize()
{
    PORT_Initialize();

    /* DIR Registers Initialization */
    PORTA.DIR = 0x2A;
    PORTB.DIR = 0xC5;
    PORTC.DIR = 0x11;

    /* OUT Registers Initialization */
    PORTA.OUT = 0x51;
    PORTB.OUT = 0xC1;
    PORTC.OUT = 0x3E;

    /* PINxCTRL registers Initialization */
    PORTA.PIN0CTRL = 0x04;
    PORTA.PIN1CTRL = 0x00;
    PORTA.PIN2CTRL = 0x00;
    PORTA.PIN3CTRL = 0x00;
    PORTA.PIN4CTRL = 0x00;
    PORTA.PIN5CTRL = 0x00;
    PORTA.PIN6CTRL = 0x04;
    PORTA.PIN7CTRL = 0x04;
    PORTB.PIN0CTRL = 0x04;
    PORTB.PIN1CTRL = 0x04;
    PORTB.PIN2CTRL = 0x00;
    PORTB.PIN3CTRL = 0x00;
    PORTB.PIN4CTRL = 0x00;
    PORTB.PIN5CTRL = 0x00;
    PORTB.PIN6CTRL = 0x00;
    PORTB.PIN7CTRL = 0x00;
    PORTC.PIN0CTRL = 0x00;
    PORTC.PIN1CTRL = 0x00;
    PORTC.PIN2CTRL = 0x00;
    PORTC.PIN3CTRL = 0x00;
    PORTC.PIN4CTRL = 0x00;
    PORTC.PIN5CTRL = 0x03;
    PORTC.PIN6CTRL = 0x00;
    PORTC.PIN7CTRL = 0x00;

    /* PORTMUX Initialization */
    PORTMUX.CTRLA = 0x00;
    PORTMUX.CTRLB = 0x00;
    PORTMUX.CTRLC = 0x00;
    PORTMUX.CTRLD = 0x00;

    // register default ISC callback functions at runtime; use these methods to register a custom function
    PORTA_PA2_SetInterruptHandler(PORTA_PA2_DefaultInterruptHandler);
    PORTB_PB3_SetInterruptHandler(PORTB_PB3_DefaultInterruptHandler);
    PORTC_IO_PC4_R_SetInterruptHandler(PORTC_IO_PC4_R_DefaultInterruptHandler);
    PORTA_PA1_SetInterruptHandler(PORTA_PA1_DefaultInterruptHandler);
    PORTB_PB2_SetInterruptHandler(PORTB_PB2_DefaultInterruptHandler);
    PORTC_SW0_SetInterruptHandler(PORTC_SW0_DefaultInterruptHandler);
    PORTA_PA3_SetInterruptHandler(PORTA_PA3_DefaultInterruptHandler);
    PORTB_IO_PB7_B_SetInterruptHandler(PORTB_IO_PB7_B_DefaultInterruptHandler);
    PORTA_PA5_SetInterruptHandler(PORTA_PA5_DefaultInterruptHandler);
    PORTB_IO_PB6_G_SetInterruptHandler(PORTB_IO_PB6_G_DefaultInterruptHandler);
    PORTA_PA7_SetInterruptHandler(PORTA_PA7_DefaultInterruptHandler);
    PORTC_LED0_SetInterruptHandler(PORTC_LED0_DefaultInterruptHandler);
    PORTB_PB1_SetInterruptHandler(PORTB_PB1_DefaultInterruptHandler);
    PORTB_SS_SetInterruptHandler(PORTB_SS_DefaultInterruptHandler);
}

void PORT_Initialize(void)
{
    /* On AVR devices all peripherals are enable from power on reset, this
     * disables all peripherals to save power. Driver shall enable
     * peripheral if used */

    /* Set all pins to low power mode */
    for (uint8_t i = 0; i < 8; i++) {
        *((uint8_t *)&PORTA + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
    }
    
    for (uint8_t i = 0; i < 8; i++) {
        *((uint8_t *)&PORTB + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
    }
    
    for (uint8_t i = 0; i < 8; i++) {
        *((uint8_t *)&PORTC + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
    }
    
}

/**
  Allows selecting an interrupt handler for PORTA_PA2 at application runtime
*/
void PORTA_PA2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_PA2_InterruptHandler = interruptHandler;
}

void PORTA_PA2_DefaultInterruptHandler(void)
{
    // add your PORTA_PA2 interrupt custom code
    // or set custom function using PORTA_PA2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTB_PB3 at application runtime
*/
void PORTB_PB3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTB_PB3_InterruptHandler = interruptHandler;
}

void PORTB_PB3_DefaultInterruptHandler(void)
{
    // add your PORTB_PB3 interrupt custom code
    // or set custom function using PORTB_PB3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTC_IO_PC4_R at application runtime
*/
void PORTC_IO_PC4_R_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTC_IO_PC4_R_InterruptHandler = interruptHandler;
}

void PORTC_IO_PC4_R_DefaultInterruptHandler(void)
{
    // add your PORTC_IO_PC4_R interrupt custom code
    // or set custom function using PORTC_IO_PC4_R_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTA_PA1 at application runtime
*/
void PORTA_PA1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_PA1_InterruptHandler = interruptHandler;
}

void PORTA_PA1_DefaultInterruptHandler(void)
{
    // add your PORTA_PA1 interrupt custom code
    // or set custom function using PORTA_PA1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTB_PB2 at application runtime
*/
void PORTB_PB2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTB_PB2_InterruptHandler = interruptHandler;
}

void PORTB_PB2_DefaultInterruptHandler(void)
{
    // add your PORTB_PB2 interrupt custom code
    // or set custom function using PORTB_PB2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTC_SW0 at application runtime
*/
void PORTC_SW0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTC_SW0_InterruptHandler = interruptHandler;
}

void PORTC_SW0_DefaultInterruptHandler(void)
{
    // add your PORTC_SW0 interrupt custom code
    // or set custom function using PORTC_SW0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTA_PA3 at application runtime
*/
void PORTA_PA3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_PA3_InterruptHandler = interruptHandler;
}

void PORTA_PA3_DefaultInterruptHandler(void)
{
    // add your PORTA_PA3 interrupt custom code
    // or set custom function using PORTA_PA3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTB_IO_PB7_B at application runtime
*/
void PORTB_IO_PB7_B_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTB_IO_PB7_B_InterruptHandler = interruptHandler;
}

void PORTB_IO_PB7_B_DefaultInterruptHandler(void)
{
    // add your PORTB_IO_PB7_B interrupt custom code
    // or set custom function using PORTB_IO_PB7_B_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTA_PA5 at application runtime
*/
void PORTA_PA5_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_PA5_InterruptHandler = interruptHandler;
}

void PORTA_PA5_DefaultInterruptHandler(void)
{
    // add your PORTA_PA5 interrupt custom code
    // or set custom function using PORTA_PA5_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTB_IO_PB6_G at application runtime
*/
void PORTB_IO_PB6_G_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTB_IO_PB6_G_InterruptHandler = interruptHandler;
}

void PORTB_IO_PB6_G_DefaultInterruptHandler(void)
{
    // add your PORTB_IO_PB6_G interrupt custom code
    // or set custom function using PORTB_IO_PB6_G_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTA_PA7 at application runtime
*/
void PORTA_PA7_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_PA7_InterruptHandler = interruptHandler;
}

void PORTA_PA7_DefaultInterruptHandler(void)
{
    // add your PORTA_PA7 interrupt custom code
    // or set custom function using PORTA_PA7_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTC_LED0 at application runtime
*/
void PORTC_LED0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTC_LED0_InterruptHandler = interruptHandler;
}

void PORTC_LED0_DefaultInterruptHandler(void)
{
    // add your PORTC_LED0 interrupt custom code
    // or set custom function using PORTC_LED0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTB_PB1 at application runtime
*/
void PORTB_PB1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTB_PB1_InterruptHandler = interruptHandler;
}

void PORTB_PB1_DefaultInterruptHandler(void)
{
    // add your PORTB_PB1 interrupt custom code
    // or set custom function using PORTB_PB1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTB_SS at application runtime
*/
void PORTB_SS_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTB_SS_InterruptHandler = interruptHandler;
}

void PORTB_SS_DefaultInterruptHandler(void)
{
    // add your PORTB_SS interrupt custom code
    // or set custom function using PORTB_SS_SetInterruptHandler()
}
ISR(PORTC_PORT_vect)
{  
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTC.INTFLAGS & PORT_INT4_bm)
    {
       PORTC_IO_PC4_R_InterruptHandler();
    }
    if(VPORTC.INTFLAGS & PORT_INT5_bm)
    {
       PORTC_SW0_InterruptHandler();
    }
    if(VPORTC.INTFLAGS & PORT_INT0_bm)
    {
       PORTC_LED0_InterruptHandler();
    }

    /* Clear interrupt flags */
    VPORTC.INTFLAGS = 0xff;
}

