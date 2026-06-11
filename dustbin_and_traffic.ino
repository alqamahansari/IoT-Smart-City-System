#include <Servo.h>

Servo myservo;

const int trigPin = 2;
const int echoPin = 3;

float distance = 0;

bool lidOpen = false;
unsigned long lidTimer = 0;

const int NS_RED = 4;
const int NS_YELLOW = 5;
const int NS_GREEN = 6;

const int EW_RED = 7;
const int EW_YELLOW = 8;
const int EW_GREEN = 10;

unsigned long previousMillis = 0;
int trafficState = 0;

void setup() {

  Serial.begin(9600);

  myservo.attach(9);
  myservo.write(0);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(NS_RED, OUTPUT);
  pinMode(NS_YELLOW, OUTPUT);
  pinMode(NS_GREEN, OUTPUT);

  pinMode(EW_RED, OUTPUT);
  pinMode(EW_YELLOW, OUTPUT);
  pinMode(EW_GREEN, OUTPUT);

  digitalWrite(NS_RED, HIGH);
  digitalWrite(NS_YELLOW, HIGH);
  digitalWrite(NS_GREEN, HIGH);

  digitalWrite(EW_RED, HIGH);
  digitalWrite(EW_YELLOW, HIGH);
  digitalWrite(EW_GREEN, HIGH);
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration > 0) {

    distance = duration * 0.034 / 2;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance <= 5) {

      if (!lidOpen) {
        myservo.write(45);
        lidOpen = true;
      }

      lidTimer = millis();
    }
  }

  if (lidOpen && (millis() - lidTimer >= 3000)) {
    myservo.write(0);
    lidOpen = false;
  }

  unsigned long currentMillis = millis();

  switch (trafficState) {

    case 0:

      digitalWrite(NS_RED, HIGH);
      digitalWrite(NS_YELLOW, HIGH);
      digitalWrite(NS_GREEN, LOW);

      digitalWrite(EW_RED, LOW);
      digitalWrite(EW_YELLOW, HIGH);
      digitalWrite(EW_GREEN, HIGH);

      if (currentMillis - previousMillis >= 5000) {
        previousMillis = currentMillis;
        trafficState = 1;
      }
      break;

    case 1:

      digitalWrite(NS_RED, HIGH);
      digitalWrite(NS_YELLOW, LOW);
      digitalWrite(NS_GREEN, HIGH);

      digitalWrite(EW_RED, LOW);
      digitalWrite(EW_YELLOW, HIGH);
      digitalWrite(EW_GREEN, HIGH);

      if (currentMillis - previousMillis >= 2000) {
        previousMillis = currentMillis;
        trafficState = 2;
      }
      break;

    case 2:

      digitalWrite(NS_RED, LOW);
      digitalWrite(NS_YELLOW, HIGH);
      digitalWrite(NS_GREEN, HIGH);

      digitalWrite(EW_RED, HIGH);
      digitalWrite(EW_YELLOW, HIGH);
      digitalWrite(EW_GREEN, LOW);

      if (currentMillis - previousMillis >= 5000) {
        previousMillis = currentMillis;
        trafficState = 3;
      }
      break;

    case 3:

      digitalWrite(NS_RED, LOW);
      digitalWrite(NS_YELLOW, HIGH);
      digitalWrite(NS_GREEN, HIGH);

      digitalWrite(EW_RED, HIGH);
      digitalWrite(EW_YELLOW, LOW);
      digitalWrite(EW_GREEN, HIGH);

      if (currentMillis - previousMillis >= 2000) {
        previousMillis = currentMillis;
        trafficState = 0;
      }
      break;
  }
}