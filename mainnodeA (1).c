#include"header.h"
#define LEFT_INDICATOR ((IOPIN0>>14)&1)
#define RIGHT_INDICATOR ((IOPIN0>>15)&1)
#define HEADLIGHT ((IOPIN0>>16)&1)

unsigned char s[20];
unsigned char s1[20];

float vout,tempr;
CAN1 frame;// CREAT STR VAR_

/////**** FLAGS FOR CONTROL ****/////
int left=0,right=0,head=0;

int num,num1,speed;

int main()
{
  int adcval=0;
  adc_init();
  can1_init();
  uart0_init(9600);

  enableExtIntr2();
  enableExtIntr1();
  enableExtIntr0();

  configVicExt2();
  configVicExt1();
  configVicExt0();
  
 while(1)
 {
 	num=0;
	num1=0;
	speed=0;

	frame.id=0x1FF;
	frame.rtr=0;
	frame.dlc=8;
	////**** LEFT INDICATOR MONITORING ****////
	if(left)		  
		num=0xAA;			
	else
		num=0xBB;

////**** RIGHT INDICATOR MONITORING ****////

	if(right)
		num=num|0xAA00;
	else
		num=num|0xBB00;

////**** HEAD LIGHT MONITORING ****////

		if(head)
			 num=num|0xAA0000;
		else
			num=num|0xBB0000;

		//STORED INTO A BYTEA
		frame.byteA=num; 

		////**** TEMPERATURE READING ****/////
		 adcval=adc_read(1);
		 vout=(adcval *3.3f)/1023.0f;
	     tempr=(vout-0.5f)/0.01f;
		
		num1=((int)tempr)%100;
		num1=((num1/10)<<4)|(num1%10); //CONVERTED TO HEX
		
		////**** POTENTIOAMETER READING ****////		
		adcval=adc_read(2);
		vout=(adcval *3.3f)/1023.0f;
		speed=(int)((vout*180)/3.3f);

		 

		speed=((speed/100)<<8)|(((speed%100)/10)<<4)|(speed%10); //CONVERTED TO HEX
		num1=(speed<<8)|num1;

	   	////**** PRINTING ON TERMINAL READING ****////
		sprintf(s,"%x ",speed);
		sprintf(s1,"%d \r\n",(int)tempr);
		uart0_tx_string("Speed ->");
		uart0_tx_string(s);
		uart0_tx_string("  Temp ->");
		uart0_tx_string(s1);

	    frame.byteB=num1;
		////**** DATA FRAME SENDING.....**** ////
	    can1_tx(frame);
	   delay_ms(500); //**** DATA FRAME SENDING....FOR EVREY 100ms
 }

}
