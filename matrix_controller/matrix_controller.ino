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

int waveIntensity = 0;
char c = 0;

void setup() {
  matrix.begin();
  Serial.begin(9600);
  // Initialize wave to zero
  color = matrix.Color333(7,0,0);
  black = matrix.Color333(0,0,0);
}

void loop() {
// Block untill serial is available  
   while(Serial.available()){
   waveIntensity = Serial.parseInt();
   
   waveIntensity = ceil(waveIntensity / 8);
   matrix.drawFastVLine(currentFrame, 0, 15, 0x0000);
   matrix.drawFastVLine(currentFrame, 15-waveIntensity, waveIntensity+1, color);

   currentFrame = (currentFrame + 1) % 32;
   }
}
