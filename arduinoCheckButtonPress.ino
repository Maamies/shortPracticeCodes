const int buttonPin = 2;

int buttonState = 0;
int buttonStateTwo = 0;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(3, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    digitalWrite(13, HIGH);
    delay(1000);
	buttonStateTwo = digitalRead(3);
    if (buttonStateTwo == HIGH){
   	 digitalWrite(12,HIGH);
   	 delay(1000);
    
    }else {
     digitalWrite(11,HIGH);
   	 delay(1000);
    }
  
  } else {
    digitalWrite(13, LOW);
    digitalWrite(12,LOW);
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
    digitalWrite(9,LOW);
  }
}