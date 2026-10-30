#ifndef __OLED_H
#define __OLED_H
#include "stm32f1xx_hal.h"

#define  u8 unsigned char 
#define  u32 unsigned int 
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
#define OLED_MODE 0


#define ADDR 0x78
#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64

void SDA_ON(void);
void SDA_OFF(void);
void SCL_ON(void);
void SCL_OFF(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_Wait_Ack(void);//准确来说这是第九个与应答相连的额外脉冲
void Write_IIC_Byte(unsigned char IIC_Byte);
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void OLED_WR_Byte(unsigned char dat, unsigned char cmd);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void fill_picture(unsigned char fill_Data);
void oled_init(void);
void OLED_Clear(void);
void OLED_Init(void);
void OLED_ShowString(u8 x, u8 y, u8 *chr,u8 Char_Size);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2);

void OLED_PrintCircle_ol315(u8 x, u8 y, u8 Char_Size);
void OLED_PrintCircle_ol0(u8 x, u8 y, u8 Char_Size);
void OLED_PrintCircle_ol45(u8 x, u8 y, u8 Char_Size);
void OLED_PrintCircle_ol225(u8 x, u8 y, u8 Char_Size);
void OLED_PrintCircle(u8 x, u8 y,u8 Char_Size);
char QEOOU_Answer(double a, double b, double c, unsigned char re);
void OLED_Round(double m, double n, unsigned char r);
void draw_circle(u8 x0, u8 y0, u8 r); //圆心(x0,y0),半径r
void Bresenham_Circle(int xc, int yc, int r);;
void OLED_PrintCircle2(void);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
//unsigned int pow(u8 x, u8 y);
void OLED_PrintCircle_ol90(u8 x, u8 y, u8 Char_Size);
void PrintPoint(u8 x, u8 y);
void OLED_Show(void);
#endif
