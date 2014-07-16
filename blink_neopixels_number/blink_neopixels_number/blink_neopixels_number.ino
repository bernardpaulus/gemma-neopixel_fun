#include <Adafruit_NeoPixel.h>

/**
 flash each neopixel with its number in the strip
 */

#define PIN 1
#define STRIP_SIZE 10

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIP_SIZE, PIN, NEO_GRB + NEO_KHZ800);

#define FIRST_FLASH_DURATION_MS 1000
#define FLASH_SEPARATION_DURATION_MS 500
#define FLASH_DURATION_MS 500
#define LOOP_END_DURATION_MS 500
#define RED strip.Color(255, 0, 0)

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  light_all(RED, FIRST_FLASH_DURATION_MS); // Red
  flash_number_of_neopixel();
  black_all(LOOP_END_DURATION_MS);
}

void light_all(uint32_t c, int duration) {
  light_all_pixels_starting_at(0, c, duration);
}

void flash_number_of_neopixel() {
  for (uint16_t pixel_number = 1; pixel_number <= strip.numPixels(); pixel_number++) {
    black_all(FLASH_SEPARATION_DURATION_MS);
    light_all_pixels_starting_at(pixel_number, RED, FLASH_DURATION_MS);
  }
}

void black_all(int duration) {
  light_all(strip.Color(0, 0, 0), duration);
}

void light_all_pixels_starting_at(uint16_t pixel_number, uint32_t color, int duration) {
  for(uint16_t i = pixel_number; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
      strip.show();
  }
  delay(duration);
}


