#include "headfile.h"

// ��ʱ���ж�

void TIMG0_IRQHandler()
{	
	if(DL_TimerG_getPendingInterrupt(TIMG0) == DL_TIMER_IIDX_LOAD)
	{
						// �˴���д�жϺ���
		

	}
}

void TIMG6_IRQHandler()
{
	if(DL_TimerG_getPendingInterrupt(TIMG6) == DL_TIMER_IIDX_LOAD)
	{
						// �˴���д�жϺ���

	}
}

void TIMG7_IRQHandler()
{
	if(DL_TimerG_getPendingInterrupt(TIMG7) == DL_TIMER_IIDX_LOAD)
	{
						// �˴���д�жϺ���
     gpio_set(GPIOB, DL_GPIO_PIN_8,  1);    //off
	   gpio_set(GPIOB, DL_GPIO_PIN_26, 0);    //off
		 DL_TimerG_disablePower(TIMG7);
	}
}


void TIMG12_IRQHandler()
{
	if(DL_TimerG_getPendingInterrupt(TIMG12) == DL_TIMER_IIDX_LOAD)
	{
						// �˴���д�жϺ���

	}
}


// �����ж�
//void UART0_IRQHandler(void)
//{
//	if(DL_UART_getPendingInterrupt(UART0) == DL_UART_IIDX_RX)
//	{
//						// �˴���д�жϺ���

//	}
// 
//}


void UART1_IRQHandler(void)
{
	if(DL_UART_getPendingInterrupt(UART1) == DL_UART_IIDX_RX)
	{
						// �˴���д�жϺ���
    imu_uart_callback();
	}
	NVIC_ClearPendingIRQ(UART1_INT_IRQn);
}


void UART2_IRQHandler(void)
{
	if(DL_UART_getPendingInterrupt(UART2) == DL_UART_IIDX_RX)
	{
						// �˴���д�жϺ���

	}
}


void UART3_IRQHandler(void)
{
	if(DL_UART_getPendingInterrupt(UART3) == DL_UART_IIDX_RX)
	{
						// �˴���д�жϺ���

	}
}



		
// �������Ҫ�����ⲿ�ж����� ���԰��������ģ���������
//		if(GPIOA->CPU_INT.MIS & DL_GPIO_PIN_0) // PA0�ⲿ�ж�
//		{
//        // �˴���д�ж�ִ�к���
		
//			GPIOA->CPU_INT.ICLR |= DL_GPIO_PIN_0; // ����жϱ�־λ
//		}






