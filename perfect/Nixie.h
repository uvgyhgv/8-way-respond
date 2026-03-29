#ifndef __NIXIE_H__
#define __NIXIE_H__

void Nixie_Loop();
void Nixie_Scan(unsigned char Location,Number);
void Nixie_SetBuf(unsigned char Location,Number);
unsigned char NixieTable[];
unsigned char Nixie_Buf[];



#endif