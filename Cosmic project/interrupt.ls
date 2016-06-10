   1                     ;	C STARTUP FOR STM8
   2                     ;	WITHOUT ANY DATA INITIALIZATION
   3                     ;	Copyright (c) 2006 by COSMIC Software
   4                     ;
   5                     	xref	f_recept, __stack
   6                     	xdef	f_exitC, f__stextC
   7                     ;
   8                     ;	startup routine from reset vector
   9                     ;
  10                     	switch	.text
  11  0000               f__stextC:
  12                     ;
  13                     ;	initialize stack pointer
  14                     ;
  15  0000 ae0000        	ldw	x,#__stack	; stack pointer
  16  0003 94            	ldw	sp,x		; in place
  17  0004 96            	ldw	x,sp		; in place
  18                     
  19                     ;
  20                     ;	execute main() function
  21                     ;	may be called by a 'jpf' instruction if no return expected
  22                     ;
  23  0005 8d000000      	callf	f_recept	; execute main
  24  0009               f_exitC:
  25  0009 20fe          	jra	f_exitC		; and stay here
  26                     ;
  27                     	end
