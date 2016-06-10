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
2251                     ; 63 void main(void)
2251                     ; 64 	{
2252                     	switch	.text
2253  003d               f_main:
2257                     ; 65 	ptecr = ptlec = buffer;		/* initialize pointers */
2259  003d ae0004        	ldw	x,#_buffer
2260  0040 cf0002        	ldw	_ptlec,x
2261  0043 cf0000        	ldw	_ptecr,x
2262                     ; 66 	USART_BRR1 = 0xc9;		/* parameter for baud rate */
2264  0046 35c94a32      	mov	_USART_BRR1,#201
2265                     ; 67 	USART_CR1 = 0x00;		/* parameter for word length */
2267  004a 725f4a34      	clr	_USART_CR1
2268                     ; 68 	USART_CR2 = 0x2c;		/* parameters for interrupt */
2270  004e 352c4a35      	mov	_USART_CR2,#44
2271                     ; 69 	rim();				/* authorize interrupts */
2274  0052 9a            	rim	
2276  0053               L1441:
2277                     ; 71 		outch(getch());		/* get and put a char */
2279  0053 8d000000      	callf	f_getch
2281  0057 8d190019      	callf	f_outch
2284  005b 20f6          	jra	L1441
2328                     	xdef	f_main
2329                     	xdef	f_recept
2330                     	xdef	f_outch
2331                     	xdef	f_getch
2332                     	switch	.bss
2333  0000               _ptecr:
2334  0000 0000          	ds.b	2
2335                     	xdef	_ptecr
2336  0002               _ptlec:
2337  0002 0000          	ds.b	2
2338                     	xdef	_ptlec
2339  0004               _buffer:
2340  0004 000000000000  	ds.b	64
2341                     	xdef	_buffer
2361                     	end
