.data
PUBLIC Luck_ReadSyscall
PUBLIC Luck_WriteSyscall
Luck_ReadSyscall  dd 0
Luck_WriteSyscall dd 0

.code
PUBLIC Luck_ReadVirtualMemory
PUBLIC Luck_WriteVirtualMemory

Luck_ReadVirtualMemory PROC
	mov r10, rcx
	mov eax, Luck_ReadSyscall
	syscall
	ret
Luck_ReadVirtualMemory ENDP

Luck_WriteVirtualMemory PROC
	mov r10, rcx
	mov eax, Luck_WriteSyscall
	syscall
	ret
Luck_WriteVirtualMemory ENDP
END