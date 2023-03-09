#include <Keypad.h>//https://github.com/Chris--A/Keypad
#include <MIDI.h>
#include <USB-MIDI.h>
#define ROWS 3
#define COLS 6

USBMIDI_CREATE_DEFAULT_INSTANCE();
int i;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// probleme avec les drums: lors d'un apuis sur l'un des pads, le signal se repercute sur l'autres; j'essaerrai de filtrer le signal avec un filtre passe bas/////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////
//        drums            //
/////////////////////////////

/*
int analogPin = A0; //  connected to analog pin 0                 // outside leads to ground and +5V
int splashval = 0;  // variable to store the value read
int maxsplash = 0;
unsigned long splashtimer = 0;

int analogPin1 = A1; //  connected to analog pin 0                 // outside leads to ground and +5V
int kickval = 0;  // variable to store the value read
int maxkick = 0;
unsigned long kicktimer = 0;
//avec le clavier a diode, l'ordre des colones// lignes a son importance donc mon clavier sera constituer de 3 lignes sur 2 3 4 et le reste en colones
*/
static char selectedMode;


char footkeymatrix [ROWS][COLS]  = {   
  {'0', '1', '2', '3', '4', '5'}, 
  {'6', '7', '8', '9', 'A', 'B'},
  {'C', 'D', 'E', 'F', 'G', 'H'}
};

byte rowfootkey [3] = {2, 3, 4}; //atribution des pins
byte colfootkey [6] = {5, 6, 7, 8, 9, 10};


Keypad footkey = Keypad( makeKeymap(footkeymatrix), rowfootkey, colfootkey, ROWS, COLS);

bool status0 = false;
bool status1 = false;
bool status2 = false;
bool status3 = false;
bool status4 = false;
bool status5 = false;
bool status6 = false;
bool status7 = false;
bool status8 = false;
bool status9 = false;
bool status10 = false;
bool status11 = false;
bool status12 = false;
bool status13 = false;

void handleModeSelection() {
  char pressed=footkey.getKey();
  
  if (pressed) {
    selectedMode = pressed;

 }
}


void setup()
{
 Serial.begin(9600);
  //Serial.begin(31250);
  // while (!Serial); //demarrer le port serie pour demarer l'arduino

  for(int i=0;i<4;i++){               //defining the output and input pins
    pinMode(pinCols[i], OUTPUT);
    pinMode(pinRows[i],  INPUT);
    digitalWrite(pinCols[i], HIGH);

  MIDI.begin();

}



void loop() {


  
}
  // put your main code here, to run repeatedly:
 // char key = footkey.getKey();
  //bool kstatus = footkey.key[0].kstate;

 /// if (key){
    //Serial.print(key);


 // }
 // delay(12);
   //   Serial.print(footkey.kstate);
  //    Serial.println(footkey.stateChanged);
