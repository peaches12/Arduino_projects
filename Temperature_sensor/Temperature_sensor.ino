int temp_pin = A0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int analogValue;
  float temp;
  analogValue = analogRead(temp_pin);

  temp = float(analogValue) / 1023;
  temp = temp * 500;
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print("C");

  delay(1000);
}

