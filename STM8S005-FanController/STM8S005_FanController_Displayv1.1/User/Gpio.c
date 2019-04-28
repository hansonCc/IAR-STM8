#include "Gpio.h"

void Gpio_Init(void)
{
    GPIO_Init(BACK_LIGHT_PROT,BACK_LIGHT_PIN_1,GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(BACK_LIGHT_PROT,BACK_LIGHT_PIN_2,GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(BACK_LIGHT_PROT,BACK_LIGHT_PIN_3,GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(BACK_LIGHT_PROT,BACK_LIGHT_PIN_4,GPIO_MODE_OUT_PP_LOW_SLOW);    
}
void Back_Light_On()
{
    GPIO_WriteHigh(BACK_LIGHT_PROT,BACK_LIGHT_PIN_1);
<<<<<<< HEAD
    GPIO_WriteHigh(BACK_LIGHT_PROT,BACK_LIGHT_PIN_2);
    GPIO_WriteHigh(BACK_LIGHT_PROT,BACK_LIGHT_PIN_3);
    GPIO_WriteHigh(BACK_LIGHT_PROT,BACK_LIGHT_PIN_4);  
=======
   GPIO_WriteHigh(BACK_LIGHT_PROT,BACK_LIGHT_PIN_2);
   GPIO_WriteHigh(BACK_LIGHT_PROT,BACK_LIGHT_PIN_3);
   GPIO_WriteHigh(BACK_LIGHT_PROT,BACK_LIGHT_PIN_4);  
>>>>>>> e941cfb1e7f1c2cd66d0fdeab945266a4984030a
}
void Back_Light_Off()
{
    GPIO_WriteLow(BACK_LIGHT_PROT,BACK_LIGHT_PIN_1);
    GPIO_WriteLow(BACK_LIGHT_PROT,BACK_LIGHT_PIN_2);
    GPIO_WriteLow(BACK_LIGHT_PROT,BACK_LIGHT_PIN_3);
    GPIO_WriteLow(BACK_LIGHT_PROT,BACK_LIGHT_PIN_4);  
}