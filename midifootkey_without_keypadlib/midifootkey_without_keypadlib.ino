#include <MIDI.h>
#include <USB-MIDI.h>
#define ROWS 3
#define COLS 6

USBMIDI_CREATE_DEFAULT_INSTANCE();
//int i;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// probleme avec les drums: lors d'un apuis sur l'un des pads, le signal se repercute sur l'autres; j'essaerrai de filtrer le signal avec un filtre passe bas/////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////
//        drums            //
/////////////////////////////


int analogPin = A0; //  connected to analog pin 0                 // outside leads to ground and +5V
int splashval = 0;  // variable to store the value read
int maxsplash = 0;
unsigned long splashtimer = 0;

int analogPin1 = A1; //  connected to analog pin 0                 // outside leads to ground and +5V
int kickval = 0;  // variable to store the value read
int maxkick = 0;
unsigned long kicktimer = 0;


//avec le clavier a diode, l'ordre des colones// lignes a son importance donc mon clavier sera constituer de 3 lignes sur 2 3 4 et le reste en colones


int footkeymatrix [ROWS][COLS]  = {   
  {24, 25, 26, 27, 28, 29 }, 
  {30, 31, 32, 33, 34, 35},
  {36, 37, 38, 39, 40, 41}
};

byte rowfootkey [3] = {2, 3, 4}; //atribution des pins
byte colfootkey [6] = {5, 6, 7, 8, 9, 10};

bool statusmatrix [ROWS][COLS]  = {   
  {false, false, false, false, false, false}, 
  {false, false, false, false, false, false},
  {false, false, false, false, false, false}
};


void setup()
{
// Serial.begin(9600);
  Serial.begin(31250);
  MIDI.begin();
  
    pinMode(colfootkey[0], OUTPUT);
    pinMode(colfootkey[1], OUTPUT);
    pinMode(colfootkey[2], OUTPUT);
    pinMode(colfootkey[3], OUTPUT);
    pinMode(colfootkey[4], OUTPUT);
    pinMode(colfootkey[5], OUTPUT);
    
    pinMode(rowfootkey[0],  INPUT_PULLUP);
    pinMode(rowfootkey[1],  INPUT_PULLUP);
    pinMode(rowfootkey[2],  INPUT_PULLUP);
    
    digitalWrite(colfootkey[0], HIGH);
    digitalWrite(colfootkey[1], HIGH);
    digitalWrite(colfootkey[2], HIGH);
    digitalWrite(colfootkey[3], HIGH);
    digitalWrite(colfootkey[4], HIGH);
    digitalWrite(colfootkey[5], HIGH);

  MIDI.begin();

}



void loop() {

  splashval = map(analogRead(analogPin), 0, 1023, 60, 127);
  if(splashval > 69)
  {
    if(maxsplash < splashval)
    {
      splashtimer = millis();
      maxsplash = splashval;
    }
    
        if(millis() > 27+splashtimer)
    {
 //     Serial.println("noteon");
 //     Serial.println(maxsplash);
 //     Serial.println("noteoff");
      MIDI.sendNoteOn(38, maxsplash, 10);
   //   MIDI.sendNoteOff(38, 0, 10);
      
      maxsplash = 0;
    }
  }

  kickval = map(analogRead(analogPin1), 0, 1023, 60, 127);
  if(kickval > 69)
  {
    if(maxkick < kickval)
    {
      kicktimer = millis();
      maxkick = kickval;
    }
    
        if(millis() > 27+kicktimer)
    {
 //     Serial.println("noteon");
 //     Serial.println(maxsplash);
 //     Serial.println("noteoff");
      MIDI.sendNoteOn(37, maxkick, 10);
  //    MIDI.sendNoteOff(37, 0, 10);
      
      maxkick = 0;
    }
  }

  
  for(int col = 0; col < 6; col++){
    digitalWrite(colfootkey[col], LOW);
    
    for(int row = 0; row < 3; row++){
      if(digitalRead(rowfootkey[row])==LOW and statusmatrix[row][col] == false){
            MIDI.sendNoteOn(footkeymatrix[row][col], 80, 4);
            statusmatrix[row][col] = true;
            //Serial.print(" noteon  ");
            //Serial.println(footkeymatrix[row][col]);
          
      }
      if(digitalRead(rowfootkey[row])== HIGH and statusmatrix[row][col] == true){
            MIDI.sendNoteOff(footkeymatrix[row][col], 0, 4);
            statusmatrix[row][col] = false;
           
            //Serial.print(" noteoff  ");
            //Serial.println(footkeymatrix[row][col]);
          
      }
    }

    digitalWrite(colfootkey[col], HIGH);

  }

/*  
    digitalWrite(colfootkey[0], LOW);
    digitalWrite(colfootkey[1], LOW);
    digitalWrite(colfootkey[2], LOW);
    digitalWrite(colfootkey[3], LOW);
    digitalWrite(colfootkey[4], LOW);
    digitalWrite(colfootkey[5], LOW);
    delay(500);

    Serial.println("low");
    Serial.println(digitalRead(rowfootkey[0]));
    Serial.println(digitalRead(rowfootkey[1]));
    Serial.println(digitalRead(rowfootkey[2]));



    digitalWrite(colfootkey[0], HIGH);
    digitalWrite(colfootkey[1], HIGH);
    digitalWrite(colfootkey[2], HIGH);
    digitalWrite(colfootkey[3], HIGH);
    digitalWrite(colfootkey[4], HIGH);
    digitalWrite(colfootkey[5], HIGH);
    delay(500);
    Serial.println("high");
    Serial.println(digitalRead(rowfootkey[0]));
    Serial.println(digitalRead(rowfootkey[1]));
    Serial.println(digitalRead(rowfootkey[2]));

*/


}
 
