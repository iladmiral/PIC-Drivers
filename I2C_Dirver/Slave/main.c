/*
 File:   main.c
 * Author: Khalid BENEDDINE @iladmiral
 * I2C Slave Receiver
 * PIC16F877A - Or Any Other Similar PIC MCU
 */


#include <xc.h>
#include "Config.h"
#include <stdio.h>
#define _XTAL_FREQ 4000000  // Fose
unsigned char RX_Data = 0x00;

// Functions Prototypes
void I2C_Slave_Init(unsigned char Address);

void main(void) {
    TRISD = 0x00;
    PORTD = 0x00;
    I2C_Slave_Init(0x40); // Initiate I2C slave with addresse = 64 or 0x40
    while (1){
    
    }
    return;
}

// Configures The I2C In Slave Mode
void I2C_Slave_Init(unsigned char Address){
  TRISB0 = 1;     // Set As Input - SDA
  TRISB1 = 1;     // Set As Input - SCL
  SSPADD = Address;  // Set I2C Device Address
  SSPSTAT = 0x80; // Disable Slew Rate Control (Standard Mode)
  SSPCON = 0x36; // Select & Enable I2C (Slave Mode)
  SSPCON2 = 0x01; // Enable Clock Stretching
  SSPIF = 0;      // Enable Interrupts
  SSPIE = 1;
  PEIE = 1;
  GIE = 1;
}
// General ISR For I2C Slave. it could be for write, read, or overflow error
void __interrupt() ISR(void) {
  if(SSPIF)
  {
    if(!R_nW){ // Slave Write (Receive)
      char Dummy = SSPBUF; // Dummy Read
      CKP = 1; // Release The SCL Clock Line
      while(!BF); // Wait Until Completion
      RX_Data = SSPBUF; // Read The Buffer Data
      PORTD = RX_Data;  // Output The Received Byte
    }
  CKP = 1;   // Release The SCL Clock Line
  SSPIF = 0; // Clear The Interrupt Flag
  }
}