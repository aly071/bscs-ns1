
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

mov cx, 3 ;

loophere: 

    mov ah, 9
    lea dx, string
    int 21h
    loop loophere ;
    
mov ah, 4ch ;
int 21h

ret

string db "this is a loop", 0Ah,0Dh,"$"


