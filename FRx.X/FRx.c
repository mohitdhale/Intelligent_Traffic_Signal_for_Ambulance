#include <xc.h>
#include "USART.h"
#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF

void delay(unsigned int DEL);

#define SR1 PORTCbits.RC0
#define SY1 PORTCbits.RC1
#define SG1 PORTCbits.RC2

#define SR2 PORTDbits.RD0
#define SY2 PORTDbits.RD1
#define SG2 PORTDbits.RD2

#define SR3 PORTDbits.RD3
#define SY3 PORTDbits.RD4
#define SG3 PORTDbits.RD5

#define SR4 PORTDbits.RD6
#define SY4 PORTBbits.RB0
#define SG4 PORTDbits.RD7

//void sig();
void main()
{
    uint8_t packet[5],data=0,i;
    TRISCbits.RC0=0;
    TRISCbits.RC1=0;
    TRISCbits.RC2=0;

    TRISDbits.RD0=0;
    TRISDbits.RD1=0;
    TRISDbits.RD2=0;
    //TRISDbits.RD3=0;
    TRISDbits.RD3=0;
    TRISDbits.RD4=0;
    TRISDbits.RD5=0;
    
    TRISDbits.RD6=0;
    TRISBbits.RB0=0;
    TRISDbits.RD7=0;
    
    //sig();
    USARTInit(2400);
    while(1)
    {
              while(!USARTDataAvailable());
            if(USARTReadData()!='A') continue;
            while(!USARTDataAvailable());
            if(USARTReadData()!='A') continue;
            while(USARTDataAvailable()!=3);
            for(i=2;i<5;i++)
            {
               packet[i]=USARTReadData();
            }
            
			if(packet[2]!=((uint8_t)~packet[3])) continue;
            
			if(packet[4]!='Z') continue;
			
            data=packet[2];
            if(data=='F')
            {
                SR1=0;SY1=1;SG1=0;
                SR2=1;SY2=0;SG2=0;
                SR3=1;SY3=0;SG3=0;
                SR4=1;SY4=0;SG4=0;
                delay(100);
                SR1=0;SY1=0;SG1=1;
                SR2=1;SY2=0;SG2=0;
                SR3=1;SY3=0;SG3=0;
                SR4=1;SY4=0;SG4=0;
                delay(300);
                //sig();
            }
            else if(data=='B')
            {   SR1=1;SY1=0;SG1=0;
                SR2=0;SY2=1;SG2=0;
                SR3=1;SY3=0;SG3=0;
                SR4=1;SY4=0;SG4=0;
                delay(100);
                SR1=1;SY1=0;SG1=0;
                SR2=0;SY2=0;SG2=1;
                SR3=1;SY3=0;SG3=0;
                SR4=1;SY4=0;SG4=0;
                delay(200);
                 //sig();

            }
            else if(data=='L')
            {   SR1=1;SY1=0;SG1=0;
                SR2=1;SY2=0;SG2=0;
                SR3=0;SY3=1;SG3=0;
                SR4=1;SY4=0;SG4=0;
                delay(100);
                SR1=1;SY1=0;SG1=0;
                SR2=1;SY2=0;SG2=0;
                SR3=0;SY3=0;SG3=1;
                SR4=1;SY4=0;SG4=0;
                delay(200);
                 //sig();

            }
            else if(data=='R')
            {   SR1=1;SY1=0;SG1=0;
                SR2=1;SY2=0;SG2=0;
                SR3=1;SY3=0;SG3=0;
                SR4=0;SY4=1;SG4=0;
                delay(100);
                SR1=1;SY1=0;SG1=0;
                SR2=1;SY2=0;SG2=0;
                SR3=1;SY3=0;SG3=0;
                SR4=0;SY4=0;SG4=1;
                delay(200);
                 
            }
            USARTFlushBuffer();
            //sig();
            
              
     }
              
}
void delay(unsigned int DEL)
{
    int j;
    for(j=0;j<DEL;j++)
        __delay_ms(10);
}
void sig()
{               SR1=0;SY1=0;SG1=1;
                SR2=1;SY2=0;SG2=0;
                SR3=1;SY3=0;SG3=0;
                SR4=1;SY4=0;SG4=0;
                delay(300);
                SR1=1;SY1=0;SG1=0;
                SR2=0;SY2=0;SG2=1;
                SR3=1;SY3=0;SG3=0;
                SR4=1;SY4=0;SG4=0;
                delay(300);
                SR1=1;SY1=0;SG1=0;
                SR2=1;SY2=0;SG2=0;
                SR3=0;SY3=0;SG3=1;
                SR4=1;SY4=0;SG4=0;
                delay(300);
                SR1=1;SY1=0;SG1=0;
                SR2=1;SY2=0;SG2=0;
                SR3=1;SY3=0;SG3=0;
                SR4=0;SY4=0;SG4=1;
                delay(300);
}