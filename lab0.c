// ******************************************************************************************* //
//
// File:         lab0.c
// Date: 2/2/1015
// Authors:Christopher Yingst
//
// Description:  Lab 0 assignment for ECE 372 Spring 2015.
// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "initLab0.h"
#include <stdio.h>

// ******************************************************************************************* //
// Configuration bits for CONFIG1 settings.
//
// These settings are appropriate for debugging the PIC microcontroller. If you need to
// program the PIC for standalone operation, change the COE_ON option to COE_OFF.

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF &
          BKBUG_ON & COE_ON & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )



typedef enum stateTypeEnum{
    LED4ON, LED5ON,LED6ON, LED7ON

    //TODO: Define states by name
} stateType;
volatile stateType currentState;
volatile unsigned int count = 0;
#define RELEASED 1
#define PRESSED 0
#define RESET 0
int main(void)
{

    //TODO: Finish these functions in the provided c files
    initLEDs();
    initTimer1();
    initSW1();
    currentState = LED4ON;
    while(1)
    {

            switch(currentState)
            {
                case LED4ON:
                {
                    LATBbits.LATB15 = ON; //LED15
                    LATBbits.LATB14 = OFF; //LED14
                    LATBbits.LATB13 = OFF; //LED13
                    LATBbits.LATB12 = OFF; //LED12
                    break;
                }
                case LED5ON:
                {
                    LATBbits.LATB15 = OFF; //LED15
                    LATBbits.LATB14 = ON; //LED14
                    LATBbits.LATB13 = OFF; //LED13
                    LATBbits.LATB12 = OFF; //LED12
                    break;
                }
                case LED6ON:
                {
                    LATBbits.LATB15 = OFF; //LED15
                    LATBbits.LATB14 = OFF; //LED14
                    LATBbits.LATB13 = ON; //LED13
                    LATBbits.LATB12 = OFF; //LED12
                    break;
                }
                case LED7ON:
                {
                    LATBbits.LATB15 = OFF; //LED15
                    LATBbits.LATB14 = OFF; //LED14
                    LATBbits.LATB13 = OFF; //LED13
                    LATBbits.LATB12 = ON; //LED12
                    break;
                }
                default:
                {
                    LATBbits.LATB15 = OFF; //LED15
                    LATBbits.LATB14 = OFF; //LED14
                    LATBbits.LATB13 = OFF; //LED13
                    LATBbits.LATB12 = OFF; //LED12
                    break;
                }
            }
            
     }
        //Use a switch statement to define the behavior based on the state
    return 0;
}

void _ISR _T1Interrupt(void){
    //TODO: Put down the timer 1 flag first!
    IFS0bits.T1IF = 0;

    count  = count + 1;
    //Make sure if you use any variables that they are declared volatile!
}
void _ISR _CNInterrupt(void)
{
    IFS1bits.CNIF = 0;

     if(PORTBbits.RB5 == PRESSED)//equal to 1
    {
       T1CONbits.TON = 1;
    }
    
     if (PORTBbits.RB5 == RELEASED && count < 4)//equal to 0
     {
        T1CONbits.TON = 0;
        count = 0;
        TMR1 = 0;

        if(currentState == LED4ON)
         currentState = LED5ON;
        else if(currentState == LED5ON)
         currentState = LED6ON;
        else if(currentState == LED6ON)
        currentState = LED7ON;
        else if(currentState == LED7ON)
         currentState = LED4ON;
     }
     else if(PORTBbits.RB5 == RELEASED && count >= 4)//equal to 0
    {
        count = 0;
        T1CONbits.TON = 0;
        TMR1 = 0;

         if(currentState == LED4ON)
             currentState = LED7ON;
         else if(currentState == LED5ON)
             currentState = LED4ON;
         else if(currentState == LED6ON)
            currentState = LED5ON;
         else if(currentState == LED7ON)
             currentState = LED6ON;
    }

}