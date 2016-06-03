;	C STARTUP FOR STM8
;	WITHOUT ANY DATA INITIALIZATION
;	Copyright (c) 2006 by COSMIC Software
;
	xref	f_minus, __stack
	xdef	f_exitB, f__stextB
;
;	startup routine from reset vector
;
	switch	.text
f__stextB:
;
;	initialize stack pointer
;
	ldw	x,#__stack	; stack pointer
	ldw	sp,x		; in place
	ldw	sp,x		; in place
	ldw	sp,x		; in place

;
;	execute main() function
;	may be called by a 'jpf' instruction if no return expected
;
	callf	f_minus		; execute main
f_exitB:
	jra	f__stextB		; and stay here
;
	end
