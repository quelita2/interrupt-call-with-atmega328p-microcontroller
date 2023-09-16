#include <util/delay.h>

unsigned int enable_count = 1;
unsigned int counter = 0;

void zero(){
  PORTB = 0b00000111;
  PORTD = 0b11101100;
}

void one(){
  PORTB = 0b00000001;
  PORTD = 0b00101100;
}

void two(){
  PORTB = 0b00001011;
  PORTD = 0b11001100;
}

void three(){
  PORTB = 0b00001011;
  PORTD = 0b01101100;
}

void four(){
  PORTB = 0b00001101;
  PORTD = 0b00101100;
}

void five(){  
  PORTB = 0b00001110;
  PORTD = 0b01101100;
}

void six(){
  PORTB = 0b00001110;
  PORTD = 0b11101100;
}

void seven(){
  PORTB = 0b00000011;
  PORTD = 0b00101100;
}


ISR (INT0_vect) {
  if(!(PIND & 0x04)){
    zero();
    counter = 0;
  }
}

ISR (INT1_vect) {
  void (*display_num[8])() = { zero, one, two, three, four, five, six, seven };

  if((!(PIND & 0x08) && counter < 7) && enable_count == 1){ 
    counter++;
    Serial.print(counter);
    display_num[counter]();
    enable_count = 0;
  }else if((PIND & 0x08)){
    enable_count = 1;
  }
}

int main(void){
  sei(); // enable interruptions;

  DDRD = 0b11110000;
  DDRB = 0b00001111;
  
  zero(); // start display with zero;

  EICRA = 0b00001010; // enable interruptions on up edge;
  EIMSK = 0b00000000; // enable interruptions on INT0 and INT1;
  
  return 0;
}


