section .data
	m1 db 'Accept 5 64 bit numbers', 0xa
	len1 equ $ - m1
	
	m2 db 'Display 5  64 bit numbers', 0xa
	len2 equ $ - m2
	
section .bss
	array resd 200    ; resd- for reserving the space
	counter resb 1

section .text
	global _start
_start:
	mov rax,1	;write syscall
	mov rdi,1	;destination index  stdout
	mov rsi,m1	;source index
	mov rdx,len1
	syscall 
	
	; Accept 5 64 bit numbers
	mov byte[counter],05
	mov rbx,00
		loop1:
			mov rax,0
			mov rdi,0
			mov rsi,array
			add rsi,rbx
			mov rdx,17
			syscall
			
			add rbx,17
			dec byte[counter]
			JNZ loop1
		
		
	mov rax,1	;write syscall
	mov rdi,1	;destination index  stdout
	mov rsi,m2	;source index
	mov rdx,len2
	syscall 
	
	; Display 5 64 bit numbers
	mov byte[counter], 05
	mov rbx,00
		loop2:
			mov rax,1
			mov rdi,1
			mov rsi,array
			add rsi,rbx
			mov rdx,17
			syscall
			
			add rbx,17
			dec byte[counter]
			JNZ loop2
	
	mov rax,60
	mov rdi,0
	syscall
	
