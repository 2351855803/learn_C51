#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "AT24C02.h"

/**
  *@brief	通过按键来选择模式
  *@param	
  *@return	按键代表的模式  
 */
unsigned char Matrix_key()
{
	unsigned char n,m;
	P1=0xf0;
	
	//检测到有按键按下，高四位会有一个变成0
	if((P1&0xf0)!=0xf0);
	{
		Delayms(10);
			
		if((P1&0xf0)!=0xf0);
		{
			//取高四位
			n=P1&0xf0;
			
			P1=0x0f;

			//取低四位
			m=P1&0x0f;
			
			return(n+m);
		}
	}
}

/**
  *@brief	通过矩阵键盘来设置温度湿度上下限
  *@param	分别是 湿度上限 湿度下线 温度上限 温度下线
  *@return  void
 */
void Matrix_Set_DH(unsigned char * humHWarn, unsigned char * humLWarn,\
			  unsigned char * tmpHWarn, unsigned char * tmpLWarn)
{
	//湿度上下限加减
	if(0x77 == Matrix_key()) {(*humHWarn)++; AT24C02_Write(1,(*humHWarn)); while(0x77 == Matrix_key());}
	if(0x7b == Matrix_key()) {(*humHWarn)--; AT24C02_Write(1,(*humHWarn)); while(0x7b == Matrix_key());}
	if(0x7d == Matrix_key()) {(*humLWarn)++; AT24C02_Write(2,(*humLWarn)); while(0x7d == Matrix_key());}
	if(0x7e == Matrix_key()) {(*humLWarn)--; AT24C02_Write(2,(*humLWarn)); while(0x7e == Matrix_key());}
	
	//温度上下限加减
	if(0xb7 == Matrix_key()) {(*tmpHWarn)++; AT24C02_Write(3,(*tmpHWarn)); while(0xb7 == Matrix_key());}
	if(0xbb == Matrix_key()) {(*tmpHWarn)--; AT24C02_Write(3,(*tmpHWarn)); while(0xbb == Matrix_key());}
	if(0xbd == Matrix_key()) {(*tmpLWarn)++; AT24C02_Write(4,(*tmpLWarn)); while(0xbd == Matrix_key());}
	if(0xbe == Matrix_key()) {(*tmpLWarn)--; AT24C02_Write(4,(*tmpLWarn)); while(0xbe == Matrix_key());}
	

}


/**
  *@brief	通过选择来进行一键设置
  *@param	温湿度上下限预警值
  *@return  void
 */
void Key_OnetouchSet(unsigned char * humHWarn, unsigned char * humLWarn,\
			  unsigned char * tmpHWarn, unsigned char * tmpLWarn)
{
	char i;
	Write_cmd(0x01);
	Delayms(100);
	for(i = 15; i >= 0; i--)
	{
		Lcd_write_string(0x80+i,"OnetouchSet: ");
		Delayms(300);
	}	

	while(0xee != Matrix_key())
	{
		//一键设置番茄最佳温湿度
		if(0xd7 == Matrix_key())
		{
			Lcd_write_string(0xc0,"            ");
			Lcd_write_string(0xc0,"Toamato!");
			(*humHWarn) = 60;
			AT24C02_Write(1,(*humHWarn));
			(*humLWarn) = 30;
			AT24C02_Write(2,(*humLWarn));
			(*tmpHWarn) = 30;
			AT24C02_Write(3,(*tmpHWarn));
			(*tmpLWarn) = 25;
			AT24C02_Write(4,(*tmpLWarn));
		}
		//一键设置茄子最佳温湿度
		if(0xdb == Matrix_key())
		{
			Lcd_write_string(0xc0,"            ");
			Lcd_write_string(0xc0,"Eggplant!");
			(*humHWarn) = 40;
			AT24C02_Write(1,(*humHWarn));
			(*humLWarn) = 30;
			AT24C02_Write(2,(*humLWarn));
			(*tmpHWarn) = 30;
			AT24C02_Write(3,(*tmpHWarn));
			(*tmpLWarn) = 15;
			AT24C02_Write(4,(*tmpLWarn));
		}		
		//一键设置胡萝卜最佳温湿度
		if(0xdd == Matrix_key())
		{
			Lcd_write_string(0xc0,"            ");
			Lcd_write_string(0xc0,"Carrot!");
			(*humHWarn) = 50;
			AT24C02_Write(1,(*humHWarn));
			(*humLWarn) = 35;
			AT24C02_Write(2,(*humLWarn));
			(*tmpHWarn) = 30;
			AT24C02_Write(3,(*tmpHWarn));
			(*tmpLWarn) = 13;
			AT24C02_Write(4,(*tmpLWarn));
		}		
		//一键设置韭菜最佳温湿度
		if(0xde == Matrix_key())
		{
			Lcd_write_string(0xc0,"            ");
			Lcd_write_string(0xc0,"Leek!");
			(*humHWarn) = 70;
			AT24C02_Write(1,(*humHWarn));
			(*humLWarn) = 40;
			AT24C02_Write(2,(*humLWarn));
			(*tmpHWarn) = 25;
			AT24C02_Write(3,(*tmpHWarn));
			(*tmpLWarn) = 20;
			AT24C02_Write(4,(*tmpLWarn));
		}
	}
	Write_cmd(0x01);
	Delayms(100);
}

	





