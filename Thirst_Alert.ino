
/*
 * Built for Patchr.io's Thirst Alert Plant Alarm
 * Tutorial: www.hackster.io/patchr
 * PCB Design: www.patchr.io
 * November 2019
*/

#include "Volume.h" /* Developed by Connor Nishijima (2016) */

int sensorPin = A0; //set the pin for the moisture sensor
int sensorValue;
int limit = 300;

Volume vol; 

void setup()
{
  Serial.begin(9600);
  vol.begin();
  vol.setMasterVolume(1.00); //Set this between 0.00 and 1.00 dependent on how loud you want the project to be
  vol.delay(500);
}

void loop()
{ 
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);

  if (sensorValue>limit) {
    Serial.println("*cricket*"); //if the sensor value is greater than 300 then play the cricket noise at a random interval between 1 an 30 seconds
    chirp();
    vol.delay(random (1000, 30000));
  } 
  else {
    vol.noTone();
  }
}


void chirp() { //this part of the software was written by Connor Nishijima and creates the chirp tones
  int freq = random(3700, 4000);
  float volume = random(10, 100+1) / 100.00;

  int chirpType = 1;

  if (chirpType == 1) {
    Serial.println("2");
    int chirpCount = random (1,3);
    chirp(chirpCount, freq, volume);
  }
}

void chirp(byte times, int freq, float volume) {
  float fadeOut = 1.00;
  while (times > 0) {
    float mv = 0;
    while (mv < 1.00) {
      int v = 0;
      while (v < 255) {
        vol.tone(freq, v * volume * mv * fadeOut);
        v += 4;
      }
      v = 255;
      while (v > 0) {
        vol.tone(freq, v * volume * mv * fadeOut);
        v -= 4;
      }
      vol.delay(20);
      mv += 0.2;
    }
    mv = 1.00;
    while (mv > 0.00) {
      int v = 0;
      while (v < 255) {
        vol.tone(freq, v * volume * mv * fadeOut);
        v += 4;
      }
      v = 255;
      while (v > 0) {
        vol.tone(freq, v * volume * mv * fadeOut);
        v -= 4;
      }
      vol.delay(20);
      mv -= 0.2;
    }
    vol.noTone();
    fadeOut -= 0.75;
    times--;
  }
}
