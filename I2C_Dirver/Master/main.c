/*
 * File:   main.c
 * Author: Khalid BENEDDINE
 * I2C Master Transmitter
 * PIC16F877A - Or Any Other Similar PIC MCU
 * 
 */


#include <xc.h>
#include "Config.h"
#include <stdio.h>
#define _XTAL_FREQ 4000000  // Fose
#define I2C_BaudRate 100000 // I2C Baud Rate = 100 Kbps


// Functions Prototypes
void I2C_Start();
void I2C_Master_Init(void);
void I2C_Start();
void I2C_Stop();
void I2C_Restart();
void I2C_ACK();
void I2C_NACK();
unsigned char I2C_Write(unsigned char Data);
unsigned char I2C_Read_Byte(void);

void main(void) {
    TRISB = 0xFF;
    TRISD = 0x00;
    PORTD = 0x00;
    unsigned char i=1;
    I2C_Master_Init();
    while(1){
    I2C_Start();
    I2C_Write(0x40);
    I2C_Write(i++);
    I2C_Stop();
    __delay_ms(500);
    RD3 = ~RD3; // Toggle a LED each time a bayte is send
    }
    return;
}

//Verify the previous state has reached completion successfully 
void I2C_Wait(void){
    while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

// Satup I2C for Master Mode
void I2C_Master_Init(void){
    SSPCON = 0x28;
    SSPCON2 = 0x00;
    SSPSTAT = 0x00;
    SSPADD = ((_XTAL_FREQ) / (4 * I2C_BaudRate)) - 1;
    TRISC3 = 1;
    TRISC4 = 1;
}

// Initiate I2C Start Condition Sequence
void I2C_Start(){
    I2C_Wait();
    SEN = 1;
}
// Initiate I2C Stop Condition Sequence
void I2C_Stop(){
    I2C_Wait();
    PEN = 1;
}
// Initiate I2C Restart Condition Sequence
void I2C_Restart(){
    I2C_Wait();
    RSEN = 1;
}
// Initiate I2C Acknowledge Sequence
void I2C_ACK(){
    I2C_Wait();
    ACKDT = 0;  // 1 = Not Acknowledge,  0 = Acknowledge        
    ACKEN = 1;  // Send ACK Signal
}
// Initiate I2C Not Acknowledge Sequence
void I2C_NACK(){
    I2C_Wait();
    ACKDT = 1;  // 1 = Not Acknowledge,  0 = Acknowledge        
    ACKEN = 1;  // Send ACK Signal
}
// Send Byte, Return The ACK/NACK
unsigned char I2C_Write(unsigned char Data){
    I2C_Wait();
    SSPBUF = Data;
    I2C_Wait();
    return ACKSTAT;
}
// Receive & Return A Byte
unsigned char I2C_Read_Byte(void){
    RCEN = 1; // Enable & Start Reception
    while(!SSPIF);
    SSPIF = 0; // Clear The Interrupt Flag Bit
    return SSPBUF;
}
