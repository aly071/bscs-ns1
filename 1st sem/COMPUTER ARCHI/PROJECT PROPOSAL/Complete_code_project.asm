                                            ;You may customize this and other start-up templates;
; The location of this template is c:\emu8086\inc\0_com_template.txt
include emu8086.inc  

name "printer"
.MODEL SMALL
.DATA                                            
        SIZE EQU 10
        HEAD DB  '                                 ',0dh, 0ah
             DB  '                    [<---------- Security lock ---------->]',0dh, 0ah, '$'
        MSG1 DB 13, 10, "     Select your Vault:",13,10, 0dh, 0ah, "     1. Vault A",13,10,"     2. Vault B",13,10,"     3. Vault C",13,10, 0dh, 0ah,"     Input Only [1-3]: $"
        MSG2 DB 13, 10,0dh, 0ah, '     Enter your Password: $' 
        MSG3 DB 13, 10, '     Invalid vault number. Please enter a number between 1 and 3.$'
        MSG4 DB 13, 10, '     Wrong Password! Access denied$'
        ;MSG5 DB 13, 10, ' Correct! Welcome to Vault$'
        MS1  DB 13, 10,' ',13,10, '                 [<---------- Welcome to Vault# 1 ---------->]',0dh, 0ah, '$'
        MS2  DB 13, 10,' ',13,10, '                 [<---------- Welcome to Vault# 2 ---------->]',0dh, 0ah, '$'
        MS3  DB 13, 10,' ',13,10, '                 [<---------- Welcome to Vault# 3 ---------->]',0dh, 0ah, '$'
        
        MSG6 DB 13, 10, ' Too Long password!$'
        MSG7 DB 13, 10, " You've entered the wrong password three times.", 0dh, 0ah 
             DB         " Your account and locker are temporarily locked." , 0dh, 0ah 
             DB         " Please contact the admin to recover your locker." , 0dh, 0ah
             DB         " The lock occurred on:$"    
        GOODBYE DB 0dh, 0ah,  "     Press any key to exit... $" 
        input db 13,10,"     Enter the weight [in KG]: $"                                                               
        overweight_msg db 0ah, 0dh, 0dh, 0ah,  "           We would like to inform you that your baggage",13,10, "           has been found to be overweight according to our regulations.",13,10, "           The weight limit for checked baggage is 50kg.",13,10,"$",13,10
        welcome_msg db 0ah, 0dh,0dh, 0ah, "           We are excited to welcome you to TUP-Manila!",13,10, "           We hope you have a great time as a student here. If you need",13,10, "           anything, don't hesitate to reach out to us.$",13,10
        TEMP_Pass DB 1 DUP(?)
        PassSize = $-Temp_Pass
        Password1 DB  1
        Password2 DB  2
        Password3 DB  3
        Counter DB 0
        ;curr_time db 0dh,0ah,0dh,0ah, ' Error Occurred at Time: $'
        ;curr_date db 0dh,0ah, ' Error Occurred at Date: $'
        vault_select1 db 0    
        
        msg db " WARNING! WARNING! WARNING! ", 0dh, 0ah, 0dh, 0ah 
        msg_vaul1  db ' ALERT:',13,10, ' Unauthorized access attempt detected.',13,10, 0dh, 0ah, ' Possible passcode ',13,10, ' input error by student or unauthorized individual.',13,10, 0dh, 0ah, ' Please investigate and take necessary  actions.', 0dh, 0ah 
        
        curr_date db 0dh,0ah, ' Error Occurred at Date: '
        day  db 0, 0, '-'
        mont db 0, 0, '-'
        year db 0, 0, 
        
        curr_time db 0dh,0ah,' Error Occurred at Time: ' 
        hour db 0, 0, ':'       
        minu db 0, 0, ':' 
        seco db 0, 0, ' '
             ;db 0Dh, 0Ah, 24h 
        
        msg_end db 0   
                
            
.CODE         



MAIN        PROC 
            MOV AX,@DATA  
            MOV DS,AX
            MOV AX,0000H 
           
                     

Title:      
            ;MOV AH, 09H
            ;MOV BL, 11
            ;MOV CX, 140
            ;INT 10H    
 
            LEA DX,HEAD     ; show the title
            MOV AH,09H
            INT 21H
            

Vault_Select:
prompt:     LEA DX,MSG1
            MOV AH,09H
            INT 21H
            
            ; Get input for vault selection
            CALL scan_num        ;read input
            MOV vault_select1, CL
            
            ; Check if input is valid
            CMP vault_select1, 1
            JE  PASS_PROMPT
            CMP vault_select1, 2
            JE  PASS_PROMPT
            CMP vault_select1, 3
            JE  PASS_PROMPT
            
            JMP ERRORMSG
            
PASS_PROMPT:LEA DX,MSG2
            MOV AH,09H
            INT 21H

Pass_INPUT: CALL   scan_num
            CMP    CL,0FH    ;check if single digit
            JAE    TooLong   

            ; Check password based on vault selection
            CMP vault_select1, 1
            JE  CheckPass1
            CMP vault_select1, 2
            JE  CheckPass2
            CMP vault_select1, 3
            JE  CheckPass3            
            JMP ERRORMSG

CheckPass1: MOV    BH,00H
            MOV    DL,Password1[BX]
            CMP    CL,DL
            JE     CORRECT1
            JMP INCORRECT
            
CheckPass2: MOV    BH,00H
            MOV    DL,Password2[BX]
            CMP    CL,DL
            JE     CORRECT2
            JMP INCORRECT
            
CheckPass3: MOV    BH,00H
            MOV    DL,Password3[BX]
            CMP CL,DL
            JE CORRECT3
            JMP INCORRECT  

            

