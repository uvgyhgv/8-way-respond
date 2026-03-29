#include <REGX52.H>


void Timer1Init(void)		//1毫秒@11.0592MHz
{
	TMOD &= 0x0F;		
	TL1 = 0xCD;		
	TH1 = 0xD4;		
	TF1 = 0;		
	TR1 = 1;
	ET1 = 1;       
	PT1 = 1;
	
}
