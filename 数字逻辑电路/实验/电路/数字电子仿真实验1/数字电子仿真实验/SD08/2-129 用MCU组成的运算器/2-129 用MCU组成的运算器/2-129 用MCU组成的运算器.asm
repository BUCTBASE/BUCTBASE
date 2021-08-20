; --------------------------------------------------------------
; Calculator Example 
;
; This program performs calculations of the form:
; 	operand1 operator operand2
; where the operator can be +,-,* or /.
; The operands 1 and 2 are positive integers between 0 and 9999.
; If the result of the calculations exceeds the range between
; 0 and 9999, it is considered an error.
;
; If an error occurs, "EEEE" will be applied to the output pins
; on ports P0 and P2.  The operands and operator are obtained by 
; reading the input signals received on port P1.
; --------------------------------------------------------------
$MOD51

$TITLE(TEST DEMO)

;
; Variables
;

NUM1L		DATA	020H	; low byte of first operand
NUM1H		DATA	021H	; high byte of first operand
OPERATOR	DATA	022H	; operator
NUM2L		DATA	023H	; low byte of second operand
NUM2H		DATA	024H	; high byte of second operand
EWB     DATA  0F8H  ;EWB TRACE SFR

; Program Start

reset:
        ; move stack pointer past register banks and variables
        MOV SP, #28H

	MOV P0, #00H
	MOV P2, #00H

	JMP readystate

; Initialize values in memory	
initVar:
	MOV NUM1L, #00H
	MOV NUM1H, #00H
	MOV OPERATOR, #0FH
	MOV NUM2L, #00H
	MOV NUM2H, #00H
	MOV R5, #00H
	MOV R6, #00H
	RET

; Getting first operand
getnum1:
	MOV A, R1
	MOV A, R5
	MOV NUM1L, A
	MOV A, R6
	MOV NUM1H, A
	
	CALL keyscan
	call displaynum

	MOV A, R1
	XRL A, #03H	; C pressed
	JZ readystate
	MOV A, R1
	XRL A, #02H	; = pressed
	JZ getoperator
	MOV A, R1
	JZ getnum1op	; operator pressed
	JMP getnum1	; continue getting first num

; Got first operand and operator
getnum1op:
	MOV R5, #00H
	MOV R6, #00H
	MOV A, R7
	MOV OPERATOR, A
	JMP getnum2

; Get operator
getoperator:
	MOV R5, #00H
	MOV R6, #00H
		
	CALL keyscan
	call displaynum

	MOV A, R1
	XRL A, #03H	; C pressed
	JZ readystate
	MOV A, R1
	XRL A, #02H 	; = pressed
	JZ getoperator
	MOV A, R1
	JZ gotop	; operator pressed
	JMP getnum1

; Got the operator
gotop:
	MOV A, R7
	MOV OPERATOR, A
	JMP getnum2

; First state that program goes to when started.
; Waiting for the first key press.
readystate:
	CALL initVar

	CALL keyscan
	CALL displaynum

	MOV A, R1
	XRL A, #03H
	JZ readystate	; C pressed
	MOV A, R1
	JZ readystate	; operator pressed
	MOV A, R1
	XRL A, #02H	; = pressed
	JZ readystate
	JMP getnum1

; Get first digit of second operand.
getnum2:
	MOV A, R5
	MOV NUM2L, A
	MOV A, R6
	MOV NUM2H, A

	CALL keyscan
	call displaynum
	
	MOV A, R1
	XRL A, #03H	; C pressed
	JZ readystate	
	MOV A, R1
	XRL A, #02H	; = pressed
	JZ getoperator
	MOV A, R1
	JZ gotop	; operator pressed
	JMP gettingnum2 ; continue getting second num

