/*adc-driver*/

//#include <LPC21xx.H>
#include "header.h"

void adc_init(void)
{

	PINSEL1 |=0x15400000;//p0.27 p0.28 p0.29 p0.30
	ADCR=0x00200400; //no.of channel selected, VPBCLK=4  ,PDN=1 ,

}

#define DONE ((ADDR>>31)&1)

int adc_read(int channel_num)
{
    unsigned int result=0;
	ADCR |=(1<<channel_num); //channel no. select
	ADCR |=(1<<24);//start conversation
	while(DONE==0);//monitoring the done flag for data
	ADCR ^=(1<<24);//stop adc conversation
	ADCR^=(1<<channel_num);	 //channel no. diselect
	result=(ADDR>>6)&0x3FF;// data stored in result var
	return result;
}

