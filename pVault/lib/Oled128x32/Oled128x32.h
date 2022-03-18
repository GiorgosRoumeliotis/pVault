#include <Arduino.h>
#include <U8g2lib.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include "XBM.h"

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);


void oled_init(void){
  u8g2.begin();
}

void oled_show_ip(char* ip){
  // u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_7x13_tf);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
  u8g2.drawStr(1,9,"home.local");
  int place_it = (128 - (8 * strlen(ip))) / 2;
  u8g2.setFont(u8g2_font_7x14_tf);
  u8g2.drawStr(place_it,32,ip);
  u8g2.sendBuffer();					// transfer internal memory to the display
}

void oled_loading(){
  u8g2.setDrawColor(1);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_t0_11_tf);
  u8g2.drawStr(10,11,"INITIALIZE DEVICE");

  u8g2.setFont(u8g2_font_open_iconic_all_4x_t);
  u8g2.drawFrame(5, 20, 118, 10);
  for (size_t i = 0; i < 114; i++) {
    u8g2.drawBox(7, 22,i, 6);
    u8g2.sendBuffer();
    delay(600);
  }
}

void oled_wifi_signal(long rssi){
  u8g2.clearBuffer();

  if (rssi > -50) {
    /* EXCELLENT */
    u8g2.firstPage();
    do {
      u8g2.drawXBMP( 80, 1, wifi_excellent_width, wifi_excellent_height, wifi_excellent_bits);
    } while( u8g2.nextPage() );
  }
  else if(rssi <= -50 && rssi > -60){
    /* GOOD */
    u8g2.firstPage();
    do {
      u8g2.drawXBMP( 80, 1, wifi_good_width, wifi_good_height, wifi_good_bits);
    } while( u8g2.nextPage() );
  }
  else if(rssi <= -60 && rssi > -70){
    /* FAIR */
    u8g2.firstPage();
    do {
      u8g2.drawXBMP( 80, 1, wifi_fair_width, wifi_fair_height, wifi_fair_bits);
    } while( u8g2.nextPage() );
  }
  else if(rssi < 70){
    /* WEAK */
    u8g2.firstPage();
    do {
      u8g2.drawXBMP( 80, 1, wifi_bad_width, wifi_bad_height, wifi_bad_bits);
    } while( u8g2.nextPage() );
  }

  u8g2.setFont(u8g2_font_5x7_tr);

  u8g2.drawStr(94,9,String(rssi).c_str());
  u8g2.drawStr(110,9,"dBm");
  u8g2.sendBuffer();

  /* IPAddress to char array */
  char ip[WiFi.localIP().toString().length()+1];
  WiFi.localIP().toString().toCharArray(ip, WiFi.localIP().toString().length()+1);

  oled_show_ip(ip);
}



void oled_wifi_message(void){
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_7x14_tf);
  u8g2.drawStr(6,12,"PLEASE CONNECT");
  int place_it = (128 - (8 * strlen("TO WIFI"))) / 2;
  u8g2.drawStr(place_it,32,"TO WIFI");
  u8g2.sendBuffer();
}

void oled_wifi_try_to_connect(void){
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_7x14_tf);
  u8g2.drawStr(6,12,"TRY TO CONNECT");
  int place_it = (128 - (8 * strlen("TO WIFI ..."))) / 2;
  u8g2.drawStr(place_it,32,"TO WIFI");
  u8g2.sendBuffer();
  delay(500);

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_7x14_tf);
  u8g2.drawStr(6,12,"TRY TO CONNECT");
  u8g2.drawStr(place_it,32,"TO WIFI .");
  u8g2.sendBuffer();
  delay(500);

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_7x14_tf);
  u8g2.drawStr(6,12,"TRY TO CONNECT");
  u8g2.drawStr(place_it,32,"TO WIFI ..");
  u8g2.sendBuffer();
  delay(500);

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_7x14_tf);
  u8g2.drawStr(6,12,"TRY TO CONNECT");
  u8g2.drawStr(place_it,32,"TO WIFI ...");
  u8g2.sendBuffer();
  delay(500);

}

void oled_logo_intro(void) {
  u8g2.firstPage();
  do {
    u8g2.drawXBMP( 0, 0, logo_intro_width, logo_intro_height, logo_intro_bits);
  } while( u8g2.nextPage() );
}
