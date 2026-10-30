#include "oled.h"
#include "oledfont.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "math.h"
#include "bmp.h"
void SDA_ON(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
}
void SDA_OFF(void) 
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);
}
void SCL_ON(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);
}
void SCL_OFF(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);
}

void IIC_Start(void)
{
	SCL_ON();
	SDA_ON();
//	IIC_Delay_4us();
	SDA_OFF();
//	IIC_Delay_4us();
	SCL_OFF();
}

void IIC_Stop(void)
{
		SCL_OFF();
//    SDA=0;
//    IIC_Delay_4us();
    SCL_ON();
    SDA_ON();
//    IIC_Delay_4us();
}

void IIC_Wait_Ack(void)//准确来说这是第九个与应答相连的额外脉冲
{
	SCL_ON();
	SCL_OFF();
}

void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m, da;
	da = IIC_Byte;
	SCL_OFF();//此处是为了清除其他程序对此的影响
//	SDA = 0;
	for ( i = 0; i < 8; i++)
	{
		m = da;
		m = m&0x80;
		if(m == 0x80)
		{
			SDA_ON();
		}
		else
		{
			SDA_OFF();
		}
		da = da << 1;
		SCL_ON();//用它作为跳变沿发送m中的数据信号
		SCL_OFF();
	}
}

void Write_IIC_Command(unsigned char IIC_Command)
{
	IIC_Start();
	Write_IIC_Byte(0x78);
	IIC_Wait_Ack();
	Write_IIC_Byte(0x00);
	IIC_Wait_Ack();
	Write_IIC_Byte(IIC_Command);
	IIC_Wait_Ack();
	IIC_Stop();
}

void Write_IIC_Data(unsigned char IIC_Data)
{
	IIC_Start();
	Write_IIC_Byte(0x78);
	IIC_Wait_Ack();
	Write_IIC_Byte(0x40);
	IIC_Wait_Ack();
	Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();
	IIC_Stop();
}

void OLED_WR_Byte(unsigned char dat, unsigned char cmd)
{
	if(cmd)
	{
		Write_IIC_Data(dat);
	}
	else
	{
		Write_IIC_Command(dat);
	}
}


void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m = 0; m < 8; m++)
	{
		OLED_WR_Byte(0xb0+m,0);//page0-page1
		OLED_WR_Byte(0x00,0);//low column start address
		OLED_WR_Byte(0x10,0);//high column start address
		for (n = 0; n < 128; n++)
		{
			OLED_WR_Byte(fill_Data,0);
		}
	}
}



void OLED_Set_Pos(unsigned char x, unsigned char y)
{
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4) | 0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD);
}

void OLED_Display_On(void)
{
	OLED_WR_Byte(0x8d,OLED_CMD);//SET DCDC命令
	OLED_WR_Byte(0x14,OLED_CMD);//DCDC ON
	OLED_WR_Byte(0xaf,OLED_CMD);//DISPLAY ON
}

void OLED_Display_off(void)
{
	OLED_WR_Byte(0x8d,OLED_CMD);//SET DCDC命令
	OLED_WR_Byte(0x10,OLED_CMD);//DCDC OFF
	OLED_WR_Byte(0xae,OLED_CMD);//DISPLAY OFF
}

void OLED_Clear(void)
{
	u8  i,n;
	for(i = 0; i < 8; i++)
	{
		OLED_WR_Byte(0xb0+i,OLED_CMD); //设置页地址（0~7）
		OLED_WR_Byte(0x00,OLED_CMD);//设置显示位置—列低地址
		OLED_WR_Byte(0x10,OLED_CMD); //设置显示位置—列高地址   
		for(n = 0; n < 128; n++) OLED_WR_Byte(0, OLED_DATA);
	}//更新显示
}

void OLED_On(void)
{
	u8 i, n;
	for (i = 0; i < 8; i++)
	{
		OLED_WR_Byte(0xb0+i, OLED_CMD);//设置页地址（0~7）
		OLED_WR_Byte(0x00,OLED_CMD);//设置显示位置—列低地址
		OLED_WR_Byte(0x10,OLED_CMD); //设置显示位置—列高地址   
		for(n = 0; n < 128; n++)OLED_WR_Byte(1,OLED_DATA);
	}//更新显示
}
//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
//void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
//{      	
//	unsigned char c=0,i=0;	
//		c=chr-' ';//得到偏移后的值			
//		if(x>Max_Column-1){x=0;y=y+2;}
//		if(Char_Size ==16)
//			{
//			OLED_Set_Pos(x,y);	
//			for(i=0;i<8;i++)
//			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
//			OLED_Set_Pos(x,y+1);
//			for(i=0;i<8;i++)
//			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
//			}
//			else {	
//				OLED_Set_Pos(x,y);
//				for(i=0;i<6;i++)
//				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
//				
//			}
//}
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{
	unsigned char i,c;	
		c=chr-' ';//得到偏移后的值			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte((unsigned char )code_F8X16[c*16+i],(unsigned char )OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte((unsigned char )code_F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_Byte(code_F6x8[c][i],OLED_DATA);
				
			}
}
//m^n函数
u32 oled_pow(u8 m, u8 n)
{
	u32 result = 1;
	while (n--) result*= m;
	return result;
}
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{
	u8 t, temp;
	u8 enshow = 0;
	for(t = 0; t < len; t++)
	{
		temp = (num/oled_pow(10,len-t-1))%10;//该函数计算的是数据相应的位
		if (enshow == 0 && t < (len-1))
		{
			if(temp == 0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);//改行函数会在没有位数据时留出空白位置
				continue;
			}
			else enshow = 1;
		}
		OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2);//这里就显示数字数据了
	}
}

