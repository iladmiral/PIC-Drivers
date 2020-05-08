/*
 * File:   main.c
 * Author: Khalid BENEDDINE @iladmiral
 *
 * 
 */


#include <xc.h>
#include <stdint.h>
#include"Config.h"
#define _XTAL_FREQ 4000000

// Define Button
#define UP RB0
#define DOWN RB1
#define SEND RB2
//Function declaration
void SPI_init ();
void SPI_Write(uint8_t);

void main(void) {
    SPI_init ();
    uint8_t Data = 0;
    TRISB = 0x07;
    TRISD = 0x00;
    PORTD = 0x00;
    while(1){
        while(UP){
            Data++;
            __delay_ms(250);
        }
        while (DOWN){
            Data--;
            __delay_ms(250);
        }
        while (SEND){
        SPI_Write(Data);
        __delay_ms(250);
        }
        PORTD = Data;
    }
    return;
}

void SPI_init() {
    //Master mode with prescl4
SSPM0 = 0;
SSPM1 = 0;
SSPM2 = 0;
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
TRISC3 = 0; //SCK
}

void SPI_Write(uint8_t Data){
    SSPBUF = Data;
}