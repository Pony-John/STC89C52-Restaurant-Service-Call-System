
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

uchar uart_receive_buffer[30];  //从串口接收的数据
uchar uart_receive_number = 0;    //指示串口接收个数
uchar num = 0;
uchar uart_receive_data = 0;
char k;

char code text[6][25]=
	{
		{"[v10][m5]1号餐桌需要服务\0"},
		{"[v10][m5]2号餐桌需要服务\0"},
		{"[v10][m5]3号餐桌点餐\0"},
		{"[v10][m5]3号餐桌酒水\0"},
		{"[v10][m5]3号餐桌催菜\0"},
		{"[v10][m5]3号餐桌买单\0"}
	};

uchar code disc[7][17]=
	{
		{"餐厅无线呼叫系统\0"},
		{"1 号餐桌需要服务\0"},
		{"2 号餐桌需要服务\0"},
		{"3 号餐桌    点餐\0"},
		{"3 号餐桌    酒水\0"},
		{"3 号餐桌    催菜\0"},
		{"3 号餐桌    买单\0"}
	};
extern void delay_1ms(uint x);
extern void voice(char code *text);
extern void delay_1ms(uint x);
extern void lcd_init();
extern void lcd_write(unsigned char line, unsigned char code * dis) reentrant;
extern void INT0_ISR();


/********************************************************************
* 名称 : Com_Int()
* 功能 : 串口中断子函数
* 输入 : 无 * 输出 : 无
***********************************************************************/
void Com2_Int(void) interrupt 8
{
	char i = 0;
	char flag = 0;
  	if(S2CON & 0x01)	//当硬件接收到一个数据时，S2RI会置位
	{  
    	S2CON &= 0xFE;
		uart_receive_data = S2BUF;

		for(i = 0; i < uart_receive_number; i++)
		{
		  	if(uart_receive_data == uart_receive_buffer[i])
				{
					flag = 1;
					break;
				}
		}
		if (!flag)
		{
    		uart_receive_buffer[uart_receive_number] = uart_receive_data; 
    		uart_receive_number++;
		}
  	}
  
}

void display() reentrant
{
	while(!uart_receive_number);
	if(uart_receive_number) 
	{		
  		for(num = 0,k = 2;(num<uart_receive_number) && (num<3);num++,k++)
  		{
			lcd_write(k,disc[uart_receive_buffer[num]]);				
   		 //串口有数据时，可以执行数据
  		}
	
	 }
}

void voice_all()
{
	if(uart_receive_number) 
	{
		
  		for(num = 0,k = 2;(num<uart_receive_number) && (num<3);num++,k++)
  		{					
			voice(text[uart_receive_buffer[num]-1]);
			delay_1ms(12000);						
   		 //串口有数据时，可以执行数据
  		}
	
	 }
}
