#include "pid.h"
//PID�����㷨 
//λ���͹�ʽu(k)=Kp((err(k))+T/Ti��err(j)+Td/T(err(k)-err(k-1)))    T/Ti��ΪKi  Td/T��ΪKd

PID pid;
void PID_Init()
{
	pid.setnum=0.0;
	pid.actualnum=0.0;
	pid.err=0.0;
	pid.lasterr=0.0;
	pid.controlmachine=0.0;
	pid.sumerr=0.0;
	pid.kp=20;
	pid.ki=0;
	pid.kd=0;
}
float realizepid(float num)
{
	pid.setnum = num;
	pid.err = pid.setnum - pid.actualnum;
	pid.sumerr += pid.err;
	pid.controlmachine = pid.kp*pid.err+pid.ki*pid.sumerr+pid.kd*(pid.err-pid.lasterr);
	pid.lasterr = pid.err;
    if(pid.controlmachine > 256)
    {
      TIM4->CCR3 = 256;  
    }
    else if(pid.controlmachine < 0)
    {
      TIM4->CCR3 = 0; 
    }
    else 
    {
      TIM4->CCR3 = (u8)pid.controlmachine; 
    }
    return pid.controlmachine;
}


