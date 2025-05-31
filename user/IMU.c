#include "headfile.h"


uint8_t imu_flag;
uint8_t orginal_data;
double yaw_angle;   //ƫ����
int yaw_angle_int;  //ƫ����ȡ��
struct Angle YawAngle;

void imu_init()
{
	uart_init(UART1,9600,1);
}

void imu_uart_callback()
{
  static unsigned char imu_rx_buffer[250];   //�洢ԭʼ���ݵĻ�����
	static unsigned char counter = 0;	      
	
	orginal_data=uart_getbyte(UART1);      //��ȡ������ԭʼ����
	imu_rx_buffer[counter++]=orginal_data;	//���յ������ݴ��뻺������
	if (imu_rx_buffer[0]!=0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
	{
		counter=0;
		return;
	}
	if (counter<11) {return;}//���ݲ���11�����򷵻�
	else
	{
		if(imu_rx_buffer[1]==0x53) //�ж��Ƿ���z��Ƕ�����
		{
			memcpy(&YawAngle,&imu_rx_buffer[2],8);  //memcpyΪ�������Դ����ڴ濽������,�����ջ��������ַ����������ݽṹ�����棬�Ӷ�ʵ�����ݵĽ�����
      imu_flag=1;
		}
		counter=0;//��ջ�����
	}
}

void imu_analysis()
{
		yaw_angle = (float)YawAngle.Angle[2]/32768*180;  //z�� ƫ����  ����ֵ
		
		yaw_angle_int=(int)(yaw_angle);
        
}

