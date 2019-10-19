
data segment
        str db 'error$'
data ends

code segment
        assume  cs:code, ds:data
start:
               mov ax,data
               mov ds,ax
                mov ah,07h
	int 21h    
	cmp al,61h
	js error
	cmp al,7ah
	jg error
	sub al,32
	mov dl,al
	mov ah,2h
	int 21h
	jmp bye
error:
	lea dx,str
	mov ah,9h
	int 21h
bye:
        mov ah,4ch
        int 21h
code ends
end start
