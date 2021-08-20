ORG 0000H   ；指令存放的首地址
LJMP MAIN   ；跳转到MIAN
ORG 0030H   ；MAIN程序地址

MAIN:
    MOV P1,#00100001B       ；点亮南北绿灯和东西红灯
    LCALL   Delay           ；调用延时子程序
    MOV P1,#00100010B       ；点亮南北黄灯和东西红灯
    LCALL   Delay           ；调用延时子程序
    MOV P1,#00001100B       ；点亮南北红灯和东西绿灯
    LCALL   Delay           ；调用延时子程序
    MOV P1,#00010100B       ；点亮南北红灯和东西黄灯
    LCALL   Delay           ；调用延时子程序
    SJMP    MAIN            ；跳转至MAIN，循环

Delay:  MOV  R5,#50 ；外层循环次数(R5)<-50
D1: MOV  R6,#100    ；中层循环次数(R6)<-100
D2: MOV  R7,#100    ；内层循环次数 (R7)<-100
D3: DJNZ    R7,D3   ；(R7)<-(R7)-1，若(R7)≠0则跳转至D3
    DJNZ    R6,D2   ；(R6)<-(R6)-1，若(R6)≠0则跳转至D2
    DJNZ    R5,D1   ；(R5)<-(R5)-1，若(R5)≠0则跳转至D1
    RETI            ；返回

END