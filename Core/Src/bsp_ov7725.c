/**
  ******************************************************************************
  * @file    bsp_ov7725.c
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   OV7725����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 


#include "bsp_ov7725.h"
#include "bsp_sccb.h"
#include "main.h"

unsigned char Img[8192];
unsigned char Img1[8192];

OV7725_Typedef ov7725=
{
	 .X_Start=96,
	 .Y_Start=88,
	 .Height=64,
	 .Width=128,
//	 .Mode=Mode_RGB_565,
	.Mode=Mode_YUV,
	 .VGA_QVGA=0,
};


typedef struct Reg
{
	uint8_t Address;			       /*�Ĵ�����ַ*/
	uint8_t Value;		           /*�Ĵ���ֵ*/
}Reg_Info;


OV7725_MODE_PARAM cam_mode =
{
	
/*���°�����������ͷ���ã������в��ԣ�����һ�飬����������ע�͵�����*/
/************����1*********������ʾ*****************************/
	
	.QVGA_VGA = 0,	//QVGAģʽ
	.cam_sx = 0,
	.cam_sy = 0,	
	
	.cam_width = 128,
	.cam_height = 64,
	
	.lcd_sx = 0,
	.lcd_sy = 0,
	.lcd_scan = 3, //LCDɨ��ģʽ�����������ÿ���1��3��5��7ģʽ
	
	//���¿ɸ����Լ�����Ҫ������������Χ���ṹ�����Ͷ���	
	.light_mode = 0,//�Զ�����ģʽ
	.saturation = 0,	
	.brightness = 0,
	.contrast = 0,
	.effect = 0,		//����ģʽ
	
	
/**********����2*********������ʾ****************************/	
/*������ʾ��ҪVGAģʽ��ͬ�ֱ�������£���QVGA֡���Ե�*/
/*VGAģʽ�ֱ���Ϊ640*480������ȡ��240*320��ͼ������������?*/
/*�����̲�֧�ֳ���320*240�� 240*320�ķֱ�������*/

//	.QVGA_VGA = 1,	//VGAģʽ
//	//ȡVGAģʽ���еĴ��ڣ��ɸ���ʵ����Ҫ����
//	.cam_sx = (640-240)/2,
//	.cam_sy = (480-320)/2,	
//	
//	.cam_width = 240, 
//	.cam_height = 320, //��VGAģʽ�£���ֵ�ſ��Դ���240
//	
//	.lcd_sx = 0,
//	.lcd_sy = 0,
//	.lcd_scan = 0, //LCDɨ��ģʽ�����������ÿ���0��2��4��6ģʽ
//	
//	//���¿ɸ����Լ�����Ҫ������������Χ���ṹ�����Ͷ���
//	.light_mode = 0,//�Զ�����ģʽ
//	.saturation = 0,	
//	.brightness = 0,
//	.contrast = 0,
//	.effect = 0,		//����ģʽ
	
	
	/*******����3************С�ֱ���****************************/	
	/*С��320*240�ֱ��ʵģ���ʹ��QVGAģʽ,���õ�ʱ��ע��Һ�����߽�*/
	
//	.QVGA_VGA = 0,	//QVGAģʽ
//	//ȡQVGAģʽ���еĴ��ڣ��ɸ���ʵ����Ҫ����
//	.cam_sx = (320-100)/2,
//	.cam_sy = (240-150)/2,	
//	
//	.cam_width = 100, 
//	.cam_height = 150, 
//	
//	/*Һ��������ʾλ��Ҳ���Ը�����Ҫ������ע�ⲻҪ�����߽缴��*/
//	.lcd_sx = 50,
//	.lcd_sy = 50,
//	.lcd_scan = 3, //LCDɨ��ģʽ��0-7ģʽ��֧�֣�ע�ⲻҪ�����߽缴��

//	//���¿ɸ����Լ�����Ҫ������������Χ���ṹ�����Ͷ���	
//	.light_mode = 0,//�Զ�����ģʽ
//	.saturation = 0,	
//	.brightness = 0,
//	.contrast = 0,
//	.effect = 0,		//����ģʽ

};


