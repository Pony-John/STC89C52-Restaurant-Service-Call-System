
/*******************************************************************************
 �ļ���  �� ���ڽ�������.c
 ����    ��	��־ͬ  ������  ���Ϻ�
 ��дʱ�䣺 2017��5��27��
 ����    :  ���ļ�ʵ��ͨ����Ƭ���ӵ�Ƭ���������ݡ�
             ������ʹ�õľ�����11.0592MHz
***********************************************************************/

#include<stc15.h>
#include<intrins.h>

#define uchar unsigned char
#define uint  unsigned int


uchar uart_receive_number=0;    //ָʾ���ڽ�������
uchar num = 0;

extern void delay_1ms(uint x);

//��ʼ������3
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
* ���� : Com_Int()
* ���� : �����ж��Ӻ���
* ���� : �� * ��� : ��
***********************************************************************/
void Com3_Int(void) interrupt 17
{
  EA = 0;
  if(S3CON & 0x01){  //��Ӳ�����յ�һ������ʱ��S3RI����λ
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
		P07 = 1;          //�յ����������ݣ�Ϩ��ָʾ��
		uart_receive_number = 0;
	
	 }
}
