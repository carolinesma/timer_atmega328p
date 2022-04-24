#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#define FOSC 16000000UL

volatile unsigned long count_millis;

void inicializa_timer(void){
  
  TCCR2A = 0x00;
  TCCR2B |= (1<<CS21);
  TCNT2 = 56;
  TIMSK2 |= (1<<TOIE2);
  timer_millis = 0;
 
}

ISR (TIMER2_OVF_vect)
{      
   TCNT2   =    56;
   count_millis ++;
   
}

unsigned long whatsTime(void){
  unsigned long aux_millis;

  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    aux_millis = count_millis;
  }
  return aux_millis;
}

void setup_init(void){
  Serial.begin(9600);
  inicializa_timer();
}


int main( void )
{
  cli();  
  setup_init();
  unsigned long timer;
  sei();

  
  timer = whatsTime();
  Serial.println(timer);

  
  

}
