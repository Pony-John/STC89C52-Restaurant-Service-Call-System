#include <stc15.h>
#include <intrins.h>
#include <stdlib.h>
#include <string.h> 

#define uint  unsigned int 
#define uchar unsigned char

extern uchar uart_receive_buffer[30];  //�Ӵ��ڽ��յ�����
extern uchar uart_receive_number;      //ָʾ���ڽ��ո���
extern uchar num;

extern void UartInit_1(void);          //����3��ʼ����������
extern void delay_1ms(uint x);	       //��ʱ��ʼ������
extern void receive();				   //���պ�������
extern void send_1(unsigned char p);				   //���ͺ�������

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
void delay_1ms(uint x)  //1ms��ʱ����
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

