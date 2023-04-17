; SAlanatin, Nathaly Pearl F.       | BSCS NS 2AB
; CAO                               |   Machine Problem #3
  
name "attrib"

org  100h

jmp start

; Define some data

filename   db      "c:\salanatin.txt", 0
sOK        db      "File Found!", 0dh, 0ah 
sOUT       db      "Attribute/s Set$"
sERR       db      "file does not exist. (expected i/o error)", 0dh, 0ah
           db      ' you need to manually create and copy "test.txt" to:', 0dh, 0ah
           db      ' "c:\emu8086\vdrive\c"  before running this example.$ '



start: 

xor cx, cx

mov     ah, 43h       
mov     al, 1          
mov     cx, 3          
mov     dx, offset filename  
int     21h             
jc      error             

mov dx, offset sOK     
mov ah, 9            
int 21h              

jmp wait_any_key

error: 
    mov dx, offset sERR  
    mov ah, 9           
    int 21h           

wait_any_key:

    mov ah, 0           
    int 16h                   

ret