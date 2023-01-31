#include <stc15.h>
#include <intrins.h>
#include <stdlib.h>
#include <string.h> 

#define uint  unsigned int 
#define uchar unsigned char

extern uchar uart_receive_buffer[30];  //从串口接收的数据
extern uchar uart_receive_number;      //指示串口接收个数
extern uchar num;

extern void UartInit_1(void);          //串口3初始化函数声明
extern void delay_1ms(uint x);	       //延时初始化声明
extern void receive();				   //接收函数声明
extern void send_1(unsigned char p);				   //发送函数声明

void main()
{
	UartInit_1();
	P0M0=0;
	P0M1=0;
	while(1)
	{
		if(P06 == 0)
		{
			delay_1ms(30);
			if(P06 == 0)
			{
				P04=0;
				send_1(2);
				while(!P06);
			}
		}
		receive();
	}
}
void delay_1ms(uint x)  //1ms延时函数
{
	uint a,b;
	for(a=0;a<x;a++)
	{
		b=0;
		while(b<200)
		{
			_nop_();
			b++;
		}
	}
}

