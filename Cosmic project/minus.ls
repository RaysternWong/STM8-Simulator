   1                     ;	C STARTUP FOR STM8
   2                     ;	WITHOUT ANY DATA INITIALIZATION
   3                     ;	Copyright (c) 2006 by COSMIC Software
   4                     ;
   5                     	xref	f_minus, __stack
   6                     	xdef	f_exitB, f__stextB
   7                     ;
   8                     ;	startup routine from reset vector
   9                     ;
  10                     	switch	.text
  11  0000               f__stextB:
  12                     ;
  13                     ;	initialize stack pointer
  14                     ;
  15  0000 ae0000        	ldw	x,#__stack	; stack pointer
  16  0003 94            	ldw	sp,x		; in place
  17  0004 94            	ldw	sp,x		; in place
  18  0005 94            	ldw	sp,x		; in place
  19                     
  20                     ;
  21                     ;	execute main() function
  22                     ;	may be called by a 'jpf' instruction if no return expected
  23                     ;
  24  0006 8d000000      	callf	f_minus		; execute main
  25  000a               f_exitB:
  26  000a 20f4          	jra	f__stextB		; and stay here
  27                     ;
  28                     	end
