
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

uchar uart_receive_buffer[30];  //�Ӵ��ڽ��յ�����
uchar uart_receive_number = 0;    //ָʾ���ڽ��ո���
uchar num = 0;
uchar uart_receive_data = 0;
char k;

char code text[6][25]=
	{
		{"[v10][m5]1�Ų�����Ҫ����\0"},
		{"[v10][m5]2�Ų�����Ҫ����\0"},
		{"[v10][m5]3�Ų������\0"},
		{"[v10][m5]3�Ų�����ˮ\0"},
		{"[v10][m5]3�Ų����߲�\0"},
		{"[v10][m5]3�Ų�����\0"}
	};

uchar code disc[7][17]=
	{
		{"�������ߺ���ϵͳ\0"},
		{"1 �Ų�����Ҫ����\0"},
		{"2 �Ų�����Ҫ����\0"},
		{"3 �Ų���    ���\0"},
		{"3 �Ų���    ��ˮ\0"},
		{"3 �Ų���    �߲�\0"},
		{"3 �Ų���    ��\0"}
	};
extern void delay_1ms(uint x);
extern void voice(char code *text);
extern void delay_1ms(uint x);
extern void lcd_init();
extern void lcd_write(unsigned char line, unsigned char code * dis) reentrant;
extern void INT0_ISR();


/********************************************************************
* ���� : Com_Int()
* ���� : �����ж��Ӻ���
* ���� : �� * ��� : ��
***********************************************************************/
void Com2_Int(void) interrupt 8
{
	char i = 0;
	char flag = 0;
  	if(S2CON & 0x01)	//��Ӳ�����յ�һ������ʱ��S2RI����λ
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
   		 //����������ʱ������ִ������
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
   		 //����������ʱ������ִ������
  		}
	
	 }
}