void OLED_ShowString(u8 x, u8 y, u8 *chr, u8 Char_Size)
{
	unsigned char j = 0;
	while (chr[j] != '\0')
	{
		OLED_ShowChar(x,y,chr[j],Char_Size);
		x += 8;
		if ( x>128) { x = 0; y += 2;}
		j++;
	}
}
//初始化SSD1306					    
void OLED_Init(void)
{ 	
 
	OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  
	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	OLED_WR_Byte(0x81,OLED_CMD); // contract control
	OLED_WR_Byte(0xFF,OLED_CMD);//--128   
	OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap 
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00,OLED_CMD);//
	
	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_WR_Byte(0x80,OLED_CMD);//
	
	OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
	OLED_WR_Byte(0x05,OLED_CMD);//
	
	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1,OLED_CMD);//
	
	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x12,OLED_CMD);//
	
	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x30,OLED_CMD);//
	
	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);//
	
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
//	OLED_DrawBMP(0,0, 64,8,BMP1);
}  
////注意OLED还有硬件配置
//void oled_init(){
//	iic_initBus();
//	oled_sendCmd(0xAE); /*display off打开开关*/
//	oled_sendCmd(0x00); /*set lower column address设置低一点的页开始地址*/
//	oled_sendCmd(0x10); /*set higher column address设置高一点的页开始地址*/
//	oled_sendCmd(0x00); /*set display start line列开始地址*/
//	oled_sendCmd(0xB0); /*set page address设置页开始地址模式*/
//	oled_sendCmd(0x81); /*contract control设置对比度*/
//	oled_sendCmd(0xcf); /*128？*/
//	oled_sendCmd(0xA1); /*set segment remap设置Segment的重映射*/
//	oled_sendCmd(0xA6); /*normal / reverse正常显示*/
//	oled_sendCmd(0xA8); /*multiplex ratio默认*/
//	oled_sendCmd(0x3F); /*duty = 1/64*/
//	oled_sendCmd(0xC8); /*Com scan direction设置扫描方向*/
//	oled_sendCmd(0xD3); /*set display offset设置显示偏移:偏移量设置到最大是为了数据可以在全局显示*/
//	oled_sendCmd(0x00);//设置滚动命令为无
//	oled_sendCmd(0xD5); /*set osc division设置展示时钟*/
//	oled_sendCmd(0x80);/*设置高一点的页开始地址*/
//	oled_sendCmd(0xD9); /*set pre-charge period默认*/
//	oled_sendCmd(0xf1);//设置Pre-charge Period Data Set
//	oled_sendCmd(0xDA); /*set COM pins硬件配置*/
//	oled_sendCmd(0x12);//Alternative Mode Set让全部的8角控制
//	oled_sendCmd(0xdb); /*set vcomh默认*/
//	oled_sendCmd(0x40);//40h表	示64,这表示设置开始行(这是硬件确定的)
////	oled_sendCmd(0x8d); /*set charge pump disable固定供电(可去)*/
//	oled_sendCmd(0x14);//设置本来供电DB
//	oled_sendCmd(0xAF); /*display ON关闭开关*/ 
//	oled_sendCmd(0xA4);//开启全部显示
//}

///*预计增加命令模式
//AEdisplay OFF睡眠模式*/

void OLED_PrintCircle_ol315(u8 x, u8 y, u8 Char_Size)
{
	unsigned char i,c,j;
	if(x > Max_Column-1)
			{x=0;y=y+2;}
	c=Char_Size/8;
	for(i = 0;i < c;i++)
	{
		for(j=0;j < 8;j++)
		{
			OLED_Set_Pos(x+j,y);
			OLED_WR_Byte((unsigned char)code_Circle[j],(unsigned char)OLED_DATA);
		}
		if (x <= 128 && y <=7)
		{
			y++;
			x=x+8;
		}
	}
}

