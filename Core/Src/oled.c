/*
 * oled.c
 *
 *  Created on: Jun 10, 2024
 *      Author: Kevin-Rie
 */
#include "oled.h"
#include "codetab.h"


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
	OLED_WR_CMD(0xff); //�?????度调�????? 0x00~0xff
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
  * @brief  OLED_Fill，填充整�?????屏幕
  * @param  fill_Data:要填充的数据
	* @retval �?????
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


void Draw_BMP(unsigned char x0, unsigned char y0, unsigned char width, unsigned char height, unsigned char * bmp) {
    unsigned char x, y, i;
    unsigned char pages;
	if(height%8==0)
		pages = height/8;
  	else
		pages = height/8 + 1;

    for (y = 0; y < pages; y++)
    {
    	OLED_Set_Pos(x0, y + y0);  
        for (x = x0,i = 0; i < width; x++)
        {
        	OLED_WR_DATA(bmp[width * y + i]);
			i++;
        }
    }
}

void OLED_Set_Pos(unsigned char x, unsigned char y)
{ 
  OLED_WR_CMD(0xb0+y);
  OLED_WR_CMD(((x&0xf0)>>4)|0x10);
  OLED_WR_CMD((x&0x0f)|0x01);
} 



void OLED_CLS(void)
{
	OLED_Fill(0x00);
}



void OLED_ON(void)
{
	OLED_WR_CMD(0X8D);  
	OLED_WR_CMD(0X14); 
	OLED_WR_CMD(0XAF); 
}



void OLED_OFF(void)
{
	OLED_WR_CMD(0X8D);  
	OLED_WR_CMD(0X10);  
	OLED_WR_CMD(0XAE);  
}

// void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
// {
// 	unsigned char c = 0,i = 0,j = 0;
// 	switch(TextSize)
// 	{
// 		case 1:
// 		{
// 			while(ch[j] != '\0')
// 			{
// 				c = ch[j] - 32;
// 				if(x > 126)
// 				{
// 					x = 0;
// 					y++;
// 				}
// 				OLED_SetPos(x,y);
// 				for(i=0;i<6;i++)
// 					WriteDat(F6x8[c][i]);
// 				x += 6;
// 				j++;
// 			}
// 		}break;
// 		case 2:
// 		{
// 			while(ch[j] != '\0')
// 			{
// 				c = ch[j] - 32;
// 				if(x > 120)
// 				{
// 					x = 0;
// 					y++;
// 				}
// 				OLED_SetPos(x,y);
// 				for(i=0;i<8;i++)
// 					WriteDat(F8X16[c*16+i]);
// 				OLED_SetPos(x,y+1);
// 				for(i=0;i<8;i++)
// 					WriteDat(F8X16[c*16+i+8]);
// 				x += 8;
// 				j++;
// 			}
// 		}break;
// 	}
// }

// void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
// {
// 	unsigned char wm=0;
// 	unsigned int  adder=32*N;
// 	OLED_SetPos(x , y);
// 	for(wm = 0;wm < 16;wm++)
// 	{
// 		WriteDat(F16x16[adder]);
// 		adder += 1;
// 	}
// 	OLED_SetPos(x,y + 1);
// 	for(wm = 0;wm < 16;wm++)
// 	{
// 		WriteDat(F16x16[adder]);
// 		adder += 1;
// 	}
// }

void OLED_Showchar(unsigned char x, unsigned char y,unsigned char ch , unsigned char frontsize)
{
	int i,j;
	OLED_Set_Pos(x,y);
	if(frontsize == Size_F6x8)
	{
		for(i =0;i < Size_F6x8;i++)
		{
			OLED_WR_DATA(F6x8[ch - ' '][i]);
		}
	}
	else if(frontsize == Size_F8x16)
	{
		for(j = 0;j <2;j++)
		{
			OLED_Set_Pos(x,y+j);
			for(i = 0;i < Size_F8x16;i++)
			{
				OLED_WR_DATA(F8X16[ch - ' '][i+j*8]);
			}
		}

	}
	else
	{
		oled_erro_code = Oled_Erro_frontsize;
	}
}



