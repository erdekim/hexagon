#include <Adafruit_NeoPixel.h>
#include "mapping.h"
#include "ripple.h"

#define PIN 6

//#define DEBUG 

const int numPixels = 15 * 30;
const int decayRate = 16;
const int delayTime = 10;

byte pixels[numPixels][3];

Adafruit_NeoPixel strip(numPixels, PIN, NEO_GRB + NEO_KHZ800);

Ripple ripples[100];

long time = 0;
long deltaTime = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);

  ripples[0].start(centerIndex, nodeConnections[centerIndex][0], Clockwise, BLUE);
  ripples[1].start(centerIndex, nodeConnections[centerIndex][1], Clockwise, RED);
  ripples[2].start(centerIndex, nodeConnections[centerIndex][2], Clockwise, BLUE);
  ripples[3].start(centerIndex, nodeConnections[centerIndex][3], Clockwise, RED);
  ripples[4].start(centerIndex, nodeConnections[centerIndex][4], Clockwise, BLUE);
  ripples[5].start(centerIndex, nodeConnections[centerIndex][5], Clockwise, RED);

  time = millis();

  strip.begin();
  strip.show();
}

void loop() {
  strip.clear();

  for(int i = 0; i < 100; i++) {
    ripples[i].update(deltaTime);
  }

  for(int i = 0; i < 100; i++) {
    ripples[i].render(&pixels);
  }
  
  
  // Display    
  for(int i = 0; i < numPixels; i++) {
    strip.setPixelColor(i, pixels[i][0], pixels[i][1], pixels[i][2]);
  }

  // Decay the brightness
  for(int i = 0; i < numPixels; i++) {
    for(int j = 0; j < 3; j++) {
      pixels[i][j] = max(0, pixels[i][j] - decayRate);
    }
  }

  strip.show();
//  delay(delayTime);

  long currentTime = millis();
  deltaTime = currentTime - time;
  time = currentTime;
  Serial.println(deltaTime);
}

void testGetLed() {
  int led = getLed(9, 4, 1);
  Serial.print("\tLED: ");
  Serial.println(led);
  
}

void testIndices() {
  for(int i = 0; i < 30; i++) {
    int min = min(ledIndices[i][0], ledIndices[i][1]);
    int max = max(ledIndices[i][0], ledIndices[i][1]);

    if(max - min != 14) {
      Serial.print("Error at index: ");
      Serial.print(i);
      Serial.print(" min: ");
      Serial.print(min);
      Serial.print(" max: ");
      Serial.println(max);
    }
  }
}

