			ORG			0
			SJMP		MAIN
			ORG			03H
			SJMP		INT0_ISR
MAIN:		MOV			R0, #11111100B
			MOV			IE, #10000001B
			MOV			A, #00000000B
LOOP:		MOV			P1, R0	
			SJMP		LOOP
INT0_ISR:	PUSH		PSW
			PUSH		ACC
			MOV			P1, R0
			MOV			R1, #2
D1:			MOV			R2, #250
D2:			MOV			R3, #250
			DJNZ		R3, $
			DJNZ		R2, D2
			DJNZ		R1, D1
			MOV			A, R0
			RL			A
			MOV			R0, A
			POP			ACC
			POP			PSW
			RETI
			END