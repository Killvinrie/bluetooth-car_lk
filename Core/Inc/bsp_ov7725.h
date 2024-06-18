#ifndef __OV7725_H
#define __OV7725_H 

#include "stm32f1xx_hal.h"
#include "main.h"

/*����ͷ���ýṹ��*/
typedef struct
{	

	
	uint8_t QVGA_VGA; //0��QVGA��1VGA
	
	/*VGA:sx + width <= 320 �� 240 ,sy+height <= 320 �� 240*/
	/*QVGA:sx + width <= 320 ,sy+height <= 240*/
	uint16_t cam_sx; //����ͷ����X��ʼλ��
	uint16_t cam_sy; //����ͷ����Y��ʼλ��
	
	uint16_t cam_width;//ͼ��ֱ��ʣ���??
	uint16_t cam_height;//ͼ��ֱ��ʣ���??
	
	uint16_t lcd_sx;//ͼ����ʾ��Һ������X��ʼλ��
	uint16_t lcd_sy;//ͼ����ʾ��Һ������Y��ʼλ��
	uint8_t lcd_scan;//Һ������ɨ��ģʽ��0-7��
	
	uint8_t light_mode;//����ģʽ��������Χ[0~5]
	int8_t saturation;//���Ͷ�,������Χ[-4 ~ +4]   
	int8_t brightness;//���նȣ�������Χ[-4~+4]
	int8_t contrast;//�Աȶȣ�������Χ[-4~+4]
	uint8_t effect;	//����Ч����������Χ[0~6]:	


}OV7725_MODE_PARAM;

typedef struct
{
	uint16_t X_Start;
	uint16_t Y_Start;
	uint16_t Height;
	uint16_t Width;
	uint8_t Mode;
	uint8_t VGA_QVGA;
}OV7725_Typedef;


extern unsigned char Img[8192];
extern unsigned char Img1[8192];
extern OV7725_MODE_PARAM cam_mode;
extern OV7725_Typedef ov7725;



/* OV7725 state machine enum */
typedef enum
{
	OV7725_RC_idle,
	OV7725_RC_busy,
	OV7725_RC_done
}OV7725_ST;





#define OV7725_ID 		0x21
#define Mode_RGB_565 	0
#define Mode_YUV 		1
#define GrayScale 		256

