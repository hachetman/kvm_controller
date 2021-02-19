#include "../include/i2c_ddc.h"
#include <Adafruit_NeoPixel.h>
#define LEDPIN 10
#define SWITCH_PIN_1 8
#define SWITCH_PIN_2 9
#define USB_PIN_1 15
#define USB_PIN_2 14
#define NUMPIXELS 2
#define DISPLAY_OUT_1 0xf
#define DISPLAY_OUT_2 0x10

Adafruit_NeoPixel strip =
    Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);
ddc ddc_controller;
int output = DISPLAY_OUT_1;
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.

void setup() {
  int channel;
  Serial.begin(115200);
  pinMode(SWITCH_PIN_1, INPUT_PULLUP);
  pinMode(SWITCH_PIN_2, INPUT_PULLUP);
  pinMode(USB_PIN_2, OUTPUT);
  pinMode(USB_PIN_1, OUTPUT);
  digitalWrite(USB_PIN_1, LOW);
  digitalWrite(USB_PIN_2, LOW);
  strip.begin(); // initialize strip
  strip.show();  // Initialize all pixels to 'off'
  channel = ddc_controller.get_display_channel();
  if (channel == 0xf) {
    strip.setPixelColor(0, 0, 0, 0);
    strip.setPixelColor(1, 2, 0, 0);
    digitalWrite(USB_PIN_1, HIGH);
    digitalWrite(USB_PIN_2, LOW);
    delay(100);
    digitalWrite(USB_PIN_1, LOW);
  } else {
    strip.setPixelColor(0, 2, 0, 0);
    strip.setPixelColor(1, 0, 0, 0);
    digitalWrite(USB_PIN_2, HIGH);
    digitalWrite(USB_PIN_1, LOW);
    delay(100);
    digitalWrite(USB_PIN_2, LOW);
  }
  strip.show();
}

void loop() {

  if (digitalRead(SWITCH_PIN_1) == 0) {
    output = DISPLAY_OUT_1;
    ddc_controller.set_display_channel(0xf);
    strip.setPixelColor(0, 0, 0, 0);
    strip.setPixelColor(1, 2, 0, 0);
    strip.show();
    digitalWrite(USB_PIN_1, HIGH);
    digitalWrite(USB_PIN_2, LOW);
    delay(100);
    digitalWrite(USB_PIN_1, LOW);
    delay(1000);
  }
  if (digitalRead(SWITCH_PIN_2) == 0) {
    output = DISPLAY_OUT_2;
    ddc_controller.set_display_channel(0x10);
    strip.setPixelColor(0, 2, 0, 0);
    strip.setPixelColor(1, 0, 0, 0);
    strip.show();
    digitalWrite(USB_PIN_2, HIGH);
    digitalWrite(USB_PIN_1, LOW);
    delay(100);
    digitalWrite(USB_PIN_2, LOW);
    delay(1000);
  }
  // Serial.println("Getting current channel:");
  // channel = ddc_controller.get_display_channel();
}
