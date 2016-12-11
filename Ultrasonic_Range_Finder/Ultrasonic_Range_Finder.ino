/*
 * Tutorial 5: Ultrasonic Range Finder
 * 
 * Prints the distance measured from the
 * range finder over serial. Place the board on your desk
 * and open up the serial monitor. Move an object in front of the
 * ultrasonic sensor and you'll see the distance to the object
 * printed out over serial.
 *
 * The circuit:
 * - 5v, ground connected to Ultrasonic sensor
 * - digital pin 4 conneceted to Ultrasonic sensor echo pin
 * - digital pin 5 conneceted to Ultrasonic sensor trig pin
 *
 * created 3 Nov 2008
 * by David A. Mellis
 * modified 30 Aug 2011
 * by Tom Igoe
 * modified 14 August 2013
 * by Blaise Jarrett
 *
 * This example code is in the public domain.
 *
 * Derivative work from:
 * http://www.arduino.cc/en/Tutorial/Ping
 *
 */

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
int greenLed = 10;
int redLed = 9;
//password
char* password = "9";
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
    //Serial
    Serial.begin(9600);
    
}

void loop()
{
    if(debounce(STAET) == LOW && STAET == HIGH) //aka btn pressed
    {
        float distanceCentimeters;
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
            lcd.setCursor(0, 0);
            lcd.print(distanceCentimeters);
            lcd.print(" cm")
            delay(100);
            if(distanceCentimeters < 30);
            {
                digitalWrite(greenLed, LOW); //green OFF
                digitalWrite(redLed, HIGH);  //red ON
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("PASSWORD: ");
                while (1 == 1) //forever
                    if(Serial.available() > 0)
                    {
                        int typed_password = Serial.read();
                        if (typed_password == password) //if password is correct
                        {
                            digitalWrite(redLED, LOW);
                            digitalWrite(greenLed, HIGH);
                            lcd.clear();
                            lcd.print("You may enter");
                        }
                        else
                        {
                            lcd.print("Incorrect.");    
                        }
                    }
                    else
                    {
                        //do nothing
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
