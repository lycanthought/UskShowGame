#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip

DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
SoftwareSerial mySoftwareSerial(4,5); // RX, TX

#define DEBOUNCE 100  // button debouncer  

 //set up keyboard  
  const byte ROWS = 4; // Four rows
  const byte COLS = 4; //  columns
  // Define the Keymap
  char keys[ROWS][COLS] = {
   {'1','2','3','A'},
   {'4','5','6','B'}, //
   {'7','8','9','C'}, //
   {'*','0','#','D'} // 
  };
  byte rowPins[ROWS] = { 9,8,7,6 };//Connect keypad rows to these Arduino pins.
  byte colPins[COLS] = { 13,12,11,10 };// Connect keypad columns to these Arduino pins.

// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const int secretCodeOne[6]   = {'7', '5', '5', '8', '4', '4'};
int secretCodeTwo[6]   = {'1', '3', '0', '3', '4', '9'};
int secretCodeThree[6] = {'1', '2', '7', '3', '3', '4'};
int secretCodeFour[6]  = {'1', '3', '0', '3', '4', '1'};
int secretCodeFive[6]  = {'1', '2', '3', '3', '5', '5'};
int secretCodeSix[6]   = {'1', '2', '6', '3', '3', '3'};
int secretCodeSeven[6]  = {'1', '2', '1', '3', '5', '0'};

int enteredCode[6] = {0, 0, 0, 0, 0, 0};
int correctKeys = 0;
int success = 0;
byte pressed;        //stores values of button pressed
int keysPressed = 0;           //loop iteration
int currentCode = 1; // code we are currently solving
uint32_t codeTimeout = 0; // timer
const uint32_t timeoutTime = 5000;


//<------------------------------------------------------------------------------ Void Setup
void setup() {
//putstring(".");    // uncomment this to see if the loop isnt running


mySoftwareSerial.begin(9600);
Serial.begin(9600);
Serial.println("starting");
delay(5000);
myDFPlayer.begin(mySoftwareSerial);
  //----Set volume----
myDFPlayer.volume(25);  //Set volume value (0~30).
myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
myDFPlayer.play(8);  //Play the wrong answer MP3
delay(1000);
}
  

//<------------------------------------------------------------------------------------- Void Loop

void loop() {

    if( (millis() - codeTimeout ) > timeoutTime )
    {
     // clear current entries and reset timer
     keysPressed = 0;
     codeTimeout = millis();
    }
    pressed = keypad.getKey();
    if( pressed )
    {
      if( pressed == '#')
      {
        currentCode = 1;
        keysPressed = 0;
      }
      else if( (pressed == '*') && currentCode > 1)
      {
        myDFPlayer.play(currentCode);  //Play the numbered mp3
      }
      else if( (pressed >= 0x30) && (pressed <= 0x39) ) // check it is a number - ascii 0x30 = '0'
      {
        codeTimeout = millis();  // reset timer when button is pressed
        Serial.println( pressed );
        enteredCode[keysPressed] = pressed;
        keysPressed++;
        if (keysPressed == 6)
        {
          keysPressed = 0;
          switch( currentCode )
          {
            case 1:
            for (int i=0;i<6;i++)                   //Check Code One
            {
              if (enteredCode[i] == secretCodeOne[i])
              {
                correctKeys = correctKeys +1;   //counts number of correct keys
              }
            }
            if (correctKeys == 6)               //if the entered code matches code one, play track one
            { 
              Serial.println("Code One Correct");
              myDFPlayer.play(1);  //Play the numbered mp3
              delay(1000);
              currentCode++;
            }
            else
            {
              playError();
            }
            correctKeys = 0;                     //reset correct key counter
            break;
  
            case 2:
            for (int i=0;i<6;i++)                   //Check Code two
            {
              if (enteredCode[i] == secretCodeTwo[i])
              {
                correctKeys = correctKeys +1;   //counts number of correct keys
              }
            }
            if (correctKeys == 6)               //if the entered code matches code one, play track two
            { 
              Serial.println("Code Two Correct");
              myDFPlayer.play(2);  //Play the numbered mp3
              delay(1000);
              currentCode++;
            }
            else
            {
              playError();
            }
            correctKeys = 0;                     //reset correct key counter
            break;
            
            case 3:
            for (int i=0;i<6;i++)                   //Check Code three
            {
              if (enteredCode[i] == secretCodeThree[i])
              {
                correctKeys = correctKeys +1;   //counts number of correct keys
              }
            }
            if (correctKeys == 6)               //if the entered code matches code one, play track three
            { 
              Serial.println("Code Three Correct");
              myDFPlayer.play(3);  //Play the numbered mp3
              delay(1000);
              currentCode++;
            }
            else
            {
              playError();
            }
            correctKeys = 0;                     //reset correct key counter
            break;
  
            case 4:
            for (int i=0;i<6;i++)                   //Check Code four
            {
              if (enteredCode[i] == secretCodeFour[i])
              {
                correctKeys = correctKeys +1;   //counts number of correct keys
              }
            }
            if (correctKeys == 6)               //if the entered code matches code one, play track four
            { 
              Serial.println("Code Four Correct");
              myDFPlayer.play(4);  //Play the numbered mp3
              delay(1000);
              currentCode++;
            }
            else
            {
              playError();
            }
            correctKeys = 0;                     //reset correct key counter
            break;
  
            case 5:
            for (int i=0;i<6;i++)                   //Check Code five
            {
              if (enteredCode[i] == secretCodeFive[i])
              {
                correctKeys = correctKeys +1;   //counts number of correct keys
              }
            }
            if (correctKeys == 6)               //if the entered code matches code one, play track five
            { 
              Serial.println("Code Five Correct");
              myDFPlayer.play(5);  //Play the numbered mp3
              delay(1000);
              currentCode++;
            }
            else
            {
              playError();
            }
            correctKeys = 0;                     //reset correct key counter
            break;
  
            case 6:
            for (int i=0;i<6;i++)                   //Check Code six
            {
              if (enteredCode[i] == secretCodeSix[i])
              {
                correctKeys = correctKeys +1;   //counts number of correct keys
              }
            }
            if (correctKeys == 6)               //if the entered code matches code one, play track six
            { 
              Serial.println("Code Six Correct");
              myDFPlayer.play(6);  //Play the numbered mp3
              delay(1000);
              currentCode++;
            }
            else
            {
              playError();
            }
            correctKeys = 0;                     //reset correct key counter
            break;
            
            case 7:
            for (int i=0;i<6;i++)                   //Check Code six
            {
              if (enteredCode[i] == secretCodeSeven[i])
              {
                correctKeys = correctKeys +1;   //counts number of correct keys
              }
            }
            if (correctKeys == 6)               //if the entered code matches code one, play track seven
            { 
              Serial.println("Code Seven Correct");
              myDFPlayer.play(7);  //Play the numbered mp3
              delay(1000);
              currentCode++;
            }
            else
            {
              playError();
            }
            correctKeys = 0;                     //reset correct key counter
            break;
          }
        }
      }
    }
}

void playError()
{
  myDFPlayer.play(8);                          //if the entered code matches codeis wrong, play track seven
  delay(1000);
  Serial.println("You Fail");
}
