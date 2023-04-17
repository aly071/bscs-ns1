
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

mov ah, 9h
lea dx, fullname
int 21h

mov ah, 2Ch
int 21h

cmp ch, 12
jb morning

cmp ch, 18
jb noon

jmp evening

    morning: 
        mov ah, 9h
        lea dx, morningEvent
        int 21h
        jmp exit
        
    noon:
        mov ah, 9h
        lea dx, noonEvent
        int 21h
        jmp exit
        
    evening:
        mov ah, 9h
        lea dx, eveningEvent
                
    exit:
        mov ah, 4ch
        int 21h
ret

  fullname db "Nathaly Pearl F. Salanatin", 0Dh, 0Ah, 24h, '$'
  morningEvent db "Good Morning, Have a nice day!", 0Dh, 0Ah, 24h, '$'
  noonEvent db "Good Afternoon, Have nice day!", 0Dh, 0Ah, 24h, '$'
  eveningEvent db "Good Evening, Have a nice day!", 0Dh, 0Ah, 24h, '$'


