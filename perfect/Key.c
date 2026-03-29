#include <REGX52.H>
#include "INTRINS.H"

// 全局变量：存储独立按键/矩阵按键键值
unsigned char Key_KeyNum, Key_KeyNumber;

// ========== 独立按键读取（仅保留K1、K2） ==========
unsigned char Key()
{	
	unsigned char Temp = 0;
	Temp = Key_KeyNum;
	Key_KeyNum = 0;
	return Temp;	
}

// ========== 独立按键检测（删除K3、K4，P3.3专属蜂鸣器） ==========
unsigned char KeyNumber()
{	
	unsigned char KeyNum = 0;
	if(P3_1 == 0){KeyNum = 1;}  // K1：开始/暂停抢答（保留）
	if(P3_0 == 0){KeyNum = 2;}  // K2：重置状态（保留）
	// 删除K3（P3_2）、K4（P3_3），P3_3专属蜂鸣器，避免冲突
	return KeyNum;
}

// ========== 独立按键扫描（逻辑不变） ==========
void Loop_Key()
{	
	static unsigned char LastKey = 0, NowKey = 0;
	LastKey = NowKey;
	NowKey = KeyNumber();
	if(LastKey != 0 && NowKey == 0) // 松开触发
	{
		Key_KeyNum = LastKey;
	}	
}

// ========== 矩阵按键读取（逻辑不变） ==========
unsigned char Matrix_Key()
{
	unsigned char Temp;
	Temp = Key_KeyNumber;
	Key_KeyNumber = 0;
	return Temp;
}

// ========== 矩阵按键检测（新增S12、S13，匹配行P17~P14、列P13~P10） ==========
unsigned char MatrixKey()
{
	unsigned char KeyNumber = 0;

	// 行1：P17（R1）→ 拉低P17，检测列P13~P10
	P1 = 0xFF;        // 所有引脚置1，清除串扰
	P1_7 = 0;         // 拉低行1（P17）
	if(P1_3 == 0){KeyNumber = 1;}  // 列1（P13）→ S1=1
	if(P1_2 == 0){KeyNumber = 2;}  // 列2（P12）→ S2=2
	if(P1_1 == 0){KeyNumber = 3;}  // 列3（P11）→ S3=3
	if(P1_0 == 0){KeyNumber = 4;}  // 列4（P10）→ S4=4
	P1_7 = 1;         // 恢复行1电平

	// 行2：P16（R2）→ 拉低P16，检测列P13~P10
	P1 = 0xFF;
	P1_6 = 0;         // 拉低行2（P16）
	if(P1_3 == 0){KeyNumber = 5;}  // 列1（P13）→ S5=5
	if(P1_2 == 0){KeyNumber = 6;}  // 列2（P12）→ S6=6
	if(P1_1 == 0){KeyNumber = 7;}  // 列3（P11）→ S7=7
	if(P1_0 == 0){KeyNumber = 8;}  // 列4（P10）→ S8=8
	P1_6 = 1;         // 恢复行2电平

	// 行3：P15（R3）→ 拉低P15，检测列P13~P10（新增S12）
	P1 = 0xFF;
	P1_5 = 0;         // 拉低行3（P15）
	if(P1_3 == 0){KeyNumber = 9;}  // 列1（P13）→ S9=9
	if(P1_2 == 0){KeyNumber = 10;} // 列2（P12）→ S10=10
	if(P1_1 == 0){KeyNumber = 11;} // 列3（P11）→ S11=11
	if(P1_0 == 0){KeyNumber = 12;} // 列4（P10）→ S12=12（加时间）
	P1_5 = 1;         // 恢复行3电平

	// 行4：P14（R4）→ 拉低P14，检测列P13~P10（新增S13）
	P1 = 0xFF;
	P1_4 = 0;         // 拉低行4（P14）
	if(P1_3 == 0){KeyNumber = 13;} // 列1（P13）→ S13=13（减时间）
	// 行4其他列可留空，暂无扩展
	P1_4 = 1;         // 恢复行4电平

	return KeyNumber;
}

// ========== 矩阵按键扫描（逻辑不变，自动传递1-13键值） ==========
void Loop_MatrixKey()
{
	static unsigned char LastKey = 0, NowKey = 0;
	LastKey = NowKey;
	NowKey = MatrixKey();
	if(LastKey != 0 && NowKey == 0)
	{
		Key_KeyNumber = LastKey; // 传递S1-S13所有键值
	}
}





//#include <REGX52.H>