/* �Ĵ����������� */
Reg_Info Sensor_Config[] =
{
	{REG_CLKRC,     0x00}, /*clock config*/
	{REG_COM7,      0x40}, /* YUV422 */
	{REG_HSTART,    0x3f},
	{REG_HSIZE,     0x50},
	{REG_VSTRT,     0x03},
	{REG_VSIZE,     0x78},
	{REG_HREF,      0x00},
	{REG_HOutSize,  0x50},
	{REG_VOutSize,  0x78},
	{REG_EXHCH,     0x00},
	

	/*DSP control*/
	{REG_TGT_B,     0x7f},
	{REG_FixGain,   0x09},
	{REG_AWB_Ctrl0, 0xe0},
	{REG_DSP_Ctrl1, 0xff},
	{REG_DSP_Ctrl2, 0x20},
	{REG_DSP_Ctrl3,	0x00},
	{REG_DSP_Ctrl4, 0x00},

	/*AGC AEC AWB*/
	{REG_COM8,		0xf0},
	{REG_COM4,		0x81}, /*Pll AEC CONFIG*/
	{REG_COM6,		0xc5},
	{REG_COM9,		0x21},
	{REG_BDBase,	0xFF},
	{REG_BDMStep,	0x01},
	{REG_AEW,		0x34},
	{REG_AEB,		0x3c},
	{REG_VPT,		0xa1},
	{REG_EXHCL,		0x00},
	{REG_AWBCtrl3,  0xaa},
	{REG_COM8,		0xff},
	{REG_AWBCtrl1,  0x5d},

	{REG_EDGE1,		0x0a},
	{REG_DNSOff,	0x01},
	{REG_EDGE2,		0x01},
	{REG_EDGE3,		0x01},

	{REG_MTX1,		0x5f},
	{REG_MTX2,		0x53},
	{REG_MTX3,		0x11},
	{REG_MTX4,		0x1a},
	{REG_MTX5,		0x3d},
	{REG_MTX6,		0x5a},
	{REG_MTX_Ctrl,  0x1e},

	{REG_BRIGHT,	0x00},
	{REG_CNST,		0x25},
	{REG_USAT,		0x65},
	{REG_VSAT,		0x65},
	{REG_UVADJ0,	0x81},
	//{REG_SDE,		  0x20},	//�ڰ�
	{REG_SDE,		  0x06},	//��ɫ	����SDE����Ĵ���������ʵ������Ч��?
	
    /*GAMMA config*/
	{REG_GAM1,		0x0c},
	{REG_GAM2,		0x16},
	{REG_GAM3,		0x2a},
	{REG_GAM4,		0x4e},
	{REG_GAM5,		0x61},
	{REG_GAM6,		0x6f},
	{REG_GAM7,		0x7b},
	{REG_GAM8,		0x86},
	{REG_GAM9,		0x8e},
	{REG_GAM10,		0x97},
	{REG_GAM11,		0xa4},
	{REG_GAM12,		0xaf},
	{REG_GAM13,		0xc5},
	{REG_GAM14,		0xd7},
	{REG_GAM15,		0xe8},
	{REG_SLOP,		0x20},

	{REG_HUECOS,	0x80},
	{REG_HUESIN,	0x80},
	{REG_DSPAuto,	0xff},
	{REG_DM_LNL,	0x00},
	{REG_BDBase,	0x99},
	{REG_BDMStep,	0x03},
	{REG_LC_RADI,	0x00},
	{REG_LC_COEF,	0x13},
	{REG_LC_XC,		0x08},
	{REG_LC_COEFB,  0x14},
	{REG_LC_COEFR,  0x17},
	{REG_LC_CTR,	0x05},
	
	{REG_COM3,		0xd0},/*Horizontal mirror image*/

	/*night mode auto frame rate control*/
	{REG_COM5,		0xf5},	 /*��ҹ�ӻ����£��Զ�����֡�ʣ���֤���նȻ�������*/
	//{REG_COM5,		0x31},	/*ҹ�ӻ���֡�ʲ���*/
};
Reg_Info ov7725_init_reg_YUV[]= 
{   
  {CLKRC,     0x00}, /*clock config*/
	{COM7,      0x40}, /*YUV*/
  {HSTART,    0x3f},
	{HSIZE,     0x50},
	{VSTRT,     0x03},
	{VSIZE,     0x78},
	{HREF,      0x00},
	{HOutSize,  0x50},
	{VOutSize,  0x78},
	{EXHCH,     0x00},

	/*DSP control*/
	{TGT_B,     0x7f},
	{FixGain,   0x09},
	{AWB_Ctrl0, 0xe0},
	{DSP_Ctrl1, 0xff},
	{DSP_Ctrl2, 0x20},
	{DSP_Ctrl3,	0x00},
	{DSP_Ctrl4, 0x00},

	/*AGC AEC AWB*/
	{COM8,		  0xf0},
//	{COM4,		  0x81}, /*Pll AEC CONFIG*/
	{COM4,		  0xC1},
	{COM6,		  0xc5},
	{COM9,		  0x21},
	{BDBase,	  0xFF},
	{BDMStep,	  0x01},
	{AEW,		    0x34},
	{AEB,		    0x3c},
	{VPT,		    0xa1},
	{EXHCL,		  0x00},
	{AWBCtrl3,  0xaa},
	{COM8,		  0xff},
	{AWBCtrl1,  0x5d},

	{EDGE1,		  0x0a},
	{DNSOff,	  0x01},
	{EDGE2,		  0x01},
	{EDGE3,		  0x01},

	{MTX1,		  0x5f},
	{MTX2,		  0x53},
	{MTX3,		  0x11},
	{MTX4,		  0x1a},
	{MTX5,		  0x3d},
	{MTX6,		  0x5a},
	{MTX_Ctrl,  0x1e},

	{BRIGHT,	  0x00},
	{CNST,		  0x25},
	{USAT,		  0x65},
	{VSAT,		  0x65},
	{UVADJ0,	  0x81},
	{SDE,		    0x06},
	
    /*GAMMA config*/
	{GAM1,		  0x0c},
	{GAM2,		  0x16},
	{GAM3,		  0x2a},
	{GAM4,		  0x4e},
	{GAM5,		  0x61},
	{GAM6,		  0x6f},
	{GAM7,		  0x7b},
	{GAM8,		  0x86},
	{GAM9,		  0x8e},
	{GAM10,		  0x97},
	{GAM11,		  0xa4},
	{GAM12,		  0xaf},
	{GAM13,		  0xc5},
	{GAM14,		  0xd7},
	{GAM15,		  0xe8},
	{SLOP,		  0x20},

	{HUECOS,	  0x80},
	{HUESIN,	  0x80},
	{DSPAuto,	  0xff},
	{DM_LNL,	  0x00},
	{BDBase,	  0x99},
	{BDMStep,	  0x03},
	{LC_RADI,	  0x00},
	{LC_COEF,	  0x13},
	{LC_XC,		  0x08},
	{LC_COEFB,  0x14},
	{LC_COEFR,  0x17},
	{LC_CTR,	  0x05},
	
//	{COM3,		  0x00},
	{COM3,		  0xd0},/*Horizontal mirror image*/

	/*night mode auto frame rate control*/
	{COM5,		0xf5},	 /*��ҹ�ӻ����£��Զ�����֡�ʣ���֤���նȻ�������*/
	//{COM5,		0x31},	/*ҹ�ӻ���֡�ʲ���*/	
};
uint8_t OV7725_REG_NUM = sizeof(Sensor_Config)/sizeof(Sensor_Config[0]);	  /*�ṹ�������Ա���?*/
uint8_t OV7725_REG_YUV_NUM = sizeof(ov7725_init_reg_YUV)/sizeof(ov7725_init_reg_YUV[0]);

