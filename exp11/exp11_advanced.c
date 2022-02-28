#include "regx51.h"
void delay(int t);
void turn();

code char one_phase[] = {0x01, 0x04, 0x02, 0x08};
code char two_phase[] = {0x0C, 0x06, 0x03, 0x09};
code char one_a_half_phase[] = {0x0C, 0x01, 0x06, 0x04, 0x03, 0x02, 0x09, 0x08};
int dir, delay_time;
int delay_time_slow = 6000;
int delay_time_fast = 3000;
int debounce_time = 15000;

void main(){
	IT0 = 0;
	IT1 = 0;
	IE = 0x85;									//enable INT0 and INT1
	delay_time = delay_time_fast;
	dir = 1;
	while(1){
		turn();
	}
}

void turn(){
	int x;
	if(dir == 1){
		for(x=0; x<8; x++){
			P1 = one_a_half_phase[x];
			delay(delay_time);
		}
	}
	else{
		for(x=7; x>=0; x--){
			P1 = one_a_half_phase[x];
			delay(delay_time);
		}
	}
}

void delay(int t){
	int x;
	for(x=0; x<t; x++);
}

void int_0(void) interrupt 0{				//change rotate velocity
	if(delay_time == delay_time_fast)
		delay_time = delay_time_slow;
	else
		delay_time = delay_time_fast;
	delay(debounce_time);
}

void int_1(void) interrupt 2{				//change rotate direction
	if(dir == 1)
		dir = 0;
	else
		dir = 1;
	delay(debounce_time);
}