

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
    //time factors
    static int yone = 1, ytwo = 1, rone = 1, rtwo = 1, gone = 1, gtwo = 1, bone = 1, btwo = 1;
    //signal factors
    static int sigyo = 1, sigyt = 1, sigro = 1, sigrt = 1, siggo = 1, siggt = 1, sigbo = 1, sigbt = 1;

    static int siglist[8] = {sigyo, sigyt, sigro, sigrt, siggo, siggt, sigbo, sigbt};

    static int timelist[8] = {yone, ytwo, rone, rtwo, gone, gtwo, bone, btwo};
    // read the potentiometer
    int potReading = analogRead(potPin);
    // map the result to a range from 0 to the number of LEDs
    int ledLevel = map(potReading, 0, 1023, 0, ledCount);
    // loop over the LED array:
    for (int thisLed = 0; thisLed < ledCount; thisLed++)
    {
        if (thisLed < ledLevel)
        {
            signall = siglist[thisLed]; //signal 1--that led is on, signal 0--that led is off
            timepassed = timelist[thisLed];
            if (signall == 1) 
            {
                if (timepassed < 15)
                {
                    digitalWrite(ledPins[thisLed], HIGH);
                    timepassed++; //timepassed increases by 1
                }
                else
                {
                    signall = 0;
                    timepassed = 0;
                } 
                Serial.println(timepassed);
            }
            else
            {
                if (timepassed < 15)
                {
                    digitalWrite(ledPins[thisLed], LOW);
                    timepassed++; //timepassed increases by 1
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