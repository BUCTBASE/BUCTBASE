code segment
   assume  cs:code
start:
   mov dl,'G';在此处添加代码
   mov ah,02h
   int 21h 	
   mov ah,4ch
   int 21h
code ends
end start
