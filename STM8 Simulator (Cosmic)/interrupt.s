;	C STARTUP FOR STM8
;	WITHOUT ANY DATA INITIALIZATION
;	Copyright (c) 2006 by COSMIC Software
;
	xref	f_recept, __stack
	xdef	f_exitIRQ, f__stextIRQ
;
;	startup routine from reset vector
;
	switch	.text
f__stextIRQ:
;
;	initialize stack pointer
;
	ldw	x,#__stack	; stack pointer
	ldw	sp,x		; in place
;
;	execute main() function
;	may be called by a 'jpf' instruction if no return expected
;
	callf	f_recept	; execute main
f_exitIRQ:
	jra	f_exitIRQ		; and stay here
;
	end
