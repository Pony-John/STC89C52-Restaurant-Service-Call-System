
/**************************************************************
    �ļ�����12864Һ������
      ���ߣ���־ͬ  ������  ���Ϻ�
  ��дʱ�䣺2017��5��27��
**************************************************************/


#include <stc15.h>
#include <intrins.h>
#include <stdlib.h>

#define uint  unsigned int 
#define uchar unsigned char
#define LCD_data P2				//�������ݹܽſ�P2
							 //����12864���õ��Ĺܽſ�
sbit LCD_RS=P4^1;					  		//�Ĵ���ѡ������  H���� L����
sbit LCD_RW=P4^2;							  //Һ����д����  H��  Lд
sbit LCD_EN=P4^4;
sbit LCD_PSB=P4^5;


uchar code dis1[]={"�������ߺ���ϵͳ"};
uchar code dis2[]={"1 �Ų�����Ҫ����"};
uchar code dis3[]={"2 �Ų�����Ҫ����"};
uchar code dis4[]={"3 �Ų���    ���"};
uchar code dis5[]={"3 �Ų���    ��ˮ"};
uchar code dis6[]={"2 �Ų���    �߲�"};
uchar code dis7[]={"3 �Ų���    ��"};


void delay_1ms(uint x)  //12864����1ms��ʱ
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
void write_cmd(uchar cmd)		//д1�ֽ�ָ�12864
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

void write_dat(uchar dat)		//д1�ֽ����ݵ�12864
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

void lcd_pos(uchar X,uchar Y)//�趨��ʾλ��
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

void lcd_init()		   //��ʼ���趨
{
	uchar i;
	P4M1=0;P4M0=0;
	P2M0=0;P2M1=0;
	delay_1ms(5);
    LCD_PSB=1;    //����ģʽ
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
