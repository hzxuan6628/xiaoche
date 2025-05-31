#include "headfile.h"
#include "_pid.h"
#include "key.h"

int left_pwm,right_pwm,left_angle_pwm,right_angle_pwm;
int base_left_pwm,base_right_pwm,angle_pwm,angle_pwm1;
int cur_state,last_state,pre_state;
unsigned int Temp[2] = { 0 };
int turn_pwm,cnt;
//int mode,set;

uint8_t KeyNum;

int main(void)
{
		system_init();  // ϵͳ��ʼ�� ϵͳƵ��80MHZ �����
		delay_ms(500);  // ��ʱ0.5s �ȴ���Դ�ȶ�
		OLED_Init();
	  imu_init();     // imu��ʼ�� ��ʵ���ǳ�ʼ������ �����Ǵ���1 
    key_init();

		motor_init();
		encoder_init();
	  uart0_init();
	  xunji_init();
//	track_init();
    buzzer_light_init(); 
		tim_interrupt_ms_init(TIMG8, 10, 1);   // ��ʱ���жϳ�ʼ�� �ж��ڷŵ��PID���Ƴ���
     
	  pid_init(&motorA,DELTA_PID,10,10,5);  
    pid_init(&motorB,DELTA_PID,10,10,5);
	  pid_init(&angle,POSITION_PID,0.04117,0,0.102);   //0.0405  0.1
		 
    while (1) 
	 {
			 if(imu_flag)
			{
				imu_flag=0;
				imu_analysis();  //��ȡ�Ƕ�ֵ�����  yaw_angle_int
			}
			
		  KeyNum = key_GetNum();
		  if (KeyNum == 1)			
		 {
		   mode++;
       if(mode==5)
			 {mode=1;}
       if(set==1)
       {set=0; }				 
		 }
		  if (KeyNum == 2)			
		 {
			 set=1;
		 }
			
			OLED_ShowString(1, 1, "mode:");
			OLED_ShowString(2, 1, "set:");
			OLED_ShowString(3, 1, "yaw:");
			OLED_ShowNum(1, 6, mode,3);
			OLED_ShowNum(2, 6, set,1);
		  OLED_ShowSignedNum(3, 6, yaw_angle_int,3);
   }
}

void TIMG8_IRQHandler()
{
	   if(DL_TimerG_getPendingInterrupt(TIMG8) == DL_TIMER_IIDX_LOAD)
	  {
        left_encoder=-read_encoder1();  
		    right_encoder=-read_encoder2();

		    if(mode==1&&set==1)
		   {
          track1();
		   }
			 	if(mode==2&&set==1)
		   {
          track2();
		   }
			 	if(mode==3&&set==1)
		   {
          track3();
		   }
			 	if(mode==4&&set==1)
		   {
          track4();
		   }	
	  } 
}









