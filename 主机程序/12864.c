
/**************************************************************
    文件名：12864液晶函数
      作者：陈志同  刘晓哲  张紫豪
  编写时间：2017年5月27日
**************************************************************/


#include <stc15.h>
#include <intrins.h>
#include <stdlib.h>

#define uint  unsigned int 
#define uchar unsigned char
#define LCD_data P2				//定义数据管脚口P2
							 //定义12864所用到的管脚口
sbit LCD_RS=P4^1;					  		//寄存器选择输入  H数据 L命令
sbit LCD_RW=P4^2;							  //液晶读写控制  H读  L写
sbit LCD_EN=P4^4;
sbit LCD_PSB=P4^5;


uchar code dis1[]={"餐厅无线呼叫系统"};
uchar code dis2[]={"1 号餐桌需要服务"};
uchar code dis3[]={"2 号餐桌需要服务"};
uchar code dis4[]={"3 号餐桌    点餐"};
uchar code dis5[]={"3 号餐桌    酒水"};
uchar code dis6[]={"2 号餐桌    催菜"};
uchar code dis7[]={"3 号餐桌    买单"};


void delay_1ms(uint x)  //12864所用1ms延时
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
void write_cmd(uchar cmd)		//写1字节指令到12864
{
	LCD_RS=0;
	LCD_RW=0;
	LCD_EN=0;
	P2=cmd;
	delay_1ms(5);
	LCD_EN=1;
	delay_1ms(5);
	LCD_EN=0;
}

void write_dat(uchar dat)		//写1字节数据到12864
{
	LCD_RS=1;
	LCD_RW=0;
	LCD_EN=0;
	P2=dat;
	delay_1ms(5);
	LCD_EN=1;
	delay_1ms(5);
	LCD_EN=0;
}

void lcd_pos(uchar X,uchar Y)//设定显示位置
{
	uchar pos;
	if(X==1)
		{X=0x80;}
	else if(X==2)
		{X=0x90;}
	else if(X==3)
		{X=0x88;}
	else if(X==4)
		{X=0x98;}
	pos=X+Y;
	write_cmd(pos);
}

void lcd_init()		   //初始化设定
{
	uchar i;
	P4M1=0;P4M0=0;
	P2M0=0;P2M1=0;
	delay_1ms(5);
    LCD_PSB=1;    //并口模式
	write_cmd(0x30);
	delay_1ms(5);
	write_cmd(0x0c);
	delay_1ms(5);
	write_cmd(0x01);
	delay_1ms(5);
	i=0;
	delay_1ms(10);	
	lcd_pos(1,0);
	while(dis1[i]!='\0')
	{
		write_dat(dis1[i]);
		i++;
	}
}

/****************************************************************/
void lcd_write(unsigned char line, unsigned char code * dis)  reentrant
{
    uchar i;
	lcd_pos(line,0);	
	i=0;
	while((dis[i]!='\0')&&(i < 16))
	{
		write_dat(dis[i]);
		i++;
	}	
}
