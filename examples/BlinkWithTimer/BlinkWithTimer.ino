#include <timer.h>

byte ledPin = 13;
Timer tm;

void setup() {
  pinMode(ledPin,OUTPUT);
  tm.startTimer(1000,toggleLED);
}

void loop() {
  tm.runTimers();
}

void toggleLED(int timer) {
  static int LEDState = 1;

  digitalWrite(ledPin,LEDState?HIGH:LOW);
  LEDState = !LEDState;
}

