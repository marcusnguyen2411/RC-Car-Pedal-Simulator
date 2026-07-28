auto upButton = A0;
auto downButton = A1;
auto LED = 8;
auto fiV = 12;

int brightness = 0;

void setup() {
  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(fiV, OUTPUT);
  digitalWrite(fiV, 1);
  Serial.begin(9600);
}

int oldupEvent = 1;
int olddownEvent = 1;
int upHold = 0;
int downHold = 0;
int upTemp = 0;
int upTime = 80;
int downTemp = 0;
int downTime = 80;

void loop() {
  int upEvent = digitalRead(upButton);
  int downEvent = digitalRead(downButton);

  if (upEvent == 0) {
    upHold += 1;
    if (upHold >= 8) {
      if (upTime - upTemp > 0) {
        delay(upTime - upTemp);
        upTemp = upTemp + 2;
      };
      brightness += 2 + (upTemp / 10);
      brightness = check(brightness);
      analogWrite(LED, brightness);
      Serial.println(brightness);
    }
  } else if (upEvent == 1) {
    upHold = 0;
    upTemp = 0;
  }

  if (downEvent == 0) {
    downHold += 1;
    if (downHold >= 8) {
      if (downTime - downTemp > 0) {
        delay(downTime - downTemp);
        downTemp = downTemp + 2;
      };
      brightness -= 2 + (downTemp / 10);
      brightness = check(brightness);
      analogWrite(LED, brightness);
      Serial.println(brightness);
    }
  } else if (downEvent == 1) {
    downHold = 0;
    downTemp = 0;
  }

  if (upEvent == 0 && oldupEvent == 1) {
    delay(10);
    brightness += 15;
    brightness = check(brightness);
    analogWrite(LED, brightness);
    Serial.println(brightness);
  }
  delay(10);
  oldupEvent = upEvent;

  if (downEvent == 0 && olddownEvent == 1) {
    delay(10);
    brightness -= 15;
    brightness = check(brightness);
    analogWrite(LED, brightness);
    Serial.println(brightness);
  }
  delay(10);
  olddownEvent = downEvent;
}

int check(int brightness) {
  if (brightness > 255) {
    brightness = 255;
    return brightness;
  };
  if (brightness < 0) {
    brightness = 0;
    return brightness;
  };
  return brightness;
}