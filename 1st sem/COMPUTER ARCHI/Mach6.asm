org 100h

jmp start

        oldfn db "C:\emu8086\vdrive\D\xyro.txt", 0   
        newfn db "C:\emu8086\vdrive\D\SALANATIN.txt",0
        ok db "File renamed$"
        del db " and Successfully Deleted file!$"
        notok db "Error! File not reanamed$"

start:
mov ax, cs
mov dx, ax
mov es, ax          

; rename txt file
mov ah, 56h
mov dx, offset oldfn    
mov di, offset newfn   
int 21h                

jc error
mov dx, offset ok   
mov ah, 09h
int 21h 
 
; delete txt file 
mov ah, 41h
mov dx, offset newfn    
int 21h

jc error                
mov dx, offset del      
mov ah, 09h
int 21h

jmp over

error:
    mov dx, offset notok
    mov ah, 09
    int 21h

over:

    mov ah, 4ch
    int 21h
    end start
ret