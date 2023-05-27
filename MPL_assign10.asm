section .bss

  number: resb 1
  temp: resb 1
  num: resb 1
  n: resw 1
  nod: resb 1

section .data

msg1: db "Enter the number : "
size1: equ $-msg1
msg2: db "factorial of  number: "
size2: equ $-msg2
changeline: db " ",0xa
size3: equ $-changeline


section .text
  global _start

_start:
 
;Printing the message to enter the number
  mov eax, 4
  mov ebx, 1
  mov ecx, msg1
  mov edx, size1
  int 80h
 
  ;Reading the number
  mov eax, 3
  mov ebx, 0
  mov ecx, number
  mov edx, 1
  int 80h
 
  sub byte[number], 30h
  mov al, byte[number]
  mov ah,0
  mov word[n],ax

call fact

  mov word[num],cx
  mov byte[nod], 0 ;No of digits...

  ;to display msg2
  mov eax, 4
  mov ebx, 1
  mov ecx, msg2
  mov edx, size2
  int 80h

extract_no:

  cmp word[num], 0
  je print_no
  inc byte[nod]
  mov dx, 0
  mov ax, word[num]
  mov bx, 10
  div bx
  push dx
  mov word[num], ax
  jmp extract_no

print_no:
  cmp byte[nod], 0
  je end_print
  dec byte[nod]
  pop dx
  mov byte[temp], dl
  add byte[temp], 30h


  mov eax, 4
  mov ebx, 1
  mov ecx, temp
  mov edx, 1
  int 80h

  jmp print_no

end_print:
    ; for new line
    mov eax, 4
    mov ebx, 1
    mov ecx, changeline
    mov edx, size3
    int 80h
 
    mov eax, 1
    mov ebx, 0
    int 80h

fact:
 
  mov ax, word[n]
  cmp ax, 0
  je terminate
  push word[n]

  dec word[n]
  call fact

  pop word[n]
  mov dx, word[n]

  mov ax, cx
  mul dx
  mov cx, ax
  jmp exit
 
terminate:
  mov cx, 1

exit:
  ret
