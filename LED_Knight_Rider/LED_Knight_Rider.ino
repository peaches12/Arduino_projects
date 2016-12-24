/*Traffic light--press btn #1 and pedestrian light turns on for 10 secs, or press btn #2 (panic mode) and the 
green light turns on until you press btn #2 again. */
//the LEDS
int red_traf = 9;
int yellow_traf = 6;
int green_traf = 5;
int red_pedestrian = 11;
int blue_pedestrian = 10;
int LED_LIST[5] = {9, 6, 5, 11, 10};

//the BTNS
int pedestrian_btn = 4;
int panic_btn = 2;

int loop_led;
boolean State, StateNow;
void setup()
{
    //setup the LEDS
    for(int k = 0; k < 5; k++)
    {
        loop_led = LED_LIST[k];
        pinMode(loop_led, OUTPUT);
        digitalWrite(loop_led, LOW);
    }
    //setup the BTNs
    pinMode(pedestrian_btn, INPUT_PULLUP);
    pinMode(panic_btn, INPUT_PULLUP);
}

void loop()
{
    digitalWrite(red_pedestrian, HIGH);
    //before YELLOW--just came out before RED
    if(ped_btn_pressed(pedestrian_btn) == LOW)
    {
        ped_function();
    }
    panic_function();
    yellow_function();
    //before GREEN--just came out before YELLOW
    if(ped_btn_pressed(pedestrian_btn) == LOW)
    {
        ped_function();
        yellow_function();
    }
    panic_function();
    green_function();
    //before YELLOW--just came out before GREEN
    if(ped_btn_pressed(pedestrian_btn) == LOW)
    {
        yellow_function();
        ped_function();
        yellow_function();
        green_function();
    }
    panic_function();
    yellow_function();
    //before RED--just came out before YELLOW
    if(ped_btn_pressed(pedestrian_btn) == LOW)
    {
        ped_function();
        yellow_function();
        green_function;
        yellow_function();
    }
    panic_function();
    red_function();
}

boolean ped_btn_pressed(int btn_type)
{
    StateNow = digitalRead(btn_type);
    if (StateNow == LOW)
    {   
        delay(200);
        StateNow = digitalRead(btn_type);
    }
    return StateNow;
            
}

void yellow_function()
{
    digitalWrite(green_traf, LOW);
    digitalWrite(yellow_traf, HIGH);
    digitalWrite(red_traf, LOW);     //YELLOW
    delay(1000);
}

void red_function()
{
    digitalWrite(green_traf, LOW);
    digitalWrite(yellow_traf, LOW);
    digitalWrite(red_traf, HIGH);     //RED
    delay(1000);
}

void green_function()
{
    digitalWrite(green_traf, HIGH);
    digitalWrite(yellow_traf, LOW);
    digitalWrite(red_traf, LOW);     //GREEN
    delay(1000);
}

void ped_function()
{
    digitalWrite(red_pedestrian, LOW);
    digitalWrite(blue_pedestrian, HIGH);
    red_function();
    delay(9000); //ten seconds to cross--is that enough?
    digitalWrite(red_pedestrian, HIGH);
    digitalWrite(blue_pedestrian, LOW);
}

void panic_function()
{
    if(ped_btn_pressed(panic_btn) == LOW)
    {
        delay(1000);
        while(ped_btn_pressed(panic_btn) != LOW) //while the btn is NOT pressed
        {
            green_function();
            digitalWrite(green_traf, LOW);
            delay(1000);
        }
    }
}