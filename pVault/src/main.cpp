/* ARDUINO LIBRARIES */
#include <Arduino.h>
#include <Wire.h>

/* ESP8266 LIBRARIES */
#include <ESP8266WebServer.h>

/* C/C++ LIBRARIES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* CUSTOM LIBRARIES */
#include <Oled128x32.h>
/**/
#define LEFT D0
#define RIGHT D5

void setup() {
  /* PIN SETUP */

  oled_init();
  delay(1000);

  /* SPASH SCREEN */
  oled_logo_intro();
  delay(3000);

  pinMode(LEFT,INPUT);
  pinMode(RIGHT,INPUT_PULLUP);

  Serial.begin(115200);
}

void loop() {
  Serial.println("LEFT "+String(digitalRead(LEFT)));
  Serial.println("RIGHT "+String(digitalRead(RIGHT)));
  delay(1000);
}
