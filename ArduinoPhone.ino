const int SENSE_COUNT = 3;
const int SENSE[SENSE_COUNT] = {A0, A1, A2};

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < SENSE_COUNT; i++) {
    pinMode(SENSE[i], INPUT);
  }

}

void loop() {
  int raw_val[3];
  String output = "";
  bool pressed = false;
  static bool was_pressed = false;
  static bool reported = true;
  static long press_start = 0;

  for (int i = 0; i < SENSE_COUNT; i++) {
    raw_val[i] = analogRead(SENSE[i]);
    output = "A" + String(i) + ": " + String(raw_val[i]) + "  ";

    if (raw_val[i] < 900) {
      if (!was_pressed) {
        press_start = millis();
        reported = false;
      }

      if (!reported && millis() - press_start > 60) {
//        Serial.print(output);
//        Serial.println("");

        char key = getKey(i, raw_val[i]);
        Serial.print(key);
//        Serial.println("");        

        reported = true;
      }
    }
  }

  pressed = false;
  for (int i = 0; i < SENSE_COUNT; i++) {
    if (raw_val[i] < 900) {
      pressed = true;
    }
  }

  was_pressed = pressed;
}


char getKey(int group, int val) {
  switch (group) {
    case 0:
      if (val > 780)
        return '1';
      else if (val > 690)
        return '*';
      else if (val > 500)
        return '7';
      else
        return '4';
      break;
    case 1:
      if (val > 720)
        return '2';
      else if (val > 620)
        return '0';
      else if (val > 500)
        return '8';
      else
        return '5';
      break;
    case 2:
      if (val > 720)
        return '3';
      else if (val > 620)
        return '#';
      else if (val > 500)
        return '9';
      else
        return '6';
      break;
  }
}
