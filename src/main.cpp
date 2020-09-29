#include <Arduino.h>

#define INP  23
#define INM  22
#define READ 21
#define M0   19
#define OUT  18



void reset();
void microDelay();

void setup() {
  pinMode(INP, OUTPUT);
  pinMode(INM, OUTPUT);
  pinMode(READ, OUTPUT);
  pinMode(M0, OUTPUT);
  pinMode(OUT, INPUT);


  reset();
  digitalWrite(M0, LOW);
  Serial.begin(115200);
  Serial.println("Waiting for you...");
  
}

uint32_t value=0, time2 = 0, time1 = 0;

void loop() {
  
  if(Serial.available() > 0) {
      char a = Serial.read();
      Serial.println(a);
      if(a == '2') {
        // Write 121k
        digitalWrite(READ, LOW);
        digitalWrite(INP, HIGH);
        digitalWrite(INM, LOW);

        digitalWrite(M0, HIGH);
        delayMicroseconds(500);
        digitalWrite(M0, LOW);
        reset();

        delayMicroseconds(20);

        // Read 121k

        digitalWrite(READ, HIGH);
        digitalWrite(INP, LOW);
        digitalWrite(INM, HIGH);

        time1 = micros();
        digitalWrite(M0, HIGH);
        microDelay();
        value = digitalRead(OUT);
        time2 = micros();
        digitalWrite(M0, LOW);

        Serial.print("Wrote to 121k, read value ");
        Serial.println(value);
        Serial.print("Time ");
        Serial.println(time2-time1);
        reset();

        // Write 4.42k
        digitalWrite(READ, LOW);
        digitalWrite(INP, LOW);
        digitalWrite(INM, HIGH);

        digitalWrite(M0, HIGH);
        delayMicroseconds(500);
        digitalWrite(M0, LOW);
        reset();

        delayMicroseconds(20);

        // Read 4.42k
        digitalWrite(READ, HIGH);
        digitalWrite(INP, LOW);
        digitalWrite(INM, HIGH);


        time1 = micros();
        digitalWrite(M0, HIGH);
        microDelay();
        value = digitalRead(OUT);
        time2 = micros();
        digitalWrite(M0, LOW);

        Serial.print("Wrote to 4.42k, read value ");
        Serial.println(value);
        Serial.print("Time ");
        Serial.println(time2-time1);
        reset();
      }
      
      Serial.println("Waiting for you...");
  }
  

}




void reset() {
  digitalWrite(INP, HIGH);
  digitalWrite(INM, HIGH);
  digitalWrite(READ, LOW);
}

void microDelay() {
  delay(2000);
}