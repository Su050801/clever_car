#include "usart1.h"
#include "usart.h"
#include <stdio.h>

uint8_t RxBuffer[1];//串口接收缓冲
uint16_t RxLine = 0;//指令长度
uint8_t DataBuff[200];//指令内容
float  a1;
float Get_Data(void)
{
    uint8_t data_Start_Num = 0; // 记录数据位开始的地方
    uint8_t data_End_Num = 0; // 记录数据位结束的地方
    uint8_t data_Num = 0; // 记录数据位数
    uint8_t minus_Flag = 0; // 判断是不是负数
    float data_return = 0; // 解析得到的数据
    for(uint8_t i=0;i<200;i++) // 查找等号和感叹号的位置
    {
        if(DataBuff[i] == '=') data_Start_Num = i + 1; // +1是直接定位到数据起始位
        if(DataBuff[i] == '!')
        {
            data_End_Num = i - 1;
            break;
        }
    }
    if(DataBuff[data_Start_Num] == '-') // 如果是负数
    {
        data_Start_Num += 1; // 后移一位到数据位
        minus_Flag = 1; // 负数flag
    }
    data_Num = data_End_Num - data_Start_Num + 1;
    if(data_Num == 4) // 数据共4位
    {
        data_return = (DataBuff[data_Start_Num]-48)  + (DataBuff[data_Start_Num+2]-48)*0.1f +
                (DataBuff[data_Start_Num+3]-48)*0.01f;
    }
    else if(data_Num == 5) // 数据共5位
    {
        data_return = (DataBuff[data_Start_Num]-48)*10 + (DataBuff[data_Start_Num+1]-48) + (DataBuff[data_Start_Num+3]-48)*0.1f +
                (DataBuff[data_Start_Num+4]-48)*0.01f;
    }
    else if(data_Num == 6) // 数据共6位
    {
        data_return = (DataBuff[data_Start_Num]-48)*100 + (DataBuff[data_Start_Num+1]-48)*10 + (DataBuff[data_Start_Num+2]-48) +
                (DataBuff[data_Start_Num+4]-48)*0.1f + (DataBuff[data_Start_Num+5]-48)*0.01f;
    }
    if(minus_Flag == 1)  data_return = -data_return;

    return data_return;
}
void USART_PID_Adjust(void )
{
   float data_Get = Get_Data(); // 存放接收到的数据
   //printf("data=%.2f\r\n",data_Get);
    
        if(DataBuff[0]=='p' && DataBuff[1]=='p') // 位置环P
		{
		a1 = Get_Data();
		}
		 if(DataBuff[0]=='d' && DataBuff[1]=='d') // 位置环P
		{
		a1 = Get_Data();
		}
        
          
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    if(UartHandle->Instance==USART1)
    {
        RxLine++;                      //每接收到一个数据，进入回调数据长度加1
        DataBuff[RxLine-1]=RxBuffer[0];  //把每次接收到的数据保存到缓存数组
        if(RxBuffer[0]==0x21)            //接收结束标志位，这个数据可以自定义，根据实际需求，这里只做示例使用，不一定是0x21
        {
            //printf("RXLen=%d\r\n",RxLine);
            for(int i=0;i<RxLine;i++)
            //printf("UART DataBuff[%d] = %c\r\n",i,DataBuff[i]);
            USART_PID_Adjust();
            memset(DataBuff,0,sizeof(DataBuff));  //清空缓存数组
            RxLine=0;  //清空接收长度
        }
        RxBuffer[0]=0;
        HAL_UART_Receive_IT(&huart1, (uint8_t *)RxBuffer, 1); //每接收一个数据，就打开一次串口中断接收，否则只会接收一个数据就停止接收
    }
}

