/*
 * oled.c
 *
 *  Created on: Jun 10, 2024
 *      Author: Kevin-Rie
 */
#include"oled.h"

typedef enum
{
	F6x8,
	F8x16
} frontsize;
	
typedef enum
{
	Oled_Erro_None,
	Oled_Erro_frontsize,
	Oled_Erro_edge
}oled_erro;

unsigned char oled_erro_code = Oled_Erro_None;


__UINT8_TYPE__ OLED_WR_CMD(__UINT8_TYPE__ CMD)
{
   __UINT8_TYPE__ RXDATA =0;

   HAL_GPIO_WritePin(DC_GPIO_Port,DC_Pin,0);//д����DC�͵�ƽ

   HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,0);//�͵�ƽѡ����ʾ��

   HAL_SPI_TransmitReceive(&hspi1,&CMD,&RXDATA,1,1000);

   HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,1);//CS�ߵ�ƽdisable
   
   return RXDATA;
}

__UINT8_TYPE__ OLED_WR_DATA(__UINT8_TYPE__ DATA)
{
    __UINT8_TYPE__ RXDATA =0;

   HAL_GPIO_WritePin(DC_GPIO_Port,DC_Pin,1);//д����DC�͵�ƽ

   HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,0);//�͵�ƽѡ����ʾ��

   HAL_SPI_TransmitReceive(&hspi1,&DATA,&RXDATA,1,1000);

   HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,1);//CS�ߵ�ƽdisable
   
   return RXDATA;
}


 /**
  * @brief  OLED_Init，send command to initialize the oled register
  * @param  None
	* @retval None
  */
void OLED_Init(void)        
{ 
  Delay_tick(100);
	OLED_WR_CMD(0xAE); //display off
	OLED_WR_CMD(0x20);	//Set Memory Addressing Mode	
	OLED_WR_CMD(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	OLED_WR_CMD(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	OLED_WR_CMD(0xc8);	//Set COM Output Scan Direction
	OLED_WR_CMD(0x00); //---set low column address
	OLED_WR_CMD(0x10); //---set high column address
	OLED_WR_CMD(0x40); //--set start line address
	OLED_WR_CMD(0x81); //--set contrast control register
	OLED_WR_CMD(0xff); //亮度调节 0x00~0xff
	OLED_WR_CMD(0xa1); //--set segment re-map 0 to 127
	OLED_WR_CMD(0xa6); //--set normal display
	OLED_WR_CMD(0xa8); //--set multiplex ratio(1 to 64)
	OLED_WR_CMD(0x3F); //
	OLED_WR_CMD(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	OLED_WR_CMD(0xd3); //-set display offset
	OLED_WR_CMD(0x00); //-not offset
	OLED_WR_CMD(0xd5); //--set display clock divide ratio/oscillator frequency
	OLED_WR_CMD(0xf0); //--set divide ratio
	OLED_WR_CMD(0xd9); //--set pre-charge period
	OLED_WR_CMD(0x22); //
	OLED_WR_CMD(0xda); //--set com pins hardware configuration
	OLED_WR_CMD(0x12);
	OLED_WR_CMD(0xdb); //--set vcomh
	OLED_WR_CMD(0x20); //0x20,0.77xVcc
	OLED_WR_CMD(0x8d); //--set DC-DC enable
	OLED_WR_CMD(0x14); //
	OLED_WR_CMD(0xaf); //--turn on oled panel
  Delay_tick(100);
} 


 /**
  * @brief  OLED_Fill，填充整个屏幕
  * @param  fill_Data:要填充的数据
	* @retval 无
  */
void OLED_Fill(unsigned char bmp_data)
{
	unsigned char y,x;
	
	for(y=0;y<8;y++)
	{
		OLED_WR_CMD(0xb0+y);
		OLED_WR_CMD(0x01);
		OLED_WR_CMD(0x10);
		for(x=0;x<128;x++)
			OLED_WR_DATA(bmp_data);
	}
}


void Draw_BMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char * bmp)
{ 	
  unsigned int ii=0;
  unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<=y1;y++)
	{
		OLED_Set_Pos(x0,y);				
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_DATA(bmp[ii++]);	    	
	    }
	}
}

void OLED_Set_Pos(unsigned char x, unsigned char y)
{ 
  OLED_WR_CMD(0xb0+y);
  OLED_WR_CMD(((x&0xf0)>>4)|0x10);
  OLED_WR_CMD((x&0x0f)|0x01); 
} 


 /**
  * @brief  OLED_CLS，清屏
  * @param  无
	* @retval 无
  */
void OLED_CLS(void)//清屏
{
	OLED_Fill(0x00);
}


 /**
  * @brief  OLED_ON，将OLED从休眠中唤醒
  * @param  无
	* @retval 无
  */
void OLED_ON(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X14);  //开启电荷泵
	WriteCmd(0XAF);  //OLED唤醒
}


 /**
  * @brief  OLED_OFF，让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
  * @param  无
	* @retval 无
  */
void OLED_OFF(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X10);  //关闭电荷泵
	WriteCmd(0XAE);  //OLED休眠
}


 /**
  * @brief  OLED_ShowStr，显示codetab.h中的ASCII字符,有6*8和8*16可选择
  * @param  x,y : 起始点坐标(x:0~127, y:0~7);
	*					ch[] :- 要显示的字符串; 
	*					TextSize : 字符大小(1:6*8 ; 2:8*16)
	* @retval 无
  */
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
{
	unsigned char c = 0,i = 0,j = 0;
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
					WriteDat(F6x8[c][i]);
				x += 6;
				j++;
			}
		}break;
		case 2:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i]);
				OLED_SetPos(x,y+1);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i+8]);
				x += 8;
				j++;
			}
		}break;
	}
}

 /**
  * @brief  OLED_ShowCN，显示codetab.h中的汉字,16*16点阵
  * @param  x,y: 起始点坐标(x:0~127, y:0~7); 
	*					N:汉字在codetab.h中的索引
	* @retval 无
  */
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int  adder=32*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder]);
		adder += 1;
	}
}

OLED_Showchar(unsigned char x, unsigned char y,unsigned char ch , unsigned char frontsize)
{
	if(frontsize == F6x8)
	{

	}
	else if(frontsize == F8x16)
	{
		
	}
	else
	{
		oled_erro_code = Oled_Erro_frontsize;
	}
}



