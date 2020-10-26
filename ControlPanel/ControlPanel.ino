
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
#define KEY_A 4
#define KEY_B 5
#define KEY_C 6
#define KEY_D 7
#define KEY_E 8
#define KEY_F 9
#define KEY_G 10
#define KEY_H 11
#define KEY_I 12
#define KEY_J 13
#define KEY_K 14
#define KEY_L 15
#define KEY_M 16
#define KEY_N 17
#define KEY_O 18
#define KEY_P 19
#define KEY_Q 20
#define KEY_R 21
#define KEY_S 22
#define KEY_T 23
#define KEY_U 24
#define KEY_V 25
#define KEY_W 26
#define KEY_X 27
#define KEY_Y 28
#define KEY_Z 29
#define KEY_ESC 41
#define KEY_SPACEBAR 44
#define KEY_1 30
#define KEY_F3 60
#define KEY_VOL_MUTE 127
#define KEY_VOL_DOWN 129
#define KEY_VOL_UP 128
#define KEY_PAUSE 126
#define KEY_POWER 0x66

// Define Input Pins for switches
#define SWITCH_GREEN 9
#define SWITCH_SILVER 2

// Define default signal states
int state = 1;
int funct = 1;

// Define Functions

// GENERIC MAC FUNCTIONS
funct_t lock = {.mod = KEY_LEFT_CMD + KEY_LEFT_CONTROL, .key=KEY_Q};
funct_t force_quit = {.mod = KEY_LEFT_CMD + KEY_LEFT_ALT, .key=KEY_ESC};
funct_t spotlight_siri = {.mod = KEY_LEFT_CMD, .key=KEY_SPACEBAR};


funct_t launch_chrome = {.mod = KEY_LEFT_SHIFT + KEY_LEFT_CONTROL + KEY_LEFT_ALT + KEY_LEFT_CMD, .key=KEY_A};
funct_t launch_terminal = {.mod = KEY_LEFT_CMD + KEY_LEFT_ALT, .key=KEY_T};
funct_t shut_down = {.mod = KEY_LEFT_CONTROL + KEY_LEFT_ALT + KEY_LEFT_CMD, .key=KEY_POWER};

// MICROSOFT TEAMS FUNCTIONS
// WINDOWS
funct_t teams_toggle_mute = {.mod = KEY_LEFT_CONTROL + KEY_LEFT_SHIFT, .key = KEY_M};
funct_t teams_toggle_video = {.mod = KEY_LEFT_CONTROL + KEY_LEFT_SHIFT, .key = KEY_O};
funct_t teams_sharing = {.mod = KEY_LEFT_CONTROL + KEY_LEFT_SHIFT, .key = KEY_SPACEBAR};
funct_t teams_toggle_blur = {.mod = KEY_LEFT_CONTROL + KEY_LEFT_SHIFT, .key = KEY_P};
funct_t teams_leave_meeting = { .mod = KEY_LEFT_CONTROL + KEY_LEFT_SHIFT, .key = KEY_B};



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
  buttons[0][0].functs[0] = lock;
  buttons[0][1].functs[0] = force_quit;
  buttons[0][2].functs[0] = spotlight_siri;
  buttons[1][0].functs[0] = launch_chrome;
  buttons[1][1].functs[0] = shut_down;
  buttons[1][2].functs[0] = launch_terminal;

  // Define FUNCT2 for buttons
  buttons[0][0].functs[1] = teams_sharing;
  buttons[0][1].functs[1] = teams_leave_meeting;
  buttons[0][2].functs[1] = {.mod=0, .key=12 };
  buttons[1][0].functs[1] = teams_toggle_mute;
  buttons[1][1].functs[1] = teams_toggle_video;
  buttons[1][2].functs[1] = teams_toggle_blur;


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
