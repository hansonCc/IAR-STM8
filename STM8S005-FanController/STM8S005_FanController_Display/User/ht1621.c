#include "ht1621.h"
//1 ~ 11
const unsigned char Cs1_Dis_Digitron_Addr[] = 
{
  0XFF,0x00,0x02,0x04,0x06,0X08,0X0A,0X0C,0X0E,0X15,0x17,0x19,
  0x00,0x02,0x04,0x06,0X18,0X16,0X14,0X12,0X10,0x0E,0x0C,0X0A,0X08
};
//12 ~ 24
const unsigned char Cs2_Dis_Digitron_Addr[] = 
{
  0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
  0x1A,0X17,0x04,0x06,0X02,0X16,0X14,0X12,0X10,0x0E,0x0C,0X0A,0X08
};

const unsigned char Cs1_Dis_Digitron_Num[] = 
{   
  0xf5, 0X60, 0Xd3, 0X97, 0X27, 0XB6, 0Xf6, 0X15, 0Xf7, 0Xb7 
};
const unsigned char Cs2_Dis_Digitron_Num[] = 
{   
  0xAF,0xA0,0xCB,0xE9,0xE4,0x6D,0x6F,0xA8,0xEF,0xED
};

const unsigned char T_Addr[] =
{
	0x00,0x04,0x0e,0x10,0x10,0x12,0x12,0x12,0x12,0x10,0x10,0x10,0x10,0x12,0x12,0x12,0x12,0x14,0x14,0x14,0x1A,0x10,0x10
};
const unsigned char T_Mask[] =
{
	0x00,0x08,0x08,0x80,0x02,0x80,0x40,0x20,0x10,0x01,0x40,0x20,0x10,0x08,0x04,0x02,0x01,0x20,0x40,0x10,0x80,0x08,0x04
};

unsigned char cs1_ram_map[33] = 
{
	0
};
unsigned char cs2_ram_map[33] = 
{
	0
};

const unsigned char S_Addr[] = {0X00,0x10,0x10};
const unsigned char S_Mask[] = {0X00,0x08,0x04};

const unsigned char P_Addr[] = {0X00,0X00,0x02,0X06,0X08,0X0C,0X15,0X17};
const unsigned char P_Mask[] = {0X00,0x08,0X08,0X80,0X80,0X80,0X80,0X80};
void ht1621_send_high_order_data(u8 data, u8 len)
{
	u8 i;
 
	for (i=0; i<len; i++)
	{
                
		if((data&0x80) == 0)
		{
			Set_Port_Val(DATA_PIN, 0);	
		}
		else
		{
			Set_Port_Val(DATA_PIN, 1);
		}
                
		Set_Port_Val(WR_PIN, 0);
		Delay_Us(DELAY_US_NUM);
		Set_Port_Val(WR_PIN, 1);	
		
		data <<= 1;
	}
}


void ht1621_send_low_order_data(u8 data, u8 len)
{
	u8 i;
	
	for (i=0; i<len; i++)
	{
                
		if((data&0x01) == 0)
		{
			Set_Port_Val(DATA_PIN, 0);	
		}
		else
		{
			Set_Port_Val(DATA_PIN, 1);
		}
                
		Set_Port_Val(WR_PIN, 0);
		Delay_Us(DELAY_US_NUM);
		Set_Port_Val(WR_PIN, 1);	
		
		data >>= 1;
	}
}


void ht1621_send_cmd(u8 command)
{
	Set_Port_Val(CS_1_PIN, 0);
        Set_Port_Val(CS_2_PIN, 0);
	ht1621_send_high_order_data(0x80, 4);
	ht1621_send_high_order_data(command, 8);
        Set_Port_Val(CS_2_PIN, 1);
	Set_Port_Val(CS_1_PIN, 1);	
}
 
void ht1621_write(u8 cs ,u8 addr, u8 data)
{
  
  if(cs==1)
  { 
	cs1_ram_map[addr] = data;
	Set_Port_Val(CS_1_PIN, 0);
	ht1621_send_high_order_data(0xA0, 3);
	ht1621_send_high_order_data(addr<<2, 6);
	ht1621_send_high_order_data(data, 8);
	Set_Port_Val(CS_1_PIN, 1);
  }
  else if(cs==2)
  {
        cs1_ram_map[addr] = data;
        Set_Port_Val(CS_2_PIN, 0);
        ht1621_send_high_order_data(0xA0, 3);
        ht1621_send_high_order_data(addr<<2, 6);
        ht1621_send_high_order_data(data, 8);
        Set_Port_Val(CS_2_PIN, 1);  
  }      
}
void ht1621_Char_write(u8 cs ,u8 addr, u8 data ,u8 status)
{
  u8 cs_1=cs;
  u8 t_data;
  t_data=cs1_ram_map[addr];
  if(status) t_data |= data;
  else t_data &= ~data;
  cs1_ram_map[addr] = t_data;
  Set_Port_Val(CS_1_PIN, 0);
  ht1621_send_high_order_data(0xA0, 3);
  ht1621_send_high_order_data(addr<<2, 6);
  ht1621_send_high_order_data(t_data, 8);
  Set_Port_Val(CS_1_PIN, 1);  
}

void ht1621_init()
{
        u8 i;
	GPIO_Init(LCD_PROT,CS_1_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
        GPIO_Init(LCD_PROT,RD_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
        GPIO_Init(LCD_PROT,WR_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
        GPIO_Init(LCD_PROT,DATA_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
        GPIO_Init(LCD_PROT,CS_2_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);        
        
        ht1621_send_cmd(HT_SYS_EN);
	ht1621_send_cmd(HT_RCOSC);
	ht1621_send_cmd(HT_BISA_COM);
	ht1621_send_cmd(HT_LCD_ON);
#if 0        
        for(i=1;i<10;i++)
        {
          ht1621_write(1,Cs1_Dis_Digitron_Addr[i],Cs1_Dis_Digitron_Num[i]);
        }
        for(i=1;i<10;i++)
        {
          ht1621_Char_write(1,T_Addr[i],T_Mask[i],1);
        }        
        for(i=1;i<3;i++)
          ht1621_Char_write(1,S_Addr[i],S_Mask[i],1);
#endif        
        ht1621_write(2,Cs2_Dis_Digitron_Addr[12],Cs2_Dis_Digitron_Num[8]);
        //ht1621_write(1,Cs1_Dis_Digitron_Addr[15],Cs1_Dis_Digitron_Num[2]);
        
}
 
 
void set_lcd_on()
{
	ht1621_send_cmd(HT_LCD_ON);
}
 
void set_lcd_off()
{
	ht1621_send_cmd(HT_LCD_OFF);
}
