/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone
*/

#include "pitches.h"
#define BoxRelais A5

const int BUTTON1 = A0;
const int BUTTON2 = A1;
const int BUTTON3 = A2;
const int BUTTON4 = A3;


// notes in the melody:
int melody_Button1[] = {
  NOTE_FS4, NOTE_FS4, NOTE_A4, NOTE_G4, NOTE_FS4,   NOTE_E4, NOTE_E4, NOTE_E4, 0,    NOTE_FS4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_B4, 0, NOTE_A4, 0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations_Button1[] = {
  4, 8, 8, 8, 8,   4, 8, 4, 8,     4, 8, 8, 8, 8, 4, 8, 4,8
};

int length_Melody_Button1 = 18;

int melody_Button2[] = {
  NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_FS4,     NOTE_FS4,   NOTE_E4, NOTE_D4, 0,    NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_FS4, NOTE_E4,0
};

int noteDurations_Button2[] = {
  4, 8, 4, 8,  4, 8, 4, 8,     4, 8, 8, 8, 8,    4, 8, 4, 8
};

int length_Melody_Button2 = 17;

int melody_Button3[] = {
  NOTE_FS4, NOTE_FS4, NOTE_A4, NOTE_G4, NOTE_FS4,   NOTE_FS4, 0, NOTE_E4, 0
};

int noteDurations_Button3[] = {
  4, 8, 8, 8, 8,    4,8,4, 8
};

int length_Melody_Button3 = 9;

int melody_Button4[] = {
  NOTE_FS4, NOTE_A4, NOTE_B4, NOTE_B4,     NOTE_A4,   NOTE_B4, NOTE_CS5, NOTE_D5, 0, NOTE_D5, NOTE_B4, NOTE_A4, NOTE_FS4, NOTE_E4, 0, NOTE_FS4, NOTE_E4, NOTE_D4
};

int noteDurations_Button4[] = {
  4, 8, 4, 8,  8, 8, 8, 4,8,     4, 8, 4, 8,    8, 16, 16, 8, 4
};
int length_Melody_Button4 = 18;

bool inMelody = false;
bool rightMelody = false;
int beforePlayed = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);  
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);
  pinMode(BoxRelais, OUTPUT);
  digitalWrite(BoxRelais, HIGH);
}

void loop() {
  Serial.println(digitalRead(BUTTON1));
  if(digitalRead(BUTTON1)==LOW){
    Serial.println("Button1");
    playMelodie(melody_Button1, noteDurations_Button1, length_Melody_Button1);
    rightMelody = true;
    beforePlayed = 1;
  }
  if(digitalRead(BUTTON2)==LOW){
    Serial.println("Button2");
    playMelodie(melody_Button2, noteDurations_Button2, length_Melody_Button2);
    if (rightMelody == true && beforePlayed == 1) {
      Serial.println("NOICE");  
    }
    else {rightMelody = false;}
    beforePlayed = 2;
  }
  if(digitalRead(BUTTON3)==LOW){
    Serial.println("Button3");
    playMelodie(melody_Button3, noteDurations_Button3, length_Melody_Button3);
    if (rightMelody == true && beforePlayed == 2) {
      Serial.println("GOOD WAY");
    }
    else {rightMelody = false;}
    beforePlayed = 3;
  }
  if(digitalRead(BUTTON4)==LOW){
    Serial.println("Button4");
    playMelodie(melody_Button4, noteDurations_Button4, length_Melody_Button4);
    if (rightMelody == true && beforePlayed == 3) {
      Serial.println("NOICE DU HAST GEWONNEN!!!!!!");
      OpenBox();
    }
    else {rightMelody = false;}
    beforePlayed = 4;
  }
  
  
  // no need to repeat the melody.
}


//Funktion Ton abspielen (int array Melodie, int array tonlänegen, int töne)
//Funktion wie im Setup
void playMelodie(int Notes[], int Duration[], int length_Melody) {
  while (inMelody == true) {}
  inMelody = true;
  for (int thisNote = 0; thisNote < length_Melody; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 2000 / Duration[thisNote];
    tone(8, Notes[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
  inMelody = false;
}

void OpenBox() {
  digitalWrite(BoxRelais, LOW);
  delay(5000);
  digitalWrite(BoxRelais, HIGH);
}
