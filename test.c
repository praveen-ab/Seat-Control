//Seat Control Module
//Praveen Bailwad
#include<avr/io.h>
#include<util/delay.h>
//PORT|=(1<<PIN); 
//PORT&=~(1<<PIN);
uint16_t readADC();

void initADC()
{
    ADMUX=(1<<REFS0);
    ADCSRA=(1<<ADEN)|(7<<ADPS0);
}
uint16_t readADC(uint8_t ch)
{

    ADMUX&=0xf8;
    ch=ch&0b00000111;
    ADMUX|=ch;
    ADCSRA|=(1<<ADSC);
    while(!(ADCSRA&(1<<ADIF)));
    ADCSRA|=(1<<ADIF);
    return(ADC);
}
uint16_t temperature=0;
void seattemp()
{
    temperature=readADC(5);
    _delay_ms(1000);
    if(temperature>200)
    {
      PORTD|=(1<<PD2);
            
    }
    else 
    {  
      PORTD&=~(1<<PD2);
    }

}
int main()
{
    DDRB |=(1<<PB5);
  	DDRB |=(1<<PB3);
    DDRB |=(1<<PB1);
    PORTB|=(1<<PB5);
  
    DDRD|=(1<<PD6);
    DDRD |=(1<<PD5);
  
    DDRD&=~(1<<PD0);
    DDRD&=~(1<<PD1);
    DDRD&=~(1<<PD3);
    DDRD&=~(1<<PD4);
    DDRD|=(1<<PD2); //op
    DDRC&=~(1<<PC5); //ip
  initADC();  
while(1)
{
  seattemp();
  
  if(PIND&(1<<PD0))
  {
    PORTB|=(1<<PB3);//Clockwise
    PORTB &=~(1<<PB1); 
  }
  if(PIND&(1<<PD1))
  {
    PORTB &=~(1<<PB3);//anticlockwise
    PORTB |=(1<<PB1);  
  }
  if(PIND&(1<<PD3))
  {
    PORTD|=(1<<PD6);//clockwise
    PORTD &=~(1<<PD5); 
  } 
  if(PIND&(1<<PD4))
  {
    
    PORTD&=~(1<<PD6);//anticlockwise
    PORTD |=(1<<PD5);  
  }
  
  else
  {
    PORTB&=~(1<<PB3);//off
    PORTB &=~(1<<PB1);
    PORTD&=~(1<<PD6);
    PORTD &=~(1<<PD5);
  } 
  } 
return 0;
}
