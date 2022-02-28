#include "regx51.h"

void main(){
	IT0 = 0;							//
	EX0 = 1;							//
	EA = 1;								//
	P3 &= 0xEF;						//WR(P3.4) = 0, ADC start operate
	P3 |= 0x10;						//WR(P3.4) = 1, ADC stop operate
	while(1){ }						//infinite loop
}

void int_0(void) interrupt 0{
	P3 &= 0xDF;						//RD(P3.5) = 0, start loading Data
	if(P1 <= 0){
		P2 = 0x00;
	}
	else if(0 < P1 < 32){
		P2 = 0x01;
	}
	else if( 32 <= P1 < 64){
		P2 = 0x03;
	}
	else if( 64 <= P1 < 96){
		P2 = 0x07;
	}
	else if( 96 <= P1 < 128){
		P2 = 0x0F;
	}
	else if( 128 <= P1 < 160){
		P2 = 0x1F;
	}
	else if( 160 <= P1 < 192){
		P2 = 0x3F;
	}
	else if( 192 <= P1 < 224){
		P2 = 0x7F;
	}
	else if( 224 <= P1){
		P2 = 0xFF;
	}
	P3 |= 0x20;						//RD(P3.5) = 1, stop loading Data
	P3 &= 0xEF;
	P3 |= 0x10;						//WR(P3.4) = 1
}