volatile uint8_t OV7725_state ;	 /* ֡ͬ���źű�־�����жϺ�����main��������ʹ�� */





ErrorStatus OV7725_Init(void)
{
	uint16_t i = 0;
	uint8_t Sensor_IDCode = 0;	
	
	//DEBUG("ov7725 Register Config Start......");
	
	if( 0 == SCCB_WriteByte ( 0x12, 0x80 ) ) 
	{
		//DEBUG("sccb write data error");		
		return ERROR ;
	}	

	if( 0 == SCCB_ReadByte( &Sensor_IDCode, 1, 0x0b ) )	 
	{
		//DEBUG("read id faild");		
		return ERROR;
	}
	//DEBUG("Sensor ID is 0x%x", Sensor_IDCode);	
	
	if(Sensor_IDCode == OV7725_ID)
	{
		for( i = 0 ; i < OV7725_REG_YUV_NUM ; i++ )
		{
			if( 0 == SCCB_WriteByte(ov7725_init_reg_YUV[i].Address, ov7725_init_reg_YUV[i].Value) )
			{                
				//DEBUG("write reg faild", Sensor_Config[i].Address);
				return ERROR;
			}
		}
	}
	else
	{
		return ERROR;
	}
	//DEBUG("ov7725 Register Config Success");
	
	return SUCCESS;
}



