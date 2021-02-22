/*
 * File:   lcd.h
 * Author: Nilesh Mundphan
 *
 * Created on December 22, 2014, 1:17 PM
 */
#include <xc.h>
#include "lcd.h"
void LcdInit()
    {
        TRISB=0x00;
        TRISDbits.TRISD6=0;
        TRISDbits.TRISD7=0;
        LcdCmd(0x38);
        LcdCmd(0x01);
        LcdCmd(0x06);
        LcdCmd(0x0c);
        LcdCmd(0x80);
    }
void LcdClear()
    {
        LcdCmd(0x01);
        LcdCmd(0x80);
    }
void LcdCmd(unsigned char k)
    {
        delay(1);
        LCDP=k;
        RS=0;
        EN=1;
        delay(1);
        EN=0;
    }
  void LcdData(unsigned char l)
    {
        delay(1);
        LCDP=l;
        RS=1;
        EN=1;
        delay(1);
        EN=0;
    }
 void GotoXY(unsigned int x,unsigned int y)
    {
        if(x==0)
           LcdCmd(0x80+y);
        else
           LcdCmd(0xC0+y);
    }
void LcdLine(const unsigned char *msg )
    {
        while(*msg!='\0')
                LcdData(*msg++);

    }
void LcdLineXY(unsigned int x,unsigned int y ,const unsigned char *msg )
{
    GotoXY(x,y);
    LcdLine(msg);
}
void delay(unsigned int d)
{
        int i;
        for(i=0;i<d;i++)
          __delay_ms(10);
}
