

// the pin that the potentiometer is attached to
int potPin = A0;

// an array of pin numbers to which LEDs are attached
// to add more LEDs just list them here in this array
int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
// the number of LEDs in the bar graph
int ledCount = sizeof(ledPins) / sizeof(ledPins[0]);


void setup()
{
    // use a for loop to initialize each pin as an output
    for (int thisLed = 0; thisLed < ledCount; thisLed++)
    {
        pinMode(ledPins[thisLed], OUTPUT);
        delay(200);
    }
    Serial.begin(9600);

}

void loop()
{
    
    static int signall;
    static int timepassed;
    static int signall_array[8];
    static int time_array[8];
    //everything in signall_array = 1
    for (int y = 0; y < 8; y++)
    {
        signall_array[y] = 1;
    }
    //everything in time_array = 0
    for (int k = 0; k < 8; k++)
    {
        time_array[k] = 0;
    }

    
    // read the potentiometer
    int potReading = analogRead(potPin);
    // map the result to a range from 0 to the number of LEDs
    int ledLevel = map(potReading, 0, 1023, 0, ledCount);
    // this blinks all the ON LEDS simultaneously
    for (int thisLed = 0; thisLed < ledCount; thisLed++)
    {
        if (thisLed < ledLevel)
        {
            signall = signall_array[thisLed]; //signall 1--that led is on, signall 0--that led is off
            timepassed = time_array[thisLed];
            //aka the ON part of the blinking
            if (signall == 1) 
            {
                if (timepassed < 10)
                {
                    digitalWrite(ledPins[thisLed], HIGH);
                    timepassed = timepassed + 1; //timepassed increases by 1
                    time_array[thisLed] = timepassed;
                    Serial.println(timepassed);
                }
                else
                {
                    signall = 0;
                    timepassed = 0;
                }
            }
            //aka the OFF part of the blinking
            else
            {
                if (timepassed < 10)
                {
                    digitalWrite(ledPins[thisLed], LOW);
                    timepassed++; //timepassed increases by 1
                    time_array[thisLed] = timepassed;
                }
                else
                {
                    signall = 1;
                    timepassed = 0;
                }
            }                
        }
        // turn off all pins higher than the ledLevel
        else
        {
            digitalWrite(ledPins[thisLed], LOW);
        }
             
    }

}