#include <LPC21xx.H>
#include "header.h"
void uart0_init(unsigned int baud)
{
	int a[]={15,60,30,15,15};
	unsigned int pclk=a[VPBDIV%4]*1000000;
	unsigned int result=0;
	result=pclk/(16*baud);
	
	PINSEL0 |=0x05;
	U0LCR=0x83;
	U0DLL=result &0xFF;
	U0DLM=(result>>8)&0xFF;
	U0LCR=0x03;	

}
void uart0_tx(unsigned char data)
{
	U0THR=data;
	while(((U0LSR>>5)&1)==0);
}

void uart0_tx_string(char *ptr)
{
	while(*ptr)
	{
	  uart0_tx(*ptr);
	  ptr++;
	}
}
unsigned char uart0_rx(void)
{
	while((U0LSR&1)==0);
	return U0RBR;
}
void uart0_rx_string(char *ptr,int max_bytes)
{
	int i;
	for(i=0;i<max_bytes;i++)
	{
	  	while((U0LSR&1)==0);
		ptr[i]=U0RBR;
		uart0_tx(ptr[i]);
		if(ptr[i]=='\r')
			break;
	}
		ptr[i]='\0';
}
/*void uart0_tx_float(float f)
{
	int n=f;
	float g=n-f;
	uart0_i_to_a(n);
	if(g!=0)
		 uart0_i_to_a(g);
   int c,c1,i,n,k;
	char a[30];
 	long long int num;
	if(f==0)
	{
	 	uart0_tx('0');
		return;
	
	}
	if(f<0)
	{
		uart0_tx('-');
		f=-f;
	}
	n=f;
	for(k=0;(n%10==0);k++,n/=10);
	num=f*1000000;
	for(c=0;(num%10==0);c++,num/=10);
	c=6-c;
	c1=c;
	i=0;
	while(num || c1>=0)
	{
		 if(i==c)
	   {	  	
		while(k!=0)
		{
		a[i++]='0';
		k--;
		}
				  a[i++]='.';
	    }
	   	  a[i++]=num%10+48;
		  num/=10;
		  c1--;
	}

	for(--i;i>=0;i--)
	{
		uart0_tx(a[i]);
	}
	if(a[0]=='.')
		uart0_tx('0');
	}	*/
  
 
 double uart0_float(char *ptr)
 {	
 		int a[]={10,100,1000,10000,100000,1000000};
 		int f=1,c=0,i;
 		int d1=0,temp=0;
		double result=0,d2=0;
 	if(ptr[0]=='-' || ptr[0]=='+')
	{
	  i=1;
	}
	else
		i=0;
	for( ;ptr[i];i++)
	{
	   if(f)
	   {
	   	  if(ptr[i]!='.')
		  {
		   	   d1=d1*10+(ptr[i]-48);
		  
		  }
		  else
		  {
		  	f=0;
		  }
	   
	   }
	   else
	   {	
	   	 if(ptr[i]!='.')
		  {
		   	   d2=d2*10+(ptr[i]-48);
		  }
	   		
	   }
	}

 	temp=d2;
	for(c=0;temp;temp/=10,c++);
	d2=d2/a[c-1];
	result=d1+d2;
	return result;


 }
 int uart0_int(char*ptr)
 {
 	int n=0,i;
 	if(ptr[0]=='-'||ptr[0]=='+')
		i=1;
	else
		i=0;
	for( ;ptr[i];i++)
	{
		 n=n*10+ptr[i]-48;
	
	}
 	  if(ptr[0]=='-')
	    n=-n;
	 return n;
 }
void uart0_i_to_a(int num)
{
	char s[20]={0};
	int i=0;
	if(num==0)
	{
		 uart0_tx('0');
		 return;
	} 
	if(num<0)
	{
	 	uart0_tx('-');
		num=-num;
	}

	
	for(i=0;num;num/=10)
	{
		s[i++]=(num%10)+48;
	}
	//uart0_tx_string(s);
	for(--i;i>=0;i--)
	{
		uart0_tx(s[i]);
	}		
}
 






