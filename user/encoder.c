#include "headfile.h"

int Encoder_count1=0;
int Encoder_count2=0;

int mode,set;

void encoder_init(void)
{	
//		exti_init(EXTI_PA12, FALLING, 1);
//		gpio_init(GPIOA, DL_GPIO_PIN_13, PA13, IN_UP);
//		exti_init(EXTI_PA14, FALLING, 1);
//		gpio_init(GPIOA, DL_GPIO_PIN_15, PA15, IN_UP);
	
	  exti_init(EXTI_PA12, RISING, 0);                          //����A   PA12
	  exti_init(EXTI_PA13, FALLING,  0);			                     //����B  PA13
		gpio_init(GPIOA, DL_GPIO_PIN_12, PA12, IN_UP);           //������ ����
	  gpio_init(GPIOA, DL_GPIO_PIN_13, PA13, IN_DOWN);  			 //�½���  ����
	
		exti_init(EXTI_PA24, RISING, 0);													 //����A    PA24
	  exti_init(EXTI_PA15, FALLING, 0);													 //����B	  PA15
		gpio_init(GPIOA, DL_GPIO_PIN_24, PA24, IN_UP);            
	  gpio_init(GPIOA, DL_GPIO_PIN_15, PA15, IN_DOWN);                  
}

//��ȡ����������ֵ
int read_encoder1(void)
{
	int num;
	num = Encoder_count1; //��ȡ����ֵ
	Encoder_count1 = 0;   //����ֵ����
	return num;
}

int read_encoder2(void)
{
	int num;
	num = Encoder_count2; //��ȡ����ֵ
	Encoder_count2 = 0;   //����ֵ����
	return num;
}



// �ⲿ�ж�
void GROUP1_IRQHandler(void)//Group1���жϷ�����
{
	
  if(GPIOA->CPU_INT.MIS & DL_GPIO_PIN_12) // PA12�ⲿ�ж�   A������
		{
			if(gpio_get(GPIOA, DL_GPIO_PIN_13)==0)       //B �߼���
			{
				Encoder_count1 ++;
			}
			else
			{
				Encoder_count1 --;
			}

			GPIOA->CPU_INT.ICLR |= DL_GPIO_PIN_12; // ����жϱ�־λ
		}
		
		  if(GPIOA->CPU_INT.MIS & DL_GPIO_PIN_13) // PA13�ⲿ�ж�   B���½���
		{
			if(gpio_get(GPIOA, DL_GPIO_PIN_12)==0)   // A �߼���
			{
				Encoder_count1 ++;
			}
			else
			{
				Encoder_count1 --;
			}

			GPIOA->CPU_INT.ICLR |= DL_GPIO_PIN_13; // ����жϱ�־λ
		}
		
		if(GPIOA->CPU_INT.MIS & DL_GPIO_PIN_24) // PA24�ⲿ�ж�   A��������
		{
			if(gpio_get(GPIOA, DL_GPIO_PIN_15)==0)      	//B�߼���
			{
				Encoder_count2 ++;
			}
			else
			{
				Encoder_count2 --;
			}

			
			GPIOA->CPU_INT.ICLR |= DL_GPIO_PIN_24; // ����жϱ�־λ
		}
		
			if(GPIOA->CPU_INT.MIS & DL_GPIO_PIN_15) // PA15�ⲿ�ж�   B���½���
		{
			if(gpio_get(GPIOA, DL_GPIO_PIN_24)==0)    //A�߼���
			{
				Encoder_count2 ++;
			}
			else
			{
				Encoder_count2 --;
			}
			
			GPIOA->CPU_INT.ICLR |= DL_GPIO_PIN_15; // ����жϱ�־λ
		}
		
			 if(GPIOA->CPU_INT.MIS & DL_GPIO_PIN_17) // PA14�ⲿ�ж�
		 {
         delay_ms(10);
			   mode++;
			   set=0;
			   if(mode==5)
		    {
			     mode=1;
			  }
		  
			GPIOA->CPU_INT.ICLR |= DL_GPIO_PIN_17; // ����жϱ�־λ
		}
		
		  if(GPIOA->CPU_INT.MIS & DL_GPIO_PIN_27) // PA14�ⲿ�ж�
		{
			delay_ms(10);
			if(set==0)
        set=1;
			else set=0;
			GPIOA->CPU_INT.ICLR |= DL_GPIO_PIN_27; // ����жϱ�־λ
		}
}

	
	