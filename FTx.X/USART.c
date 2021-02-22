#include <stdint.h>
#include <xc.h>
#include "USART.h"
void USARTInit(uint16_t baud_rate)
{
    //Setup queue
    UQFront=UQEnd=-1;
    //SPBRG
    switch(baud_rate)
    {
         case 2400:
            SPBRG=129;
            break;
        
    }
            //TXSTA
            TXSTAbits.TX9=0;  //8 bit transmission
            TXSTAbits.TXEN=1; //Transmit enable
            TXSTAbits.SYNC=0; //Async mode
            TXSTAbits.BRGH=0; //High speed baud rate
            //RCSTA
            RCSTAbits.SPEN=1;   //Serial port enabled
            RCSTAbits.RX9=0;    //8 bit mode
            RCSTAbits.CREN=1;   //Enable receive
            RCSTAbits.ADDEN=0;  //Disable address detection
            //Receive interrupt
            RCIE=1;
            PEIE=1;
            ei();
}
void interrupt ISR(void)
{
    if (RCIE && RCIF) {
        USARTHandleRxInt();
        return;
    }
}
void USARTWriteChar(char ch)
{
          while(!PIR1bits.TXIF);
          TXREG=ch;
}

void USARTWriteString(const char *str)
{
  while(*str!='\0')
  {
      USARTWriteChar(*str);
      str++;
  }
}

void USARTWriteLine(const char *str)
{
    USARTWriteChar('\r');//CR
    USARTWriteChar('\n');//LF
    USARTWriteString(str);
}

void USARTHandleRxInt()
{
    //Read the data
    char data=RCREG;
    //Now add it to q
    if(((UQEnd==RECEIVE_BUFF_SIZE-1) && UQFront==0) || ((UQEnd+1)==UQFront))
    {
        //Q Full
	UQFront++;
	if(UQFront==RECEIVE_BUFF_SIZE) UQFront=0;
    }
    if(UQEnd==RECEIVE_BUFF_SIZE-1)
        UQEnd=0;
    else
	UQEnd++;
    URBuff[UQEnd]=data;
    if(UQFront==-1) UQFront=0;
}

char USARTReadData()
{
    char data;
    //Check if q is empty
    if(UQFront==-1)
	return 0;
    data=URBuff[UQFront];
    if(UQFront==UQEnd)
    {
        //If single data is left
	//So empty q
	UQFront=UQEnd=-1;
    }
    else
    {
	UQFront++;
	if(UQFront==RECEIVE_BUFF_SIZE)
            UQFront=0;
    }

    return data;
}

uint8_t USARTDataAvailable()
{
    if(UQFront==-1) return 0;
    if(UQFront<UQEnd)
	return(UQEnd-UQFront+1);
    else if(UQFront>UQEnd)
	return (RECEIVE_BUFF_SIZE-UQFront+UQEnd+1);
    else
	return 1;
}
void USARTGotoNewLine()
{
    USARTWriteChar('\r');//CR
    USARTWriteChar('\n');//LF
}

void USARTReadBuffer(char *buff,uint16_t len)
{
	uint16_t i;
	for(i=0;i<len;i++)
	{
		buff[i]=USARTReadData();
	}
}
void USARTFlushBuffer()
{
	while(USARTDataAvailable()>0)
	{
		USARTReadData();
	}
}
