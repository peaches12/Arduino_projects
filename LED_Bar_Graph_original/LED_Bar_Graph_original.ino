

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
    int signall;
    int timepassed;
    static int signall_array;
    static int time_array;
    //signal array
    signall_array[8] = {[0 ... 7] = 1}; //everything in this array is 1
    time_array[8] = {[0 ... 7] = 0}; //everything here is 0
    
    // read the potentiometer
    int potReading = analogRead(potPin);
    // map the result to a range from 0 to the number of LEDs
    int ledLevel = map(potReading, 0, 1023, 0, ledCount);
    // loop over the LED array:
    for (int thisLed = 0; thisLed < ledCount; thisLed++)
    {
        if (thisLed < ledLevel)
        {
            signall = signall_array[thisLed]; //signall 1--that led is on, signall 0--that led is off
            timepassed = time_array[thisLed];
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
                Serial.println("LED is: ");
                Serial.print(thisLed);
                Serial.println("Timepassed is: ");
                Serial.print(timepassed);
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