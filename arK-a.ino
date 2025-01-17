#include <Mouse.h>
#include <Keyboard.h>

void setup() {
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  static bool active = false;

  if (Serial.available() > 0) {
    String incoming = Serial.readStringUntil('\n');
    incoming.trim();

    if (incoming == "arK?") {
      Serial.println("arK!");
      active = true;
    }
    if (incoming == "arK/") {
      active = false;
    }

    if (!active){
      return;
    }

    if (incoming.length() < 2) {
      return;
    }

    else if (incoming[0] == 'D'){
      Keyboard.press(incoming[1]);
    }
    else if (incoming[0] == 'U'){
      Keyboard.release(incoming[1]);
    }
  }
}