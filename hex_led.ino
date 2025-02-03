
#include <M5Stack.h>
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32.h>
#include <std_msgs/ColorRGBA.h>

ros::NodeHandle  nh;
#include "FastLED.h"

#define Neopixel_PIN 21
#define NUM_LEDS     73

CRGB leds[NUM_LEDS];
uint8_t gHue = 0;  // Initial tone value.

int led_mode = 1;
float r, g, b, brightness;
float duration = 3;
int blink_time = 1;
int rainbow_delta_hue = 1;

void ledModeMessageCb(const std_msgs::UInt16& msg){
  led_mode = msg.data;
}

void colorMessageCb( const std_msgs::ColorRGBA& msg){
  r = msg.r;
  g = msg.g;
  b = msg.b;
  brightness = msg.a;
 }

void blinkTimeMessageCb(const std_msgs::UInt16& msg){
  blink_time = msg.data;
}

void durationMessageCb(const std_msgs::Float32& msg){
  duration = msg.data;
}

void rainbowDeltaHueMessageCb(const std_msgs::UInt16& msg){
  rainbow_delta_hue = msg.data;
}


ros::Subscriber<std_msgs::UInt16> led_mode_subscriber("led_mode", &ledModeMessageCb);
ros::Subscriber<std_msgs::ColorRGBA> led_color_subscriber("led_rgb", &colorMessageCb);
ros::Subscriber<std_msgs::UInt16> led_blink_time_subscriber("led_blink_time", &blinkTimeMessageCb);
ros::Subscriber<std_msgs::Float32> led_duration_subscriber("led_duration", &durationMessageCb);
ros::Subscriber<std_msgs::UInt16> led_rainbow_delta_hue_subscriber("led_rainbow_delta_hue", &rainbowDeltaHueMessageCb);

void brighten_led(){
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

void fade_led(){
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

void blink_led(){
 for (blink_time; blink_time > 0; blink_time -= 1){
  brighten_led();
  delay(duration * 1000);
  fade_led();
 }
 brightness = 0;
}

void setup() {

    M5.begin();             // Init M5Stack. 
    M5.Power.begin();       // Init power  
    M5.Lcd.setTextSize(2);  
    M5.Lcd.println("      HEX Example");
    M5.Lcd.println("Display rainbow effect");

    // Neopixel initialization. 
    FastLED.addLeds<WS2811, Neopixel_PIN, GRB>(leds, NUM_LEDS)
        .setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(5);  // set the LED brightness to 5. 
    nh.initNode();
    nh.subscribe(led_mode_subscriber);
    nh.subscribe(led_color_subscriber);
    nh.subscribe(led_blink_time_subscriber);
    nh.subscribe(led_duration_subscriber);
    nh.subscribe(led_rainbow_delta_hue_subscriber);
}

void loop() {
    nh.spinOnce();
    if (led_mode == 1){
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