/**
  * @brief  ���ù���ģʽ
  * @param  mode :����ģʽ��������Χ[0~5]
			@arg 0:�Զ�
			@arg 1:����
			@arg 2:����
			@arg 3:�칫��
			@arg 4:����
			@arg 5:ҹ��
  * @retval ��
  */
void OV7725_Light_Mode(uint8_t mode)
{
	switch(mode)
	{
		case 0:	//Auto���Զ�ģʽ
			SCCB_WriteByte(0x13, 0xff); //AWB on 
			SCCB_WriteByte(0x0e, 0x65);
			SCCB_WriteByte(0x2d, 0x00);
			SCCB_WriteByte(0x2e, 0x00);
			break;
		case 1://sunny������
			SCCB_WriteByte(0x13, 0xfd); //AWB off
			SCCB_WriteByte(0x01, 0x5a);
			SCCB_WriteByte(0x02, 0x5c);
			SCCB_WriteByte(0x0e, 0x65);
			SCCB_WriteByte(0x2d, 0x00);
			SCCB_WriteByte(0x2e, 0x00);
			break;	
		case 2://cloudy������
			SCCB_WriteByte(0x13, 0xfd); //AWB off
			SCCB_WriteByte(0x01, 0x58);
			SCCB_WriteByte(0x02, 0x60);
			SCCB_WriteByte(0x0e, 0x65);
			SCCB_WriteByte(0x2d, 0x00);
			SCCB_WriteByte(0x2e, 0x00);
			break;	
		case 3://office���칫��
			SCCB_WriteByte(0x13, 0xfd); //AWB off
			SCCB_WriteByte(0x01, 0x84);
			SCCB_WriteByte(0x02, 0x4c);
			SCCB_WriteByte(0x0e, 0x65);
			SCCB_WriteByte(0x2d, 0x00);
			SCCB_WriteByte(0x2e, 0x00);
			break;	
		case 4://home������
			SCCB_WriteByte(0x13, 0xfd); //AWB off
			SCCB_WriteByte(0x01, 0x96);
			SCCB_WriteByte(0x02, 0x40);
			SCCB_WriteByte(0x0e, 0x65);
			SCCB_WriteByte(0x2d, 0x00);
			SCCB_WriteByte(0x2e, 0x00);
			break;	
		
		case 5://night��ҹ��
			SCCB_WriteByte(0x13, 0xff); //AWB on
			SCCB_WriteByte(0x0e, 0xe5);
			break;	
		
		default:
			 OV7725_DEBUG("Light Mode parameter error!"); 

			break;
	}

}			


