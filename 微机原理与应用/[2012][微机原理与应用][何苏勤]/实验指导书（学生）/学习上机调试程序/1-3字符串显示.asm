data segment
str db 'I love DOTA$'
data ends

code segment
        assume  cs:code, ds:data
start:
        mov ax,data
        mov ds,ax
        lea dx,str
        mov ah,09h             
        int 21h
        mov ah,4ch
        int 21h
code ends
end start