; Got first digit of second operand.  Continue
; getting subsequent digits of the operand or the next
; operator, = or C key press.
gettingnum2:
	MOV A, R5
	MOV NUM2L, A
	MOV A, R6
	MOV NUM2H, A

	CALL keyscan
	call displaynum

	MOV A, R1
	XRL A, #03H	; C pressed
	JZ readystate	
	MOV A, R1
	XRL A, #02H	; = pressed
	JZ calcgetop	; Go do calculation
	MOV A, R1 
	JZ calcgetnum2	; operator pressed; go do calculation
	JMP gettingnum2	

; calculate result then get next operator	
calcgetop:
	CALL calculate

	MOV A, R0
	XRL A, #0EEH
	JNZ calcgetopend
	MOV A, R1
	XRL A, #0EEH
	JZ readystate
calcgetopend: 
	MOV A, R0
	MOV NUM1L, A
	MOV A, R1
	MOV NUM1H, A
	JMP getoperator

; calculate result then get next number
calcgetnum2:
	CALL calculate
	
	MOV A, R0
	XRL A, #0EEH
	JNZ calcgetnum2end
	MOV A, R1
	XRL A, #0EEH
	JZ readystate
calcgetnum2end:
	MOV A, R0
	MOV NUM1L, A
	MOV A, R1
	MOV NUM1H, A
	MOV A, R7
	MOV OPERATOR, A
	MOV R5, #00H
	MOV R6, #00H
	JMP getnum2

; Perform +, -, * or / operations
; Input:
; Values stored in variables NUM1L, NUM1H, OPERATOR, NUM2L, NUM2H
; Output:
; R0 - low byte of result
; R1 - high byte of result
; Valid values of R1, R0 range from 0 to 270FH (9999 in base 10)
; In case of overflow or error, R0 and R1 will each contain #0EEh
calculate:
	PUSH ACC
	MOV A, R2
	PUSH ACC
	MOV A, R3
	PUSH ACC
	MOV A, R5
	PUSH ACC
	MOV A, R6
	PUSH ACC

	MOV R0, NUM1L
	MOV R1, NUM1H
	MOV R2, NUM2L
	MOV R3, NUM2H
calcAdd:
	MOV A, OPERATOR
	CJNE A, #0CH, calcSub
	CALL ADD16
	; check for overflow
	MOV A, #027H
	SUBB A, R1
	JC calcoverflow
	JNZ calcAddEnd
	MOV A, #0FH
	SUBB A, R0
	JC calcoverflow
calcAddEnd:
	JMP calcDisplay	
	
calcSub:
	MOV A, OPERATOR
	CJNE A, #08H, calcMul
	CALL SUB16
	MOV A, #027H
	SUBB A, R1
	JC calcoverflow
	JNZ calcSubEnd
	MOV A, #0FH 
	SUBB A, R0
	JNC calcSubEnd
	JMP calcoverflow
calcSubNeg:		; calculate the negative value in BCD 
	MOV A, R0	; (not used right now - negative values are
	MOV R2, A	; considered an overflow)
	MOV A, R1
	MOV R3, A
	MOV R0, #00H
	MOV R1, #00H
	CALL SUB16
	SETB C
calcSubEnd:
	JMP calcDisplay

calcMul:
	MOV A, OPERATOR
	CJNE A, #04H, calcDiv
	CALL UMUL16	
	; make sure that result is not greater than 270FH (9999 in base 10)
	MOV A, R3
	JNZ calcoverflow
	MOV A, R2
	JNZ calcoverflow
	
	MOV A, #027H
	SUBB A, R1
	JC calcoverflow
	JNZ calcMulEnd
	MOV A, #0FH
	SUBB A, R0
	JC calcoverflow
calcMulEnd:
	JMP calcDisplay

calcDiv:
	MOV A, OPERATOR 
	CJNE A, #00H, calcError
	; check divide by zero
	MOV A, R2
	JNZ calcDoDiv
	MOV A, R3
	JZ calcDivByZero
calcDoDiv:
	CALL UDIV16
	JMP calcDisplay