/**
  * @brief  ���ñ��Ͷ�
  * @param  sat:���Ͷ�,������Χ[-4 ~ +4]             	
  * @retval ��
  */
void OV7725_Color_Saturation(int8_t sat)
{

 	if(sat >=-4 && sat<=4)
	{	
		SCCB_WriteByte(REG_USAT, (sat+4)<<4); 
		SCCB_WriteByte(REG_VSAT, (sat+4)<<4);
	}
	else
	{
		OV7725_DEBUG("Color Saturation parameter error!");
	}
	
}			


/**
  * @brief  ���ù��ն�
	* @param  bri:���նȣ�������Χ[-4~+4]
  * @retval ��
  */
void OV7725_Brightness(int8_t bri)
{
	uint8_t BRIGHT_Value,SIGN_Value;	
	
	switch(bri)
	{
		case 4:
				BRIGHT_Value = 0x48;
				SIGN_Value = 0x06;
			break;
		
		case 3:
				BRIGHT_Value = 0x38;
				SIGN_Value = 0x06;		
		break;	
		
		case 2:
				BRIGHT_Value = 0x28;
				SIGN_Value = 0x06;			
		break;	
		
		case 1:
				BRIGHT_Value = 0x18;
				SIGN_Value = 0x06;			
		break;	
		
		case 0:
				BRIGHT_Value = 0x08;
				SIGN_Value = 0x06;			
		break;	
		
		case -1:
				BRIGHT_Value = 0x08;
				SIGN_Value = 0x0e;		
		break;	
		
		case -2:
				BRIGHT_Value = 0x18;
				SIGN_Value = 0x0e;		
		break;	
		
		case -3:
				BRIGHT_Value = 0x28;
				SIGN_Value = 0x0e;		
		break;	
		
		case -4:
				BRIGHT_Value = 0x38;
				SIGN_Value = 0x0e;		
		break;	
		
		default:
			OV7725_DEBUG("Brightness parameter error!");
			break;
	}

		SCCB_WriteByte(REG_BRIGHT, BRIGHT_Value); //AWB on
		SCCB_WriteByte(REG_SIGN, SIGN_Value);
}		

/**
  * @brief  ���öԱȶ�
	* @param  cnst:�Աȶȣ�������Χ[-4~+4]
  * @retval ��
  */
void OV7725_Contrast(int8_t cnst)
{
	if(cnst >= -4 && cnst <=4)
	{
		SCCB_WriteByte(REG_CNST, (0x30-(4-cnst)*4));
	}
	else
	{
		OV7725_DEBUG("Contrast parameter error!");
	}
}		


/**
  * @brief  ��������Ч��
	* @param  eff:����Ч����������Χ[0~6]:
			@arg 0:����
			@arg 1:�ڰ�
			@arg 2:ƫ��
			@arg 3:����
			@arg 4:ƫ��
			@arg 5:ƫ��
			@arg 6:����
  * @retval ��
  */
void OV7725_Special_Effect(uint8_t eff)
{
	switch(eff)
	{
		case 0://����
			SCCB_WriteByte(0xa6, 0x06);
			SCCB_WriteByte(0x60, 0x80);
			SCCB_WriteByte(0x61, 0x80);
		break;
		
		case 1://�ڰ�
			SCCB_WriteByte(0xa6, 0x26);
			SCCB_WriteByte(0x60, 0x80);
			SCCB_WriteByte(0x61, 0x80);
		break;	
		
		case 2://ƫ��
			SCCB_WriteByte(0xa6, 0x1e);
			SCCB_WriteByte(0x60, 0xa0);
			SCCB_WriteByte(0x61, 0x40);	
		break;	
		
		case 3://����
			SCCB_WriteByte(0xa6, 0x1e);
			SCCB_WriteByte(0x60, 0x40);
			SCCB_WriteByte(0x61, 0xa0);	
		break;	
		
		case 4://ƫ��
			SCCB_WriteByte(0xa6, 0x1e);
			SCCB_WriteByte(0x60, 0x80);
			SCCB_WriteByte(0x61, 0xc0);		
		break;	
		
		case 5://ƫ��
			SCCB_WriteByte(0xa6, 0x1e);
			SCCB_WriteByte(0x60, 0x60);
			SCCB_WriteByte(0x61, 0x60);		
		break;	
		
		case 6://����
			SCCB_WriteByte(0xa6, 0x46);
		break;	
				
		default:
			OV7725_DEBUG("Special Effect error!");
			break;
	}
}		