/* �Ĵ����궨�� */
#define REG_GAIN      0x00
#define REG_BLUE      0x01
#define REG_RED       0x02
#define REG_GREEN     0x03
#define REG_BAVG      0x05
#define REG_GAVG      0x06
#define REG_RAVG      0x07
#define REG_AECH      0x08
#define REG_COM2      0x09
#define REG_PID       0x0A
#define REG_VER       0x0B
#define REG_COM3      0x0C
#define REG_COM4      0x0D
#define REG_COM5      0x0E
#define REG_COM6      0x0F
#define REG_AEC       0x10
#define REG_CLKRC     0x11
#define REG_COM7      0x12
#define REG_COM8      0x13
#define REG_COM9      0x14
#define REG_COM10     0x15
#define REG_REG16     0x16
#define REG_HSTART    0x17
#define REG_HSIZE     0x18
#define REG_VSTRT     0x19
#define REG_VSIZE     0x1A
#define REG_PSHFT     0x1B
#define REG_MIDH      0x1C
#define REG_MIDL      0x1D
#define REG_LAEC      0x1F
#define REG_COM11     0x20
#define REG_BDBase    0x22
#define REG_BDMStep   0x23
#define REG_AEW       0x24
#define REG_AEB       0x25
#define REG_VPT       0x26
#define REG_REG28     0x28
#define REG_HOutSize  0x29
#define REG_EXHCH     0x2A
#define REG_EXHCL     0x2B
#define REG_VOutSize  0x2C
#define REG_ADVFL     0x2D
#define REG_ADVFH     0x2E
#define REG_YAVE      0x2F
#define REG_LumHTh    0x30
#define REG_LumLTh    0x31
#define REG_HREF      0x32
#define REG_DM_LNL    0x33
#define REG_DM_LNH    0x34
#define REG_ADoff_B   0x35
#define REG_ADoff_R   0x36
#define REG_ADoff_Gb  0x37
#define REG_ADoff_Gr  0x38
#define REG_Off_B     0x39
#define REG_Off_R     0x3A
#define REG_Off_Gb    0x3B
#define REG_Off_Gr    0x3C
#define REG_COM12     0x3D
#define REG_COM13     0x3E
#define REG_COM14     0x3F
#define REG_COM16     0x41
#define REG_TGT_B     0x42
#define REG_TGT_R     0x43
#define REG_TGT_Gb    0x44
#define REG_TGT_Gr    0x45
#define REG_LC_CTR    0x46
#define REG_LC_XC     0x47
#define REG_LC_YC     0x48
#define REG_LC_COEF   0x49
#define REG_LC_RADI   0x4A
#define REG_LC_COEFB  0x4B 
#define REG_LC_COEFR  0x4C
#define REG_FixGain   0x4D
#define REG_AREF1     0x4F
#define REG_AREF6     0x54
#define REG_UFix      0x60
#define REG_VFix      0x61
#define REG_AWBb_blk  0x62
#define REG_AWB_Ctrl0 0x63
#define REG_DSP_Ctrl1 0x64
#define REG_DSP_Ctrl2 0x65
#define REG_DSP_Ctrl3 0x66
#define REG_DSP_Ctrl4 0x67
#define REG_AWB_bias  0x68
#define REG_AWBCtrl1  0x69
#define REG_AWBCtrl2  0x6A
#define REG_AWBCtrl3  0x6B
#define REG_AWBCtrl4  0x6C
#define REG_AWBCtrl5  0x6D
#define REG_AWBCtrl6  0x6E
#define REG_AWBCtrl7  0x6F
#define REG_AWBCtrl8  0x70
#define REG_AWBCtrl9  0x71
#define REG_AWBCtrl10 0x72
#define REG_AWBCtrl11 0x73
#define REG_AWBCtrl12 0x74
#define REG_AWBCtrl13 0x75
#define REG_AWBCtrl14 0x76
#define REG_AWBCtrl15 0x77
#define REG_AWBCtrl16 0x78
#define REG_AWBCtrl17 0x79
#define REG_AWBCtrl18 0x7A
#define REG_AWBCtrl19 0x7B
#define REG_AWBCtrl20 0x7C
#define REG_AWBCtrl21 0x7D 
#define REG_GAM1      0x7E
#define REG_GAM2      0x7F
#define REG_GAM3      0x80
#define REG_GAM4      0x81
#define REG_GAM5      0x82
#define REG_GAM6      0x83
#define REG_GAM7      0x84
#define REG_GAM8      0x85
#define REG_GAM9      0x86
#define REG_GAM10     0x87
#define REG_GAM11     0x88
#define REG_GAM12     0x89
#define REG_GAM13     0x8A
#define REG_GAM14     0x8B
#define REG_GAM15     0x8C
#define REG_SLOP      0x8D
#define REG_DNSTh     0x8E
#define REG_EDGE0     0x8F
#define REG_EDGE1     0x90
#define REG_DNSOff    0x91
#define REG_EDGE2     0x92
#define REG_EDGE3     0x93
#define REG_MTX1      0x94
#define REG_MTX2      0x95
#define REG_MTX3      0x96
#define REG_MTX4      0x97
#define REG_MTX5      0x98
#define REG_MTX6      0x99
#define REG_MTX_Ctrl  0x9A
#define REG_BRIGHT    0x9B
#define REG_CNST      0x9C
#define REG_UVADJ0    0x9E
#define REG_UVADJ1    0x9F
#define REG_SCAL0     0xA0
#define REG_SCAL1     0xA1
#define REG_SCAL2     0xA2
#define REG_SDE       0xA6
#define REG_USAT      0xA7
#define REG_VSAT      0xA8
#define REG_HUECOS    0xA9
#define REG_HUESIN    0xAA
#define REG_SIGN      0xAB
#define REG_DSPAuto   0xAC


/* �Ĵ����궨�� */
#define GAIN      0x00

