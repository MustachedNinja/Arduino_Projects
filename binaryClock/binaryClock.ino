#include <DS3231.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(84, PIN, NEO_GRB + NEO_KHZ800);
DS3231 rtc(SDA, SCL);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel (int8_t)power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // Set up the RTC
  Serial.begin(115200);
  rtc.begin();
  
  // Set the time and day
  rtc.setDOW(THURSDAY);     // Set Day-of-Week
  rtc.setTime(1, 0, 0);     // Set the time
  rtc.setDate(6, 14, 2019);   // Set the date

  
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  strip.clear();
  // End of trinket special code

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  strip.clear();
  Time curr_time = rtc.getTime();
  binaryClock(strip.Color(50, 0, 0), curr_time.hour, curr_time.min, curr_time.sec);
}


// Binary Clock

void binaryClock(int32_t c, int8_t hour, int8_t minute, int8_t second) {
  int8_t currPxl = 0;

  // Set pixels for seconds
  for (int8_t i = 5; i >= 0; i--) {

    int8_t curr_pow = pow(2, i) + 0.01;
    if (second >= curr_pow) {
      strip.setPixelColor(currPxl + i, c);
      second = second - curr_pow;
    }    
  }

  // Set divider pixel
  currPxl += 6;
  strip.setPixelColor(currPxl, 0, 50, 0);
  currPxl++;
  
    // Set pixels for minutes
  for (int8_t i = 5; i >= 0; i--) {

    int8_t curr_pow = pow(2, i) + 0.01;
    if (minute >= curr_pow) {
      strip.setPixelColor(currPxl + i, c);
      minute = minute - curr_pow;
    }
  }

  // Set divider pixel
  currPxl += 6;
  strip.setPixelColor(currPxl, 0, 50, 0);
  currPxl++;
  
  // Set pixels for hours
  for (int8_t i = 4; i >= 0; i--) {
    
    int8_t curr_pow = pow(2, i) + 0.01;
    if (hour >= curr_pow) {
      strip.setPixelColor(currPxl + i, c);
      hour = hour - curr_pow;
    }    
  }

  // Set divider pixel
  currPxl += 5;
  strip.setPixelColor(currPxl, 0, 50, 0);
  currPxl++;
  
  strip.show();
}
