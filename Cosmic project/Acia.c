/*	STM8 EXAMPLE PROGRAM WITH INTERRUPT HANDLING
 *	Copyright (c) 2007 by COSMIC Software
 *
 *	Each character received is copied in a buffer
 *	by the interrupt routine. The main program reads
 *	characters from the buffer and echoes them.
 */
#include <iostm8.h>

#define SIZE	64		/* buffer size */
#define TRDE	0x80		/* transmit ready bit */

/*	Authorize interrupts.
 */
#define rim() _asm("rim")

/*	Some variables
 */
char buffer[SIZE];		/* reception buffer */
char *ptlec;			/* read pointer */
char *ptecr;			/* write pointer */

/*	Character reception.
 *	Loops until a character is received.
 */
char getch(void)
	{
	char c;				/* character to be returned */

	while (ptlec == ptecr)		/* equal pointers => loop */
		;
	c = *ptlec++;			/* get the received char */
	if (ptlec >= &buffer[SIZE])	/* put in in buffer */
		ptlec = buffer;
	return (c);
	}

/*	Send a char to the SCI.
 */
void outch(char c)
	{
	while (!(USART_SR & TRDE))	/* wait for READY */
		;
	USART_DR = c;			/* send it */
	}

/*	Character reception routine.
 *	This routine is called on interrupt.
 *	It puts the received char in the buffer.
 */
@interrupt void recept(void)
	{
	USART_SR;			/* clear interrupt */
	*ptecr++ = USART_DR;		/* get the char */
	if (ptecr >= &buffer[SIZE])	/* put it in buffer */
		ptecr = buffer;
	}

/*	Main program.
 *	Sets up the SCI and starts an infinite loop
 *	of receive transmit.
 */
 
 
 int add(int a, int b)
 {
	 return a+b;
 }
 
 int minus(int a, int b)
 {
	 return a-b;
 }
 
 
void main(void)
	{
	int result =0;
	
	result = minus( 3 , 2 );
	result = add( 2 , 3 );
	
	result += 7;
	
	ptecr = ptlec = buffer;		/* initialize pointers */
	USART_BRR1 = 0xc9;		/* parameter for baud rate */
	USART_CR1 = 0x00;		/* parameter for word length */
	USART_CR2 = 0x2c;		/* parameters for interrupt */
	rim();				/* authorize interrupts */
	
	
	
	for (;;)			/* loop */
		outch(getch());		/* get and put a char */
	}
