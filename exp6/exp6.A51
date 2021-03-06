			ORG 	00H
			SJMP 	MAIN
			ORG		03H
			SJMP	INT0_ISR
MAIN:		MOV 	IE, #10000001B
			MOV		SP, #30H
			SETB	IT0				;Have this, falling edge; otherwise, low level
			MOV		A, #00000000B
LOOP:		MOV 	P1, A
			CALL 	DELAY
			CPL		A
			SJMP	LOOP
INT0_ISR:	PUSH 	PSW
			PUSH	ACC
			SETB	RS0
			MOV		A, #11111110B
			MOV		R0, #24
ROTATE_L:	MOV		P1, A
			CALL 	DELAY
			RL		A
			DJNZ	R0, ROTATE_L
			POP		ACC
			POP		PSW
			RETI
DELAY:		MOV		R7, #200
D1:			MOV		R6, #250
			DJNZ	R6, $
			DJNZ	R7, D1
			RET
			END