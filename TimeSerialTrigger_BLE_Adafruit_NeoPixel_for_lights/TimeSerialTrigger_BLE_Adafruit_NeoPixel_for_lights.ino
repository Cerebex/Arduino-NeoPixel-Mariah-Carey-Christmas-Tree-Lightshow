/*

Copyright (c) 2012-2014 RedBearLab

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

/*
 * This code is uses the lightblue iOS app to send a hexcode digit 1 command from an iphone over bluetooth to a RedBearLab
 * Blend arduino V1.0 to start specifically coded light sequences on a Adafruit neopixel light strip with 150 LEDs to Mariah Carey's All I Want For Christmas
*/

/*
* TimeSerial.pde
* example code illustrating Time library set through serial port messages.
*
* Messages consist of the letter T followed by ten digit time (as seconds since Jan 1 1970)
* you can send the text on the next line using Serial Monitor to set the clock to noon Jan 1 2013
T1357041600
*
* A Processing example sketch to automatically send the messages is included in the download
* On Linux, you can use "date +T%s\n > /dev/ttyACM0" (UTC time zone)
*/
//"RBL_nRF8001.h/spi.h/boards.h" is needed in every new project
#include <SPI.h>
#include <EEPROM.h>
#include <boards.h>
#include <RBL_nRF8001.h>
#include <TimeLib.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
//
#define PIN 6
//
//// Parameter 1 = number of pixels in strip
//// Parameter 2 = Arduino pin number (most are valid)
//// Parameter 3 = pixel type flags, add together as needed:
////   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
////   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
////   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
////   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
////   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(150, PIN, NEO_KHZ800 + NEO_RGBW);
//
//// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
//// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
//// and minimize distance between Arduino and first pixel.  Avoid connecting
//// on a live circuit...if you must, connect GND first.

#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message

