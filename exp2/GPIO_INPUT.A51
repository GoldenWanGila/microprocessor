			ORG 0				;start from 0000H
			MOV DPTR, #TABLE	;DPTR point to TABLE
START:		MOV R0, #0			;initialize typed signal
			MOV R1, #3			;set 3 rows
			MOV R2, #11110111B	;set first row
SCAN:		MOV A, R2			;move R2 to A
			MOV P2, A			;move A to P2->input scanned signal
			JNB P2.7, KEYIN		;scan column 1
			INC R0				;add #01 into R0
			JNB P2.6, KEYIN		;scan column 2
			INC R0				;add #01 into R0
			JNB P2.5, KEYIN		;scan column 3
			INC R0				;add #01 into R0
			RR A				;right rotate A->next row
			MOV R2, A			;move A to R2
			DJNZ R1, SCAN		;scan 3 rows
			SJMP START			;jump to scan jeypad again
KEYIN:		CALL DEBOUNCE		;call DEBOUNCE function
			MOV A, R0			;move R0 to A->get typed signal
			MOVC A, @A+DPTR		;according A, get signal from TABLE
			MOV P1, A			;move A to P1->output displayed signal
			SJMP START			;jump to scan keypad again
DEBOUNCE:	MOV R4, #100		;move 50 times into R4
DE_500_us:	MOV R3, #250		;move 250times into R3
			DJNZ R3, $			;jump to itself R3 times
			DJNZ R4, DE_500_us	;delay 25ms
			RET					;return to main code
TABLE:		DB 11111001B		;display "1"
			DB 10100100B		;display "2"
			DB 10110000B		;display "3"
			DB 10011001B		;display "4"
			DB 10010010B		;display "5"
			DB 10000010B		;display "6"
			DB 11011000B		;display "7"
			DB 10000000B		;display "8"
			DB 10010000B		;display "9"
			END