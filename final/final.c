#include "regx51.h"

int i = 0;

void print_msg(char msg);
void write(char cmd, char rs_value);
void delay(unsigned int t);

void main(){
	write(0x38, 0);												//�\��]�w8�줸�B2��B5x7�r��
	write(0x0F, 0);												//��ܾ��]�w�}�ҡB�����(�|�{�{)
	write(0x06, 0);												//��ƿ�JLCD�ɡA��Хk���@��B��ܾ�����
	write(0x01, 0);												//�M����ܾ�
	write(0x80, 0);												//DDRAM��}�]�w00H
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