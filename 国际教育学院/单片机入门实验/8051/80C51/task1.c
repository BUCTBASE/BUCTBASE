ORG    0000H     
AJMP    MAIN    ;转主程序

/*****主程序*****/
ORG    0050H    
MAIN:	
    MOV        DPTR,#LED_TABLE    ;表首地址
	MOV        R2,#6   ;循环次数计数器
	MOV        R1,#0   ;查状态表指针
	MOV        P1,#0   ;初始化LED输出

LOOP:	
    MOV        A,R1
	MOVC      A,@A+DPTR       ;查LED_TABLE状态
	MOV        P1,A      ;输出P1，控制LED灯
	LCALL      DELAY   ;进入延时子程序
	INC   R1         ;每轮状态表指针向后移动一位
	DJNZ       R2, LOOP     ;循环递减，不为0时进入下一个状态
	SJMP       MAIN    ;每6次重新初始化，进入下一轮循环

/*****状态表*****/
LED_TABLE:	
	DB    00000001B, 00000010B, 00000100B, 00001000B, 00010000B, 00100000B  ;交通灯的四个状态

/*****延时子程序*****/
DELAY:   ;嵌套延迟，共延迟2*100*100*100us=2s	
    MOV       R0,#100      
LOOP1:	
    MOV       R3,#100      
LOOP2:	
    MOV       R4,#100
LOOP3:
    DJNZ       R4,LOOP3
	DJNZ       R3,LOOP2         
	DJNZ       R0,LOOP1         
RET         ;返回主程序

END