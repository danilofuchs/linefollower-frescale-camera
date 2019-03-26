#ifndef FRESCALE_CAMERA_H
#define FRESCALE_CAMERA_H

#include <digitalWriteFast.h>
#include "Arduino.h";

#define DEFAULT_NUM_PIXELS 128 // No. of pixels in array

class FrescaleCamera
{
public:
  FrescaleCamera(int pinAOut, int pinSI, int pinCLK) : pinAOut(pinAOut), pinSI(pinSI), pinCLK(pinCLK), numPixels(DEFAULT_NUM_PIXELS)
  {
    pinMode(pinSI, OUTPUT);
    pinMode(pinCLK, OUTPUT);
    pinMode(pinAOut, INPUT);
    digitalWrite(pinSI, LOW);  // IDLE state
    digitalWrite(pinCLK, LOW); // IDLE state
  };
  int *leSensor();

private:
  int pinAOut;                        // Analog output - yellow
  int pinSI;                          // Start Integration - orange
  int pinCLK;                         // Clock - red
  int pixelArray[DEFAULT_NUM_PIXELS]; // Field for measured values <0-255>
  byte numPixels;
};

#endif
