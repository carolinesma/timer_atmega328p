#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#define FOSC 16000000UL

volatile unsigned long count_millis;

/* Uso do Timer2 para contar 1ms

ts = (TOP + 1) x preescaler/ Fosc
ts = (255 + 1 - 56) x 8/16mHz
ts = 0,1 ms

*/
void inicializa_timer(void){
  
  TCCR2A = 0x00;            // Modo de operação normal
  TCCR2B |= (1<<CS21);      // Set Preescaler de 8 bits
  TCNT2 = 56;               // Inicializa o contador do Timer com 56 para que conte apenas 200 vezes
  TIMSK2 |= (1<<TOIE2);     // Ativa a interrupção por overflow
  count_millis = 0;         // inicializa contador
 
}

/* Chamada de Interurpçação para contabilizar os 0,1ms a cada estouro*/
ISR (TIMER2_OVF_vect)
{      
   TCNT2   =    56;
   count_millis ++;
   
}

/* Função para retornar  o valor contabilizado na hora da requisição*/
unsigned long whatsTime(void){
  unsigned long aux_millis;

  ATOMIC_BLOCK(ATOMIC_FORCEON) { //desabilita as interrupções gerais
    aux_millis = count_millis;
  }
  return aux_millis;
}

void setup_init(void){
  inicializa_timer();
}


int main( void )
{
  cli();    // desabilita interrupções
  setup_init();
  
  /*
  ...
  */
  
  sei();    // habilita interrupções
  

}
