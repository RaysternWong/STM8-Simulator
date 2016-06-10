   1                     ;	C STARTUP FOR STM8
   2                     ;	WITHOUT ANY DATA INITIALIZATION
   3                     ;	Copyright (c) 2006 by COSMIC Software
   4                     ;
   5                     	xref	f_recept, __stack
   6                     	xdef	f_exitIRQ, f__stextIRQ
   7                     ;
   8                     ;	startup routine from reset vector
   9                     ;
  10                     	switch	.text
  11  0000               f__stextIRQ:
  12                     ;
  13                     ;	initialize stack pointer
  14                     ;
  15  0000 ae0000        	ldw	x,#__stack	; stack pointer
  16  0003 94            	ldw	sp,x		; in place
  17                     ;
  18                     ;	execute main() function
  19                     ;	may be called by a 'jpf' instruction if no return expected
  20                     ;
  21  0004 8d000000      	callf	f_recept	; execute main
  22  0008               f_exitIRQ:
  23  0008 20fe          	jra	f_exitIRQ		; and stay here
  24                     ;
  25                     	end
