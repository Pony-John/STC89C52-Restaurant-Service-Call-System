
/**************************************************************
    文件名：餐厅无线呼叫系统主函数
      作者：陈志同  刘晓哲  张紫豪
  编写时间：2017年5月30日
**************************************************************/

#include <stc15.h>
#include <intrins.h>
#include <stdlib.h>
#include <string.h> 

#define uint  unsigned int 
#define uchar unsigned char


extern uchar uart_receive_buffer[30];  //从串口接收的数据
extern uchar uart_receive_number;    //指示串口接收个数
extern uchar num;
extern uchar k;

extern void lcd_init();
extern void delay_1ms(uint x);
extern void voice_all();
extern void display() reentrant;
extern void send(unsigned char p);
extern void lcd_write(unsigned char line, unsigned char code * dis) reentrant;
void C51_Init(void);

char code a[] = {"                \0"};

void main()
{
	P02 = 0;
	C51_Init();
	
	lcd_init();
	while(1)
	{
		display();
		voice_all();		
	}
}

void INT0_ISR() interrupt 0
{
	if(P32 == 0)
	{
		delay_1ms(30);
		if(P32 == 0)
		{
			char i = 0;
			EX0 = 0;
			if(uart_receive_number)
			{
				P02 = 1;
				delay_1ms(1000);
				P02 = 0;
				lcd_write(2,a);
				lcd_write(3,a);
				lcd_write(4,a);
				send(uart_receive_buffer[0]);
				for (; i < uart_receive_number; i++)
				{
					uart_receive_buffer[i] = uart_receive_buffer[i + 1];
				}
				uart_receive_number--;	
				display();
			}
			EX0 = 1;			
		}
		while(!P32);
	}

}

void C51_Init(void)
{
	//Uart_2
	S2CON = 0x50;	
	AUXR |= 0x04;	
	T2L = 0xE0;		
	T2H = 0xFE;		
	AUXR |= 0x10;
	IE2  = 0x01;
	IP2 = 0x01;
	//Uart_3
	S3CON = 0x10;	
	S3CON |= 0x40;	
	T4T3M |= 0x02;	
	T3L = 0xE0;		
	T3H = 0xFE;		
	T4T3M |= 0x08;			    	 
	EA = 1;
	//INT0
	IT0 = 1;
	EX0 = 1;	
}




