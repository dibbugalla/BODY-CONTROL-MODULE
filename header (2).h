#include <LPC21xx.H>
#include <stdio.h>
////**** STRUCTURE DECLARATION FOR CREAT FRAME ****////
typedef struct CAN1_MSG
{
   unsigned int id;
   unsigned char rtr;
   unsigned char dlc;
   unsigned int byteA;
   unsigned int byteB;

}CAN1;

////**** CAN_DRIVER HEADER  ****////
void can1_init(void);
void can1_tx(CAN1 v);
void can1_rx(CAN1 *ptr);


////**** UART0_DRIVER HEADER  ****////
void uart0_init(unsigned int baud);
 void uart0_tx(unsigned char data);
  void uart0_tx_string(unsigned char *ptr);

////**** TIMRR HEADER  ****////
void delay_ms(unsigned int ms);

 ////**** ADC_DRIVER HEADER  ****////
 void adc_init(void);
 int adc_read(int channel_num);

////**** EXTERNAL_INTERRUPT HEADER  ****////
void configVicExt0(void);
void configVicExt1(void);
void configVicExt2(void);
void  enableExtIntr2(void);
void  enableExtIntr1(void);
void  enableExtIntr0(void);



