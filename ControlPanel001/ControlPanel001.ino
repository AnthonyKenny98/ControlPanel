
// Keyboard buffer bit rate
uint8_t buf[8] = {0};

// Number of functions per button
#define NUM_FUNCTS 2

// Function for a button
typedef struct funct_t {
  uint8_t mod;
  uint8_t key;
} funct_t;

// Button has a pin on the board and a number of functions
typedef struct button_t {
  int pin;
  funct_t functs[NUM_FUNCTS]; 
} button_t;

// Define a keyrelease function, all zeroes for buffer
funct_t keyrelease = {
  .mod = 0,
  .key = 0
};

// Rows and Columns of buttons
#define BUTTON_ROWS 2
#define BUTTON_COLS 3

// Define the array of buttons
button_t buttons[BUTTON_ROWS][BUTTON_COLS] = {{
  {
    .pin = 0,
    .functs = {keyrelease}
  }
}};

// Define Modifier Keys
#define KEY_LEFT_CONTROL 1
#define KEY_LEFT_SHIFT 2
#define KEY_LEFT_ALT 4
#define KEY_LEFT_CMD 8
#define KEY_RIGHT_CONTROL 1
#define KEY_RIGHT_SHIFT 2
#define KEY_RIGHT_ALT 4
#define KEY_RIGHT_CMD 8

// Define Regular Keys
#define KEY_VOL_MUTE 127
#define KEY_VOL_DOWN 129
#define KEY_VOL_UP 128
#define KEY_PAUSE 126

// Define Input Pins for switches
#define SWITCH_GREEN 9
#define SWITCH_SILVER 2

// Define default signal states
int state = 1;
int funct = 1;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  // Define Pins for Buttons
  buttons[0][0].pin = 8;
  buttons[0][1].pin = 6;
  buttons[0][2].pin = 4;
  buttons[1][0].pin = 7;
  buttons[1][1].pin = 5;
  buttons[1][2].pin = 3;

  // Define FUNCT1 for buttons
  buttons[0][0].functs[0] = {.mod=0, .key=4 };
  buttons[0][1].functs[0] = {.mod=0, .key=5 };
  buttons[0][2].functs[0] = {.mod=0, .key=6 };
  buttons[1][0].functs[0] = {.mod=0, .key=7 };
  buttons[1][1].functs[0] = {.mod=0, .key=8 };
  buttons[1][2].functs[0] = {.mod=0, .key=9 };

  // Define FUNCT2 for buttons
  buttons[0][0].functs[1] = {.mod=0, .key=10 };
  buttons[0][1].functs[1] = {.mod=0, .key=11 };
  buttons[0][2].functs[1] = {.mod=0, .key=12 };
  buttons[1][0].functs[1] = {.mod=0, .key=13 };
  buttons[1][1].functs[1] = {.mod=0, .key=14 };
  buttons[1][2].functs[1] = {.mod=0, .key=15 };


  // Set Pin Modes
  pinMode(SWITCH_GREEN, INPUT);
  pinMode(SWITCH_SILVER, INPUT);
  pinMode(buttons[0][0].pin, INPUT);
  pinMode(buttons[0][1].pin, INPUT);
  pinMode(buttons[0][2].pin, INPUT);
  pinMode(buttons[1][0].pin, INPUT);
  pinMode(buttons[1][1].pin, INPUT);
  pinMode(buttons[1][2].pin, INPUT);
  

  // Set input pins to pullup
  digitalWrite(SWITCH_GREEN, INPUT_PULLUP);
  digitalWrite(SWITCH_SILVER, INPUT_PULLUP);
  digitalWrite(buttons[0][0].pin, INPUT_PULLUP);
  digitalWrite(buttons[0][1].pin, INPUT_PULLUP);
  digitalWrite(buttons[0][2].pin, INPUT_PULLUP);
  digitalWrite(buttons[1][0].pin, INPUT_PULLUP);
  digitalWrite(buttons[1][1].pin, INPUT_PULLUP);
  digitalWrite(buttons[1][2].pin, INPUT_PULLUP);

  delay(200);

}

void loop() {

  if (!digitalRead(SWITCH_GREEN)) {

    int8_t modifier, key;
  
    funct = digitalRead(SWITCH_SILVER);
      
    for (int row=0; row<BUTTON_ROWS; row++){
      for (int col=0; col<BUTTON_COLS; col++) {
        state = digitalRead(buttons[row][col].pin);
        if (!state) {
          if (funct) {
            pressKeySequence(buttons[row][col].functs[0]);
          } else { 
            pressKeySequence(buttons[row][col].functs[1]);
          }
          releaseKey();
        }
      }
    }
  }
}

void pressKeySequence(funct_t funct) {
  buf[0] = funct.mod;
  buf[2] = funct.key;
  Serial.write(buf, 8); 
}

void releaseKey() {
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Release key  
  delay(200);
}
