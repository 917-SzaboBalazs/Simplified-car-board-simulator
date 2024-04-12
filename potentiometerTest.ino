#include <Servo.h>

Servo myservo;  // create servo object to control a servo

#define servoPin A5
#define indexPin A4
#define rightIndex 3
#define leftIndex 4
#define buttonPin 5
#define lightOpenPin 6
#define servoCtrlPin 7

int servoPos = 0;
int indexPos = 0;
//set initial servo flags to 0
bool t_left = false;
bool t_forward = false;
bool t_right = false;

bool lightFlag = false;
int buttonPushCounter = 0;
int buttonState = HIGH;
int prevButtonState = HIGH;

#define threeway23 341
#define threeway12 682
#define indexDiv 511

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(servoCtrlPin);  // attaches the servo on pin 9 to the servo object
  pinMode(rightIndex, OUTPUT);
  pinMode(leftIndex, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(lightOpenPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  servoPos = analogRead(servoPin);
  indexPos = analogRead(indexPin);
  if (servoPos > threeway12) {
    t_left = false;
    t_forward = false;
    t_right = true;
    myservo.write(179);
  } else if (servoPos < threeway23) {
    t_left = true;
    t_forward = false;
    t_right = false;
    myservo.write(1);
  } else {
    t_left = false;
    t_forward = true;
    t_right = false;
    myservo.write(90);
  }

  if (indexPos > threeway12) {

    digitalWrite(rightIndex, HIGH);
    digitalWrite(leftIndex, LOW);
  } else if (indexPos < threeway23) {
    digitalWrite(rightIndex, LOW);
    digitalWrite(leftIndex, HIGH);
  } else {
    digitalWrite(rightIndex, LOW);
    digitalWrite(leftIndex, LOW);
  }

  if (lightFlag == false) {
    digitalWrite(lightOpenPin, LOW);
  } else {
    digitalWrite(lightOpenPin, HIGH);
  }
  buttonState = digitalRead(buttonPin);
  if (buttonState != prevButtonState) {
    delay(50);
    if (buttonState == LOW) {
      buttonPushCounter++;
      if (lightFlag == true) {
        lightFlag = false;
      } else {
        lightFlag = true;
      }
    }
  }
  prevButtonState = buttonState;
}