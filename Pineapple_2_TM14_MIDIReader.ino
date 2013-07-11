#define BUFF_SIZE 128

#define LED 13

#define RELAY1 4
#define RELAY2 7
#define RELAY3 8
#define RELAY4 12

#define NOTE_A3 57
#define NOTE_B3 59
#define NOTE_C4 60
#define NOTE_D4 62

void blink() {
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
}

void relay(int r) {
  digitalWrite(r, HIGH);
  // delay(200);
  blink();
  digitalWrite(r, LOW);
}

void setup() {
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  pinMode(13, OUTPUT);
  Serial1.begin(31250);
  Serial.begin(9600);
}

void loop() {
  char buffer[BUFF_SIZE];
  int count = 0;
  while (Serial1.available() > 0 && count < BUFF_SIZE) {
    char buff = 0;
    Serial1.readBytes(&buff, 1);
    buffer[count] = buff & 0xFF;
    ++count;
    delay(1);
  }
  if (count > 0) {
    int i;
    for (i = 0; i < count; ++i) {
      int buff0 = buffer[i] & 0xFF;
      Serial.print(buff0, HEX);
      Serial.print(' ');
      if (buff0 == 0x90) {
        if (i < count - 1) {
          int buff1 = buffer[i + 1] & 0xFF;
          switch (buff1) {
            case NOTE_A3:
              relay(RELAY1);
              break;
            case NOTE_B3:
              relay(RELAY2);
              break;
            case NOTE_C4:
              relay(RELAY3);
              break;
            case NOTE_D4:
              relay(RELAY4);
              break;
            default:
              break;
          }
        }
      }
    }
    Serial.print('\n');
  }
  delay(100);
}
