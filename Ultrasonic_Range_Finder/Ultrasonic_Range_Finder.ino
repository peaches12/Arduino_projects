/*press the btn to start the program.
  when the distance is <10, you must enter a password into the serial monitor
  if password is wrong, you may retry as many times as you like
  if password is right, you have 4 secs. to 'enter' and then you must press btn again to restart */

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
    pinMode(greenLed, OUTPUT);
    pinMode(redLed, OUTPUT);
}

void loop()
{
    if(debounce(STAET) == LOW && STAET == HIGH) //aka btn pressed
    {
        digitalWrite(greenLed, HIGH);
        digitalWrite(redLed, LOW);
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
            if(distanceCentimeters < 10)
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
                            digitalWrite(greenLed, HIGH);
                            digitalWrite(redLed, LOW);
                            lcd.clear();
                            lcd.setCursor(0, 0);
                            lcd.print("You may enter");
                            delay(4000);
                            software_Reset();
                        }
                        else
                        {
                            lcd.setCursor(0, 0);
                            lcd.print("You are wrong.");
                            lcd.setCursor(0, 1);
                            lcd.print("Try again:");
                        }
                    }
                }
            }              
        }
    }  
    else
    {
        digitalWrite(greenLed, LOW);
    }        
}
boolean debounce(boolean State) //make sure btn is pressed ONCE
{
    boolean stateNow = digitalRead(btnPin);
    if (stateNow != State)
    {
        delay(200);
        stateNow = digitalRead(btnPin);
    }
    return stateNow;
}

void software_Reset() //restart program without pressing the button
{
    asm volatile ("  jmp 0");
}