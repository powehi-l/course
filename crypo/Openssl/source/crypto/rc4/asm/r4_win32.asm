	; Don't even think of reading this code
	; It was automatically generated by rc4-586.pl
	; Which is a perl program used to generate the x86 assember for
	; any of ELF, a.out, COFF, Win32, ...
	; eric <eay@cryptsoft.com>
	; 
%ifdef __omf__
section	code	use32 class=code
%else
section	.text
%endif
global	_RC4
_RC4:
	mov	edx,		DWORD [8+esp]
	cmp	edx,		0
	jne NEAR	@L000proceed
	ret
@L000proceed:
	; 
	push	ebp
	push	ebx
	push	esi
	xor	eax,		eax
	push	edi
	xor	ebx,		ebx
	mov	ebp,		DWORD [20+esp]
	mov	esi,		DWORD [28+esp]
	mov	al,		BYTE [ebp]
	mov	bl,		BYTE [4+ebp]
	mov	edi,		DWORD [32+esp]
	inc	al
	sub	esp,		12
	add	ebp,		8
	cmp	DWORD [256+ebp],-1
	je NEAR	@L001RC4_CHAR
	lea	edx,		[esi+edx-8]
	mov	DWORD [8+esp],	edx
	mov	ecx,		DWORD [eax*4+ebp]
	cmp	edx,		esi
	jb NEAR	@L002end
@L003start:
	add	esi,		8
	; Round 0
	add	bl,		cl
	mov	edx,		DWORD [ebx*4+ebp]
	mov	DWORD [eax*4+ebp],edx
	add	edx,		ecx
	mov	DWORD [ebx*4+ebp],ecx
	and	edx,		255
	inc	al
	mov	ecx,		DWORD [eax*4+ebp]
	mov	edx,		DWORD [edx*4+ebp]
	mov	BYTE [esp],	dl
	; Round 1
	add	bl,		cl
	mov	edx,		DWORD [ebx*4+ebp]
	mov	DWORD [eax*4+ebp],edx
	add	edx,		ecx
	mov	DWORD [ebx*4+ebp],ecx
	and	edx,		255
	inc	al
	mov	ecx,		DWORD [eax*4+ebp]
	mov	edx,		DWORD [edx*4+ebp]
	mov	BYTE [1+esp],	dl
	; Round 2
	add	bl,		cl
	mov	edx,		DWORD [ebx*4+ebp]
	mov	DWORD [eax*4+ebp],edx
	add	edx,		ecx
	mov	DWORD [ebx*4+ebp],ecx
	and	edx,		255
	inc	al
	mov	ecx,		DWORD [eax*4+ebp]
	mov	edx,		DWORD [edx*4+ebp]
	mov	BYTE [2+esp],	dl
	; Round 3
	add	bl,		cl
	mov	edx,		DWORD [ebx*4+ebp]
	mov	DWORD [eax*4+ebp],edx
	add	edx,		ecx
	mov	DWORD [ebx*4+ebp],ecx
	and	edx,		255
	inc	al
	mov	ecx,		DWORD [eax*4+ebp]
	mov	edx,		DWORD [edx*4+ebp]
	mov	BYTE [3+esp],	dl
	; Round 4
	add	bl,		cl
	mov	edx,		DWORD [ebx*4+ebp]
	mov	DWORD [eax*4+ebp],edx
	add	edx,		ecx
	mov	DWORD [ebx*4+ebp],ecx
	and	edx,		255
	inc	al
	mov	ecx,		DWORD [eax*4+ebp]
	mov	edx,		DWORD [edx*4+ebp]
	mov	BYTE [4+esp],	dl
	; Round 5
	add	bl,		cl
	mov	edx,		DWORD [ebx*4+ebp]
	mov	DWORD [eax*4+ebp],edx
	add	edx,		ecx
	mov	DWORD [ebx*4+ebp],ecx
	and	edx,		255
	inc	al
	mov	ecx,		DWORD [eax*4+ebp]
	mov	edx,		DWORD [edx*4+ebp]
	mov	BYTE [5+esp],	dl
	; Round 6
	add	bl,		cl
	mov	edx,		DWORD [ebx*4+ebp]
	mov	DWORD [eax*4+ebp],edx
	add	edx,		ecx
	mov	DWORD [ebx*4+ebp],ecx
	and	edx,		255
	inc	al
	mov	ecx,		DWORD [eax*4+ebp]
	mov	edx,		DWORD [edx*4+ebp]
	mov	BYTE [6+esp],	dl
	; Round 7
	add	bl,		cl
	mov	edx,		DWORD [ebx*4+ebp]
	mov	DWORD [eax*4+ebp],edx
	add	edx,		ecx
	mov	DWORD [ebx*4+ebp],ecx
	and	edx,		255
	inc	al
	mov	edx,		DWORD [edx*4+ebp]
	add	edi,		8
	mov	BYTE [7+esp],	dl
	; apply the cipher text
	mov	ecx,		DWORD [esp]
	mov	edx,		DWORD [esi-8]
	xor	ecx,		edx
	mov	edx,		DWORD [esi-4]
	mov	DWORD [edi-8],	ecx
	mov	ecx,		DWORD [4+esp]
	xor	ecx,		edx
	mov	edx,		DWORD [8+esp]
	mov	DWORD [edi-4],	ecx
	mov	ecx,		DWORD [eax*4+ebp]
	cmp	esi,		edx
	jbe NEAR	@L003start
