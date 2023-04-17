#start=led_display.exe# 

org 100h

        mov ax, 20
        mov cx, 21 
        
jmphere: ;
        out 199, ax ;
        dec ax
        
loop jmphere
        
mov ah, 4ch
int 21h    

ret

