#include "stm32f10x.h"
#include "LED.h"
#include "delay.h"
#include "adc.h"
#include "usart.h"


/************************************************
www.stm32vn.com
************************************************/

u16 adc = 0;
int a =0;
 
 int main(void)
 {	
	 
	 delay_init();
	 
	// LED_init();
	 
	 ADCx_Init(ADC1,ADC_Channel_1);
	 
	 USARTx_Init(USART1,Pins_PA9PA10,115200);	 
		
   USART_Puts(	USART1,"LVD_IC \n" );
	 
	 
 
  while(1)
	{
		//a++;
	 
	// 	adc = Get_ADCx(ADC1,ADC_Channel_1); 
		
	   adc = TB_ADC(ADC1 ,ADC_Channel_1,200);
		 printf("%d\n",adc);
		
			delay_ms(200);
	
//	 	LED0 =0;
//		delay_ms(300);
//		LED0 =1;
//		delay_ms(300);
//		
		
	}
 }
