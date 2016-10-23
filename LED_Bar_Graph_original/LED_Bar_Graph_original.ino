

// the pin that the potentiometer is attached to
int signall = 1;
int potPin = A0;

// an array of pin numbers to which LEDs are attached
// to add more LEDs just list them here in this array
int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
// the number of LEDs in the bar graph
int ledCount = sizeof(ledPins) / sizeof(ledPins[0]);
//time factors
int yone = 1, ytwo = 2, rone = 3, rtwo = 4, gone = 5, gtwo = 6, bone = 7, btwo = 8;
//signal factors
int sigyo = 1, sigyt = 1, sigro = 1, sigrt = 1, siggo = 1, siggt = 1, sigbo = 1, sigbt = 1;

int siglist[] = {sigyo, sigyt, sigro, sigrt, siggo, siggt, sigbo, sigbt};

float timelist[] = {yone, ytwo, rone, rtwo, gone, gtwo, bone, btwo};

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
    int signall;
    int timepassed;
    // read the potentiometer
    int potReading = analogRead(potPin);
    // map the result to a range from 0 to the number of LEDs
    int ledLevel = map(potReading, 0, 1023, 0, ledCount);
    // loop over the LED array:
    for (int thisLed = 0; thisLed < ledCount; thisLed++)
    {

        if (thisLed < ledLevel)
        {
            signall = siglist[thisLed];
            timepassed = timelist[thisLed];
            if (signall == 1)
            {
                if (timepassed < 15)
                {
                    digitalWrite(ledPins[thisLed], HIGH);
                    timepassed = timepassed + 1; //timepassed increases by 1
                }
                else
                {
                    signall = 0;
                    timepassed = 0;
                }
                
            }
            else
            {
                if (timepassed < 15)
                {
                    digitalWrite(ledPins[thisLed], LOW);
                    timepassed = timepassed + 1; //timepassed increases by 1
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