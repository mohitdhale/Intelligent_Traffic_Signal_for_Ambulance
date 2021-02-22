#include <xc.h>
#include "USART.h"
#include "lcd.h"
#define F PORTCbits.RC0
#define B PORTCbits.RC1
#define L PORTCbits.RC2
#define R PORTDbits.RD0



#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF         // Low-Voltage (Single-Supply)
void Normal();
void main()
{
        unsigned char FD='F',RD='R',LD='L',BD='B';
        int i;
        TRISCbits.TRISC0=1;
        TRISCbits.TRISC1=1;
        TRISCbits.TRISC2=1;
        TRISDbits.TRISD0=1;
        LcdInit();
        LcdClear();
        LcdLineXY(0,1,"Smart Traffic Sys");
        LcdLineXY(1,0,"TE E&TC PROJECT ");
        delay(100);
        Normal();
        USARTInit(2400);
    while(1)
    {
        if(F==1)
        {
            for(i=0;i<20;i++)
            {
                USARTWriteChar('A');
                USARTWriteChar('A');
                USARTWriteChar(FD);
                USARTWriteChar(~FD);
                USARTWriteChar('Z');
            }
                LcdClear();
                LcdLineXY(0,4,"FORWARD");
                delay(30);
                Normal();
        }
        else if(B==1)
        {
            for(i=0;i<20;i++)
            {
                USARTWriteChar('A');
                USARTWriteChar('A');
                USARTWriteChar(BD);
                USARTWriteChar(~BD);
                USARTWriteChar('Z');
            }
                LcdClear();
                LcdLineXY(0,4,"REVERSE");
                delay(30);
                Normal();
        }
        else if(L==1)
        {
            for(i=0;i<20;i++)
            {
                USARTWriteChar('A');
                USARTWriteChar('A');
                USARTWriteChar(LD);
                USARTWriteChar(~LD);
                USARTWriteChar('Z');
            }
                LcdClear();
                LcdLineXY(0,3,"TURN LEFT");
                delay(30);
                Normal();
        }
        else if(R==1)
        {
            for(i=0;i<20;i++)
            {
                USARTWriteChar('A');
                USARTWriteChar('A');
                USARTWriteChar(RD);
                USARTWriteChar(~RD);
                USARTWriteChar('Z');
            }
                LcdClear();
                LcdLineXY(0,3,"TURN RIGHT");
                delay(30);
                Normal();
        }
        
    }
}
void Normal()
{
            LcdClear();
            LcdLineXY(0,1,"WAITING FOR KEY");
            LcdLineXY(1,4,"PRESSED");
}


