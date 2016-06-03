;	C STARTUP FOR STM8
;	WITHOUT ANY DATA INITIALIZATION
;	Copyright (c) 2006 by COSMIC Software
;
	xref	f_add, __stack
	xdef	f_exitA, f__stextA
;
;	startup routine from reset vector
;
	switch	.text
f__stextA:
;
;	initialize stack pointer
;
	ldw	x,#__stack	; stack pointer
	ldw	sp,x		; in place
	ldw	x,sp		; in place

;
;	execute main() function
;	may be called by a 'jpf' instruction if no return expected
;
	callf	f_add		; execute main
f_exitA:
	jra	f_exitA		; and stay here
;
	end
