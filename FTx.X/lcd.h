/* 
 * File:   lcd.h
 * Author: Nilesh Mundphan
 *
 * Created on December 22, 2014, 1:17 PM
 */

#ifndef LCD_H
    #define	LCD_H
#ifdef	__cplusplus
extern "C" {
#endif
#define RS PORTDbits.RD6
#define EN PORTDbits.RD7

#define LCDP PORTB
void LcdInit();
void LcdClear();
void LcdData(unsigned char l);
void LcdCmd(unsigned char k);
void LcdLine(const unsigned char *msg);
void GotoXY(unsigned int x,unsigned int y);
void LcdLineXY(unsigned int x,unsigned int y ,const unsigned char *msg );
void delay(unsigned int d);
#ifdef	__cplusplus
}
#endif
#endif	/* LCD_H */

