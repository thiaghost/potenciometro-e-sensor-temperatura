
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

char texto[64];
volatile uint16_t leitura;
volatile uint16_t leitura1;
volatile uint16_t leitura2;
volatile float volt;
volatile float temp;
volatile float pot;

void print_dec(uint16_t);

void init_serial()
{
  UCSR0A = 0x02;
  UCSR0B = 0x08;
  UCSR0C = 0x06;
  UBRR0  = 207;
}

void init_adc()
{
   ADCSRA = 0x87;
   ADMUX  = 0x40;
}

void init_io()
{
  DDRB = 1<<5;
}

void uart_tx(uint8_t byte)
{
  while ((UCSR0A & (1<<UDRE0)) == 0);
  UDR0 = byte;
}

void uart_string(char * ptr)
{
  while( *ptr )
  {
    uart_tx(*ptr++);
  }
}

uint16_t read_adc(uint8_t canal)
{
  ADMUX  = 0x40 | (canal & 0x0F);
  _delay_us(20);  
  ADCSRA |= (1<<ADSC);
  while (ADCSRA & (1<<ADSC) );
  return ADCW;
}

char bin2char(uint8_t x)
{
  x = x & 0x0F;
  if (x<10)
    return x + '0';
  return x + 'A' - 10;
}

void print_names(){
	texto[0] = 'M';
	texto[1] = 'a';
	texto[2] = 'u';
	texto[3] = 'r';
	texto[4] = 'i';
	texto[5] = 'c';
	texto[6] = 'i';
	texto[7] = 'o';
	
	texto[8] = ' ';
	
	texto[9] = 'T';
	texto[10] = 'h';
	texto[11] = 'i';
	texto[12] = 'a';
	texto[13] = 'g';
	texto[14] = 'o';
	texto[15] = ':';
	texto[16] = 0;
}


void print_hexa(uint16_t valor)
{
  texto[0] = 'A';
  texto[1] = 'D';
  texto[2] = 'C';
  texto[3] = ':';
  texto[4] = '0';
  texto[5] = 'x';
  texto[6] = bin2char(valor>>8);
  texto[7] = bin2char(valor>>4);
  texto[8] = bin2char(valor);
  texto[9] = 0;
}

void print_dec(uint16_t valor)
{
  texto[0] = '=';
  texto[1] = ((valor/1000)%10 + '0');
  texto[2] = ((valor/100)%10 + '0');
  texto[3] = ((valor/10)%10 + '0');
  texto[4] = ((valor/1)%10 + '0');
  texto[5] = ' ';
  texto[6] = 0;
}

void print_volt(uint16_t valor)
{
  int16_t vin = ((uint32_t) valor * 5000) >> 10;
  
  texto[0] = 'V';
  texto[1] = 'i';
  texto[2] = 'n';
  texto[3] = '='; 
  texto[4] = ((vin/1000)%10 + '0');
  texto[5] = '.';
  texto[6] = ((vin/100)%10 + '0');
  texto[7] = ((vin/10)%10 + '0');
  texto[8] = ((vin/1)%10 + '0');
  texto[9] = 'V';
  texto[10] = ' ';
  texto[11] = 0;
}

void print_POT(uint16_t valor)
{
	int16_t vin = ((uint32_t) valor * 5000)/5 >> 10;
	texto[0] = 'P';
	texto[1] = 'o';
	texto[2] = 't';
	texto[3] = '=';
	texto[4] = ((vin/1000)%10 + '0');
	texto[5] = ((vin/100)%10 + '0');
	texto[6] = ((vin/10)%10 + '0');
	texto[7] = '.';
	texto[8] = ((vin/1)%10 + '0');
	texto[9] = '%';
	texto[10] = ' ';
	texto[11] = 0;
}

void print_TEMP(uint16_t valor)
{
	int16_t vin = ((uint32_t) valor * 5000) >> 10;
	texto[0] = 'T';
	texto[1] = 'e';
	texto[2] = 'm';
	texto[3] = 'p';
	texto[4] = '=';
	texto[5] = ((vin/1000)%10 + '0');
	texto[6] = ((vin/100)%10 + '0');
	texto[7] = ((vin/10)%10 + '0');
	texto[8] = '.';
	texto[9] = ((vin/1)%10 + '0');
	texto[10] = '°';
	texto[11] = 'C';
	texto[12] = ' ';
	texto[13] = '\n';
	texto[14] = 0;
}

int main(void)
{
  init_serial();
  init_adc();
  init_io();
   
        
    while (1) 
    {
		leitura = 0;
		leitura1 = 0;
		
	for (int i=0; i<8; i++ ) {	
    leitura += read_adc(2);
    leitura1 += read_adc(0);
	_delay_ms(75);
	
	}
	temp = leitura /8;
	pot = leitura1 /8;
	
    print_names();
	uart_string(texto);
	
    print_hexa(pot);
    uart_string(texto);
    
    print_dec(temp);
    uart_string(texto);
    PORTB |= 1<<5;//LED = 1;
    print_volt(temp);
    PORTB &= ~(1<<5);//LED = 0;
    uart_string(texto);
	PORTB |= 1<<5;//LED = 1;
	print_POT(temp);
	PORTB &= ~(1<<5);//LED = 0;
	uart_string(texto);
	
    print_hexa(pot);
    uart_string(texto);
    print_dec(pot);
    uart_string(texto);
    PORTB |= 1<<5;//LED = 1;
    print_volt(pot);
	PORTB &= ~(1<<5);//LED = 0;
    uart_string(texto);
	
	print_TEMP(pot);
    PORTB &= ~(1<<5);//LED = 0;
	uart_string(texto);
	
	
    _delay_ms(300);
    }
}

