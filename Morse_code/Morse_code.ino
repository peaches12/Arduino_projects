// sketch 5-05
// MODERN MORSE CODE
//2 quick blue blinks--dot
//one red blink--dash
const int blueLed = 3;
const int greenLed = 4;
const int dotDelay = 200;

char* letters[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",    // A-I
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",  // J-R
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."          // S-Z
};

char* numbers[] = {
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};

void setup()                 
{
  pinMode(blueLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  Serial.begin(9600);
  digitalWrite(blueLed, LOW);
  digitalWrite(greenLed, LOW);
}

void loop()
// finds the sequence we use                    
{
  char ch;
  char* the_number;
  int ch_thing;
  if (Serial.available() > 0) // if something was typed into the monitor
  {
    // what is the 
    ch = Serial.read(); //read typed stuff letter by letter
    if (ch >= 'a' && ch <= 'z') // lowercase 
    {
      the_number = letters[ch - 'a'];
    }
    else if (ch >= 'A' && ch <= 'Z') // uppercase
    {
      the_number = letters[ch - 'A'];
    }
    else if (ch >= '0' && ch <= '9') // numbers
    {
      the_number = numbers[ch - '0'];
    }
    else if (ch == ' ') // space
    {
        the_number = 's';
    }
    flash(the_number);
    delay(1500); // space btw LETTERS
        
  }
  
}

void flash(char* sequence)
{
    char* our_char;
    for(int i = 0; i < strlen(sequence) + 1; i++)
    {
        our_char = sequence[i];
        if (our_char == '.')
        {
            digitalWrite(blueLed, HIGH);
            digitalWrite(greenLed, LOW);
            delay(200);
            digitalWrite(blueLed, LOW);
            digitalWrite(greenLed, LOW);
            delay(100);
            digitalWrite(blueLed, HIGH);
            digitalWrite(greenLed, LOW);
            delay(200);
        }
        else if (our_char == '-')
        {
            digitalWrite(blueLed, LOW);
            digitalWrite(greenLed, HIGH);
            delay(500);
        }
        else if (our_char == 's')
        {
            delay(2000); // space btw WORDS
        }
        digitalWrite(blueLed, LOW);
        digitalWrite(greenLed, LOW);
        delay(300); // space btw FLASHES
    }

}