//// 全局变量：存储独立按键/矩阵按键键值
//unsigned char Key_KeyNum, Key_KeyNumber;

//// ========== 独立按键读取（原有不变） ==========
//unsigned char Key()
//{	
//	unsigned char Temp = 0;
//	Temp = Key_KeyNum;
//	Key_KeyNum = 0;
//	return Temp;	
//}

//// ========== 独立按键检测（原有不变） ==========
//unsigned char KeyNumber()
//{	
//	unsigned char KeyNum = 0;
//	if(P3_1 == 0){KeyNum = 1;}
//	if(P3_0 == 0){KeyNum = 2;}
//	if(P3_2 == 0){KeyNum = 3;}
//	if(P3_3 == 0){KeyNum = 4;}
//	return KeyNum;
//}

//// ========== 独立按键扫描（原有不变） ==========
//void Loop_Key()
//{	
//	static unsigned char LastKey = 0, NowKey = 0;
//	LastKey = NowKey;
//	NowKey = KeyNumber();
//	if(LastKey != 0 && NowKey == 0) // 松开触发
//	{
//		Key_KeyNum = LastKey;
//	}	
//}

//// ========== 矩阵按键读取（原有不变） ==========
//unsigned char Matrix_Key()
//{
//	unsigned char Temp;
//	Temp = Key_KeyNumber;
//	Key_KeyNumber = 0;
//	return Temp;
//}

//// ========== 矩阵按键检测（核心修正：匹配行=P17~P14、列=P13~P10） ==========
//unsigned char MatrixKey()
//{
//	unsigned char KeyNumber = 0;

//	// 行1：P17（R1）→ 拉低P17，检测列P13~P10
//	P1 = 0xFF;        // 所有引脚置1，清除串扰
//	P1_7 = 0;         // 拉低行1（P17）
//	if(P1_3 == 0){KeyNumber = 1;}  // 列1（P13）→ S1=1
//	if(P1_2 == 0){KeyNumber = 2;}  // 列2（P12）→ S2=2
//	if(P1_1 == 0){KeyNumber = 3;}  // 列3（P11）→ S3=3
//	if(P1_0 == 0){KeyNumber = 4;}  // 列4（P10）→ S4=4
//	P1_7 = 1;         // 恢复行1电平

//	// 行2：P16（R2）→ 拉低P16，检测列P13~P10
//	P1 = 0xFF;
//	P1_6 = 0;         // 拉低行2（P16）
//	if(P1_3 == 0){KeyNumber = 5;}  // 列1（P13）→ S5=5
//	if(P1_2 == 0){KeyNumber = 6;}  // 列2（P12）→ S6=6
//	if(P1_1 == 0){KeyNumber = 7;}  // 列3（P11）→ S7=7
//	if(P1_0 == 0){KeyNumber = 8;}  // 列4（P10）→ S8=8
//	P1_6 = 1;         // 恢复行2电平

//	// 行3：P15（R3）→ 拉低P15，检测列P13~P10
//	P1 = 0xFF;
//	P1_5 = 0;         // 拉低行3（P15）
//	if(P1_3 == 0){KeyNumber = 9;}  // 列1（P13）→ S9=9
//	if(P1_2 == 0){KeyNumber = 10;} // 列2（P12）→ S10=10
//	if(P1_1 == 0){KeyNumber = 11;} // 列3（P11）→ S11=11
//	P1_5 = 1;         // 恢复行3电平

//	// 行4：P14（R4）→ 拉低P14，检测列P13~P10（可留空，或扩展其他按键）
//	P1 = 0xFF;
//	P1_4 = 0;         // 拉低行4（P14）
//	// 若有其他按键可在此扩展，暂无则留空
//	P1_4 = 1;         // 恢复行4电平

//	return KeyNumber;
//}

//void Loop_MatrixKey()
//{
//	static unsigned char LastKey = 0, NowKey = 0;
//	LastKey = NowKey;
//	NowKey = MatrixKey();
//	if(LastKey != 0 && NowKey == 0)
//	{
//		Key_KeyNumber = LastKey; // 自动传递1-11所有键值
//	}
//}

////这是矩阵按键的封装，引脚为行：P17到P14，列是P13到P10，修改这个矩阵按键的封装，增加S12和S13按键，取代主函数原本独立按键K3和K4，加减时间的功能，把P3.3引脚单独给蜂鸣器，原本独立按键的加减时间区间功能改为矩阵按键的S12和S13，把矩阵按键的封装和修改后的主函数都给我