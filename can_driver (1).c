#include "header.h"

#define RBS (C2GSR & 1)
#define TCS ((C2GSR>>3)&1)
void can1_init(void)
{
 	PINSEL1|=0x0014000;				////**** P0.24 ->TD2 & P.23 ->RE2  ****////
	VPBDIV=1;						////**** PCLK=60MHz  ****////
	C2MOD=1	; 						 ////**** SELECT RESET MODE ****////
	C2BTR=0x001C001D; 				 ////**** 125 kbps   ****////
	AFMR=2;							/////**** ACCEPT ALL INCOMING MESSAGES ****////
	C2MOD=0;						 ////**** DESELECT RESET MODE ****////

}

void can1_tx(CAN1 v)
{
 	C2TID1=v.id;
	C2TFI1=v.dlc<<16;					 ////**** RTR=0 ****////
	if(v.rtr==0) 					 ////**** IF DATA FRAME  ****////
	{
	 
	 C2TDA1=v.byteA;
	 C2TDB1=v.byteB;
	}
	else
	{
	 	C2TFI1|=(1<<30);				////**** RTR=1 ****////
	}
	C2CMR=1|(1<<5);					////**** START TRANSMISSION & SELECT TXBUF1 ****////

	while(TCS==0);					////**** TX MONITORING ****////

}

void can1_rx(CAN1 *ptr)
{

 	while(RBS==0);
	ptr->id=C2RID;
	ptr->dlc=(C2RFS>>16)&0XF; 		   	////**** EXTRACT DLC ****////
	ptr->rtr=(C2RFS>>30)&0X1;				////**** EXTRACT RTR ****////


	if(ptr->rtr==0)						    ////**** IF DATA FRAME  ****////
	{
		ptr->byteA=C2RDA;
		ptr->byteB=C2RDB;
	}

	C2CMR=(1<<2);					  ////**** RELEASE RXBUF  ****////

}
