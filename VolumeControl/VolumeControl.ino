
// Keyboard buffer bit rate
uint8_t buf[8] = {0}; 

int state = 1;

// Define Keys
#define KEY_VOL_MUTE 127
#define KEY_VOL_DOWN 129
#define KEY_VOL_UP 128
#define KEY_PAUSE 126

// Define Pins
#define PIN_0 2
#define PIN_1 3
#define PIN_2 4
#define PIN_3 5

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  // Pin Modes
  pinMode(PIN_0, INPUT);
  pinMode(PIN_1, INPUT);
  pinMode(PIN_2, INPUT);
  pinMode(PIN_3, INPUT);

  // Input pull-ups
  digitalWrite(PIN_0, INPUT_PULLUP);
  digitalWrite(PIN_1, INPUT_PULLUP);
  digitalWrite(PIN_2, INPUT_PULLUP);
  digitalWrite(PIN_3, INPUT_PULLUP);

  delay(200);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // Pin 0 - Mute
  state = digitalRead(PIN_0);
  if (!state) {
    if(!digitalRead(PIN_3)) {
      buf[2] = KEY_VOL_UP;
    } else { 
      buf[2] = KEY_VOL_MUTE; 
    }
    Serial.write(buf, 8);
    releaseKey();
  }

  state = digitalRead(PIN_1);
  if (!state) {
    buf[2] = KEY_VOL_DOWN;
    Serial.write(buf, 8);
    releaseKey();
  }

  state = digitalRead(PIN_2);
  if (!state) {
    buf[2] = KEY_VOL_UP;  
    Serial.write(buf, 8);
    releaseKey();
  }

  state = digitalRead(PIN_3);
  if(!state) {
    buf[2] = KEY_PAUSE;
    Serial.write(buf, 8);
    releaseKey();
  }

}

void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Release key  
  delay(200);
}
