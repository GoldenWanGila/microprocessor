#include "regx51.h"

int i = 0;

void print_msg(char msg);
void write(char cmd, char rs_value);
void delay(unsigned int t);

void main(){
	write(0x38, 0);												//功能設定8位元、2行、5x7字型
	write(0x0F, 0);												//顯示器設定開啟、有游標(會閃爍)
	write(0x06, 0);												//資料輸入LCD時，游標右移一格、顯示器不動
	write(0x01, 0);												//清除顯示器
	write(0x80, 0);												//DDRAM位址設定00H
	while(1){
		i++;
		if(i == 10000)
			i = 0;
		if(P2_0 == 0){
			write(0x01, 0);
			print_msg(i);
		}
	}
}

void print_msg(char msg){
		write(msg, 1);
}

void write(char cmd, char rs_value){
	P1 = cmd;
	P3_0 = rs_value;
	P3_1 = 1;
	delay(1000);
	P3_1 = 0;
	delay(1000);
}

void delay(unsigned int t){
	while(t--);
}