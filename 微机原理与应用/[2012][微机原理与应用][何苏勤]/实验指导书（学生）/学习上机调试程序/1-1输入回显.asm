

code segment
   assume  cs:code
start:
   mov ah,01h
   int 21h
   mov ah,4ch
   int 21h
code ends
end start
