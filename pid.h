#ifndef _PID_H_
#define _PID_H_

#include "global.h"

typedef struct
{
	float setnum;
	float actualnum;
	float err;
	float lasterr;
	float kp,ki,kd;
	float controlmachine;
	float  sumerr;
}PID;
extern PID pid;
extern void PID_Init();
extern float realizepid(float num);
#endif

