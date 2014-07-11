/*
 make grren ligh when switch is on, make red ligh when switch is off
*/

#include <Adafruit_NeoPixel.h>

#define HIGH_READ 1023
#define LOW_READ 0
#define MID_READ (HIGH_READ - LOW_READ) / 2

// noted as Dx (~digital output x?)
#define OUT_PIN 1
// noted as Ax (~analog input x?)
#define IN_PIN 1

//maybe both types are I/O?


// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, OUT_PIN, NEO_GRB + NEO_KHZ800);

// the setup routine runs once when you press reset:
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

// the loop routine runs over and over again forever:
void loop() {
  if (is_switch_on()) {
    show_green();
  } else {
    show_red();
  }
}

boolean is_switch_on() {
    // read the input on analog pin 0:
  int sensor_value = analogRead(IN_PIN);
  // Convert the analog reading (which goes from 0 - 1023) to true if voltage is above midpoint
  return sensor_value > MID_READ;
}

void show_red() {
  colorWipe(strip.Color(255, 0, 0), 50);
}

void show_green() {
  colorWipe(strip.Color(0, 255, 0), 50);
}

// Fill the dots one after the other with a color
// Note: This seems to be code adapted to multiple neopixels.
// Iterating on them with a delay might cause the delay observed 
// when switching from red to green and vice-versa
// TODO aptimize for a single flora neopixel v2
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
