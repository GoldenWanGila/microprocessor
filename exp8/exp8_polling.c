#include "regx51.h"

void init_uart();
char recivevalue;

void main(){
	init_uart();
	while(1){
		if(RI == 1)
		{
			RI = 0;
			recivevalue = SBUF;
			P1 = recivevalue;
			if(recivevalue == 'p')
			{
				SBUF = recivevalue;
			}
		}
		
		if(TI == 1){
			TI = 0;
		}
	}
}

void init_uart(void){
	SCON = 0x50;
	TMOD = 0x20;
	TH1 = 0xE6;
	TR1 = 1;
}