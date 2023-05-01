;Assignment No-5
;Write an X86/64 ALP to count number of positive and negative numbers from the array. 


%macro print 2
mov rax,01
mov rdi,01
mov rsi,%1
mov rdx,%2
syscall
%endmacro


;______________________________ .data section_________________________________________
section .data
msg1 db "Count of Positive numbers:"
len1 equ $-msg1
msg2 db "Count of negative numbers:"
len2 equ $-msg2
array db 10,12,-21,-12,-19,-34,41

______________________________ .bss section_________________________________________
section .data
section .bss
count resb 2
pcount resb 2
ncount resb 2
totalcount resb 2

______________________________ . text section_________________________________________
section .data

section .text
global _start
_start:

mov byte[count],07
mov byte[pcount],00
mov byte[ncount],00

mov rsi,array

Up:
        mov al,00
        add al,[rsi]
        js neg
        inc byte[pcount]
        jmp Down
        neg:
        inc byte[ncount]

Down:
        add rsi,01
        dec byte[count]
        jnz Up

mov bl,[pcount]
mov dl,[ncount]
b1:

print msg1,len1
mov bh,[pcount]
call disp



print msg2,len2
mov bh,[ncount]
call disp

mov rax,60
mov rdi,00
syscall

disp:
mov byte[count],02

loop:
        rol bh,04
        mov al,bh
        AND al,0FH
        cmp al,09
        jbe l1
        add al,07h
        l1:add al,30h
        mov[totalcount],al
        print totalcount,02
        dec byte[count]
        jnz loop
ret


;___________________________Output__________________________
;Count of Positive numbers:03Count of negative numbers:04
