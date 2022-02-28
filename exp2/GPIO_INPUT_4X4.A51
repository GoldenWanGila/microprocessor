			ORG 0				;start from 0000H
			MOV DPTR, #TABLE	;DPTR point to TABLE
START:		MOV R0, #0			;initialize typed signal
			MOV R1, #4			;set 4 rows
			MOV R2, #11110111B	;set first row
SCAN:		MOV A, R2			;move R2 to A
			MOV P2, A			;move A to P2->input scanned signal
			JNB P2.7, KEYIN		;scan column 1
			INC R0				;add #01 into R0
			JNB P2.6, KEYIN		;scan column 2
			INC R0				;add #01 into R0
			JNB P2.5, KEYIN		;scan column 3
			INC R0				;add #01 into R0
			JNB P2.4, KEYIN		;scan column 4
			INC R0				;add #01 into R0
			RR A				;right rotate A->next row
			MOV R2, A			;move A to R2
			DJNZ R1, SCAN		;scan 4 rows
			SJMP START			;jump to scan jeypad again
KEYIN:		CALL DEBOUNCE		;call DEBOUNCE function
			MOV A, R0			;move R0 to A->get typed signal
			MOVC A, @A+DPTR		;according A, get signal from TABLE
			MOV P1, A			;move A to P1->output displayed signal
			SJMP START			;jump to scan keypad again
DEBOUNCE:	MOV R4, #50			;move 50 times into R4
DE_500_us:	MOV R3, #250		;move 250times into R3
			DJNZ R3, $			;jump to itself R3 times
			DJNZ R4, DE_500_us	;delay 25ms
			RET					;return to main code
TABLE:		DB 11111001B		;display "1"
			DB 10100100B		;display "2"
			DB 10110000B		;display "3"
			DB 01000110B		;display "C"
			DB 10011001B		;display "4"
			DB 10010010B		;display "5"
			DB 10000010B		;display "6"
			DB 01000000B		;display "D"
			DB 11011000B		;display "7"
			DB 10000000B		;display "8"
			DB 10010000B		;display "9"
			DB 00000110B		;display "E"
			DB 00001000B		;display "A"
			DB 11000000B		;display "0"
			DB 00000000B		;display "B"
			DB 00001110B		;display "F"
			END