/**
  * @brief  ����ͼ��������ڣ��ֱ��ʣ�QVGA
	* @param  sx:����x��ʼλ��
	* @param  sy:����y��ʼλ��
	* @param  width:���ڿ��?
	* @param  height:���ڸ߶�
	* @param QVGA_VGA:0,QVGAģʽ��1��VGAģʽ
  *
	* @note 	QVGAģʽ ����Ҫ��sx + width <= 320 ,sy+height <= 240
	* 			 	VGAģʽ����Ҫ��sx + width <= 640 ,sy+height <= 480
	*					������ Һ�����ֱ��� �� FIFO�ռ� �����ƣ������̲������ڳ���320*240������
	*         ʹ��VGAģʽ��Ҫ����ΪOV7725�޷�ֱ�ӽ���XY����QVGA������ʹ����ƽ��ʾ��
	*					���ó�VGAģʽ������ʹ��������ʾ��
	*					���QVGAģʽ��ͬ���ֱ����� VGAģʽ ͼ�����֡������?
  * @retval ��
  */
void OV7725_Window_Set(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height,uint8_t QVGA_VGA)
{
	uint8_t reg_raw,cal_temp;

	/***********QVGA or VGA *************/
	if(QVGA_VGA == 0)
	{
		/*QVGA RGB565 */
		SCCB_WriteByte(REG_COM7,0x46); 
	}
	else
	{
			/*VGA RGB565 */
		SCCB_WriteByte(REG_COM7,0x06); 
	}

	/***************HSTART*********************/
	//��ȡ�Ĵ�����ԭ���ݣ�HStart����ƫ��ֵ����ԭʼƫ��ֲ�Ļ����ϼ��ϴ���ƫ��	
	SCCB_ReadByte(&reg_raw,1,REG_HSTART);
	
	//sxΪ����ƫ�ƣ���8λ�洢��HSTART����2λ��HREF
	cal_temp = (reg_raw + (sx>>2));	
	SCCB_WriteByte(REG_HSTART,cal_temp ); 
	
	/***************HSIZE*********************/
	//ˮƽ��ȣ���?8λ�洢��HSIZE����2λ�洢��HREF
	SCCB_WriteByte(REG_HSIZE,width>>2);//HSIZE������λ 
	
	
	/***************VSTART*********************/
	//��ȡ�Ĵ�����ԭ���ݣ�VStart����ƫ��ֵ����ԭʼƫ��ֲ�Ļ����ϼ��ϴ���ƫ��	
	SCCB_ReadByte(&reg_raw,1,REG_VSTRT);	
	//syΪ����ƫ�ƣ���8λ�洢��HSTART����1λ��HREF
	cal_temp = (reg_raw + (sy>>1));	
	
	SCCB_WriteByte(REG_VSTRT,cal_temp);
	
	/***************VSIZE*********************/
	//��ֱ�߶ȣ���8λ�洢��VSIZE����1λ�洢��HREF
	SCCB_WriteByte(REG_VSIZE,height>>1);//VSIZE����һλ
	
	/***************VSTART*********************/
	//��ȡ�Ĵ�����ԭ����	
	SCCB_ReadByte(&reg_raw,1,REG_HREF);	
	//��ˮƽ��ȵĵ�?2λ����ֱ�߶ȵĵ�1λ��ˮƽƫ�Ƶĵ�2λ����ֱƫ�Ƶĵ�1λ��������ӵ�HREF
	cal_temp = (reg_raw |(width&0x03)|((height&0x01)<<2)|((sx&0x03)<<4)|((sy&0x01)<<6));	
	
	SCCB_WriteByte(REG_HREF,cal_temp);
	
	/***************HOUTSIZIE /VOUTSIZE*********************/
	SCCB_WriteByte(REG_HOutSize,width>>2);
	SCCB_WriteByte(REG_VOutSize,height>>1);
	
	//��ȡ�Ĵ�����ԭ����	
	SCCB_ReadByte(&reg_raw,1,REG_EXHCH);	
	cal_temp = (reg_raw |(width&0x03)|((height&0x01)<<2));	

	SCCB_WriteByte(REG_EXHCH,cal_temp);	
}


