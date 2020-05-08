/*
 * File:   main.c
 * Author: Khalid BENEDDINE
 *
 * Created on 29 décembre 2019, 00:22
 */


#include <xc.h>
#include <stdint.h>
#include "Config.h"
#define _XTAL_FREQ 4000000

// IO Pins Defines (Mappings)
#define UP RB0
#define Down RB1
#define Send RB2

void UART_TX_Init(void);
void UART_Write(uint8_t);


void main(void) {
  UART_TX_Init(); // Initialize The UART in Master Mode @ 9600bps
  uint8_t Data = 0; // The Data Byte
  TRISB = 0x07; // RB0, RB1 & RB2 Are Input Pins (Push Buttons)
  TRISD = 0x00; // Output Port (4-Pins)
  PORTD = 0x00; // Initially OFF
    while (1){
       if(UP) {
           Data++;
           __delay_ms(250);
       }
       if(Down){
           Data--;
           __delay_ms(250);
       }
       if(Send){
           UART_Write(Data);
           __delay_ms(250);
       }
       PORTD = Data; // Display the current value
    }
    
    return;
}

void UART_TX_Init(void){
    BRGH = 1; //Set High-speed Baud Rate
    SPBRG = 25; // 96000 Baud Rate
    SYNC = 0; // Enable Asyn mode
    SPEN = 1; 
    TRISC6 = 1; // TX & RT Pins
    TRISC7 = 1;
    TXEN = 1; // Enable the transmission 
}

void UART_Write(uint8_t Data){
    while(!TRMT);
    TXREG = Data;
}