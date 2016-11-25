//This program plays the song 'IMPERIAL MARCH' when you press the black buzzer. This is the non-LED version. 

// the piezo is connected to analog pin 0
int piezo_Pin = A0;
int speakerPin = 8;
#include "pitches.h"
#include "Melody_Array.h"

// Threshold value to decide when the detected sound is a knock or not
const int Threshold = 10; 
const int ledList[] = {1, 2, 3, 4, 5, 6, 7, 8};

void setup()
{
    // use the serial port
    Serial.begin(9600);
    
    // set up our LED
}

void loop()
{
    int analogValue;

    // read the sensor and store it in the variable sensorReading:
    analogValue = analogRead(piezo_Pin);

    // if the sensor reading is greater than the Threshold:
    if (analogValue > Threshold)
    {
        // send the string "Knock!" back to the computer, followed by newline
        Serial.println("Imperial March Playing: ");
        for(int k = 0; k < 64; k++)
        {
            static int our_Note, Time, LedIndex, LedOn;
            LedIndex = rand() % 8;
            LedOn = ledList[LedIndex];
            our_Note = Melody_Array[k][0];
            Time = Melody_Array[k][1];
            tone(speakerPin, our_Note, Time);
            delay(Time * 1.3);
        }

    }

    // delay to avoid overloading the serial port buffer
    delay(100);
}
