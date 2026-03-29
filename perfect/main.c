#include <REGX52.H>
#include "Timer0.H"
#include "Key.H"
#include "Timer1.H"
#include "INTRINS.H"
#include "LCD1602.H"

// 蜂鸣器引脚：P3^3（专属，无其他复用）
sbit Buzzer=P3^3;  
#define LED_PORT P2       // LED控制端口（P20~P27）
unsigned char code LED_Index[] = {0,1,2,3,4,5,6,7}; // 选手1-8对应LED引脚位
unsigned char KeyNum,Sec=3,TimeLock,MemoryTime,UserKey,User;
bit TimeOutFlag = 0;  
unsigned char FoulUser = 0;  
// 记分牌定义
unsigned char Score[8] = {100,100,100,100,100,100,100,100}; // 8选手初始分数100
unsigned char SelectUser = 1; // 当前选中的计分选手

void LED_AllOff()
{
    LED_PORT = 0xFF;
}

// 点亮指定选手对应的LED（user:1-8）
void LED_On(unsigned char user)
{
    if(user >= 1 && user <= 8)
    {
        LED_PORT &= ~(1 << LED_Index[user-1]); // 对应位清0点亮
    }
}

// 蜂鸣器延时函数（500us）
void Buzzer_Delay500us()		
{
	unsigned char i;
	_nop_();
	i = 247;
	while (--i);
}

// 蜂鸣器发声函数（低电平触发，P3^3专属）
void Buzzer_Time(unsigned int ms)		
{
	unsigned int i;
    Buzzer = 1; // 初始置高，防止电平漂移
	for(i=0;i<ms*2;i++)
	{
		Buzzer=0;       // 低电平触发蜂鸣器发声
		Buzzer_Delay500us();
		Buzzer=1;       // 高电平停止发声
		Buzzer_Delay500us();
	}
    Buzzer = 1; // 强制置高，确保发声结束后关闭
}

void main()
{	
	Timer0_Init();
	Timer1Init();	
	LCD_Init();
    LED_AllOff(); 
	MemoryTime=Sec;		
    Buzzer = 1; // 初始化蜂鸣器为高电平，避免上电误发声

	while(1)
	{	
		// LCD显示逻辑
		LCD_ShowString(1,1,"Responder:");
		LCD_ShowString(2,14,"-");
		LCD_ShowNum(2,13,User,1);
		LCD_ShowNum(2,15,Sec,2);
		// 犯规显示
		if(FoulUser != 0)
			LCD_ShowNum(1,16,FoulUser,1);
		else
			LCD_ShowString(1,16," ");
		// LCD计分显示
		LCD_ShowNum(2,1,SelectUser,1);    // 第二行第1列：当前选中选手编号（1-8）
		LCD_ShowNum(2,3,Score[SelectUser-1],3); // 第二行3-5列：对应选手分数（3位）
		
		// 独立按键处理（仅保留K1、K2）
		KeyNum=Key();
		if(KeyNum)		
		{		
			if(KeyNum==1) // K1：开始/暂停抢答
			{
				TimeLock=~TimeLock;
				ET1=1;
				Buzzer_Time(500); // 蜂鸣器响500ms
				TimeOutFlag = 0;
				FoulUser = 0;
                LED_AllOff(); // 开始抢答前熄灭所有LED
			}
			if(KeyNum==2) // K2：重置所有状态
			{
				TimeLock=0;
				Sec=MemoryTime;
				User=0;
				ET1=1;
				TimeOutFlag = 0;
				FoulUser = 0;
                LED_AllOff(); // 重置时熄灭所有LED
			}
			// 移除K3、K4处理逻辑，功能迁移到矩阵按键S12、S13
		}
		
		// 矩阵按键处理（新增S12、S13）
		UserKey=Matrix_Key();
		if(UserKey)
		{
			// 1. 选手抢答（S1~S8）
			if(User==0 && TimeLock && !TimeOutFlag && UserKey>=1 && UserKey<=8)
			{
				switch(UserKey)		
				{	
					case 1:{User=1;ET1=0;Buzzer_Time(500);LED_On(1);}break;
					case 2:{User=2;ET1=0;Buzzer_Time(500);LED_On(2);}break;
					case 3:{User=3;ET1=0;Buzzer_Time(500);LED_On(3);}break;
					case 4:{User=4;ET1=0;Buzzer_Time(500);LED_On(4);}break;
					case 5:{User=5;ET1=0;Buzzer_Time(500);LED_On(5);}break;
					case 6:{User=6;ET1=0;Buzzer_Time(500);LED_On(6);}break;
					case 7:{User=7;ET1=0;Buzzer_Time(500);LED_On(7);}break;
					case 8:{User=8;ET1=0;Buzzer_Time(500);LED_On(8);}break;		
				}
			}
			// 2. 犯规抢答（S1~S8）
			else if((!TimeLock || TimeOutFlag) && UserKey>=1 && UserKey<=8)
			{
				FoulUser = UserKey;
				Buzzer_Time(500); // 犯规时蜂鸣器响500ms
			}
			// 3. 计分/时间操作（S9~S13）
			else
			{
				switch(UserKey)
				{
					case 9: // S9：切换选中选手（1-8循环）
						SelectUser++;
						if(SelectUser>8) SelectUser=1;
						break;
					case 10: // S10：当前选手分数+10
						Score[SelectUser-1] += 10;
						break;
					case 11: // S11：当前选手分数-10（防止负数）
						if(Score[SelectUser-1] >= 10)
							Score[SelectUser-1] -= 10;
						break;
					case 12: // S12：加时间（取代原K3）
						if(TimeLock==0 && !TimeOutFlag)
						{
							if(Sec<60){Sec++;} 
							MemoryTime=Sec;
						}
						break;
					case 13: // S13：减时间（取代原K4）
						if(TimeLock==0 && !TimeOutFlag)
						{
							if(Sec>0){Sec--;} 
							MemoryTime=Sec;
						}
						break;
				}
			}
		}
	}
}

// 定时器0中断服务函数（按键扫描）
void Timer0_Routine() interrupt 1			
{
	static unsigned int T0Count1,T0Count2;
	TL0 = 0x18;		
	TH0 = 0xFC;		
	T0Count1++;
	T0Count2++;
	
	if(T0Count2>40)
	{
		T0Count2=0;
		Loop_MatrixKey(); // 矩阵按键扫描
	}	

	if(T0Count1>30)
	{
		T0Count1=0;
		Loop_Key(); // 独立按键扫描
	}
}

// 定时器1中断服务函数（倒计时）
void Timer1_Routine() interrupt 3
{
	static unsigned int T1Count;
	TL1 = 0xCD;		
	TH1 = 0xD4;	
	if(TimeLock && !TimeOutFlag)
	{	
		T1Count++;
		if(T1Count>=1000)		
		{
			T1Count=0;
			if(Sec>0)
			{
				Sec--;
			}
			else
			{
				TimeOutFlag = 1;    
				ET1 = 0;            
				Buzzer_Time(500);   // 超时蜂鸣器响500ms
				TimeLock = 0;       
                LED_AllOff(); // 超时后熄灭所有LED
			}
		}
	}
}