/**
  * @brief  ����ͼ��������ڣ��ֱ��ʣ�VGA
	* @param  sx:����x��ʼλ��
	* @param  sy:����y��ʼλ��
	* @param  width:���ڿ��?
	* @param  height:���ڸ߶�
	* @note 	����������Ҫ��sx + width <= 640 ,sy+height <= 480
	*					������ Һ�����ֱ��� �� FIFO�ռ� �����ƣ������̲������ڳ���320*240������
	*         ʹ�ñ�������Ҫ����ΪOV7725�޷�ֱ�ӽ���XY����QVGA������ʹ����ƽ��ʾ��
	*					ʹ�ñ��������ó�VGAģʽ������ʹ��������ʾ��
	*					���QVGAģʽ��ͬ���ֱ����� VGAģʽ ͼ�����֡������?
  * @retval ��
  */
void OV7725_Window_VGA_Set(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{
	
	uint8_t reg_raw,cal_temp;

	/***********QVGA or VGA *************/
	/*VGA RGB565 */
	SCCB_WriteByte(REG_COM7,0x06); 

	/***************HSTART*********************/
	//��ȡ�Ĵ�����ԭ���ݣ�HStart����ƫ��ֵ����ԭʼƫ��ֲ�Ļ����ϼ��ϴ���ƫ��	
	SCCB_ReadByte(&reg_raw,1,REG_HSTART);
	
	//sxΪ����ƫ�ƣ���8λ�洢��HSTART����2λ��HREF
	cal_temp = (reg_raw + (sx>>2));	
	SCCB_WriteByte(REG_HSTART,cal_temp ); 
	
	/***************HSIZE*********************/
	//ˮƽ��ȣ���?8λ�洢��HSIZE����2λ�洢��HREF
	SCCB_WriteByte(REG_HSIZE,width>>2);//HSIZE������λ 320 
	
	
	/***************VSTART*********************/
	//��ȡ�Ĵ�����ԭ���ݣ�VStart����ƫ��ֵ����ԭʼƫ��ֲ�Ļ����ϼ��ϴ���ƫ��	
	SCCB_ReadByte(&reg_raw,1,REG_VSTRT);	
	//syΪ����ƫ�ƣ���8λ�洢��HSTART����1λ��HREF
	cal_temp = (reg_raw + (sy>>1));	
	
	SCCB_WriteByte(REG_VSTRT,cal_temp);
	
	/***************VSIZE*********************/
	//��ֱ�߶ȣ���8λ�洢��VSIZE����1λ�洢��HREF
	SCCB_WriteByte(REG_VSIZE,height>>1);//VSIZE����һλ 240
	
	/***************VSTART*********************/
	//��ȡ�Ĵ�����ԭ����	
	SCCB_ReadByte(&reg_raw,1,REG_HREF);	
	//��ˮƽ��ȵĵ�?2λ����ֱ�߶ȵĵ�1λ��ˮƽƫ�Ƶĵ�2λ����ֱƫ�Ƶĵ�1λ��������ӵ�HREF
	cal_temp = (reg_raw |(width&0x03)|((height&0x01)<<2)|((sx&0x03)<<4)|((sy&0x01)<<6));	
	
	SCCB_WriteByte(REG_VSTRT,cal_temp);
	
	/***************HOUTSIZIE /VOUTSIZE*********************/
	SCCB_WriteByte(REG_HOutSize,width>>2);
	SCCB_WriteByte(REG_VOutSize,height>>1);
	
	//��ȡ�Ĵ�����ԭ����	
	SCCB_ReadByte(&reg_raw,1,REG_EXHCH);	
	
	cal_temp = (reg_raw |(width&0x03)|((height&0x01)<<2));	

	SCCB_WriteByte(REG_EXHCH,cal_temp);	
}

/* process the image with ostu*/
int Otsu(uint8_t *frame)  
{  
    int pixelCount[GrayScale]={0};  
    float pixelPro[GrayScale]={0};  
    int i, j, pixelSum = cam_mode.cam_width * cam_mode.cam_height, threshold = 0;
  
    for(i = 0; i < cam_mode.cam_height; i++)  
    {  
        for(j = 0;j < cam_mode.cam_width;j++)  
        {  
            pixelCount[(int)frame[i * cam_mode.cam_width + j]]++;  
        }  
    }  
  
    for(i = 0; i < GrayScale; i++)  
    {  
        pixelPro[i] = (float)pixelCount[i] / pixelSum;  
    }  
  
    float w0, w1, u0tmp, u1tmp, u0, u1, deltaTmp, deltaMax = 0;  
    for(i = 0; i < GrayScale; i++)  
    {  
        w0 = w1 = u0tmp = u1tmp = u0 = u1 = deltaTmp = 0;  
        for(j = 0; j < GrayScale; j++)  
        {  
            if(j <= i) 
            {  
                w0 += pixelPro[j];  
                u0tmp += j * pixelPro[j];  
            }  
            else 
            {  
                w1 += pixelPro[j];  
                u1tmp += j * pixelPro[j];  
            }  
        }  
        u0 = u0tmp / w0;  
        u1 = u1tmp / w1;  
        deltaTmp = (float)(w0 *w1* pow((u0 - u1), 2)) ;  
        if(deltaTmp > deltaMax)  
        {  
            deltaMax = deltaTmp;  
            threshold = i;  
        }  
    }  
    return threshold;  
}  

void READ_FIFO_PIXEL(uint8_t *p)   	
{
	FIFO_RCLK_L();
	*p = (uint8_t)((D0_GPIO_Port->IDR & 0xff00)>>8);
	FIFO_RCLK_H();
	FIFO_RCLK_L();
//	p[1] = (uint8_t)(GPIOC->IDR & 0xff);
	FIFO_RCLK_H();
}

void Img_Read(uint8_t *img)
{
	uint16_t i,j;
	// EXTI->IMR&=~(1<<10);
	// EXTI->EMR&=~(1<<10);
	for(i = 0; i < cam_mode.cam_height; i++)
	{
		for(j = 0; j < cam_mode.cam_width; j++)
		{
			READ_FIFO_PIXEL(img++);			
//			if(Camera_Data>0x5F) 
//				*img++=0xff;//��ɫ             
//			else
//				*img++=0x00;//��ɫ
		}
	}
	// EXTI->IMR|=(1<<10);
	// EXTI->EMR|=(1<<10);
}

void Img_Process(uint8_t *img_in,uint8_t *img_out)
{
	int threshold;
	uint8_t i,j;
	threshold=Otsu(img_in);
	for(i=0;i<cam_mode.cam_height;i++)
	{
		for(j=0;j<cam_mode.cam_width;j++)
		{
			if(*img_in++>threshold)
				*img_out++=0xff;
			else
				*img_out++=0x00;
		}
	}
	
}


/****************************End OF File*************************************/
