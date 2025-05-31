
#include "pid.h"


//extern float Kp,Ki,Kd;   //�ǶȻ�����
//float err;               //�˴����
//float last_err;          //�ϴ����
//float err_sum=0;         //����ۼ�
//float err_difference;    //���Ĳ�ֵ

//extern float Kp1,Ki1,Kd1;   //�ǶȻ�����
//float err1;               //�˴����
//float last_err1;          //�ϴ����
//float err_sum1=0;         //����ۼ�
//float err_difference1;    //���Ĳ�ֵ

typedef struct
{
	float target;	
	float now;
	float error[3];		
	float p,i,d;
	float pout, dout, iout;
	float out;   
}pid_t;


extern float VKp,VKi;    //�ٶȻ�����
float err2;               //�˴����
float filt_velocity;     //�˲�����ٶ�
float last_filt_velocity;//��һ�ε��˲�����ٶ�
//float velocity_err_sum=0;    //�ٶȵ��ۼ�
float velocity_sum;

extern float VKp1,VKi1;    //�ٶȻ�����
float err21;               //�˴����
float filt_velocity1;     //�˲�����ٶ�
float last_filt_velocity1;//��һ�ε��˲�����ٶ�
//float velocity_err_sum=0;    //�ٶȵ��ۼ�
float velocity_sum1;

extern float VKp2,VKi2;    //�ٶȻ�����
float err22;               //�˴����
float filt_velocity2;     //�˲�����ٶ�
float last_filt_velocity2;//��һ�ε��˲�����ٶ�
//float velocity_err_sum=0;    //�ٶȵ��ۼ�
float velocity_sum2;


extern float VKp3,VKi3;    //�ٶȻ�����
float err23;               //�˴����
float filt_velocity3;     //�˲�����ٶ�
float last_filt_velocity3;//��һ�ε��˲�����ٶ�
//float velocity_err_sum=0;    //�ٶȵ��ۼ�
float velocity_sum3;


//ת��
extern float tkp,tkd;
float line_err,line_err_differnence,last_line_err;

void I_xianfu(float *velocity_sum,int max)
{
	if(*velocity_sum>max)  *velocity_sum=max;
	if(*velocity_sum<-max) *velocity_sum=-max;
}



int velocity_PID_value(int velocity_measure,int velocity_calcu)
{
	float a=0.3; 	//�˲�ϵ������ӳ�˲��̶ȣ�
	err2=velocity_measure-velocity_calcu;
	filt_velocity = a*err2 + (1-a)*last_filt_velocity; //һ���ٶ��˲�
	
	velocity_sum+=  filt_velocity;                        //�ٶȵ��ۼ�
	I_xianfu(&velocity_sum,1500);                         //�ۼ��޷�,����ʱ����ȥ��
	last_filt_velocity = filt_velocity;                   //�˴��ٶȼ�¼Ϊ���ϴ��ٶȡ�

	return VKp*filt_velocity + VKi*velocity_sum;
}

int velocity_PID_value1(int velocity_measure,int velocity_calcu)
{
	float a=0.3; 	//�˲�ϵ������ӳ�˲��̶ȣ�
	err21=velocity_measure-velocity_calcu;
	filt_velocity1 = a*err21 + (1-a)*last_filt_velocity1; //һ���ٶ��˲�
	
	velocity_sum1+=  filt_velocity1;                        //�ٶȵ��ۼ�
	I_xianfu(&velocity_sum1,1500);                         //�ۼ��޷�,����ʱ����ȥ��
	last_filt_velocity1 = filt_velocity1;                   //�˴��ٶȼ�¼Ϊ���ϴ��ٶȡ�

	return VKp1*filt_velocity1 + VKi1*velocity_sum1;
}

int velocity_PID_value2(int velocity_measure,int velocity_calcu)
{
	float a=0.3; 	//�˲�ϵ������ӳ�˲��̶ȣ�
	err22=velocity_measure-velocity_calcu;
	filt_velocity2 = a*err22 + (1-a)*last_filt_velocity2; //һ���ٶ��˲�
	
	velocity_sum2+=  filt_velocity2;                        //�ٶȵ��ۼ�
	I_xianfu(&velocity_sum,1500);                         //�ۼ��޷�,����ʱ����ȥ��
	last_filt_velocity2 = filt_velocity2;                   //�˴��ٶȼ�¼Ϊ���ϴ��ٶȡ�

	return VKp2*filt_velocity2 + VKi2*velocity_sum2;
}

