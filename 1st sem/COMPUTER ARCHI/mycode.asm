
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

; add your code here 

mov ah, 9;
LEA dx, MSG;
int 21h
mov ah, 4ch;
int 21h

ret
;
MSG db "Hi, My name is Nathaly Pearl F. Salanatin", 0Dh, 0Ah, 24h