@L002end:
	; Round 0
	add	edx,		8
	inc	esi
	cmp	edx,		esi
	jb NEAR	@L004finished
	mov	DWORD [8+esp],	edx
	add	bl,		cl
	mov	edx,		DWORD [ebx*4+ebp]
	mov	DWORD [eax*4+ebp],edx
	add	edx,		ecx
	mov	DWORD [ebx*4+ebp],ecx
	and	edx,		255
	inc	al
	mov	ecx,		DWORD [eax*4+ebp]
	mov	edx,		DWORD [edx*4+ebp]
	mov	dh,		BYTE [esi-1]
	xor	dl,		dh
	mov	BYTE [edi],	dl
	; Round 1
	mov	edx,		DWORD [8+esp]
	cmp	edx,		esi
	jbe NEAR	@L004finished
	inc	esi
	add	bl,		cl
	mov	edx,		DWORD [ebx*4+ebp]
	mov	DWORD [eax*4+ebp],edx
	add	edx,		ecx
	mov	DWORD [ebx*4+ebp],ecx
	and	edx,		255
	inc	al
	mov	ecx,		DWORD [eax*4+ebp]
	mov	edx,		DWORD [edx*4+ebp]
	mov	dh,		BYTE [esi-1]
	xor	dl,		dh
	mov	BYTE [1+edi],	dl
	; Round 2
	mov	edx,		DWORD [8+esp]
	cmp	edx,		esi
	jbe NEAR	@L004finished
	inc	esi
	add	bl,		cl
	mov	edx,		DWORD [ebx*4+ebp]
	mov	DWORD [eax*4+ebp],edx
	add	edx,		ecx
	mov	DWORD [ebx*4+ebp],ecx
	and	edx,		255
	inc	al
	mov	ecx,		DWORD [eax*4+ebp]
	mov	edx,		DWORD [edx*4+ebp]
	mov	dh,		BYTE [esi-1]
	xor	dl,		dh
	mov	BYTE [2+edi],	dl
	; Round 3
	mov	edx,		DWORD [8+esp]
	cmp	edx,		esi
	jbe NEAR	@L004finished
	inc	esi
	add	bl,		cl
	mov	edx,		DWORD [ebx*4+ebp]
	mov	DWORD [eax*4+ebp],edx
	add	edx,		ecx
	mov	DWORD [ebx*4+ebp],ecx
	and	edx,		255
	inc	al
	mov	ecx,		DWORD [eax*4+ebp]
	mov	edx,		DWORD [edx*4+ebp]
	mov	dh,		BYTE [esi-1]
	xor	dl,		dh
	mov	BYTE [3+edi],	dl
	; Round 4
	mov	edx,		DWORD [8+esp]
	cmp	edx,		esi
	jbe NEAR	@L004finished
	inc	esi
	add	bl,		cl
	mov	edx,		DWORD [ebx*4+ebp]
	mov	DWORD [eax*4+ebp],edx
	add	edx,		ecx
	mov	DWORD [ebx*4+ebp],ecx
	and	edx,		255
	inc	al
	mov	ecx,		DWORD [eax*4+ebp]
	mov	edx,		DWORD [edx*4+ebp]
	mov	dh,		BYTE [esi-1]
	xor	dl,		dh
	mov	BYTE [4+edi],	dl
	; Round 5
	mov	edx,		DWORD [8+esp]
	cmp	edx,		esi
	jbe NEAR	@L004finished
	inc	esi
	add	bl,		cl
	mov	edx,		DWORD [ebx*4+ebp]
	mov	DWORD [eax*4+ebp],edx
	add	edx,		ecx
	mov	DWORD [ebx*4+ebp],ecx
	and	edx,		255
	inc	al
	mov	ecx,		DWORD [eax*4+ebp]
	mov	edx,		DWORD [edx*4+ebp]
	mov	dh,		BYTE [esi-1]
	xor	dl,		dh
	mov	BYTE [5+edi],	dl
	; Round 6
	mov	edx,		DWORD [8+esp]
	cmp	edx,		esi
	jbe NEAR	@L004finished
	inc	esi
	add	bl,		cl
	mov	edx,		DWORD [ebx*4+ebp]
	mov	DWORD [eax*4+ebp],edx
	add	edx,		ecx
	mov	DWORD [ebx*4+ebp],ecx
	and	edx,		255
	inc	al
	mov	edx,		DWORD [edx*4+ebp]
	mov	dh,		BYTE [esi-1]
	xor	dl,		dh
	mov	BYTE [6+edi],	dl
	jmp	@L004finished
align	16
@L001RC4_CHAR:
	lea	edx,		[edx+esi]
	mov	DWORD [8+esp],	edx
	movzx	ecx,		BYTE [eax+ebp]
@L005RC4_CHAR_loop:
	add	bl,		cl
	movzx	edx,		BYTE [ebx+ebp]
	mov	BYTE [ebx+ebp],	cl
	mov	BYTE [eax+ebp],	dl
	add	dl,		cl
	movzx	edx,		BYTE [edx+ebp]
	add	al,		1
	xor	dl,		BYTE [esi]
	lea	esi,		[1+esi]
	movzx	ecx,		BYTE [eax+ebp]
	cmp	esi,		DWORD [8+esp]
	mov	BYTE [edi],	dl
	lea	edi,		[1+edi]
	jb NEAR	@L005RC4_CHAR_loop
@L004finished:
	dec	eax
	add	esp,		12
	mov	BYTE [ebp-4],	bl
	mov	BYTE [ebp-8],	al
	pop	edi
	pop	esi
	pop	ebx
	pop	ebp
	ret
