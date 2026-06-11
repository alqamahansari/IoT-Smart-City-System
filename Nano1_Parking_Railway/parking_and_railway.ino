#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo parkingServo;
Servo railwayServo;

const int slot1 = 2;
const int slot2 = 3;
const int slot3 = 4;
const int parkingGateSensor = 5;

const int railwayIR = 7;
const int redLED = 8;
const int greenLED = 9;
const int buzzerPin = 10;

const int parkingServoPin = 6;
const int railwayServoPin = 11;

unsigned long previousMillis = 0;
bool warningState = false;

bool parkingGateOpen = false;
unsigned long gateOpenTime = 0;

bool crossingActive = false;
unsigned long trainGoneTime = 0;

void setup() {

  pinMode(slot1, INPUT);
  pinMode(slot2, INPUT);
  pinMode(slot3, INPUT);
  pinMode(parkingGateSensor, INPUT);

  pinMode(railwayIR, INPUT);

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.init();
  lcd.backlight();

  parkingServo.attach(parkingServoPin);
  railwayServo.attach(railwayServoPin);

  parkingServo.write(0);
  railwayServo.write(90);

  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, LOW);

  noTone(buzzerPin);
}

void loop() {

  parkingSystem();

  railwaySystem();
}

void parkingSystem() {

  int s1 = digitalRead(slot1);
  int s2 = digitalRead(slot2);
  int s3 = digitalRead(slot3);

  int available = 0;

  if (s1 == HIGH) available++;
  if (s2 == HIGH) available++;
  if (s3 == HIGH) available++;

  lcd.setCursor(0, 0);
  lcd.print("Slots Left:");
  lcd.print(available);
  lcd.print(" ");

  int gateSensorState = digitalRead(parkingGateSensor);

  if (gateSensorState == LOW &&
      available > 0 &&
      !parkingGateOpen) {

    parkingServo.write(90);

    parkingGateOpen = true;
    gateOpenTime = millis();

    lcd.setCursor(0, 1);
    lcd.print("Gate OPEN      ");
  }

  if (parkingGateOpen &&
      millis() - gateOpenTime >= 3000) {

    parkingServo.write(0);
    parkingGateOpen = false;
  }

  if (!parkingGateOpen) {

    lcd.setCursor(0, 1);

    if (available > 0)
      lcd.print("Waiting Car    ");
    else
      lcd.print("Parking FULL   ");
  }
}

void railwaySystem() {

  bool trainDetected = (digitalRead(railwayIR) == LOW);

  if (trainDetected) {

    crossingActive = true;

    railwayServo.write(0);

    digitalWrite(greenLED, HIGH);

    warningSignal();

    trainGoneTime = 0;
  }

  else {

    if (crossingActive) {

      if (trainGoneTime == 0) {
        trainGoneTime = millis();
      }

      warningSignal();

      if (millis() - trainGoneTime >= 5000) {

        railwayServo.write(90);

        digitalWrite(greenLED, LOW);
        digitalWrite(redLED, HIGH);

        noTone(buzzerPin);

        crossingActive = false;
        trainGoneTime = 0;
      }
    }

    else {

      railwayServo.write(90);

      digitalWrite(greenLED, LOW);
      digitalWrite(redLED, HIGH);

      noTone(buzzerPin);
    }
  }
}

void warningSignal() {

  if (millis() - previousMillis >= 300) {

    previousMillis = millis();

    warningState = !warningState;

    if (warningState) {

      digitalWrite(redLED, LOW);
      tone(buzzerPin, 1000);

    } else {

      digitalWrite(redLED, HIGH);
      noTone(buzzerPin);
    }
  }
}
