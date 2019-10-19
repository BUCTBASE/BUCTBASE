DATAS SEGMENT
    str db 100 dup(?) 
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
     lea dx,str
    mov str,100
    mov ah,0ah
    int 21h
    mov bx,0
    call changeline
re:
    mov dl,[str+2+bx]
    mov ah,2h
    int 21h
    cmp bl,[str+1]
    je bye
    inc bx
    jmp re
    
bye:
    MOV AH,4CH
    INT 21H
changeline	proc near
	mov dl,0dh
	mov ah,2h
	int 21h
	mov dl,0ah
	mov ah,2h
	int 21h
	ret
changeline endp
CODES ENDS
    END START

