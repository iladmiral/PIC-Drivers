/*
 * File:   main.c
 * Author: Khalid BENEDDINE
 *
 * Created on 29 d�cembre 2019, 12:21
 */


#include <xc.h>
#include <stdint.h>
#include "Config.h"
#define _XTAL_FREQ 4000000

void UART_RX_Init(void);
uint8_t UART_READ(void);

uint8_t UART_Buffer = 0;

void main(void) {
    UART_RX_Init();
    TRISB = 0x00;
    PORTB = 0x00;
    
    while(1){
    
    }
    return;
}

void UART_RX_Init(void){
    BRGH = 1; //Set High-speed Baud Rate
    SPBRG = 25; // 96000 Baud Rate
    SYNC = 0; // Enable Asyn mode
    SPEN = 1; 
    TRISC6 = 1; // TX & RT Pins
    TRISC7 = 1;
    RCIE = 1; // Eable interrupts
    GIE = 1;  
    PEIE = 1;
    CREN = 1; //Eable data continous reception UART
}

void __interrupt() ISR (void){
    if(RCIF){
        UART_Buffer = RCREG; //Read the reciver data buffer
        PORTB = UART_Buffer; // Display the data on Leds 
        RCIF = 0;
    }
}