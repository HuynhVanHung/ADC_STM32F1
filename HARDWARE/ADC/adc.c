#include "adc.h"
#include "delay.h"
int i=0;

/*************************************************************************
 * Function Name: InitADC1
 * Parameters: none
 * Return: none
 *
 * Description: ADC Init subroutine
 *
 ************************************************************************
 */
 
 /*   CHANNEL               ADC1     ADC2     ADC3
 *   0                     PA0      PA0      PA0
 *   1                     PA1      PA1      PA1
 *   2                     PA2      PA2      PA2
 *   3                     PA3      PA3      PA3
 *   4                     PA4      PA4      PF6
 *   5                     PA5      PA5      PF7
 *   6                     PA6      PA6      PF8
 *   7                     PA7      PA7      PF9
 *   8                     PB0      PB0      PF10
 *   9                     PB1      PB1      PF3
 *   10                    PC0      PC0      PC0
 *   11                    PC1      PC1      PC1
 *   12                    PC2      PC2      PC2
 *   13                    PC3      PC3      PC3
 *   14                    PC4      PC4      PF4
 *   15                    PC5      PC5      PF5
 *
*/

	void ADCx_Init(ADC_TypeDef * ADCx ,uint8_t Channel )
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		ADC_InitTypeDef   ADC_InitStructure;

		if(ADCx == ADC1)            RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
		else if(ADCx == ADC2)       RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
		else if(ADCx == ADC3)       RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
			
	        if(Channel == ADC_Channel_0)          GPIO_Set(GPIOA,GPIO_Pin_0,GPIO_Mode_AIN,(GPIOSpeed_TypeDef)0);
		else if(Channel == ADC_Channel_1)     GPIO_Set(GPIOA,GPIO_Pin_1,GPIO_Mode_AIN,(GPIOSpeed_TypeDef)0);
		else if(Channel == ADC_Channel_2)     GPIO_Set(GPIOA,GPIO_Pin_2,GPIO_Mode_AIN,(GPIOSpeed_TypeDef)0);
		else if(Channel == ADC_Channel_3)     GPIO_Set(GPIOA,GPIO_Pin_3,GPIO_Mode_AIN,(GPIOSpeed_TypeDef)0);
		else if(Channel == ADC_Channel_4)     GPIO_Set(GPIOA,GPIO_Pin_4,GPIO_Mode_AIN,(GPIOSpeed_TypeDef)0);
		else if(Channel == ADC_Channel_5)     GPIO_Set(GPIOA,GPIO_Pin_5,GPIO_Mode_AIN,(GPIOSpeed_TypeDef)0);
		else if(Channel == ADC_Channel_6)     GPIO_Set(GPIOA,GPIO_Pin_6,GPIO_Mode_AIN,(GPIOSpeed_TypeDef)0);
		else if(Channel == ADC_Channel_7)     GPIO_Set(GPIOA,GPIO_Pin_7,GPIO_Mode_AIN,(GPIOSpeed_TypeDef)0);
		else if(Channel == ADC_Channel_8)     GPIO_Set(GPIOB,GPIO_Pin_0,GPIO_Mode_AIN,(GPIOSpeed_TypeDef)0);
		else if(Channel == ADC_Channel_9)     GPIO_Set(GPIOB,GPIO_Pin_1,GPIO_Mode_AIN,(GPIOSpeed_TypeDef)0);
		else if(Channel == ADC_Channel_10)    GPIO_Set(GPIOC,GPIO_Pin_0,GPIO_Mode_AIN,(GPIOSpeed_TypeDef)0);
		else if(Channel == ADC_Channel_11)    GPIO_Set(GPIOC,GPIO_Pin_1,GPIO_Mode_AIN,(GPIOSpeed_TypeDef)0);
		else if(Channel == ADC_Channel_12)    GPIO_Set(GPIOC,GPIO_Pin_2,GPIO_Mode_AIN,(GPIOSpeed_TypeDef)0);
		else if(Channel == ADC_Channel_13)    GPIO_Set(GPIOC,GPIO_Pin_3,GPIO_Mode_AIN,(GPIOSpeed_TypeDef)0);
		else if(Channel == ADC_Channel_14)    GPIO_Set(GPIOC,GPIO_Pin_4,GPIO_Mode_AIN,(GPIOSpeed_TypeDef)0);
		else if(Channel == ADC_Channel_15)    GPIO_Set(GPIOC,GPIO_Pin_5,GPIO_Mode_AIN,(GPIOSpeed_TypeDef)0);

 
          ADC_DeInit(ADCx);


		// ADC Structure Initialization
		ADC_StructInit(&ADC_InitStructure);

		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_InitStructure.ADC_ScanConvMode = ENABLE;
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStructure.ADC_NbrOfChannel = 1;
		ADC_Init(ADC1, &ADC_InitStructure);

		// Enable the ADC
		ADC_Cmd(ADCx, ENABLE);

		// ADC calibration
		// Enable ADC1 reset calibaration register
		ADC_ResetCalibration(ADCx);
		
		// Check the end of ADC1 reset calibration register
		while(ADC_GetResetCalibrationStatus(ADCx) == SET);

		// Start ADC1 calibaration
		ADC_StartCalibration(ADCx);
		
		// Check the end of ADC1 calibration
		while(ADC_GetCalibrationStatus(ADCx) == SET);

    }

	u16 Get_ADCx(ADC_TypeDef * ADCx ,uint8_t Channel)
	{
		// Configure channel
		ADC_RegularChannelConfig(ADCx, Channel, 1, ADC_SampleTime_239Cycles5);

		// Start the conversion
		ADC_SoftwareStartConvCmd(ADCx, ENABLE);

		// Wait until conversion completion
		while(ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) == RESET);

		// Get the conversion value
		return ADC_GetConversionValue(ADCx);
	}



	u16 TB_ADC(ADC_TypeDef * ADCx ,uint8_t Channel,u16 n)
	{
		u32 adc =0;
		for( i=0;i<n;i++)
		{
		   adc+=Get_ADCx(ADC1,ADC_Channel_1); delay_ms(5);
		}
		return adc/n;
	}
