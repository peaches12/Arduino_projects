/*
 * Tutorial 7a: Introduction to Stepper Motors
 * 
 * Simply rotates your stepper from 360 degrees forward
 * and back.
 *
 * The circuit:
 * - Stepper driver powered with 5v, GND
 * - D8-D11 connected to IN1-IN4 on the stepper driver
 *
 * by Blaise Jarrett
 *
 * This example code is in the public domain.
 *
 *
 */

#include <Stepper.h>
#include <LiquidCrystal.h>
int stepIN1Pin = 6;
int stepIN2Pin = 7;
int stepIN3Pin = 8;
int stepIN4Pin = 9;

int stepsPerRevolution = 2048;

Stepper myStepper(stepsPerRevolution,
                  stepIN1Pin, stepIN3Pin,
                  stepIN2Pin, stepIN4Pin);
                  
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int increaseBtn = 9;
boolean iBState = HIGH;
int decreaseBtn = 13;
boolean dBState = HIGH;

float motor_speed = 0.0;

int max_speed = 10;
int min_speed = 0;
void setup()
{
    // set the RPM
    myStepper.setSpeed(motor_speed);
    pinMode(increaseBtn, INPUT_PULLUP);
    pinMode(decreaseBtn, INPUT_PULLUP);
    lcd.begin(16, 2);
}

void loop()
{
    if(debounceButton(dBState, decreaseBtn) == LOW && dBState == HIGH) //aka if btn is pushed
    {
        if (motor_speed > 0.5)
        {
            motor_speed = motor_speed - 0.5;
        }
        
    }
    if(debounceButton(iBState, increaseBtn) == LOW && iBState == HIGH) //aka if other btn is pushed
    {
        if (motor_speed < 10)
        {
            motor_speed = motor_speed + 0.5;
        }
    }
    lcd.setCursor(0, 0);
    lcd.print("Speed: ");
    lcd.setCursor(0, 7);
    lcd.print(motor_speed);
    myStepper.setSpeed(motor_speed);
    myStepper.step(stepsPerRevolution);
}

boolean debounceButton(boolean state, int btn)
{
    boolean stateNow = digitalRead(btn);
    if(state != stateNow)
    {
        delay(200);
        stateNow = digitalRead(btn);
    }
    return stateNow;
} 
