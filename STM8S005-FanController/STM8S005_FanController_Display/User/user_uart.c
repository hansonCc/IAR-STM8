#include "stm8s.h"
#include "stdio.h"
#include "user_uart.h"
u8 IT_Receive_A,IT_Receive_A_num;
struct Peripheral Peripheral_Realy;
void uart2Init()
{
    UART2_DeInit();
    UART2_Init((uint32_t)115200, UART2_WORDLENGTH_8D, UART2_STOPBITS_1, \
    UART2_PARITY_NO , UART2_SYNCMODE_CLOCK_DISABLE , UART2_MODE_TXRX_ENABLE);
    UART2_ITConfig(UART2_IT_RXNE_OR,ENABLE);
    UART2_Cmd(ENABLE);
    
}
void uart2SendByte(uint8_t data)
{
    UART2->DR=data;
   /* Loop until the end of transmission */
   while (!(UART2->SR & UART2_FLAG_TXE));
}
void uart2SendString(uint8_t* Data,uint16_t len)
{
  uint16_t i=0;
  for(;i<len;i++)
    uart2SendByte(Data[i]);
}
uint8_t uart2ReceiveByte(void)
{
     uint8_t USART2_RX_BUF; 
     while (!(UART2->SR & UART2_FLAG_RXNE));
     USART2_RX_BUF=(uint8_t)UART2->DR;
     return  USART2_RX_BUF;
}
#if 1
int fputc(int ch, FILE *f)
{  
  UART2->DR=(unsigned char)ch;
  while (!(UART2->SR & UART2_FLAG_TXE));
  return (ch);
}
#endif
void Uart_IT_Receive_Hnadle(u8 data)
{
    switch(IT_Receive_A)
    {
      case 1: 
        Peripheral_Realy.a11 |= data<<4;
        IT_Receive_A_num++;
        if(IT_Receive_A_num>1)
        {
          Peripheral_Realy.a11 |= data;
          IT_Receive_A_num = 0;
          IT_Receive_A =0;
        }
      break;
      case 2: 
        Peripheral_Realy.a12 |= data<<4;
        IT_Receive_A_num++;
        if(IT_Receive_A_num>1)
        {
          Peripheral_Realy.a12 |= data;
          IT_Receive_A_num = 0;
          IT_Receive_A =0;
        }
      break;
      case 3: 
          Peripheral_Realy.a13 |= data<<4;
          IT_Receive_A_num++;
          if(IT_Receive_A_num>1)
          {
            Peripheral_Realy.a13 |= data;
            IT_Receive_A_num = 0;
            IT_Receive_A =0;
          }
      break;
      default :
      break;    
    }
    
   switch(data)
   {
      case FR_HIGH:Peripheral_Realy.Fr = 1;
      break;	
      case FR_LOW: Peripheral_Realy.Fr = 0;
      break;
      case DP_HIGH: Peripheral_Realy.Dp = 1;
      break;
      case DP_LOW: Peripheral_Realy.Dp = 0;
      break;		
      case A11_VALUE: IT_Receive_A = 1;
      break;
      case A12_VALUE: IT_Receive_A = 2;
      break;
      case A13_VALUE: IT_Receive_A = 3;
      break;
      case DOOR_UP_IN_OFF: Peripheral_Realy.Door_Up = 0;
      break;  
      case DOOR_UP_IN:Peripheral_Realy.Door_Up = 1;
      break; 
      case DOOR_DO_IN_OFF:Peripheral_Realy.Door_Do = 0;
      break; 
      case DOOR_DO_IN:Peripheral_Realy.Door_Do = 1;
      break; 
      default :
      break;
  }

   
}
void Uart_Transmit_Hnadle(struct KEYHANDLE KeyHandle)
{
  uint8_t Transmit_Data;
  
  if(KeyHandle.Led_P1_State == 1)
  {
    Transmit_Data = LED_P1_ON;
    uart2SendByte(Transmit_Data);
  }
  else if(KeyHandle.Led_P1_State == 0)
  {
    Transmit_Data = LED_P1_OFF;
    uart2SendByte(Transmit_Data);
  }
  
  if(KeyHandle.Led_P2_State == 1)
  {
    Transmit_Data = LED_P2_ON;
    uart2SendByte(Transmit_Data);
  }
  else if(KeyHandle.Led_P2_State == 0)
  {
    Transmit_Data = LED_P2_OFF;
    uart2SendByte(Transmit_Data);
  } 
  
  if(KeyHandle.Fan_Seepd_State == 0)
  {
    Transmit_Data = FAN_OFF;
    uart2SendByte(Transmit_Data);
  }
  else if(KeyHandle.Fan_Seepd_State == 1)
  {
    Transmit_Data = FAN_ON_L;
    uart2SendByte(Transmit_Data);
  }
  else if(KeyHandle.Fan_Seepd_State == 2)
  {
    Transmit_Data = FAN_ON_M;
    uart2SendByte(Transmit_Data);
  }     
  else if (KeyHandle.Fan_Seepd_State == 3)
  {
    Transmit_Data = FAN_ON_B;
    uart2SendByte(Transmit_Data);
  }
  
  if(KeyHandle.Door_State == 0)
  {
    Transmit_Data = DOOR_OFF;
    uart2SendByte(Transmit_Data);
  }
  else if(KeyHandle.Door_State == 1)
  {
    Transmit_Data = DOOR_UP_ON;
    uart2SendByte(Transmit_Data);
  }
  else if(KeyHandle.Door_State == 2)
  {
    Transmit_Data = DOOR_DO_ON;
    uart2SendByte(Transmit_Data);
  }
  
}