CORRECT1:               
            LEA DX,MS1
            MOV AH,09H
            INT 21H
            CALL checkWeight
            
            ;JMP TERMINATE

CORRECT2:   LEA DX,MS2
            MOV AH,09H
            INT 21H      
            CALL checkWeight
            
            ;JMP TERMINATE

CORRECT3:   LEA DX,MS3
            MOV AH,09H
            INT 21H      
            CALL checkWeight
            
            ;JMP TERMINATE 
            
checkWeight:
            lea dx, input ; Load the address of the input prompt into DX
            mov ah, 09h
            int 21h
            
            mov dl, 10 ; Initialize DL with 10
            mov bl, 0 ; Initialize BL with 0  
    
scanNum:
            mov ah, 01h ; Read a character
            int 21h
            
            cmp al, 13 ; Check if user pressed ENTER KEY
            je compare
                
            mov ah, 0
            sub al, 48 ; ASCII to DECIMAL
                
            mov cl, al ; Store the new value in CL
            mov al, bl ; Store the previous value in AL
                
            mul dl ; Multiply the previous value with 10
                
            add al, cl ; Previous value + new value ( after previous value is multiplied with 10 )
            mov bl, al ; Store the result in BL
                  
            jmp scanNum 
    
compare:
            cmp bl, 50 ; Compare the input number with 50
            jle welcome ; Jump to 'welcome' if input number is less than or equal to 50
            jg overweight ; Jump to 'overweight' if input number is greater than 50

overweight:
            ; Print newline
            ;mov dl, 0DH
            ;mov ah, 02H
            ;int 21H
            
            ;mov dl, 0AH
            ;mov ah, 02H
            ;int 21H
            
            lea dx, overweight_msg ; Load the address of 'overweight' into DX
            mov ah, 09h            ; call to check if overweight
            int 21h     
            
            ; Print newline
            mov dl, 0DH
            mov ah, 02H
            int 21H
            
            mov dl, 0AH
            mov ah, 02H
            int 21H
                
            jmp checkWeight ; Jump back to 'checkWeight' to re-prompt for the weight

welcome:
            ;mov dl, 0DH
            ;mov ah, 02H
            ;int 21H
            
            ;mov dl, 0AH
            ;mov ah, 02H
            ;int 21H  
            
            lea dx, welcome_msg ; Load the address of 'welcome' into DX
            mov ah, 09h
            int 21h    
            
            JMP TERMINATE

            
ERRORMSG:      

            LEA DX,MSG3
            MOV AH,09H
            INT 21H   
            
            ; Print newline
            MOV DL, 0DH
            MOV AH, 02H
            INT 21H
            
            MOV DL, 0AH
            MOV AH, 02H
            INT 21H
            
            JMP prompt

CALCU_DECIMAL:                        ; calculate in decimal 
            push cx                    ; store value ng year
            xor ah, ah                  ;
            mov cl, 10                  ;add
            div cl 
            add ax, 3030h
            pop cx                      ;return
            ret 
            
            
LOCKED:     ; Display lock-out message with date and time     
             ;CX = YEAR
             ;DH = MONTH 
             ;DL = DAY
             ;AL = DAY OF WEEK

            mov ah, 2ah   ;date               
            int 21h 
    
            add cx, 0f830h     ;year          
            mov ax, cx 
            call CALCU_DECIMAL
            mov w. year, ax 
            mov al, dh            ;month       
            call CALCU_DECIMAL 
            mov w. mont, ax 
            mov al, dl               ;day    
            call CALCU_DECIMAL
            mov w. day, ax           
    
                               ;get the time
            mov ah, 2ch                  
            int 21h 
            mov al, ch              ; hour     
            call CALCU_DECIMAL 
            mov w. hour, ax 
            mov al, cl                  ;minute 
            call CALCU_DECIMAL 
            mov w. minu, ax 
            mov al, dh                  ;second 
            call CALCU_DECIMAL 
            mov w. seco, ax
    
            mov si, offset msg
            mov cx, offset msg_end - offset msg
            mov bh, 5
            JMP PRINTER_DEMO   
            

PRINTER_DEMO: 

            MOV dl, [si]
            MOV ah, 5       ; MS-DOS print function.
            INT 21h         ; print su=ingle character to admin
            INC si	        ; next char.
            LOOP PRINTER_DEMO 
            
            MOV DX,OFFSET GOODBYE  
            MOV AH, 9
            INT 21H
            
            mov ax, 0       ; wait for any key... / pause system
            int 16h

            MOV dl, 12      ; form feed code. page out! / clear system
            MOV ah, 5
            INT 21h 
            JMP EXIT
            
           ; JMP Vault_Select            


INCORRECT:     
            LEA DX,MSG4
            MOV AH,09H
            INT 21H   
                      
            ;call start          
            ; Print newline
            MOV DL, 0DH
            MOV AH, 02H
            INT 21H
            
            MOV DL, 0AH
            MOV AH, 02H
            INT 21H
            
            INC Counter
            CMP Counter,3
            ; Check if the counter is greater than or equal to 3
            JGE LOCKED
            JMP PASS_PROMPT

TooLong:    LEA DX,MSG6
            MOV AH,09H
            INT 21H      
             
            ; Print newline
            MOV DL, 0DH
            MOV AH, 02H
            INT 21H
            
            MOV DL, 0AH
            MOV AH, 02H
            INT 21H
            JMP PASS_PROMPT   
            
CLEAR_SCREEN:
                         
 
 
EXIT:      
    MOV AH, 4ch
    INT 21h               

DEFINE_SCAN_NUM
DEFINE_GET_STRING

TERMINATE:
END MAIN

; code to execute after correct password is entered
; or after all passwords have been checked and found to be incorrect
            