void OLED_PrintCircle_ol0(u8 x, u8 y, u8 Char_Size)
{
	unsigned char i,c,j;
	if(x > Max_Column-1)
			{x=0;y=y+2;}
	c=Char_Size/8;
	for(i = 0;i < c;i++)
	{
		for(j=0;j < 8;j++)
		{
			OLED_Set_Pos(x+j,y);
			OLED_WR_Byte((unsigned char)code_Circle[0],(unsigned char)OLED_DATA);
		}
		if (x <= 128 && y <=7)
		{
			x=x+8;
		}
	}
}

void OLED_PrintCircle_ol45(u8 x, u8 y, u8 Char_Size)
{
	unsigned char i,c,j;
	if(x > Max_Column-1)
			{x=0;y=y+2;}
	c=Char_Size/8;
	x = x-1;
	for(i = 0;i < c;i++)
	{
		for(j=0;j < 8;j++)
		{
			OLED_Set_Pos(x+j,y);
			OLED_WR_Byte((unsigned char)code_Circle[7-j],(unsigned char)OLED_DATA);
		}
		if (x <= 128 && y >=0)
		{
			x=x+8;
			y = y-1;
		}
	}
}

void OLED_PrintCircle_ol225(u8 x, u8 y, u8 Char_Size)
{
	unsigned char i,c,j;
	if(x > Max_Column-1)
			{x=0;y=y+2;}
	c=Char_Size/8;
	for(i = 0;i < c;i++)
	{
		for(j=0;j < 8;j++)
		{
			OLED_Set_Pos(x-j,y);
			OLED_WR_Byte((unsigned char)code_Circle[j],(unsigned char)OLED_DATA);
		}
		if (x <= 128 && y <=7)
		{
			y++;
			x=x-8;
		}
	}
}

void OLED_PrintCircle(u8 x, u8 y,u8 Char_Size)//半径默认为32
{
	unsigned char i,j,c;
	unsigned char tempx,tempy;
	tempx = x;
	tempy = y;
	if(x > Max_Column-1)
			{x=0;y=y+2;}
	c = Char_Size/8;
	//左半圆
	for(i = 0; i < 3;i++)
	{
		for(j=0;j < 8;j++)
		{
			OLED_Set_Pos(x-j,y+c-i);
			OLED_WR_Byte((unsigned char)code_Circle[7-j],(unsigned char)OLED_DATA);
			x=x-1;
		}

		if (x >= 0 && y <=7)
		{
			y--;
		}
	}
}

char QEOOU_Answer(double a, double b, double c, unsigned char re)
{
	//ax^2+bx+c=0;
	double w;
	w = b*b - 4*a*c;
	if(w < 0)
	{
		//这个方程无解
	}
	else if(w == 0)//这个方程只有这一个解
	{
		return -b/(2*a);
	}
	else//这个方程有两个不一样的解
	{
		if(re == 0)
		{
			return (-b+sqrt(w))/(2*a);
		}
		else if(re == 1)
		{
			return (-b-sqrt(w))/(2*a);
		}
	}
	return 0;
}

void OLED_Round(double m, double n, unsigned char r)
{
	char i, y1, y2;
	char x00 = sqrt(2)*r/2;
	double c;
	n = n*8;
	for(i = m; i <= m+x00;i++)//通过x画y法
	{
		c = (n*n - r*r + i*i - 2*m*i + m*m);
		y1 = (QEOOU_Answer(1,-(2*n), c, 1))/8;
		y2 = (QEOOU_Answer(1,-(2*n), c, 0))/8;
		OLED_Set_Pos(i,y1);
		OLED_WR_Byte((unsigned char)code_Circle[0],(unsigned char)OLED_DATA);
		OLED_Set_Pos(i,y2);
		OLED_WR_Byte((unsigned char)code_Circle[0],(unsigned char)OLED_DATA);
	}
	for(i = n; i<= n+x00;i++)
	{
		c = (m*m - r*r + i*i - 2*n*i + n*n);
		y1 = (QEOOU_Answer(1, -(2*m), c ,1))/8;
		y2 = (QEOOU_Answer(1, -(2*m), c, 0))/8;
		OLED_Set_Pos(i,y1);
		OLED_WR_Byte((unsigned char)code_Circle[0],(unsigned char)OLED_DATA);
		OLED_Set_Pos(i,y2);
		OLED_WR_Byte((unsigned char)code_Circle[0],(unsigned char)OLED_DATA);
	}
}