void setup()  {
  //  Serial.begin(9600);
  //  while (!Serial) ; // Needed for Leonardo only
  //  pinMode(13, OUTPUT);
  //  setSyncProvider(requestSync);  //set function to call when sync required
  //  Serial.println("Waiting for sync message");
  //
  // For BLE Shield and Blend:
  //   Default pins set to 9 and 8 for REQN and RDYN
  //   Set your REQN and RDYN here before ble_begin() if you need
  //
  // For Blend Micro:
  //   Default pins set to 6 and 7 for REQN and RDYN
  //   So, no need to set for Blend Micro.
  //
  delay(2000);
  ble_set_pins(9, 8);

  //   Set your BLE advertising name here, max. length 10
  ble_set_name("SAM BLE");

  // Init. and start BLE library.
  ble_begin();

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

unsigned char buf[16] = {0};
unsigned char len = 0;


void loop(){
  // ble_do_events allows the BLE to process its events, if data is pending, it will be sent out.
  ble_do_events();

  //  if (Serial.available()) {
  //    processSyncMessage();
  //  }
  // any non-zero number evaluates to TRUE in if statement
  // so if there is ble data ready to read from source (ie the phone)
  // then if statement below Returns the number of bytes ready for reading and passes if statement
  if ( ble_available() )
  {
    while ( ble_available() )
    {
      byte output_now = ble_read();

      if (output_now==1)  {
               // if (hour()==22 && minute()==46 && second()==00) {
        blink_quarters_bottom_up(1); //1
        blink_quarters_top_down(1); //2
        blink_quarters_bottom_up(1); //3
        color_hit(1); //4
        delay(533);
        theaterChase(strip.Color(0, 0, 0,255), 30, 10); //5 White
        turn_on_fade(1,0); //6
        delay(1700);
        theaterChase(strip.Color(255, 0, 0,0), 30, 17); //7  Green
        turn_on_fade(2,0); //8
        delay(1300);
        theaterChase(strip.Color(0, 0, 255,0), 30, 10); //9 Blue
        turn_on_fade(3,0); //10
        delay(1000);
        theaterChase(strip.Color(0, 255, 0,0), 30, 9); //11 Red
        turn_on_fade(4,0); //12
        delay(900);
        theaterChase(strip.Color(255, 0, 0,50), 30, 11); //7 Green
        turn_on_fade(2,0); //8
        delay(1000);
        turn_on_fade(5,0); //13
        turn_on_fade(1,0); //6
        theaterChase(strip.Color(255, 0, 0,0), 30, 10); //7  Green
        turn_on_fade(6,0); //14
        delay(500);
        turn_on_fade(3,0); //6
        delay(300);
        turn_on_fade(4,0); //12
        delay(1000);
        theaterChase(strip.Color(0, 0, 255,50), 30, 10); //9 Blue
        turn_on_fade(3,0); //10
        delay(800);
        turn_on_fade(4,0); //12
        delay(7000);
        colorWipe_up(strip.Color(0, 0, 255,0), 0); // Blue
        delay(90);
        colorWipe_down(strip.Color(0, 0, 255,0), 0); // Blue
        delay(90);
        colorWipe_up(strip.Color(0, 0, 255,0), 0); // Blue
        delay(90);
        colorWipe_down(strip.Color(0, 0, 255,0), 0); // Blue
        delay(90);
        colorWipe_up(strip.Color(255, 0, 0,0), 0); // Green
        delay(90);
        colorWipe_down(strip.Color(255, 0, 0,0), 0); // Green
        delay(90);
        colorWipe_up(strip.Color(255, 0, 0,0), 0); // Green
        delay(90);
        colorWipe_down(strip.Color(255, 0, 0,0), 0); // Green
        delay(90);
        colorWipe_up(strip.Color(0, 100, 100, 0), 0); // Purple
        delay(90);
        colorWipe_down(strip.Color(0, 100, 100, 0), 0); // Purple
        delay(90);
        colorWipe_up(strip.Color(0, 100, 100, 0), 0); // Purple
        delay(90);
        colorWipe_down(strip.Color(0, 100, 100, 0), 0); // Purple
        delay(190);
        color_hit(1); //4
        delay(130);
        color_hit(1); //4
        delay(240);
        color_hit(1); //4
        delay(130);
        color_hit(1); //4
        delay(240);
        color_hit(1); //4
        delay(130);
        color_hit(1); //4
        delay(240);
        color_hit(1); //4
        delay(240);
        theaterChaseRainbow(23); 
        delay(260);
        rainbowCycle(3);
        blink_quarters_bottom_up(2); //1
        blink_quarters_top_down(2); //2
        blink_quarters_bottom_up(2); //3
        blink_quarters_top_down(2); //2
        blink_quarters_bottom_up(3); //1
        blink_quarters_top_down(3); //2
        blink_quarters_bottom_up(3); //3
        blink_quarters_top_down(3); //2
        blink_quarters_bottom_up(4); //1
        blink_quarters_top_down(4); //2
        blink_quarters_bottom_up(4); //3
        blink_quarters_top_down(4); //2
        rainbowCycle(3);
        theaterChaseRainbow(23); 
        delay(270);
        theaterChaseRainbow(23);
        delay(270);
        rainbowCycle(3);
        blink_quarters_bottom_up(2); //1
        blink_quarters_top_down(2); //2
        blink_quarters_bottom_up(2); //3
        blink_quarters_top_down(2); //2
        blink_quarters_bottom_up(3); //1
        blink_quarters_top_down(3); //2
        blink_quarters_bottom_up(3); //3
        blink_quarters_top_down(3); //2
        blink_quarters_bottom_up(4); //1
        blink_quarters_top_down(4); //2
        blink_quarters_bottom_up(4); //3
        blink_quarters_top_down(4); //2
        rainbowCycle(3);
        rainbowCycle(3);
        rainbowCycle(3);
        rainbowCycle(3);
        rainbowCycle(3);
        rainbowCycle(3);
        rainbowCycle(3);
        rainbowCycle(3);
        rainbowCycle(3);
        rainbowCycle(3);
        rainbowCycle(3);
        rainbowCycle(3);
        rainbowCycle(3);
        rainbowCycle(3);
        rainbowCycle(3);
        //        }
      }
    }
  }
}




void blink_quarters_bottom_up(int color_choice) { //1 //3
  uint16_t w;
  uint16_t h;
  if (color_choice==1) {
    for (w = 0; w < 4; w++) {
      if (w==0) {
        for (h = 0; h < 37; h++) {
          strip.setPixelColor(h,0,0,0,255);
        }
        strip.show();
        delay(410);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==1) {
        for (h = 37; h < 74; h++) {
          strip.setPixelColor(h,0,0,0,255);
        }
        strip.show();
        delay(410);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==2) {
        for (h = 74; h < 111; h++) {
          strip.setPixelColor(h,0,0,0,255);
        }
        strip.show();
        delay(410);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==3) {
        for (h = 111; h < 151; h++) {
          strip.setPixelColor(h,0,0,0,255);
        }
        strip.show();
        delay(410);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
    }
  }
  if (color_choice==2) {
    for (w = 0; w < 4; w++) {
      if (w==0) {
        for (h = 0; h < 37; h++) {
          strip.setPixelColor(h,255,0,0,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==1) {
        for (h = 37; h < 74; h++) {
          strip.setPixelColor(h,255,0,0,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==2) {
        for (h = 74; h < 111; h++) {
          strip.setPixelColor(h,255,0,0,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==3) {
        for (h = 111; h < 151; h++) {
          strip.setPixelColor(h,255,0,0,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
    }
  }
  if (color_choice==3) {
    for (w = 0; w < 4; w++) {
      if (w==0) {
        for (h = 0; h < 37; h++) {
          strip.setPixelColor(h,0,0,255,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==1) {
        for (h = 37; h < 74; h++) {
          strip.setPixelColor(h,0,0,255,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==2) {
        for (h = 74; h < 111; h++) {
          strip.setPixelColor(h,0,0,255,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==3) {
        for (h = 111; h < 151; h++) {
          strip.setPixelColor(h,0,0,255,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
    }
  }
  if (color_choice==4) {
    for (w = 0; w < 4; w++) {
      if (w==0) {
        for (h = 0; h < 37; h++) {
          strip.setPixelColor(h,0,50,100,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==1) {
        for (h = 37; h < 74; h++) {
          strip.setPixelColor(h,0,50,100,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==2) {
        for (h = 74; h < 111; h++) {
          strip.setPixelColor(h,0,50,100,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==3) {
        for (h = 111; h < 151; h++) {
          strip.setPixelColor(h,0,50,100,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
    }
  }
}

void blink_quarters_top_down(int color_choice) { //2
  uint16_t w;
  uint16_t h;

  if (color_choice==1) {
    for (w = 0; w < 4; w++) {
      if (w==3) {
        for (h = 0; h < 37; h++) {
          strip.setPixelColor(h,0,0,0,255);
        }
        strip.show();
        delay(410);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==2) {
        for (h = 37; h < 74; h++) {
          strip.setPixelColor(h,0,0,0,255);
        }
        strip.show();
        delay(410);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==1) {
        for (h = 74; h < 111; h++) {
          strip.setPixelColor(h,0,0,0,255);
        }
        strip.show();
        delay(410);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==0) {
        for (h = 111; h < 151; h++) {
          strip.setPixelColor(h,0,0,0,255);
        }
        strip.show();
        delay(410);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
    }
  }
  if (color_choice==2) {
    for (w = 0; w < 4; w++) {
      if (w==3) {
        for (h = 0; h < 37; h++) {
          strip.setPixelColor(h,255,0,0,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==2) {
        for (h = 37; h < 74; h++) {
          strip.setPixelColor(h,255,0,0,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==1) {
        for (h = 74; h < 111; h++) {
          strip.setPixelColor(h,255,0,0,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==0) {
        for (h = 111; h < 151; h++) {
          strip.setPixelColor(h,255,0,0,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
    }
  }
  if (color_choice==3) {
    for (w = 0; w < 4; w++) {
      if (w==3) {
        for (h = 0; h < 37; h++) {
          strip.setPixelColor(h,0,0,255,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==2) {
        for (h = 37; h < 74; h++) {
          strip.setPixelColor(h,0,0,255,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==1) {
        for (h = 74; h < 111; h++) {
          strip.setPixelColor(h,0,0,255,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==0) {
        for (h = 111; h < 151; h++) {
          strip.setPixelColor(h,0,0,255,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
    }
  }
  if (color_choice==4) {
    for (w = 0; w < 4; w++) {
      if (w==3) {
        for (h = 0; h < 37; h++) {
          strip.setPixelColor(h,0,50,100,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==2) {
        for (h = 37; h < 74; h++) {
          strip.setPixelColor(h,0,50,100,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==1) {
        for (h = 74; h < 111; h++) {
          strip.setPixelColor(h,0,50,100,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
      if (w==0) {
        for (h = 111; h < 151; h++) {
          strip.setPixelColor(h,0,50,100,0);
        }
        strip.show();
        delay(380);
        allOnecolor(strip.Color(0, 0, 0,0), 0);
      }
    }
  }
}







// Sends command to all the dots to change to
// one color then turns them so they blink on all together
void allOnecolor(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait, uint8_t cycles) { //5 //7 //9 //11 //13
  for (int j=0; j<cycles; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
  allOnecolor(strip.Color(0, 0, 0,0), 0);
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*2; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
  allOnecolor(strip.Color(0, 0, 0,0), 0);
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j=j+4) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
  allOnecolor(strip.Color(0, 0, 0,0), 0);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}



void turn_on_fade(int color_choice, uint8_t wait) {
  int i, j;
  if (color_choice==1) { //6
    for (j = 255; j > -1; j--) {
      for (i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i,0,0,0,j);
      }
      strip.show();
      delay(wait);
    }
  }
  if (color_choice==2) { //8
    for (j = 255; j > -1; j--) {
      for (i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i,j,0,0,0);
      }
      strip.show();
      delay(wait);
    }
  }
  if (color_choice==3) { //10
    for (j = 255; j > -1; j--) {
      for (i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i,0,0,j,0);
      }
      strip.show();
      delay(wait);
    }
  }
  if (color_choice==4) { //12
    for (j = 255; j > -1; j--) {
      for (i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i,0,j,0,0);
      }
      strip.show();
      delay(wait);
    }
  }
  if (color_choice==5) { //13
    for (j = 255; j > -1; j=j-2) {
      for (i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i,0,0,j,0);
      }
      strip.show();
      delay(wait);
    }
  }
  if (color_choice==6) { //14
    for (j = 255; j > -1; j=j-2) {
      for (i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i,j,0,0,0);
      }
      strip.show();
      delay(wait);
    }
  }
}

void color_hit(int color_choice) { //4
  if (color_choice==1) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i,0,0,0,255);
    }
    strip.show();
    allOnecolor(strip.Color(0, 0, 0,0), 0);
  }
}

// Fill the dots one after the other with a color
void colorWipe_up(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i=i+3) {
    strip.setPixelColor(i, c);
    strip.setPixelColor(i+1, c);
    strip.setPixelColor(i+2, c);
    strip.show();
    delay(wait);
  }
  allOnecolor(strip.Color(0, 0, 0,0), 0);
}

// Fill the dots one after the other with a color
void colorWipe_down(uint32_t c, uint8_t wait) {
  for(int i=149; i > -1; i=i-3) {
    strip.setPixelColor(i, c);
    strip.setPixelColor(i-1, c);
    strip.setPixelColor(i-2, c);
    strip.show();
    delay(wait);
  }
  allOnecolor(strip.Color(0, 0, 0,0), 0);
}


void processSyncMessage() {
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

  if(Serial.find(TIME_HEADER)) {
    pctime = Serial.parseInt();
    if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
      setTime(pctime); // Sync Arduino clock to the time received on the serial port
    }
  }
}

time_t requestSync()
{
  Serial.write(TIME_REQUEST);
  return 0; // the time will be sent later in response to serial mesg
}