; error occurred
calcError:
; divide by zero error
calcDivByZero:
; overflow occurred
calcoverflow:
	MOV R0, #0EEH
	MOV R1, #0EEH
	MOV A, #0EEH
	MOV P2, A
	MOV P0, A
	CALL delay
	JMP calcEnd

; Display results of calculation.
; R0 and R1 contains low and high byte of result
calcDisplay:
	MOV A, R0
	MOV R5, A
	MOV A, R1
	MOV R6, A
	CALL HEXtoDEC
	MOV A, R5
	MOV P2, A
	MOV A, R6
	MOV P0, A
	CALL delay

calcEnd:
	POP ACC
	MOV A, R6
	POP ACC
	MOV A, R5
	POP ACC
	MOV A, R3
	POP ACC
	MOV A, R2
	POP ACC
	RET

; Returns key pressed in (row,col) format in R7
; For example: R7 = #028H if 1 was pressed on the keypad
;            Keypad 
; Row # -----------------
; 8     | 7   8   9   + |
; 4     | 4   5   6   - |
; 2     | 1   2   3   * |
; 1     | C   0   =   / |
;       -----------------
; Col #   8   4   2   1
keyscan:
	PUSH ACC
	MOV A, R0
	PUSH ACC
	MOV A, R1
	PUSH ACC
	MOV A, R3
	PUSH ACC

        MOV P1, #00FH

waitkeyuploop:
	MOV A, P1
	ANL A, #00FH
	XRL A, #00FH
	JNZ waitkeyuploop

        MOV P1, #00FH

anykeyloop:
        MOV A, P1
        ANL A, #00FH
        XRL A, #00FH
        JZ anykeyloop
        MOV R0, A
        XRL A, #00FH
        MOV R3, A

        call lineclear
        MOV P1, #0EFH
        MOV R1, #010H
        NOP
        MOV A, P1
        ANL A, #00FH
        XRL A, R3
	MOV R2,#000H
        JZ scanmatch

        call lineclear
        MOV P1, #0DFH
        MOV R1, #020H
        NOP
        MOV A, P1
        ANL A, #00FH
        XRL A, R3
	MOV R2, #001H
        JZ scanmatch

        call lineclear
        MOV P1, #0BFH
        MOV R1, #040H
        NOP
        MOV A, P1
        ANL A, #00FH
        XRL A, R3
	MOV R2, #002H
        JZ scanmatch

        call lineclear
        MOV P1, #07FH
        MOV R1, #080H
        NOP
        MOV A, P1
        ANL A, #00FH
        XRL A, R3
	MOV R2, #003H
        JZ scanmatch

        MOV P1, #00FH
        JMP keyscan
scanmatch:
        MOV A, R1
        ORL A, R0  	; combine into scancode

	MOV R7, A	; R7 contains value in (row,col) format
	
keyscanend:
	POP ACC
	MOV R3, A
	POP ACC
	MOV R1, A
	POP ACC
	MOV R0, A
	POP ACC
	RET

; Input:
; R7 contains last key pressed
; R2 contains last key pressed in converted number
; R5 and R6 contains current number in hex
; Output:
; R5 and R6 contains new number in hex 
displaynum:
	MOV A, R7

	MOV R4, A
	MOV A, R2
	MOV B, #04H
	MUL AB
	MOV R2, A
	MOV A, R4
	ANL A, #00FH
	MOV R4, #000H
getnumloop:
	INC R4
	RR A
	ANL A, #00FH
	JNZ getnumloop
	DEC R4
	MOV A, R2
	ADD A, R4
	MOV R1, A

checknum2:
	CJNE A, #02H,checknum5
	MOV A, #00H
	JMP numfound 
checknum5:
	CJNE A, #05H,checknum6
	MOV A, #03H
	JMP numfound 
checknum6:
	CJNE A, #06H,checknum7
	MOV A, #02H
	JMP numfound 