void draw_circle(u8 x0, u8 y0, u8 r) //圆心(x0,y0),半径r
{
	char x;
	float y;
	char res_x, res_y;
	char last_y;
	OLED_Set_Pos(63,0);
	OLED_WR_Byte((unsigned char)code_Circle1[0],(unsigned char)OLED_DATA);
	OLED_Set_Pos(64,0);
	OLED_WR_Byte((unsigned char)code_Circle1[0],(unsigned char)OLED_DATA);
	for(x = 3; x < 128;x++)
	{
		y = sqrt(pow(r,2)-pow(x-x0,2))+ y0*8;
		res_x = x % 2;
			if(y != last_y && res_x == 0)
			{
				OLED_Set_Pos(x,y/7);
				OLED_WR_Byte((unsigned char)code_Circle1[0],(unsigned char)OLED_DATA);
			}
		last_y = sqrt(pow(r,2)-pow(x-x0,2))+ y0*8;
	}
}

void Bresenham_Circle(int xc, int yc, int r)
{
	int flag = 2 - 2 * r;
	int x = 0, y = r;
	int Direction;
	yc = yc*8;
	while (y>=0)
	{
					OLED_Set_Pos(x+xc,(y+yc)/8);
		OLED_WR_Byte((unsigned char)code_Circle1[0],(unsigned char)OLED_DATA);
					OLED_Set_Pos(x+xc,(y-yc)/8);
		OLED_WR_Byte((unsigned char)code_Circle1[0],(unsigned char)OLED_DATA);
					OLED_Set_Pos(x-xc,(y+yc)/8);
		OLED_WR_Byte((unsigned char)code_Circle1[0],(unsigned char)OLED_DATA);
					OLED_Set_Pos(x-xc,(y-yc)/8);
		OLED_WR_Byte((unsigned char)code_Circle1[0],(unsigned char)OLED_DATA);
		if (flag < 0)
		{
			int flag1 = 2 * (flag + y) - 1;
			if (flag1 <= 0)
				Direction = 1;
			else Direction = 2;
		}
		else if (flag > 0)
		{
			int flag2 = 2 * (flag - x) - 1;
			if (flag2 <= 0)
				Direction = 2;
			else Direction = 3;
		}
		else if (flag == 0)
		{
			Direction = 2;
		}

		if (Direction == 1)
		{
			x++;
			flag += (2 * x + 1);
		}
		else if (Direction == 2)
		{
			x++;
			y--;
			flag += (2 * x - 2 * y + 2);
		}
		else if (Direction == 3)
		{
			y--;
			flag += (1 - 2 * y);
		}
//			OLED_Set_Pos(x,y);
//	OLED_WR_Byte((unsigned char)code_Circle1[0],(unsigned char)OLED_DATA);
	}
}

void OLED_PrintCircle2(void)
{
	unsigned char i,y = 0,j, x0;		
	while (i <= 64)
	{
		OLED_Set_Pos(j,y);
		for(j=0;j<8;j++)
		{
				
			OLED_WR_Byte((unsigned char )code_Circle1[j],(unsigned char)OLED_DATA);
		}
		y = y+1;
		OLED_Set_Pos(j,y);
		for(j=0;j<8;j++)
		{
				
			OLED_WR_Byte((unsigned char )code_Circle1[j+8],(unsigned char)OLED_DATA);
		}
		i = i + 8;
	}
}

void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;

	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP1[j++],OLED_DATA);
//				if (OLED_WR_Byte(BMP2[0],OLED_DATA);	    	
	    }
	}
} 
void OLED_PrintCircle_ol90(u8 x, u8 y, u8 Char_Size)
{
	unsigned char i,c,j;
	if(x > Max_Column-1)
			{x=0;y=y+2;}
	c=Char_Size%9;
	for(i = 0;i < c;i++)
	{
			OLED_Set_Pos(x,y);
			OLED_WR_Byte((unsigned char)code_Circle[8],(unsigned char)OLED_DATA);
		if (x <= 128 && y <=7)
		{
			y = y + 1;
		}
	}
}

void PrintPoint(u8 x, u8 y)
{
	OLED_Set_Pos(x,y);
	OLED_WR_Byte((unsigned char )code_Circle1[0],(unsigned char)OLED_DATA);
	OLED_Set_Pos(x+1,y);
	OLED_WR_Byte((unsigned char )code_Circle1[0],(unsigned char)OLED_DATA);
		OLED_Set_Pos(x+2,y);
	OLED_WR_Byte((unsigned char )code_Circle1[0],(unsigned char)OLED_DATA);
}

void OLED_Show(void)
{
	OLED_DrawBMP(0,0, 64,8,BMP1);
	OLED_PrintCircle_ol0(0, 4, 64);
	OLED_PrintCircle_ol90(32, 0, 8);
	OLED_ShowString(70,0,"ms:",16);
	OLED_ShowNum(100,0,5,1,16);
	OLED_ShowChar(108,0,',',16);
	OLED_ShowNum(115,0,6,1,16);
	
	OLED_ShowString(70,2,"rl:",16);
	OLED_ShowNum(100,2,5,1,16);
	OLED_ShowChar(108,2,',',16);
	OLED_ShowNum(115,2,6,1,16);
}

