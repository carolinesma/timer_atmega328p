#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#define FOSC 16000000UL

volatile unsigned long time_milli;

void inicializa_timer(void){
  
  TCCR2A = 0x00;
  TCCR2B |= (1<<CS01);
  TCNT2 = 56;
  TIMSK2 |= (1<<TOIE2);
  timer_millis = 0;
 
}

ISR (TIMER2_OVF_vect)
{      
   TCNT2   =    56;
   timer_millis ++;
   
}

unsigned long whatsTime(void){
  unsigned long time_now;

  // Ensure this cannot be disrupted
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    time_now = timer_millis;
  }
  return time_now;
}

void seturp(void){
  Serial.begin(9600);
}


int main( void )
{
  cli();
  inicializa_timer();
  setup());
  sei();

  

}
