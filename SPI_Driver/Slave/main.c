/*
 * File:   main.c
 * Author: Khalid BENEDDINE
 *
 * 
 */



#include <xc.h>
#include <stdint.h>
#include"Config.h"
#define _XTAL_FREQ 4000000

void SPI_Slave_init ();
uint8_t SPI_Read();
uint8_t Data;

void main(void) {
    SPI_Slave_init();
    TRISB = 0x00;
    while(1){
        PORTB = Data;
    }
    return;
}

void SPI_Slave_init(){
//Salve mode with SS enable
SSPM0 = 0;
SSPM1 = 0;
SSPM2 = 1;
SSPM3 = 0;
//Syn mode
SSPEN = 1;
//Config CLK polarity & phase
CKP = 0;
CKE = 0;
 //Config the input data sampled
SMP = 0;
 //Config I/O Pins
TRISC5 = 0; //SDO
TRISC4 = 1; //SDI
TRISC3 = 1; //SCK
PCFG3 = 0; // Set SS (RA5/AN4) To Be Digital IO
PCFG2 = 1;
PCFG1 = 0;
PCFG0 = 0;
TRISA5 = 1; // SS -> Input
    //Enable Interrupts
SSPIE = 1;
PEIE = 1;
GIE = 1;
}

uint8_t SPI_Read(){
   uint8_t Data;
   return Data;
 
}

void __interrupt() ISR(void){
    if(SSPIF){
        Data = SSPBUF;
        SSPIF = 0;
    }
}