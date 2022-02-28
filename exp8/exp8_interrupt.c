#include "regx51.h"

void init_uart();
void delay(int t);
char recivevalue;
char id_stack[9];
char ans[9] = {'E','9','4','0','7','6','1','0','2'};
int index = 0;
int check = 0;
char c[7] = {'c','o','r','r','e','c','t'};
int len_c = 7;
char w[5] = {'w','r','o','n','g'};
int len_w = 5;
int i;
int flag = 0;

void main(){
	init_uart();
	while(1){
		
	}
}

void init_uart(void){
	SCON = 0x50;
	TMOD = 0x20;
	TH1 = 0xE6;
	TR1 = 1;
	IE = 0x90;
}

void UART_ISR(void) interrupt 4
{
	if(RI == 1){
		RI = 0;
		recivevalue = SBUF;
		P1 = recivevalue;
		if(recivevalue == 0x0D){
			for(index; index > 0; index--){
				if(id_stack[index - 1] == ans[index - 1]){
					check++;
				}
			}
			if(check == 9){
				check = 0;
				SBUF = 0x0A;
				delay(10000);
				SBUF = 0x0D;
				delay(10000);
				for(i = 1; i <= len_c; i++){
					SBUF = c[i-1];
					delay(10000);
				}
				SBUF = 0x0A;
				delay(10000);
				SBUF = 0x0D;
			}
			else{
				check = 0;
				SBUF = 0x0A;
				delay(10000);
				SBUF = 0x0D;
				delay(10000);
				for(i = 1; i <= len_w; i++){
					SBUF = w[i-1];
					delay(10000);
				}
				SBUF = 0x0A;
				delay(10000);
				SBUF = 0x0D;
			}
		}
		else{
			id_stack[index] = recivevalue;
			index++;
		}
	}
	
	if(TI == 1){
		TI = 0;
		flag = 0;
	}
}

void delay(int t){
	for(;t>0;t--);
}