checknum7:
	CJNE A, #07H,checknum9
	MOV A, #01H
	JMP numfound 
checknum9:
	CJNE A, #09H,checknum10
	MOV A, #06H
	JMP numfound 
checknum10:
	CJNE A, #0AH,checknum11
	MOV A, #05H
	JMP numfound 
checknum11:
	CJNE A, #0BH,checknum13
	MOV A, #04H
	JMP numfound 
checknum13:
	CJNE A, #0DH,checknum14
	MOV A, #09H
	JMP numfound 
checknum14:
	CJNE A, #0EH,checknum15
	MOV A, #08H
	JMP numfound 
checknum15:
	CJNE A, #0FH, checkclear 
	MOV A, #07H
	JMP numfound 
checkclear:
	CJNE A, #03H, checkplus
	JMP cleardisplay

checkplus:
	CJNE A, #0CH, checkminus
	JMP operatorfound 
checkminus:
	CJNE A, #08H, checkmultiply
	JMP operatorfound 
checkmultiply:
	CJNE A, #04H, checkdivide
	JMP operatorfound 
checkdivide:
	CJNE A, #00H, checkequalop
	JMP operatorfound 
checkequalop:
	CJNE A, #01H, numnotfound
	JMP equalfound 

equalfound:
	MOV R1, #02H
	MOV R7, A
	JMP displaynumend 

operatorfound:
	MOV R1, #00H
	MOV R7, A
	JMP displaynumend

numnotfound:
	MOV R7, #0FFH
	JMP displaynumend

numfound:
	MOV R1, #01H
	MOV R7, A
	
	; convert hex to dec
	CALL HEXtoDEC

	; Shift number to the left before displaying
	call shiftnumleft

	; display decimal numbers	
	MOV A, R5	
	MOV P2, A

	MOV A, R6
	MOV P0, A
	call delay

	;convert decimal to hex and store
	CALL DECtoHEX

displaynumend:
	RET

; R7 contains the new value
; R5 and R6 contains low and high byte of number to be shifted
shiftnumleft:
	PUSH ACC
shiftnumleftstart:
	MOV A, R7
	PUSH ACC
	
	MOV A, R6
	MOV R7, #004H
checkhighnumloop:
	RLC A
	JC noshift 
	DJNZ R7, checkhighnumloop
	JMP doshift

noshift:
	POP ACC
	MOV R7, A
	JMP shiftnumleftend

doshift:
	POP ACC
	SWAP A
	MOV R7, #004H

shiftbitleft:
	RLC A
	PUSH ACC
	; Take carry bit and rotate it into R5
	MOV A, R5
	RLC A
	MOV R5, A
	MOV A, R6
	RLC A
	MOV R6, A
	POP ACC
	DJNZ R7, shiftbitleft
		
shiftnumleftend:
	POP ACC
	RET

cleardisplay:
	MOV R5, #00H
	MOV A, R5
	MOV P2, A
	MOV R6, #00H
	MOV A, R6
	MOV P0, A
	CALL delay

	MOV R1, #03H
	JMP displaynumend
	
; Wait for no key press
lineclear:
        MOV P1, #0FFH
lineclearloop:
        MOV A, P1
        XRL A, #0FFH
        JNZ lineclearloop
        RET

delay:
        JB EWB.0,delayend  ; Jump if using EWB Trace Mode

        PUSH ACC
        MOV A, R5
        PUSH ACC
        MOV A, R6
        PUSH ACC
        MOV R5, #50  ; number of innerdelay's to call
        CLR A

outerdelay:
        MOV R6, A
        CALL innerdelay
        DJNZ R5, outerdelay

        POP ACC
        MOV R6, A
        POP ACC
        MOV R5, A
        POP ACC
delayend:
        RET
innerdelay:
        NOP
        NOP
        NOP
        NOP
        NOP
        DJNZ R6, innerdelay
        RET

