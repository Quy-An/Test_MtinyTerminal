
uint8_t pinG = 3;
uint8_t pinY = 4;
uint8_t pinR = 5;

uint32_t timeON_G = 3000; // ms
uint32_t timeON_Y = 1000; //ms
uint32_t timeON_R = timeON_G + timeON_Y; // ms

void setup() {
  // put your setup code here, to run once:
  pinMode(pinG, OUTPUT);
  pinMode(pinY, OUTPUT);
  pinMode(pinR, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(pinR, 1);
  digitalWrite(pinY, 0);
  digitalWrite(pinG, 0);

  delay(timeON_R);

  digitalWrite(pinR, 0);
  digitalWrite(pinY, 0);
  digitalWrite(pinG, 1);

  delay(timeON_G);

  digitalWrite(pinR, 0);
  digitalWrite(pinY, 1);
  digitalWrite(pinG, 0);

  delay(timeON_Y);


}
