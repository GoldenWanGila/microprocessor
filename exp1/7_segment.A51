		ORG 0					;start address is 0
		MOV DPTR, #TABLE		;DPTR point to TABLE
START:	MOV R0, #4				;4 LED
		MOV R1, #0				;table index
		MOV R2, #01111111B		;LED drive pin
LOOP:	MOV P3, R2				;select LED
		MOV A, R1				;move R1 to A
		MOVC A, @A+DPTR			;get value from table
		MOV P1, A				;move value to P1
		CALL DELAY				;delay 0.5ms
		INC R1					;increase R1
		MOV A, R2				;move R2 to A
		RR A					;rotate A
		MOV R2, A				;move A back to R2
		DJNZ R0, LOOP			;decrement R0 until 0
		SJMP START				;jump to start
DELAY:	MOV R4,	#250
D1:		MOV R3, #250			;loop 250 times
		DJNZ R3, $				;decrement R3 until 0
		DJNZ R4, D1
		RET						;return from subrotine
TABLE:	DB 083H					;6
		DB 0F9H					;1
		DB 0C0H					;0
		DB 0A4H					;2
		END						;end of program