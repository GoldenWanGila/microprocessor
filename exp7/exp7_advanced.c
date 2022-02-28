#include <regx51.h>

void delay(int t);

void main(){
	int R0 = 0xFE;
	P1 = R0;
	while(1){
		if(P3_2 == 0){
			P1 = R0;
			delay(20000);
			delay(20000);
			delay(20000);
			delay(20000);
			R0 = (R0 << 1) + 1;
			if(R0 == 0xFF){
				R0 = 0xFE;
			}
		}
	}
}

void delay(int t){
	int a = t;
	int b = t;
	for(;a>0;a--);
		for(;b>0;b--);
}
