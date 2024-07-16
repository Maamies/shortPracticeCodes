const int buttonPin = 2;

int buttonState = 0;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(12,HIGH);
    delay(1000);
    digitalWrite(11,HIGH);
    delay(1000);
    digitalWrite(10,HIGH);
    delay(1000);
    digitalWrite(9,HIGH);
    delay(1000);
  
  } else {
    digitalWrite(13, LOW);
    digitalWrite(12,LOW);
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
    digitalWrite(9,LOW);
  }
}