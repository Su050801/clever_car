#include "main.h"
#include "usart.h"
#include "tim.h"
#include "stm32f1xx_it.h"
#include "string.h"
extern uint8_t RxBuffer[1];//串口接收缓冲
extern uint16_t RxLine;//指令长度
extern uint8_t DataBuff[200];//指令内容

