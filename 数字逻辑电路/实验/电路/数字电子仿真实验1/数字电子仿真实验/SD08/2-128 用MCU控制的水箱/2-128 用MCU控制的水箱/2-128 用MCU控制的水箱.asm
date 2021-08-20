$MOD51

$TITLE(PUMP CONTROL DEMO)

; Program Start

reset:
        NOP
        NOP
        ; move stack pointer past register banks
        MOV SP, #20H

; P0B4 - empty
; P0B3 - target
; P0B0 - kill button
; P0B1 - power button
; P0B2 - run button 
; P1B2 - forward fill
; P1B1 - reverse fill
; P1B0 - stop fill

begin:

start:
	MOV P1,#000H	
; Wait for power button to be pressed
startloop:
	MOV P1,#000H 
	JB P0.1,ready	; power button was pressed
	JMP startloop
	
ready:
	MOV P1,#001H	
; Wait for run button to be pressed to start filling tank
readyloop:
	JB P0.0,start	; kill button pressed
	JB P0.2,run	; run button pressed
	JMP readyloop

; start running
run:
	MOV P1,#001H	

; Fill in forward direction
fillfwd:
	MOV P1,#004H		; set fwd signal to high
	CALL outputdelay  	; hold fwd signal high
	CALL outputdelay
	MOV P1,#000H		; set fwd signal back to low
; Wait for set point to be reached
fillfwdloop:
	JB P0.0,fillfwdkill	; kill button pressed
	JB P0.3,fillfwdend 	; set point reached 

	JMP fillfwdloop
; Stop filling in fwd direction and start timer for 5 seconds
fillfwdend:
	MOV P1,#001H		; set stop signal to high
	CALL timerdelay		; go to timer routine 
	JMP fillrev		; timer has finished, start draining
; Kill button was pressed during filling in fwd direction
fillfwdkill:
	MOV P1,#001H		; set stop signal to high
	CALL outputdelay	; hold top signal high
	CALL outputdelay
	JMP start		; go back to beginning of program
	
; Fill in reverse direction (drain)	
fillrev:
	MOV P1,#002H		; set reverse signal to high
	CALL outputdelay	; hold reverse signal
	CALL outputdelay
	MOV P1,#000H		; set reverse signal to low
; Wait for tank to reach the empty point
fillrevloop:
	JB P0.0,fillrevkill 	; kill button pressed
	JB P0.4,fillrevend 	; empty point reached 

	JMP fillrevloop
; Finished draining, go back to ready state
fillrevend:
	MOV P1,#001H		; set stop signal to high
	JMP ready	
; Kill button was pressed during filling in reverse direction
fillrevkill:
	MOV P1,#001H		; send stop signal
	CALL outputdelay
	CALL outputdelay
	JMP start

; timer
timerstart:
	MOV P1,#001H		; set stop signal to high
	CALL outputdelay	; hold stop signal
	CALL outputdelay
	MOV P1,#000H		; set stop signal to low

	MOV R2,#39H	; call outputdelay 39H times to get 5 second delay
; Wait for timer to finish
timerloop:
	JB P0.0,timerdelaykill ; kill button pressed, stop timer timer
	CALL outputdelay	
	DJNZ R2,timerloop
	JMP timerdelayend

timerdelay:
	JMP timerstart
; Kill button was pressed during timer routine, wait for power button
timerdelaykill:
	JB P0.1,timerdelayready	; power button pressed
	JMP timerdelaykill
; Power button was pressed, wait for run button to resume timer
timerdelayready:
	JB P0.2,timerdelay	; run button pressed
	JB P0.0, timerdelaykill	; kill button pressed
	JMP timerdelayready
; Timer routine finished, return from call
timerdelayend:
	RET

; timer delays
outputdelay:
	PUSH ACC
	MOV A,R5
	PUSH ACC
	MOV A,R6
	PUSH ACC
	MOV R5,#50	; number of innerdelays to call
	CLR A

outerdelay:
	MOV R6,A
	CALL innerdelay
	DJNZ R5,outerdelay

	POP ACC
	MOV R6,A
	POP ACC
	MOV R5,A
	POP ACC
outputdelayend:
	RET
innerdelay:
	NOP
	NOP
	NOP
	NOP
	NOP
	DJNZ R6,innerdelay
	RET


END

