;	C STARTUP FOR STM8
;	WITHOUT ANY DATA INITIALIZATION
;	Copyright (c) 2006 by COSMIC Software
;
	xref	f_recept, __stack
	xdef	f_exitC, f__stextC
;
;	startup routine from reset vector
;
	switch	.text
f__stextC:
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
	callf	f_recept	; execute main
f_exitC:
	jra	f_exitC		; and stay here
;
	end