; 16-bit signed (2's complement) addition
; INPUT:
; R3, R2 = X
; R1, R0 = Y 
; OUTPUT:
; R1, R0 = SUM S = X+Y
; Carry C is set if S is out of range
ADD16:
	PUSH ACC
	MOV A, R0
	ADD A, R2
	MOV R0, A
	MOV A, R1
	ADDC A, R3
	MOV R1, A
	
	MOV C, OV	

	POP ACC
	RET

; 16- bit signed (2's complement) subtraction
; INPUT:
; R1, R0 = X
; R3, R2 = Y
; OUTPUT:
; R1, R0 = signed difference D = X-Y
; Carry C is set if the result D is out of range
SUB16:
	PUSH ACC
	MOV A, R0
	CLR C
	SUBB A, R2
	MOV R0, A
	MOV A, R1
	SUBB A, R3
	MOV R1, A
	MOV C, OV
	POP ACC
	RET

; 16-bit x 16-bit to 32-bit product unsigned mulitply
; INPUT:
; R1, R0 = X
; R3, R2 = Y
; OUTPUT:
; R3, R2, R1, R0 = product P = X*Y
UMUL16:
	PUSH ACC

	PUSH B
	PUSH DPL
	MOV A, R0
	MOV B, R2
	MUL AB		; multiply XL and YL
	PUSH ACC	; stack result low byte
	PUSH B		; stack result high byte
	MOV A, R0
	MOV B, R3
	MUL AB		; multiply XL and YH
	MOV R0, A	
	POP ACC
	ADD A, R0
	MOV R0, A
	CLR A
	ADDC A, B
	MOV DPL, A
	MOV A, R2
	MOV B, R1
	MUL AB		; multiply XH and YL
	ADD A, R0
	MOV R0, A
	MOV A, DPL
	ADDC A, B
	MOV DPL, A
	CLR A
	ADDC A, #00H
	PUSH ACC	; save intermediate carry
	MOV A, R3
	MOV B, R1
	MUL AB		; multiply XH and YH
	ADD A, DPL
	MOV R2, A
	POP ACC		; retrieve carry
	ADDC A, B
	MOV R3, A
	MOV A, R0	
	MOV R1, A
	POP ACC		; retrieve result low byte
	MOV R0, A

	POP DPL
	POP B

	POP ACC
	RET

; 16-bit / 16-bit to 16-bit quotient and remainder unsigned divide
; Input:
; R1, R0 = Dividend X
; R3, R2 = Divisor Y
; Output:
; R1, R0 = quotient Q of division Q = X/Y
; R3, R2 = remainder
; alters: acc, B, dpl, dph, r4, r5, r6, r7
UDIV16:
	PUSH ACC
	MOV A, R4
	PUSH ACC
	MOV A, R5
	PUSH ACC
	MOV A, R6
	PUSH ACC
	MOV A, R7
	PUSH ACC

	MOV R7, #0H	; clear partial remainder
	MOV R6, #0H
	MOV B, #016	; set loop count

DIV_LOOP:
	CLR C		; clear carry flag
	MOV A, R0	; shift the highest bit of
	RLC A		; the dividend into...
	MOV R0, A
	MOV A, R1
	RLC A
	MOV R1, A
	MOV A, R6	; the lowest bit of the
	RLC A		; partial remainder
	MOV R6, A
	MOV A, R7
	RLC A
	MOV R7, A
	MOV A, R6	; trial subtract divisor
	CLR C		; from partial remainder
	SUBB A, R2
	MOV DPL, A
	MOV A, R7
	SUBB A, R3
	MOV DPH, A
	CPL C		; complement external borrow
	JNC DIV_1	; update partial remainder if borrow
	MOV R7, DPH	; update partial remainder
	MOV R6, DPL
DIV_1:	
	MOV A, R4	; shift result bit into partial
	RLC A		; quotient
	MOV R4, A
	MOV A, R5
	RLC A
	MOV R5, A
	DJNZ B, DIV_LOOP
	MOV A, R5	; put quotient in R0 and R1
	MOV R1, A
	MOV A, R4
	MOV R0, A
	MOV A, R7	; get remainder, saved before the
	MOV R3, A	; last subtraction
	MOV A, R6
	MOV R2, A

	POP ACC
	MOV R7, A
	POP ACC
	MOV R6, A
	POP ACC
	MOV R5, A
	POP ACC
	MOV R4, A
	POP ACC
	RET

; Conversion from base 10 to hexadecimal number
; Input:
; R5 - low byte of decimal value, R6 - high byte of decimal value
; Output:
; R5 - low byte of hex value, R6 - high byte of hex value
DECtoHEX:
	PUSH ACC
	MOV A, R0
	PUSH ACC
	MOV A, R1
	PUSH ACC
	MOV A, R2
	PUSH ACC

	MOV A, R3
	PUSH ACC
	MOV A, R4
	PUSH ACC

	MOV A, R5
	ANL A, #0FH
	MOV R3, A
	MOV A, R5
	SWAP A
	ANL A, #0FH
	MOV B, #0AH
	MUL AB
	ADD A, R3
	MOV R3, A
	MOV A, B
	MOV R4, #0H
	ADDC A, R4
	MOV R4, A

	MOV A, R6
	ANL A, #0FH
	MOV B, #064H
	MUL AB
	MOV R0, A
	MOV R1, B
	MOV A, R3
	MOV R2, A

	MOV A, R4
	MOV R3, A

	CALL ADD16	
	MOV A, R0
	MOV R3, A
	MOV A, R1
	MOV R4, A

	MOV A, R6
	SWAP A
	ANL A, #0FH
	MOV R0, A
	MOV R1, #00H
	MOV R2, #0E8H
	MOV A, R3	; save R3 value
	PUSH ACC
	MOV R3, #03H
	CALL UMUL16	; result should never be greater than 270FH	

	POP ACC		; retrieve original value of R3
	MOV R2, A
	MOV A, R4
	MOV R3, A
	CALL ADD16
	MOV A, R0
	MOV R5, A
	MOV A, R1
	MOV R6, A

	POP ACC
	MOV R4, A
	POP ACC
	MOV R3, A 
	POP ACC
	MOV R2, A
	POP ACC
	MOV R1, A
	POP ACC
	MOV R0, A
	POP ACC
	RET

; Conversion from hexadecimal to base 10 value
; Input:
; R5 - low byte of hex value, R6 - high byte of hex value
; Output:
; R5 - low byte of decimal value, R6 - high byte of decimal value
HEXtoDEC:
	PUSH ACC
	MOV A, R0
	PUSH ACC
	MOV A, R1
	PUSH ACC
	MOV A, R2
	PUSH ACC
	
	MOV A, R3
	PUSH ACC
	MOV A, R4
	PUSH ACC

	MOV A, R5	; set up dividend
	MOV R0, A
	MOV A, R6
	MOV R1, A
	MOV R3, #0H	; set up divisor
	MOV R2, #0AH
	CALL UDIV16
	MOV A, R2
	MOV R5, A
	MOV R6, #0H
	MOV R2, #0AH	
	MOV R3, #0H
	CALL UDIV16
	MOV A, R5
	SWAP A
	ADD A, R2
	SWAP A
	MOV R5, A
	MOV R2, #0AH
	MOV R3, #0H
	CALL UDIV16
	MOV A, R2
	SWAP A
	ADD A, R0
	SWAP A
	MOV R6, A

	POP ACC
	MOV R4, A
	POP ACC
	MOV R3, A
	
	POP ACC
	MOV R2, A
	POP ACC
	MOV R1, A
	POP ACC
	MOV R0, A
	POP ACC
	RET	

END
