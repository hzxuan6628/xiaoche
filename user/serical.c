#include "headfile.h"

uint8_t USART_RX_STA[22] = { 0 };    //����״̬���	���ֽ�����1+3+16+2  
uint8_t Num = 0;              //�������ݵĵ�ǰλ��


void Read_Data2(uint8_t addr, uint32_t *Data)	     
{	
	unsigned char y=0;
	unsigned int Receive_data = 0;       //���ݻ�����

//	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
//	USART_SendData(USART3, 0x57);
	while( DL_UART_isBusy(UART0) == true );
	uart_sendbyte(UART0,0x57);
	
	while( DL_UART_isBusy(UART0) == true );
	uart_sendbyte(UART0,addr);

	
///////////////////////////ƫ������ֵ///////////////////////////////	
	while(1)
  {		
		if(Num == 5)
		{
			Num = 0;
			if(USART_RX_STA[0x04] == 0x04)  //�ж�֡β0x04,���߲���ֵ
			{
				Receive_data = USART_RX_STA[2];
				Receive_data <<= 8;
				Receive_data |= USART_RX_STA[3];
				
				*Data = USART_RX_STA[1];		//λ�����ݸ�ֵ	  
				*(Data+1) = Receive_data;			//ƫ������ֵ	  
				break;
			}        
			break;
		}
    else
    {
      delay_ms(1);y++;
      if(y==3) { Num = 0;break; }
    }		
	}
///////////////////////////ƫ������ֵ///////////////////////////////	
}

void uart0_init(void)
{
	uart_init(UART0,115200,1);
}


void UART0_IRQHandler(void)
{
	if(DL_UART_getPendingInterrupt(UART0) == DL_UART_IIDX_RX)
	{
						// �˴���д�жϺ���
				USART_RX_STA[Num++] =uart_getbyte(UART0);	//��ȡ���յ�������
		if(USART_RX_STA[0] != 0x75) { Num = 0; }  //�ж�֡ͷ0x75,�������½���

   
	}
	NVIC_ClearPendingIRQ(UART0_INT_IRQn);
}



