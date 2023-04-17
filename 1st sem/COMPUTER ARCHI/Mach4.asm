Nathaly Pearl F.               |   BSCS-NS-2AB
; CAO                                       |   Machine Problem 4

name "fileio"

; General rules for file system emulation:

; 1. The emulator emulates all drive paths in c:\emu8086\vdrive\c
;    Example: the real path for "c:\test1" is "c:\emu8086\vdrive\c\test1"

; 2. Paths without drive letter are emulated to c:\emu8086\MyBuild\
;    Example: the real path for "test2" is "c:\emu8086\MyBuild\test2"

org  100h

; Label
jmp start 

    dir1 db "c:\SALANATIN", 0

start:
    mov dx, ax

; CREATE MODE
; #1
; create directory: c:\emu8086\vdrive\c\test1

    mov dx, offset dir1 ; Get File Directory
    mov ah, 39h ; Create the File Directory, AH=39H
    int 21h

ret