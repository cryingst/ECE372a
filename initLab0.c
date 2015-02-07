
/*
* File:   initLab0.c
* Author: Christopher Yingst
*
* Created on 2/2/2015, 1:31 PM
*/

#include "p24fj64ga002.h"
#include "initLab0.h"

#define FCY 14745600.0
#define TIME_DELAY .5

void initLEDs(){
    //TODO: Initialize the pin connected to the LEDs as outputs
    TRISBbits.TRISB15 = 0; //LED15
    TRISBbits.TRISB14 = 0; //LED14
    TRISBbits.TRISB13 = 0; //LED13
    TRISBbits.TRISB12 = 0; //LED12
    //TODO: Turn each LED OFF

    LATBbits.LATB15 = OFF; //LED15
    LATBbits.LATB14 = OFF; //LED14
    LATBbits.LATB13 = OFF; //LED13
    LATBbits.LATB12 = OFF; //LED12
}

void initSW1(){
    //TODO: Initialize the pin connected to the switch as an input.
    TRISBbits.TRISB5 = 1;
    IFS1bits.CNIF = 0; // Put the overall CN flag down (set it to 0)

    //Enable the change notification interrupt
    IEC1bits.CNIE = 1;
    CNEN2bits.CN27IE = 1;
   


}


void initTimer1(){
    unsigned int prVal = (FCY*TIME_DELAY)/256.0 - 1;
     PR1 = prVal;
     T1CONbits.TCKPS = 0b11; //prescalar 256
     IEC0bits.T1IE = 1; // Enable the interrupt
     //IFS0bits.T1IF = 0; // Put the interrupt flag down
     //T1CONbits.TON = 1; // Turn the timer 1 off.this was changed

}