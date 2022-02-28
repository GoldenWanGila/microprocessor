#include <regx51.h>

#define TH0_init 0x06														//TH0 = 255 ~ 249
#define TL0_init 0x06														//TL0 = 255 ~ 249
#define Timer0_int_exe_time 1050								//the machine cycles when timer0 Interrupt

void delay(int t);
int counter;

void main(){
	TMOD = 0x02;																	//set timer0 to mode2, 8-bits and Auto-reload
	IP = 0x02;																		//set timer0 Interrupt to higher priority
	IE = 0x82;																		//enable timer0 Interrupt
	P1 = 0xff;
	TL0 = TL0_init;TH0 = TH0_init;								//set TH0, TL0
	TCON = 0x10;																	//enable timer0 --> open timer0
	
	while(1){
		delay(20000);																	//the maximum number of t is 32767(2^15-1)
		P1_0 = ~P1_0;
	}
}

void timer0_interrupt(void) interrupt 1 {
	counter++;
	if(counter == Timer0_int_exe_time){
		P1_1 = ~P1_1;
		counter = 0;
	}
}

void delay(int t){
	for(;t>0;t--);
		for(;t>0;t--);
}