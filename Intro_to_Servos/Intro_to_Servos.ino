/* Gun Project
*  Turn the potentiometer to turn the servo motor ('gun'). 
*  Press the button hard
*  Arduino measures distance w/ ultrasonic range finder & calculates how long a 'bullet' will take to hit nearest 
*  object from gun. 
*  Special thanks 2 educ8s.tv for the debounce video! */

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

boolean buttonState = HIGH;
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
    if(debounceButton(buttonState) == LOW && buttonState == HIGH) //aka if btn is pushed
    {
        int pulseLenMS, LED_delay, countdown_time;
        float seconds, milliseconds, distance_ft;
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
        Serial.print(distance_ft);
        Serial.println(" cm.");
        Serial.print("Time to hit: "); //print time
        Serial.print(seconds);
        Serial.println(" seconds.");
        delay(milliseconds);
        Serial.println("TARGET HIT!"); 
    }
    else //aka if btn is not pushed
    {
        int potValue, position;
        potValue = analogRead(Potpin);
        position = map(potValue, 0, 1022, 0, 179);
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
}
//see if the button was pressed more than once or if it was just a debounce
boolean debounceButton(boolean state)
{
    boolean stateNow = digitalRead(btnPin);
    if(state != stateNow)
    {
        delay(200);
        stateNow = digitalRead(btnPin);
    }
    return stateNow;
}