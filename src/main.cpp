#include "FastLED.h"
#include <M5StickC.h>

constexpr int Neopixel_PIN = 32;
constexpr int NUM_LEDS = 73;

CRGB leds[NUM_LEDS];
uint8_t gHue = 0;  // Initial tone value.

int led_mode = 1;
float r = 255;
float g = 50;
float b = 100;
float brightness = 20;
float duration = 3;
int blink_time = 1;
int rainbow_delta_hue = 1;


void brighten_led() {
  int delta = max(int(brightness / 10), 1);
  float tmp_brightness = 0;
  for (tmp_brightness; tmp_brightness < brightness; tmp_brightness += delta){
    FastLED.setBrightness(tmp_brightness);
    FastLED.show(); 
    delay(200);
  }
  tmp_brightness = brightness;
  FastLED.setBrightness(tmp_brightness);
  FastLED.show();
  delay(200);
}


void fade_led() {
  int delta = max(int(brightness / 10), 1);
  float tmp_brightness = brightness;
  for (tmp_brightness; tmp_brightness > delta; tmp_brightness -= delta){
    FastLED.setBrightness(tmp_brightness);
    FastLED.show(); 
    delay(200);
  }
  tmp_brightness = 0;
  FastLED.setBrightness(tmp_brightness);
  FastLED.show();
  delay(200);
}


void blink_led() {
 for (blink_time; blink_time > 0; blink_time -= 1){
  brighten_led();
  delay(duration * 1000);
  fade_led();
 }
 brightness = 0;
}


void setup() {
  M5.begin();             // Init M5Stack. 
  M5.Lcd.setTextSize(2);  
  M5.Lcd.println("Display rainbow effect");
  // Neopixel initialization. 
  FastLED.addLeds<WS2811, Neopixel_PIN, GRB>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(20);  // set the LED brightness to 5.
  FastLED.show();
}


void loop() {
  if (led_mode == 1) {
    for (int i = 0; i < NUM_LEDS; i++){
      leds[i].setRGB(r, g, b);
    }
    FastLED.setBrightness(brightness);
    FastLED.show();  // Updated LED color.
  } 
  else if (led_mode == 2){
    for (int i = 0; i < NUM_LEDS; i++){
      leds[i].setRGB(r, g, b);
    }
    delay(1000);
    blink_led();
  }
  else if (led_mode == 3){
    fill_rainbow(leds, NUM_LEDS, gHue, rainbow_delta_hue);
    FastLED.setBrightness(brightness);
    FastLED.show();  // Updated LED color.
  }
  EVERY_N_MILLISECONDS(20) {
    gHue++;
  }  // The program is executed every 20 milliseconds.
}
