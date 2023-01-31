
/**************************************************************
    文件名：语音模块函数
      作者：陈志同  刘晓哲  张紫豪
  编写时间：2017年5月29日
可调用函数：  void  voice(char code *text) 
**************************************************************/


#include <stc15.h>        
#include <string.h> 
 
void  voice(char code *text) 
{    
/****************需要发送的文本**********************************/ 
         unsigned  char  headOfFrame[5];
         unsigned  char  length;  
         unsigned  char  ecc  = 0;              //定义校验字节
         unsigned  int i=0; 
         length = strlen(text);                 //需要发送文本的长度
 
/*****************发送过程**************************************/           
         headOfFrame[0] = 0xFD ;             //构造帧头FD
         headOfFrame[1] = 0x00 ;             //构造数据区长度的高字节
         headOfFrame[2] = length + 3;         //构造数据区长度的低字节
         headOfFrame[3] = 0x01 ;             //构造命令字：合成播放命令
/*****************带背景音乐**************************************/           
         headOfFrame[4] = 0x21 ;             //构造命令参数：编码格式为GBK

/*****************不带背景音乐**************************************/           
        //headOfFrame[4] = 0x01 ;             //构造命令参数：编码格式为GBK

         for(i = 0; i<5; i++)                   //依次发送构造好的5个帧头字节
         {  
             ecc=ecc^(headOfFrame[i]);         //对发送的字节进行异或校验    
             S3BUF = headOfFrame[i]; 
             while (!(S3CON & 0x02)) {;}               //等待发送中断标志位置位
             S3CON &= 0xFD;                        //发送中断标志位清零
         }

            for(i = 0; i<length; i++)           //依次发送待合成的文本数据
         {  
             ecc=ecc^(text[i]);                 //对发送的字节进行异或校验    
             S3BUF = text[i]; 
             while (!(S3CON & 0x02)) {;} 
             S3CON &= 0xFD;                
         }

           S3BUF=ecc;                            //最后发送校验字节
           while (!(S3CON & 0x02)) {;} 
		   S3CON &= 0xFD;   
        
}
