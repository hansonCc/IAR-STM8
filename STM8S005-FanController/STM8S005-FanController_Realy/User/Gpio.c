#include "Gpio.h"

void Gpio_Init(void)
{
    GPIO_Init(FAN_PORT,FAN_L_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(FAN_PORT,FAN_M_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(FAN_PORT,FAN_B_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
    
    GPIO_Init(LED_PORT,LED_P1_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(LED_PORT,LED_P2_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
    
    GPIO_Init(DOOR_UP_PORT,DOOR_UP_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(DOOR_DO_PORT,DOOR_DO_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
    
    GPIO_Init(ER_PORT,ER_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
    
    GPIO_Init(DP_PORT,DP_PIN,GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(FR_PORT,FR_PIN,GPIO_MODE_IN_PU_NO_IT);
    //low off 
    
    GPIO_Init(DOOR_UP_IN_PORT,DOOR_UP_IN_PIN,GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(DOOR_DO_IN_PORT,DOOR_DO_IN_PIN,GPIO_MODE_IN_PU_NO_IT);
    
    GPIO_WriteLow(FAN_PORT,FAN_L_PIN);
    GPIO_WriteLow(FAN_PORT,FAN_M_PIN);
    GPIO_WriteLow(FAN_PORT,FAN_B_PIN);
    GPIO_WriteLow(LED_PORT,LED_P1_PIN);
    GPIO_WriteLow(LED_PORT,LED_P2_PIN);
    GPIO_WriteLow(DOOR_UP_PORT,DOOR_UP_PIN);
    GPIO_WriteLow(DOOR_DO_PORT,DOOR_DO_PIN);
    GPIO_WriteLow(ER_PORT,ER_PIN);    
}