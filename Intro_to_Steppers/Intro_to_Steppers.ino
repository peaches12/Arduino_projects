/*
What you need: 2 buttons, 1 LCD screen, 1 potentiometer, 1 Stepper Motor
What it does: Press the buttons to increase/decrease speed of the motor. Speed is printed on the LCD screen.
 */

#include <Stepper.h>
#include <LiquidCrystal.h>
int stepIN1Pin = 13;
int stepIN2Pin = 7;
int stepIN3Pin = 8;
int stepIN4Pin = 9;

int stepsPerRevolution = 2048;

Stepper myStepper(stepsPerRevolution,
                  stepIN1Pin, stepIN3Pin,
                  stepIN2Pin, stepIN4Pin);
                  
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int increaseBtn = 10;
boolean iBState = HIGH;
int decreaseBtn = 6;
boolean dBState = HIGH;

int motor_speed = 6;

int max_speed = 12;
int min_speed = 4;
void setup()
{
    Serial.begin(9600);
    // set the RPM
    myStepper.setSpeed(motor_speed);
    pinMode(increaseBtn, INPUT_PULLUP);
    pinMode(decreaseBtn, INPUT_PULLUP);
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Speed:        ");
}

void loop()
{
    
    if(debounceDB(dBState) == LOW && dBState == HIGH) //aka if btn is pushed
    {
        if (motor_speed > min_speed)
        {
            motor_speed = motor_speed - 1;
        }
        else
        {
            //do nothing
        }
        
    }
    if(debounceIB(iBState) == LOW && iBState == HIGH) //aka if other btn is pushed
    {
        if (motor_speed < max_speed)
        {
            motor_speed = motor_speed + 1;
        }
        else
        {
            //do nothing
        }
    } 

    lcd.setCursor(0, 7);
    lcd.print(motor_speed);
    lcd.print(" ");
    myStepper.setSpeed(motor_speed);
    myStepper.step(stepsPerRevolution/8);

}

boolean debounceDB(boolean DBSTATE)
{
    boolean Nowstate = digitalRead(decreaseBtn);
    if(DBSTATE != Nowstate)
    {
        delay(200);
        Nowstate = digitalRead(decreaseBtn);
    }
    return Nowstate;
} 
boolean debounceIB(boolean State)
{
    boolean StateNow = digitalRead(increaseBtn);
    if(State != StateNow)
    {
        delay(200);
        StateNow = digitalRead(increaseBtn);
    }
    return StateNow;
} 