int velocity_PID_value3(int velocity_measure,int velocity_calcu)
{
	float a=0.3; 	//�˲�ϵ������ӳ�˲��̶ȣ�
	err23=velocity_measure-velocity_calcu;
	filt_velocity3 = a*err23 + (1-a)*last_filt_velocity3; //һ���ٶ��˲�
	
	velocity_sum3+=  filt_velocity3;                        //�ٶȵ��ۼ�
	I_xianfu(&velocity_sum,1500);                         //�ۼ��޷�,����ʱ����ȥ��
	last_filt_velocity3 = filt_velocity3;                   //�˴��ٶȼ�¼Ϊ���ϴ��ٶȡ�

	return VKp3*filt_velocity3 + VKi3*velocity_sum3;
}



//ת��
int line_pid_value(int error){ 

	line_err=error;

	line_err_differnence=line_err-last_line_err;
	last_line_err=line_err;
	return tkp*line_err+tkd*line_err_differnence;
}


//�ǶȻ���
int vertical_PID_value1(int measure,int calcu)
{
  if(calcu<0) 
	{
		  if(measure<0) measure=measure;
		  else measure=measure-360;
	}
	else if(calcu>0)
	{
		 if(measure>0) measure=measure;
		else measure=measure+360;
	}
	err = measure - calcu;             //���
	err_sum+=err;                      //�����ۼ�
	err_difference = err - last_err;   //���Ĳ�ֵ
	last_err = err;                    //�˴�����¼Ϊ���ϴ���
	
	return Kp*err + Ki*err_sum + Kd*err_difference;
}

//�ǶȻ���
//int vertical_PID_value1(float measure,float calcu)
//{

//	err1 = measure - calcu;             //���
//	err_sum1+=err1;                      //�����ۼ�
//	err_difference1 = err1 - last_err1;   //���Ĳ�ֵ
//	last_err1 = err1;                    //�˴�����¼Ϊ���ϴ���
//	
//	return Kp1*err1 + Ki1*err_sum1 + Kd1*err_difference1;
//}



void PWM_Xianfu(int max,int *PWM)
{
	if(*PWM>max)  *PWM = max;
	if(*PWM<-max) *PWM =-max;
}

//#define Const_2pi       (6.283185)
//#define Const_TS        (0.0001) //100us
// 
////���׵�ͨ�˲���,����û�õ�,���ʹ��,�����ᷢ���仯
//float LPF2(float xin) {
//   float f= 20;
//   float wc = Const_2pi * f;
//   float dampingRatio = 0.707;
// 
//   float lpf2_b0 = wc*wc*Const_TS*Const_TS;
//   float lpf2_a0 = 4 + 4*dampingRatio*wc*Const_TS + lpf2_b0;
//   float lpf2_a1 = -8 + 2*lpf2_b0;
//   //float lpf2_a2 = 4 - 4*dampingRatio*wc*Const_TS  + lpf2_a0; //ԭʼ����Ӧ������
//   float lpf2_a2 = lpf2_b0 + 4 - 4*dampingRatio*wc*Const_TS;
// 
//   static float lpf2_yout[3] = {0};
//   static float lpf2_xin[3] = {0};
// 
//   lpf2_xin[2] = xin;
//   lpf2_yout[2] = (lpf2_b0 * lpf2_xin[2] + 2*lpf2_b0 *lpf2_xin[1] + lpf2_b0 *lpf2_xin[0] -lpf2_a1 *lpf2_yout[1] - lpf2_a2*lpf2_yout[0]) / lpf2_a0;
//   lpf2_xin[0] = lpf2_xin[1];
//   lpf2_xin[1] = lpf2_xin[2];
//   lpf2_yout[0] = lpf2_yout[1];
//   lpf2_yout[1] = lpf2_yout[2];
// 
//   return lpf2_yout[2];
//}
