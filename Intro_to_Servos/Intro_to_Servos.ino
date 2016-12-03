/*
 * Tutorial 6a: Introduction to Servo Motors
 * 
 * Simply rotates your server from 0 to 180 degrees and back.
 *
 * The circuit:
 * - Brown pin to ground
 * - Red pin to 5v
 * - Orange pin to digital pin 9
 *
 * by BARRAGAN <http://barraganstudio.com>
 * modified 14 August 2013
 * by Blaise Jarrett
 *
 * This example code is in the public domain.
 *
 * Derivative work from:
 * http://arduino.cc/en/Tutorial/Sweep
 *
 */

#include <Servo.h> 

// the Orange pin is connected to digital pin 9
int SERVOPIN = 9;

int Potpin = A0;

int btnPin = 12;

const int Led_list[7] = {10, 11, 2, 3, 4, 5, 6};
// create servo object to control our servo
// a maximum of eight servo objects can be created 
Servo MYSERVO;

int echoPin = 7;
int trigPin = 8;
 
const int Interval[3] = {3, 2, 1};
void setup() 
{
    Serial.begin(9600); //monitor control
    MYSERVO.attach(SERVOPIN);// attaches the servo on pin 9 to the servo object 
    //all LEDS set to OUTPUT
    for(int k = 0; k < 7; k++)
    {
        pinMode(Led_list[k], OUTPUT);
        digitalWrite(Led_list[k], LOW); //all LEDS off at first
    }
    pinMode(btnPin, INPUT_PULLUP);
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);
    
}

void loop()
{
    int analogValue, pushed, LEDSLIGHT;
    pushed = digitalRead(btnPin);
    
    if (pushed == HIGH) //aka if btn is not pushed
    {
        int potValue, position;
        potValue = analogRead(Potpin);
        position = map(potValue, 0, 1023, 0, 179);
        MYSERVO.write(position);
        LEDSLIGHT = map(position, 0, 179, 0, 7); //sort of like a bar graph with LEDS
        //turn all the lights off
        for(int k = 0; k < 7; k++)
        {
        digitalWrite(Led_list[k], LOW); //all LEDS off at first
        }
        //turn the LEDSLIGHT leds on
        for(int y = 0; y < LEDSLIGHT; y++)
        {
            int loopLed;
            loopLed = Led_list[y];
            digitalWrite(loopLed, HIGH);
        }
        delay(15);
    }
    else //aka if btn is pushed
    {
        int distance_ft, pulseLenMS, LED_delay, countdown_time;
        float seconds, milliseconds;
        //find distance in cm.
        digitalWrite(trigPin, LOW);
        delayMicroseconds(20);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(100);
        digitalWrite(trigPin, LOW);
        
        pulseLenMS = pulseIn(echoPin, HIGH);
        
        distance_ft = pulseLenMS/29.387/2; //raw measurement in cm.--in this program cm=ft
        seconds = distance_ft/10; //converting ft. to seconds 
        milliseconds = seconds*1000; //converting secs. to millisecs.
        Serial.print("Distance: ");
        Serial.println(distance_ft);
        Serial.print("Time to hit: "); //print time
        Serial.print(seconds);
        Serial.println(" seconds.");
        delay(seconds);
        Serial.println("TARGET HIT!"); 
    }
}
