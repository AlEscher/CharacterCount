.intel_syntax noprefix
.global asm_charcount

.DATA             ;Create a near data segment.  Local variables are declared after
	.words:	.zero 1024
.CODE             ;Indicates the start of a code segment.

loopstart:	mov dl, byte ptr [edi]          // dl=data[0] 
			dword ptr [.words+edx*4]    // quantity[char]++
			inc eax
			cmp  0, [eax]
			jne loopstart
			mov eax , words
