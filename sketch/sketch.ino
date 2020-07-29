#include <Mouse.h>

int yPin = A2;
int xPin = A3;
int deadzone = 50;
int x;
int center;
int debounce = 0;

void setup() {
  Serial.begin(9600);
  Mouse.begin();
  
  while (!Serial) {
    delay(10);
  }

  Serial.print("Calibrating... ");

  int oldX = 0;
  int totalX = 0;
  int validCalibrations = 0;

  for (int i = 0; i < 5; i++) {
    int calibration = analogRead(xPin);
    
    Serial.print(calibration);
    Serial.print(" ");

    if (calibration > 0 && calibration < 1000) {
      totalX += calibration;
      validCalibrations++;
    }
  }

  center = totalX / validCalibrations;
  Serial.print("Center: ");
  Serial.println(center);
}

void loop() {
  if (debounce > 0) {
    debounce--;
  } else {
    x = analogRead(xPin);
    if (x > center + deadzone) {
      Mouse.move(0, 0, -1);
      debounce = 25;
    } else if (x < center - deadzone) {
      Mouse.move(0, 0, 1);
      debounce = 25;
    }
  }
//  Serial.print("xPin: ");
//  Serial.println(x);
  delay(1);
}
