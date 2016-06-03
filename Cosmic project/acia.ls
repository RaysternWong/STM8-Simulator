   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
   4                     ; Optimizer V4.3.6 - 29 Nov 2011
2082                     ; 26 char getch(void)
2082                     ; 27 	{
2083                     	switch	.text
2084  0000               f_getch:
2086  0000 88            	push	a
2087       00000001      OFST:	set	1
2090  0001 ce0002        	ldw	x,_ptlec
2091  0004               L7631:
2092                     ; 30 	while (ptlec == ptecr)		/* equal pointers => loop */
2094  0004 c30000        	cpw	x,_ptecr
2095  0007 27fb          	jreq	L7631
2096                     ; 32 	c = *ptlec++;			/* get the received char */
2098  0009 f6            	ld	a,(x)
2099  000a 5c            	incw	x
2100                     ; 33 	if (ptlec >= &buffer[SIZE])	/* put in in buffer */
2102  000b a30044        	cpw	x,#_buffer+64
2103  000e 2503          	jrult	L3731
2104                     ; 34 		ptlec = buffer;
2106  0010 ae0004        	ldw	x,#_buffer
2107  0013               L3731:
2108  0013 cf0002        	ldw	_ptlec,x
2109                     ; 35 	return (c);
2113  0016 5b01          	addw	sp,#1
2114  0018 87            	retf	
2147                     ; 40 void outch(char c)
2147                     ; 41 	{
2148                     	switch	.text
2149  0019               f_outch:
2151  0019 88            	push	a
2152       00000000      OFST:	set	0
2155  001a               L3141:
2156                     ; 42 	while (!(USART_SR & TRDE))	/* wait for READY */
2158  001a 720f4a30fb    	btjf	_USART_SR,#7,L3141
2159                     ; 44 	USART_DR = c;			/* send it */
2161  001f 7b01          	ld	a,(OFST+1,sp)
2162  0021 c74a31        	ld	_USART_DR,a
2163                     ; 45 	}
2166  0024 84            	pop	a
2167  0025 87            	retf	
2193                     ; 51 @interrupt void recept(void)
2193                     ; 52 	{
2194                     	switch	.text
2195  0026               f_recept:
2199                     ; 53 	USART_SR;			/* clear interrupt */
2201  0026 c64a30        	ld	a,_USART_SR
2202                     ; 54 	*ptecr++ = USART_DR;		/* get the char */
2204  0029 ce0000        	ldw	x,_ptecr
2205  002c c64a31        	ld	a,_USART_DR
2206  002f f7            	ld	(x),a
2207  0030 5c            	incw	x
2208                     ; 55 	if (ptecr >= &buffer[SIZE])	/* put it in buffer */
2210  0031 a30044        	cpw	x,#_buffer+64
2211  0034 2503          	jrult	L7241
2212                     ; 56 		ptecr = buffer;
2214  0036 ae0004        	ldw	x,#_buffer
2215  0039               L7241:
2216  0039 cf0000        	ldw	_ptecr,x
2217                     ; 57 	}
2220  003c 80            	iret	
2258                     ; 65  int add(int a, int b)
2258                     ; 66  {
2259                     	switch	.text
2260  003d               f_add:
2262  003d 89            	pushw	x
2263       00000000      OFST:	set	0
2266                     ; 67 	 return a+b;
2268  003e 72fb06        	addw	x,(OFST+6,sp)
2271  0041 5b02          	addw	sp,#2
2272  0043 87            	retf	
2310                     ; 70  int minus(int a, int b)
2310                     ; 71  {
2311                     	switch	.text
2312  0044               f_minus:
2314  0044 89            	pushw	x
2315       00000000      OFST:	set	0
2318                     ; 72 	 return a-b;
2320  0045 72f006        	subw	x,(OFST+6,sp)
2323  0048 5b02          	addw	sp,#2
2324  004a 87            	retf	
2366                     ; 76 void main(void)
2366                     ; 77 	{
2367                     	switch	.text
2368  004b               f_main:
2370  004b 89            	pushw	x
2371       00000002      OFST:	set	2
2374                     ; 78 	int result =0;
2376                     ; 80 	result = minus( 3 , 2 );
2378  004c ae0002        	ldw	x,#2
2379  004f 89            	pushw	x
2380  0050 5c            	incw	x
2381  0051 8d440044      	callf	f_minus
2383  0055 85            	popw	x
2384                     ; 81 	result = add( 2 , 3 );
2386  0056 ae0003        	ldw	x,#3
2387  0059 89            	pushw	x
2388  005a 5a            	decw	x
2389  005b 8d3d003d      	callf	f_add
2391  005f 5b02          	addw	sp,#2
2392                     ; 83 	result += 7;
2394  0061 1c0007        	addw	x,#7
2395  0064 1f01          	ldw	(OFST-1,sp),x
2396                     ; 85 	ptecr = ptlec = buffer;		/* initialize pointers */
2398  0066 ae0004        	ldw	x,#_buffer
2399  0069 cf0002        	ldw	_ptlec,x
2400  006c cf0000        	ldw	_ptecr,x
2401                     ; 86 	USART_BRR1 = 0xc9;		/* parameter for baud rate */
2403  006f 35c94a32      	mov	_USART_BRR1,#201
2404                     ; 87 	USART_CR1 = 0x00;		/* parameter for word length */
2406  0073 725f4a34      	clr	_USART_CR1
2407                     ; 88 	USART_CR2 = 0x2c;		/* parameters for interrupt */
2409  0077 352c4a35      	mov	_USART_CR2,#44
2410                     ; 89 	rim();				/* authorize interrupts */
2413  007b 9a            	rim	
2415  007c               L1051:
2416                     ; 94 		outch(getch());		/* get and put a char */
2418  007c 8d000000      	callf	f_getch
2420  0080 8d190019      	callf	f_outch
2423  0084 20f6          	jra	L1051
2467                     	xdef	f_main
2468                     	xdef	f_minus
2469                     	xdef	f_add
2470                     	xdef	f_recept
2471                     	xdef	f_outch
2472                     	xdef	f_getch
2473                     	switch	.bss
2474  0000               _ptecr:
2475  0000 0000          	ds.b	2
2476                     	xdef	_ptecr
2477  0002               _ptlec:
2478  0002 0000          	ds.b	2
2479                     	xdef	_ptlec
2480  0004               _buffer:
2481  0004 000000000000  	ds.b	64
2482                     	xdef	_buffer
2502                     	end
