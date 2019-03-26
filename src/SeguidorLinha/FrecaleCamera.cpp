#include "FrescaleCamera.h"

int *FrescaleCamera::leSensor()
{
    delayMicroseconds(1); // Integration time in microseconds
    delay(10);            // Integration time in miliseconds

    digitalWrite(this->pinCLK, LOW);
    digitalWrite(this->pinSI, HIGH);
    digitalWrite(this->pinCLK, HIGH);
    digitalWrite(this->pinSI, LOW);

    delayMicroseconds(1);

    for (byte i = 0; i < this->numPixels; i++)
    {
        this->pixelArray[i] = analogRead(this->pinAOut);
        digitalWrite(this->pinCLK, LOW);
        delayMicroseconds(1);
        digitalWrite(this->pinCLK, HIGH);
    }
    return this->pixelArray;
}