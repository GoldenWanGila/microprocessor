#include "regx51.h"

void init_uart();
char recivevalue;
char id_stack[9];
char ans[9] = {'E','9','4','0','7','6','1','0','2'};
char c[9] = {' ','c','o','r','r','e','c','t','\n'};
char w[6] = {'w','r','o','n','g','\n'};
int i;
int flag = 1;
int len_c = 9;
int len_w = 6;
int index = 0;
int check = 0;

void main(void){
	init_uart();
	while(1){
		if(recivevalue == 0x0D){
			recivevalue = '0';
			for(index; index > 0; index--){
				if(id_stack[index - 1] == ans[index - 1]){
					check++;
				}
			}
			if(check == 9){
				check = 0;
				flag = 1;
				SBUF = 0x0A;
				while(flag == 1);
				flag = 1;
				SBUF = 0x0D;
				while(flag == 1);
				for(i = 1; i <= len_c; i++){
					flag = 1;
					SBUF = c[i-1];
					while(flag == 1);
				}
				flag = 1;
				SBUF = 0x0D;
				while(flag == 1);
			}
			else{
				check = 0;
				flag = 1;
				SBUF = 0x0A;
				while(flag == 1);
				flag = 1;
				SBUF = 0x0D;
				while(flag == 1);
				for(i = 1; i <= len_w; i++){
					flag = 1;
					SBUF = w[i-1];
					while(flag == 1);
				}
				flag = 1;
				SBUF = 0x0D;
				while(flag == 1);
			}
		}
	}
}

void init_uart(void){
	SCON = 0x50;
	TMOD = 0x20;
	TH1 = 0xE6;
	TR1 = 1;
	IE = 0x90;
}

void UART_ISR(void) interrupt 4{
	if(RI == 1){
		RI = 0;
		recivevalue = SBUF;
		P1 = recivevalue;
		id_stack[index] = recivevalue;
		index++;
	}
	if(TI == 1){
		flag = 0;
		TI = 0;
	}
}