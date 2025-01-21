#include <Mouse.h>
#include <Keyboard.h>

void setup() {
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  static bool active = false;

  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    data.trim();

    if (data == "arK?") {
      Serial.println("arK!");
      active = true;
    }
    if (data == "arK/") {
      active = false;
    }

    if (!active){
      return;
    }

    if (data.length() < 1) {
      return;
    }

    //K(S/N)(KEY)(D/U)
    //M
    switch(data[0]){
      case 'K':
        KeyboardHandler(data);
        break;
      case 'M':
        MouseHandler(data);
        break;
    }

  }
}

void KeyboardHandler(String data){
  if (data.length() < 4) {
    return;
  }

  uint8_t key;

  switch(data[1]){

    //special key
    case 'S':
      key = GetSpecialKey(data[2]);

      //sentinel value for no case found
      if (key == 0) {
        return;
      }

      break;

    case 'N':
      key = static_cast<uint8_t>(data[2]);

      break;
  }

  //normal key
  switch(data[3]){
    case 'D':
      Keyboard.press(key);
      break;
    case 'U':
      Keyboard.release(key);
      break;
  }
}

uint8_t GetSpecialKey(char index){
  //(T=Tab)
  switch(index){
    case 'T':
      return KEY_TAB;
      break;
    default:
      return 0;
  }
}

void MouseHandler(String data){
  switch(data[1]){

  }
}