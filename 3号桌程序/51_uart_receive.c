
/*******************************************************************************
 文件名  ： 串口接收试验.c
 作者    ：	陈志同  刘晓哲  张紫豪
 编写时间： 2017年5月27日
 描述    :  该文件实现通过单片机从单片机接收数据。
             该试验使用的晶振是11.0592MHz
***********************************************************************/

#include<stc15.h>
#include<intrins.h>

#define uchar unsigned char
#define uint  unsigned int


uchar uart_receive_number=0;    //指示串口接收数据
uchar num = 0;

extern void delay_1ms(uint x);

//初始化串口3
void UartInit_1(void)		//9600bps@11.0592MHz
{
	
	S3CON = 0x10;	
	S3CON |= 0x40;	
	T4T3M |= 0x02;	
	T3L = 0xE0;		
	T3H = 0xFE;		
	T4T3M |= 0x08;	
	IE2  =0x08;	    	 
	EA   = 1;

}

/********************************************************************
* 名称 : Com_Int()
* 功能 : 串口中断子函数
* 输入 : 无 * 输出 : 无
***********************************************************************/
void Com3_Int(void) interrupt 17
{
  EA = 0;
  if(S3CON & 0x01){  //当硬件接收到一个数据时，S3RI会置位
    S3CON &= 0xFE;
    uart_receive_number = S3BUF;   
  }

  EA = 1;
}

void receive()
{
	if(uart_receive_number) 
	{
		if(uart_receive_number == 2||uart_receive_number == 3||uart_receive_number == 4||uart_receive_number == 6)
		P07 = 1;          //收到主机的数据，熄灭指示灯
		uart_receive_number = 0;
	
	 }
}
