			ORG			0
			SJMP		SETUP
			ORG			03H
			JMP			INT0_ISR
SETUP:		MOV			DPTR, #TABLE		;DPTR point to TABLE
			MOV			IE, #10000001B
			MOV			SP, #30H
			SETB		IT0
			MOV			P3, #11011111B		;using for choose 2nd 7-segment
			MOV			P1, #11000000B		;let 2nd 7-segment show 0
			MOV			R5, #0
			MOV			R7, #0
START:		MOV			R0, #0				;initialize typed signal
			MOV			R1, #4				;set 4 row
			MOV			R2, #11110111B		;set first row
SCAN:		MOV			A, R2				;move R2 to A
			MOV			P2, A				;input scanned signal
			JNB			P2.7, KEYIN_SPE		;scan column 1
			INC			R0
			JNB			P2.6, KEYIN_SPE		;scan column 2
			INC			R0
			JNB			P2.5, KEYIN_SPE		;scan column 3
			INC			R0
			JNB			P2.4, COUNTDOWN
			RR			A
			MOV			R2, A
			DJNZ		R1, SCAN
			SJMP		START
KEYIN_SPE:	CALL		DEBOUNCE
			DJNZ		R1, KEYIN
			CJNE		R0, #12, LABEL1
LABEL1:		CJNE		R0, #11, INCFUNCT
			JMP			DECFUNCT
COUNTDOWN:	CALL		DEBOUNCE
			DEC			R5
			MOV			A, R5
			MOVC		A, @A+DPTR
			MOV			P1, A
			CALL		DE_1_s
			CJNE		R5, #0, COUNTDOWN
			MOV			P1, #11000000B
			CJNE		R7, #0, SHOW_SAVE
			JMP			START
KEYIN:		MOV			A, R0
			MOV			R5, A
			MOVC		A, @A+DPTR
			MOV			P1, A
			SJMP		START
SHOW_SAVE:	CALL		DE_1_s
			MOV			A, R7
			MOV			R5, A
			MOVC		A, @A+DPTR
			MOV			P1, A
			JMP			START
DEBOUNCE:	MOV			R4, #250
DE_500_us:	MOV			R3, #250
			DJNZ		R3, $
			DJNZ		R4, DE_500_us
			RET
DE_1_s:		MOV			R6, #8
DE_125_ms:	MOV			R4, #250
DE_500us:	MOV			R3, #250
			DJNZ		R3, $
			DJNZ		R4, DE_500us
			DJNZ		R6, DE_125_ms
			RET
DE_100_ms:	MOV			R4, #200
DE500us:	MOV			R3, #250
			DJNZ		R3, $
			DJNZ		R4, DE500us
			RET
INCFUNCT:	INC			R5
			MOV			A, R5
			MOVC		A, @A+DPTR
			MOV			P1, A
			JMP			START
DECFUNCT:	DEC			R5
			MOV			A, R5
			MOVC		A, @A+DPTR
			MOV			P1, A
			JMP			START
INT0_ISR:	PUSH		PSW
			PUSH		ACC
			MOV			A, R5
			MOV			R7, A
			POP			ACC
			POP			PSW
			RETI
TABLE:		DB 			11111001B			;display "1"
			DB 			10100100B			;display "2"
			DB 			10110000B			;display "3"
			DB 			10011001B			;display "4"
			DB 			10010010B			;display "5"
			DB 			10000010B			;display "6"
			DB 			11011000B			;display "7"
			DB 			10000000B			;display "8"
			DB 			10010000B			;display "9"
			END