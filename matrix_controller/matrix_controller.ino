#include <RGBmatrixPanel.h>
#include <Adafruit_GFX.h>
#include <gamma.h>

#define CLK 8
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

const int width = 32;

int currentFrame = 0;
uint16_t color;
uint16_t black;

uint16_t green, yellow, red;
int waveIntensity = 0;
char c = 0;

void setup() {
  matrix.begin();
  Serial.begin(9600);
  // Initialize wave to zero
  color = matrix.Color333(0,7,0);
  black = matrix.Color333(0,0,0);
  
  red = matrix.Color333(7,0,0);
  green = matrix.Color333(0,7,0);
  yellow = matrix.Color333(7,7,0);
}

void loop() {
// Block untill serial is available  
   while(Serial.available()){
   waveIntensity = Serial.parseInt();
   
   waveIntensity = ceil(waveIntensity / 8);
   matrix.drawFastVLine(currentFrame, 0, 15, 0x0000);
   if (waveIntensity < 8) {
     matrix.drawFastVLine(currentFrame, 15-waveIntensity, waveIntensity+1, green);
   } else if (waveIntensity < 12) {
     matrix.drawFastVLine(currentFrame, 15-waveIntensity, waveIntensity+1, yellow);
     matrix.drawFastVLine(currentFrame, 8, 9, green);
   } else if (waveIntensity < 16) {
     matrix.drawFastVLine(currentFrame, 15-waveIntensity, waveIntensity+1, red);
     matrix.drawFastVLine(currentFrame, 4, 4, yellow);
     matrix.drawFastVLine(currentFrame, 8, 9, green);
   }  
//   matrix.drawFastVLine(currentFrame, 15-waveIntensity, waveIntensity+1, color);
   delay(25);
   currentFrame = (currentFrame + 1) % 32;
   }
}
