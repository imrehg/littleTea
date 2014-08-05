/*
 * littleTea: tea brewing timer
 *
 * Part of the Instructables littleBits build night with the Taipei Hackerspace
 * Feel free to copy / modify.
**/

const int dialPin = 5;
const int buzzerPin = 1;
const int buttonPin = 0;
const int buttonPowerPin = 9;

const int onVal = 180;
const int offVal = 80;

const bool doBuzz = true;

const int brewingTime = 5 * 60;  // seconds

// Taken from debounce example
int buttonState = LOW;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPowerPin, OUTPUT);

  analogWrite(dialPin, offVal);
  digitalWrite(buttonPowerPin, HIGH);

  if (Serial) {   /* needed by the Leonardo types */
    Serial.begin(115200);
  }

}

void loop() {

  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  Serial.println(lastButtonState);

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        Serial.println("NOW!");
        startBrew();
      }
    }
  }
  lastButtonState = reading;
}

void startBrew() {
  if (doBuzz) {
    digitalWrite(buzzerPin, HIGH);
    delay(200);
    digitalWrite(buzzerPin, LOW);
  }

  // dip teabag
  analogWrite(dialPin, onVal);

  // brew the tea!
  for (int i = 0; i < brewingTime; i++) {
    delay(1000);
  }

  // gradual removal of teabag
  int steps = 30;
  for (int i = 1; i <= steps; i++) {
    int setVal = (offVal - onVal)/steps*i + onVal;
    analogWrite(dialPin, setVal);
    delay(100);
  }
  analogWrite(dialPin, offVal);

  if (doBuzz) {
    digitalWrite(buzzerPin, HIGH);
    delay(200);
    digitalWrite(buzzerPin, LOW);
    delay(100);
    digitalWrite(buzzerPin, HIGH);
    delay(200);
    digitalWrite(buzzerPin, LOW);
  }
}
