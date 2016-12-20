

//button Pins
int btn[5] = {2, 4, 7, 8, 12};
//1st col is LED #, 2nd col is LED state--0 off, 1 on
int LEDS[5][2] = {
    {3, 0},
    {5, 0},
    {6, 0},
    {9, 0},
    {10, 0},
};
int start_BTN = 13;

boolean STAET = HIGH;
void setup()
{
    for(int x = 0; x < 5; x++)
    {
        pinMode(btn[x], INPUT_PULLUP); //setup button
        pinMode(LEDS[x][0], OUTPUT);   //setup LED
        digitalWrite(LEDS[x][0], LOW);
    }
    pinMode(start_BTN, INPUT_PULLUP); //setup START button
    Serial.begin(9600);
}

int loop_btn, led_num, led_state;
void loop()
{
    for(int k = 0; k < 5; k++)
    {
        loop_btn = btn[k];
        if(debounce(loop_btn) == LOW)
        {
            Serial.print("Button: ");
            Serial.println(loop_btn);
            led_num = LEDS[k][0];
            led_state = LEDS[k][1];
            if (led_state == 0)
            {
                Serial.println("LEDSTATE: 0");
                digitalWrite(led_num, HIGH);
                LEDS[k][1] = 1;
            }
            else if (led_state = 1)
            {
                Serial.println("LEDSTATE: 1");
                digitalWrite(led_num, LOW);
                LEDS[k][1] = 0;
            }
        }

    }
}

//debouncing the BTNS
boolean debounce(boolean State)
{
    boolean stateNow = digitalRead(loop_btn);
    if (stateNow != State)
    {
        delay(200);
        stateNow = digitalRead(loop_btn);
    }
    return stateNow;
}
