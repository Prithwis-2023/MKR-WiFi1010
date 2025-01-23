void setup() 
{
  pinMode(8, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);  // Low when powerup, High when idle
}

void loop() 
{
  digitalWrite(LED_BUILTIN, !digitalRead(8));
}
