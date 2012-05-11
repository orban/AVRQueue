#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "../queue.h"

#define FOSC 16000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#define sbi(var, mask)   ((var) |= (uint8_t)(1 << mask))
#define cbi(var, mask)   ((var) &= (uint8_t)~(1 << mask))

#define STATUS_LED 5

void ioinit(void);      // initializes IO
static int uart_putchar(char c, FILE *stream);
uint8_t uart_getchar(void);

static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

int testFunction(queue_time_t now)
{
    printf("Hello World! Time: %d\r\n", now);
    return 0;
}

int testFunction2(queue_time_t now)
{
    printf("Stupid World! Time: %d\r\n", now);
    return 0;
}

int main (void)
{	
    uint32_t x = 0;

    ioinit(); //Setup IO pins and defaults

    scheduleFunction(testFunction, "Test", 3, 3);
    scheduleFunction(testFunction2, "Test2", 4, 3);

    while(1)
    {

        scheduleRun(x);
        x++;

        if(x == 15)
        {
            scheduleRemoveFunction("Test2");
            scheduleChangeFunction("Test", 15, 4);
        }
		
		sbi(PORTB, STATUS_LED);
		_delay_ms(500);

		cbi(PORTB, STATUS_LED);
		_delay_ms(500);
    }
   
    return(0);
}

void ioinit (void)
{
    //1 = output, 0 = input
    DDRB = 0b11101111; //PB4 = MISO 
    DDRC = 0b11111111; //
    DDRD = 0b11111110; //PORTD (RX on PD0)

    //USART Baud rate: 9600
    UBRR0H = MYUBRR >> 8;
    UBRR0L = MYUBRR;
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    
    stdout = &mystdout; //Required for printf init
}

static int uart_putchar(char c, FILE *stream)
{
    //if (c == '\n') uart_putchar('\r', stream);
  
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
    
    return 0;
}

uint8_t uart_getchar(void)
{
    while( !(UCSR0A & (1<<RXC0)) );
    return(UDR0);
}