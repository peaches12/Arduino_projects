

//all the 'includes'
#include <LiquidCrystal.h>
// the pins connected to the Ultrasonic sensor
int echoPin = 7;
int trigPin = 8;
//button 
int btnPin = 6;
boolean STAET = HIGH;
//LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//LEDS
const int greenLed = 10;
const int redLed = 9;
//password
int password = 56787;
void setup()
{
    // set up serial
    Serial.begin(9600);
    // set the pinmode on our ultrasonic echo, and tric pins
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);
    // set the LCD screen
    lcd.begin(16, 2);
    lcd.clear(); //erase everything
    // set the BTN
    pinMode(btnPin, INPUT_PULLUP);
    // set the LEDs
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
}

void loop()
{
    if(debounce(STAET) == LOW && STAET == HIGH) //aka btn pressed
    {
        int distanceCentimeters;
        int pulseLenMicroseconds;
        while (1 == 1) //forever loop
        {
            // bit-bang a small square wave
            // on the trig pin to start the range
            // finder
            digitalWrite(trigPin, LOW);
            delayMicroseconds(20);
            digitalWrite(trigPin, HIGH);
            delayMicroseconds(100);
            digitalWrite(trigPin, LOW);

            // measure the pulse length from the echo pin
            pulseLenMicroseconds = pulseIn(echoPin, HIGH);

            // calculate the distance using the speed of sound
            distanceCentimeters = pulseLenMicroseconds / 29.387 / 2;
            // print it on LCD
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print(distanceCentimeters);
            lcd.print(" cm");
            delay(2000);
            if(distanceCentimeters < 100)
            {
                digitalWrite(greenLed, LOW); //green OFF
                digitalWrite(redLed, HIGH);  //red ON
                lcd.setCursor(0, 0);
                lcd.print("PASSWORD: ");
                while (1 == 1) //forever
                {
                    if(Serial.available() > 0)
                    {
                        int typed_password = Serial.read(); //read character over serial
                        
                        if(typed_password == 't')
                        {
                            lcd.clear();
                            lcd.setCursor(0, 0);
                            Serial.println("Case");
                            Serial.println(typed_password);
                            lcd.print("You may enter");
                        }
                        else
                        {
                            lcd.setCursor(0, 0);
                            lcd.print("You are wrong.");
                            lcd.setCursor(0, 1);
                            lcd.print("Try again:");
                            Serial.println("Default");
                            Serial.println(typed_password);
                        }
                    }
                }
            }              
        }
    }  
    else
    {
        //do nothing
    }        
}
boolean debounce(boolean State)
{
    boolean stateNow = digitalRead(btnPin);
    if (stateNow != State)
    {
        delay(200);
        stateNow = digitalRead(btnPin);
    }
    return stateNow;
}