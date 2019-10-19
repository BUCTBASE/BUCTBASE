DATAS SEGMENT
    str1 db 'Enter keyword:$'  
    str2 db 'Enter sentence:$'
    str3 db 'Match at location:$'
    str4 db 'H of the sentence$'
    str5 db 'No match$'
    key db 50 dup(?)
    sen db 100 dup(?)
DATAS ENDS


output macro str
	lea dx,str
	mov ah,9
	int 21h
	endm
change  macro p
	local re,n1,n2
	push ax
	push bx
	push cx
	push dx
	mov bx,p
	mov cx,4
re:
	push cx
	mov cl,4
	rol bx,cl
	push bx
	and bx,0fh
	add bx,30h
	cmp bx,'9'
	jle n2
	add bx,7h
	jmp n2
n1:
	add bx,30
n2:
	mov dl,bl
	mov ah,2
	int 21h
	pop bx
	pop cx
	loop re
	pop dx
	pop cx
	pop bx
	pop ax
	endm
CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    output str1
    lea dx,key
    mov key,50
    mov ah,0ah
    int 21h
    call CRLF
gonext:
    output str2
    mov bx,0
lo:
    mov ah,01h
    int 21h
    cmp al,1bh
    je exit
    cmp al,0dh
    je CR
    mov sen[bx+2],al
    inc bx
    jmp lo 
CR:
	mov sen+1,bl
    call CRLF
	mov al,sen+1
	cmp al,key+1
	jl nomatch
	cmp key+1,0
	je nomatch
	mov ax,seg key
	mov es,ax
	mov bx,0
next:
	mov cx,0
	mov cl,key+1
	cld
	lea si,sen[bx+2]
	lea di,key+2
    repe cmpsb ds:[si],es:[di]
    je match
    inc bx
    cmp bl,sen+1
    jl next
    jmp nomatch
match:
	output str3
	inc bx
	change bx
	output str4
	call CRLF
	jmp gonext 
	
nomatch:
	output str5
	call CRLF
	jmp gonext
exit:
    MOV AH,4CH
    INT 21H
CRLF proc near
	mov ah,2
	mov dl,0dh
	int 21h
	mov dl,0ah
	int 21h
	ret
CRLF endp
CODES ENDS
    END START

