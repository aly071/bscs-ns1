
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

mov ah, 9h
lea dx, fullname
int 21h

mov ah, 2Ah
int 21h

cmp al, 12
jne xmas_false
cmp ah, 25
jne xmas_false

mov ah, 09h
lea dx, xmasEvent
int 21h
jmp exit

    xmas_false:
        mov ah, 9h
        lea dx, haveagreatday
        int 21h    
    exit:
        mov ah, 4Ch
        int 21h
        

ret
      fullname db "Nathaly Pearl F. Salanatin", 0Dh, 0Ah, 24h, '$'
      xmasEvent db "HO HO HO! Have a jolly Merry Christmas", 0Dh, 0Ah, 24h, '$' 
      haveagreatday db "Have a Great Day", 0Dh, 0Ah, 24h,'$'


