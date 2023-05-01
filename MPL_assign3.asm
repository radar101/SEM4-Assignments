section .data
array db 50h,30h,60h,19h,20h

msg1 db 10,"To find the largest number in an array",10
msg1len equ $-msg1
msg2 db 10,"Number of elements in the array: ",10
msg2len equ $-msg2
msg3 db 10,10,"Largest number in array is: ",10
msg3len equ $-msg3

section .bss
counter resb 1
result resb 4

%macro write 2
mov rax,01
mov rdi,01
mov rsi,%1
mov rdx,%2
%endmacro

section .text
global _start
_start:
write msg1,msg1len
write msg2,msg2len
mov byte[counter],05
mov rsi,array

next:
mov al,[rsi]
push rsi
call disp
pop rsi
inc rsi
dec byte[counter]
jnz next

write msg3,msg3len
mov byte[counter],05
mov rsi,array
mov al, 0 ;al is 8 bit register which stores max

repeat:
cmp al, [rsi] ;compare operand 1 with operand 2 by calculating op1-op2
jg skip
mov al, [rsi]

skip:
inc rsi
dec byte[counter]
jnz repeat

call disp

mov rax,60
mov rdi,1
syscall

disp:
mov bl,al
mov rdi,result
mov cx,02

up1:
rol bl,04       ;rotate number left by 4 bits
mov al,bl       ;move lower bit in dl
and al,0fh ;get only LSB
cmp al,09h ;compare with 39h
jg add_37 ;if greater than 39h skip add 37
add al,30h
jmp skip1 ;else add 30

add_37:
add al,37h

skip1:
mov [rdi],al ;store ascii code in result variable
inc rdi ;point to next byte
dec cx ;decrement the count of digits to display
jnz up1 ;if not zero jump to repeat

write result,4

mov rax,60
mov rdi,0
syscall