#define BAVG      0x05
#define GAVG      0x06
#define RAVG      0x07
#define AECH      0x08
#define COM2      0x09
#define PID       0x0A
#define VER       0x0B
#define COM3      0x0C
#define COM4      0x0D
#define COM5      0x0E
#define COM6      0x0F
#define AEC       0x10
#define CLKRC     0x11
#define COM7      0x12
#define COM8      0x13
#define COM9      0x14
#define COM10     0x15
#define REG16     0x16
#define HSTART    0x17
#define HSIZE     0x18
#define VSTRT     0x19
#define VSIZE     0x1A
#define PSHFT     0x1B
#define MIDH      0x1C
#define MIDL      0x1D
#define LAEC      0x1F
#define COM11     0x20
#define BDBase    0x22
#define BDMStep   0x23
#define AEW       0x24
#define AEB       0x25
#define VPT       0x26
#define REG28     0x28
#define HOutSize  0x29
#define EXHCH     0x2A
#define EXHCL     0x2B
#define VOutSize  0x2C
#define ADVFL     0x2D
#define ADVFH     0x2E
#define YAVE      0x2F
#define LumHTh    0x30
#define LumLTh    0x31
#define HREF      0x32
#define DM_LNL    0x33
#define DM_LNH    0x34
#define ADoff_B   0x35
#define ADoff_R   0x36
#define ADoff_Gb  0x37
#define ADoff_Gr  0x38
#define Off_B     0x39
#define Off_R     0x3A
#define Off_Gb    0x3B
#define Off_Gr    0x3C
#define COM12     0x3D
#define COM13     0x3E
#define COM14     0x3F
#define COM16     0x41
#define TGT_B     0x42
#define TGT_R     0x43
#define TGT_Gb    0x44
#define TGT_Gr    0x45
#define LC_CTR    0x46
#define LC_XC     0x47
#define LC_YC     0x48
#define LC_COEF   0x49
#define LC_RADI   0x4A
#define LC_COEFB  0x4B 
#define LC_COEFR  0x4C
#define FixGain   0x4D
#define AREF1     0x4F
#define AREF6     0x54
#define UFix      0x60
#define VFix      0x61
#define AWBb_blk  0x62
#define AWB_Ctrl0 0x63
#define DSP_Ctrl1 0x64
#define DSP_Ctrl2 0x65
#define DSP_Ctrl3 0x66
#define DSP_Ctrl4 0x67
#define AWB_bias  0x68
#define AWBCtrl1  0x69
#define AWBCtrl2  0x6A
#define AWBCtrl3  0x6B
#define AWBCtrl4  0x6C
#define AWBCtrl5  0x6D
#define AWBCtrl6  0x6E
#define AWBCtrl7  0x6F
#define AWBCtrl8  0x70
#define AWBCtrl9  0x71
#define AWBCtrl10 0x72
#define AWBCtrl11 0x73
#define AWBCtrl12 0x74
#define AWBCtrl13 0x75
#define AWBCtrl14 0x76
#define AWBCtrl15 0x77
#define AWBCtrl16 0x78
#define AWBCtrl17 0x79
#define AWBCtrl18 0x7A
#define AWBCtrl19 0x7B
#define AWBCtrl20 0x7C
#define AWBCtrl21 0x7D 
#define GAM1      0x7E
#define GAM2      0x7F
#define GAM3      0x80
#define GAM4      0x81
#define GAM5      0x82
#define GAM6      0x83
#define GAM7      0x84
#define GAM8      0x85
#define GAM9      0x86
#define GAM10     0x87
#define GAM11     0x88
#define GAM12     0x89
#define GAM13     0x8A
#define GAM14     0x8B
#define GAM15     0x8C
#define SLOP      0x8D
#define DNSTh     0x8E
#define EDGE0     0x8F
#define EDGE1     0x90
#define DNSOff    0x91
#define EDGE2     0x92
#define EDGE3     0x93
#define MTX1      0x94
#define MTX2      0x95
#define MTX3      0x96
#define MTX4      0x97
#define MTX5      0x98
#define MTX6      0x99
#define MTX_Ctrl  0x9A
#define BRIGHT    0x9B
#define CNST      0x9C
#define UVADJ0    0x9E
#define UVADJ1    0x9F
#define SCAL0     0xA0
#define SCAL1     0xA1
#define SCAL2     0xA2
#define SDE       0xA6
#define USAT      0xA7
#define VSAT      0xA8
#define HUECOS    0xA9
#define HUESIN    0xAA
#define SIGN      0xAB
#define DSPAuto   0xAC



#define FIFO_OE_H()     FIFO_OE_GPIO_Port->BSRR =FIFO_OE_Pin	  
#define FIFO_OE_L()     FIFO_OE_GPIO_Port->BRR  =FIFO_OE_Pin	 

#define FIFO_WRST_H()   WRST_GPIO_Port->BSRR =WRST_Pin	  
#define FIFO_WRST_L()   WRST_GPIO_Port->BRR  =WRST_Pin	  

#define FIFO_RRST_H()   RRST_GPIO_Port->BSRR =RRST_Pin	 
#define FIFO_RRST_L()   RRST_GPIO_Port->BRR  =RRST_Pin	  

#define FIFO_RCLK_H()   RCLK_GPIO_Port->BSRR =RCLK_Pin	  
#define FIFO_RCLK_L()   RCLK_GPIO_Port->BRR  =RCLK_Pin	  

#define FIFO_WE_H()     FIFO_WEN_GPIO_Port->BSRR =FIFO_WEN_Pin	  
#define FIFO_WE_L()     FIFO_WEN_GPIO_Port->BRR  =FIFO_WEN_Pin


#define FIFO_PREPARE                do{\
	                                  FIFO_RRST_L();\
	                                  FIFO_RCLK_L();\
	                                  FIFO_RCLK_H();\
	                                  FIFO_RRST_H();\
	                                  FIFO_RCLK_L();\
	                                  FIFO_RCLK_H();\
                                    }while(0)

#define OV7725_ID       0x21
																		
																		
																	

																		

void OV7725_GPIO_Config(void);
ErrorStatus OV7725_Init(void);
void OV7725_Light_Mode(uint8_t mode);
void OV7725_Color_Saturation(int8_t sat);
void OV7725_Brightness(int8_t bri);
void OV7725_Contrast(int8_t cnst);
void OV7725_Special_Effect(uint8_t eff);
void VSYNC_Init(void);				
void OV7725_Window_Set(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height,uint8_t QVGA_VGA);
void Img_Process(uint8_t *img_in,uint8_t *img_out);
void Img_Read(uint8_t *img);
void OLED_PrintImage(uint8_t *pucTable, uint16_t usRowNum, uint16_t usColumnNum);
#endif























