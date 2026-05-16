section .multiboot_header
align 4
    dd 0x1BADB002            ; Magic number
    dd 0x00                  ; Flags
    dd -(0x1BADB002 + 0x00)  ; Checksum

section .text
global _start	
extern main

extern panic

_start:
	cli
	call main
 
halt:
	push dword 0x00202165
	push dword 0x6C617461
	push dword 0x46206572
	push dword 0x6F727245
	mov eax, esp
	push dword 14
	push eax
	call panic
	add esp, 8
	
	hlt
	jmp halt
