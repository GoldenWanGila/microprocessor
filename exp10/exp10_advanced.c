#include "regx51.h"

void print_msg(char* msg);
void write(char cmd, char rs_value);
void delay(unsigned int i);

void main(){
	write(0x38, 0);
	write(0x0F, 0);
	write(0x06, 0);
	write(0x01, 0);

	write(0x40, 0);										//01000000B
	write(0x00, 1);										//000 00000B
	write(0x41, 0);										//01000001B
	write(0x0A, 1);										//000 01010B
	write(0x42, 0);										//01000010B
	write(0x1F, 1);										//000 11111B
	write(0x43, 0);										//01000011B
	write(0x1F, 1);										//000 11111B
	write(0x44, 0);										//01000100B
	write(0x0E, 1);										//000 01110B
	write(0x45, 0);										//01000101B
	write(0x04, 1);										//000 00100B
	write(0x46, 0);										//01000110B
	write(0x00, 1);										//000 00000B
	write(0x47, 0);										//01000111B
	write(0x00, 1);										//000 00000B
	
	write(0x48, 0);										//01000000B
	write(0x00, 1);										//000 00000B
	write(0x49, 0);										//01000001B
	write(0x1F, 1);										//000 11111B
	write(0x4A, 0);										//01000010B
	write(0x15, 1);										//000 10101B
	write(0x4B, 0);										//01000011B
	write(0x1F, 1);										//000 11111B
	write(0x4C, 0);										//01000100B
	write(0x1F, 1);										//000 11111B
	write(0x4D, 0);										//01000101B
	write(0x0A, 1);										//000 01010B
	write(0x4E, 0);										//01000110B
	write(0x1B, 1);										//000 11011B
	write(0x4F, 0);										//01000111B
	write(0x00, 1);										//000 00000B
	
	write(0x80, 0);
	write(0x00, 1);
	
	write(0xC0, 0);
	write(0x01, 1);
	while(1);
}

/*void print_msg(char*msg){
	for(; *msg != '\0'; ++msg)
		write(*msg, 1);
}*/

void write(char cmd, char rs_value){
	P1 = cmd;
	P3_0 = rs_value;
	P3_1 = 1;
	delay(100);
	P3_1 = 0;
	delay(100);
}

void delay(unsigned int i){
	while(i--);
}