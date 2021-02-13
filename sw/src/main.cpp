#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define PIN 10
#define NUMPIXELS 4
#define TXLED 1
Adafruit_NeoPixel strip =
    Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
void rainbow(uint8_t wait) {

  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  strip.begin();          // initialize strip
  strip.show();           // Initialize all pixels to 'off'
  pinMode(TXLED, OUTPUT); // Set RX LED as an output
}

void loop() {
  int nDevices = 0;

  Serial.println("test");
  Serial.write("test");
  delay(1000);
  digitalWrite(TXLED, LOW); // set the RX LED ON

  delay(10); // waits for a second
  rainbow(20);

  delay(1000);               // waits for a second
  digitalWrite(TXLED, HIGH); // set the RX LED ON
  Serial.println("Scanning...");
  for (byte address = 1; address < 127; ++address) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println("  !");

      ++nDevices;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("done\n");
  }
}
