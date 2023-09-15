#include <avr/io.h>
#include <avr/interrupt.h>

const int buttonPin = 21;  // the number of the pushbutton pin
const int ledPin = 4;    // the number of the LED pin

// variables will change:
int portState = 0;  // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);

  // Define o pino 2 como entrada (limpa o pino 2 do registardor DDRD)
  // DDRD &= ~(31<DDD3); // DDRD = 0X08;
  
  // Habilita a interrupção:
  sei(); // habilita interruptor geral

  EICRA = 0b00000010; // habilita o tipo de disparo na subida do botão

  EIMSK = 0b00000001; // habilita a interrupção externa INT0
}

ISR (INT0_vect) {
  // digitalWrite(ledPin, HIGH);
  // delay(1000);
  // digitalWrite(ledPin, LOW);
  // read the state of the pushbutton value:
  int count = 0;
  while(count < 5){
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (count % 2  == 0) {
      // turn LED on:
      digitalWrite(ledPin, HIGH);
    } else {
      // turn LED off:
      digitalWrite(ledPin, LOW);
    }
    delay(5000);
    count++;
  }
}

void loop() {
  digitalWrite(ledPin, LOW);
}