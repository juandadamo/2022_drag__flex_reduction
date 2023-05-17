//Uses HX711 library by Bogde https://github.com/bogde/HX711
//Timer and PWM setup works for Uno or Nano only (ATmega328P)
#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 4;  //Can be another pin
const int LOADCELL_SCK_PIN = 5;  //Can be another pin
const int LOADCELL_DOUT_PIN_L = 6;  //Can be another pin
const int LOADCELL_SCK_PIN_L = 7;  //Can be another pin
const int RATE = 8;

HX711 scale;

long reading;
unsigned long previousMillis = 0;
int counter = 0;
int sampleTime = 0;
float samplePerSec = 0;
bool rate = 0;

void setup() {
  Serial.begin(115200);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);   // (Dout PIN, SCK PIN, gain) Channel A 128 or 64, Channel B 32.
  //Set up PWM on pin 3 
  TCCR2A = bit(COM2A1) | bit(COM2B1) | bit(WGM21) | bit(WGM20);
  TCCR2B = bit(WGM22) | bit(CS20);
  OCR2A = 14;  //Con estos dos valores se juega para variar frecuencia 
  OCR2B = 7;  // Con estos dos valores se juega para variar frecuencia
  pinMode(3, OUTPUT); // Output PWM pin 3  
  pinMode(2, OUTPUT); // Output PWM pin 2 
  pinMode(RATE, OUTPUT); //Change sample rate with pin 8 
  digitalWrite(RATE, LOW); //set HX711 sample rate to slow
}

void loop() {
  if (scale.is_ready()) {
    reading = scale.read();
    counter ++;
  }
  if (counter == 1) { // average over 10 samples can be changed for high or low sample rates but change value 4 lines below from 10000.0
    counter = 0;
    sampleTime = millis() - previousMillis;
    previousMillis = millis();
    samplePerSec = 1000.0 / sampleTime; // 10000  = 1000 x counter

    //Serial.print (",");
    Serial.print(sampleTime);
    Serial.print (",");
    Serial.print(samplePerSec);
    Serial.print (",");
    Serial.println(reading);
    digitalWrite(RATE, rate);
  }
  if (Serial.available() > 0) { //receive rate from serial
    rate = (Serial.parseInt());
  }
}
