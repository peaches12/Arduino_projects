
int ledPins[] = {4, 9, 2, 7, 5, 8, 6, 3};
// the number of LEDs in the bar graph
int ledCount = sizeof(ledPins) / sizeof(ledPins[0]);

void setup()
{
    // use a for loop to initialize each pin as an output
    for (int thisLed = 0; thisLed < ledCount; thisLed++)
    {
        pinMode(ledPins[thisLed], OUTPUT);
    }
}

void loop()
{
    int off[], on[], on_LEDS, off_LEDS;
    // read the potentiometer
    int potReading = analogRead(potPin);
    // map the result to a range from 0 to the number of LEDs
    int ledLevel = map(potReading, 0, 1023, 0, ledCount);
    on_LEDS = ledLevel;
    off_LEDS = sizeof(ledPins) - on_LEDS;
    //split ledPins into 2 separate arrays
    memcpy(on, ledPins, on_LEDS * sizeof(int));
    memcpy(off, &ledPins[on_LEDS], off_LEDS * sizeof(int));

    
}
