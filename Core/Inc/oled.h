/*
 * oled.h
 *
 *  Created on: Jun 10, 2024
 *      Author: Kevin-Rie
 */

#ifndef SRC_OLED_H_
#define SRC_OLED_H_

#include"main.h"
#include"gpio.h"
#include"spi.h"

__UINT8_TYPE__ OLED_WR_CMD(__UINT8_TYPE__ CMD);
__UINT8_TYPE__ OLED_WR_DATA(__UINT8_TYPE__ DATA);

void OLED_Init(void);
void OLED_Fill(unsigned char bmp_data);
void Draw_BMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char * bmp);
void OLED_Set_Pos(unsigned char x, unsigned char y);



#endif /* SRC_OLED_H_ */
