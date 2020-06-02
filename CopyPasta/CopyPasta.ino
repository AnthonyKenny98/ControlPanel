
// Keyboard buffer bit rate
uint8_t buf[8] = {0}; 

int state = 1;

// Define Keys
#define KEY_C 6
#define KEY_X 27
#define KEY_V 25
#define KEY_LEFT_CMD 0x08
#define KEY_LEFT_SHIFT 0x02

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
  
  state = digitalRead(PIN_0);
  if (!state) {
      buf[0] = KEY_LEFT_CMD;
      buf[2] = KEY_C; 
      Serial.write(buf, 8);
      releaseKey(); 
  }

  state = digitalRead(PIN_1);
  if (!state) {
    buf[0] = KEY_LEFT_CMD;
    buf[2] = KEY_X;
    Serial.write(buf, 8);
    releaseKey();
  }

  state = digitalRead(PIN_2);
  if (!state) {
    buf[0] = KEY_LEFT_CMD;
    buf[2] = KEY_V;  
    Serial.write(buf, 8);
    releaseKey();
  }

//  Test CMD + SHIFT + C
  state = digitalRead(PIN_3);
  if (!state) {
      buf[0] = KEY_LEFT_CMD + KEY_LEFT_SHIFT;
      buf[2] = KEY_C; 
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
