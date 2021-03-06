#ifndef UART_H
#define UART_H
#include "stm8l15x.h"
#define FAN_OFF     0X01
#define FAN_ON_L    0X02
#define FAN_ON_M    0X03
#define FAN_ON_B    0X04
#define LED_P1_ON   0X05
#define LED_P1_OFF  0X06
#define LED_P2_ON   0X07
#define LED_P2_OFF  0X08
#define DOOR_UP_ON  0X09
#define DOOR_UP_OFF 0X0A
#define DOOR_DO_ON  0X0B
#define DOOR_DO_OFF 0X0C
#define ER_UP       0X0D
#define ER_DOWN     0X0E
#define DP_HIGH     0X0F
#define DP_LOW     0X10
#define FR_HIGH    0X11
#define FR_LOW     0X12
#define A11_VALUE   0X13
#define A12_VALUE   0X14
#define A13_VALUE   0X15
void Uart_IT_Receive_Control(u8 data);
void Uart_Send_data(struct Peripheral data);
#endif