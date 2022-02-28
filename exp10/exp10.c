#include "regx51.h"

//code char LCD_pos_1st[] = {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F};

void print_msg(char msg);
void write(char cmd, char rs_value);
void delay(unsigned int t);

int num = 0;

void main(){
	write(0x38, 0);
	write(0x0E, 0);
	write(0x06, 0);
	write(0x01, 0);
	while(1){
		write(0xC0, 0);
		if(num < 10)
			print_msg(num+'0');
		else if(num < 100){
			print_msg(num/10+'0');
			print_msg(num%10+'0');
		}
		else{
			print_msg(num/100+'0');
			print_msg(num/10+'0');
			print_msg(num%10+'0');
		}
		num++;
		delay(10000);
	}
}

void print_msg(char msg){
		write(msg, 1);
}

void write(char cmd, char rs_value){
	P1 = cmd;
	P3_0 = rs_value;
	P3_1 = 1;
	delay(100);
	P3_1 = 0;
	delay(100);
}

void delay(unsigned int t){
	while(t--);
}