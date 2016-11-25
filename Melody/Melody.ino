//You enter how long you want your melody to be. Then the Arduino plays a random melody of that size.
//ARDUINO PROGRAM--MELODY IMPROVED

// include our list of note pitches
#include "pitches.h"

// the pin the speaker is attached to
int speakerPin = 8;

// the notes in our melody and their duration in fractions of a second
// e.g. quarter note = 4, eighth note = 8, etc.

char notes[11]={'NOTE_A3', 'NOTE_B3', 'NOTE_C4', 'NOTE_D2', 'NOTE_E2', 'NOTE_F2', 'NOTE_G2', 'NOTE_G3', 'NOTE_BLANK',
'NOTE_C1', 'NOTE_GS3'};
int note_time[4]={1, 2, 3, 4};
void setup()
{
    Serial.begin(9600);
    Serial.println("Ready to play? Good! Enter: S for short, M for medium, L for long, or V for very long:");
}

void loop()
{
    static int time_btw, num_note;
    if (Serial.available() > 0)
    {
        char letter = Serial.read();
        switch (letter)
        {
            case 's':
                num_note = 10;
                break;
            case 'm':
                num_note = 15;
                break;
            case 'l':
                num_note = 25;
                break;
            case 'v':
                num_note = 40;
                break;
        }
        static int this_note, note_ind, this_lengh, lengh_ind;
        int music_array[num_note][2]; //num_note rows and 2 columns
        for(int x = 0; x < num_note; x++)
        {
            note_ind = rand() % 11; // pick random number 0-4
            lengh_ind = rand() % 4; 
            this_note = notes[note_ind];
            this_lengh = note_time[lengh_ind];
            music_array[x][0] = this_note; //add the note 2 array
            music_array[x][1] = this_lengh; //add the lengh (whole, half, quarter, eighth)
        }
        for(int z = 0; z < 2; z++)
        {
            for(int k = 0; k < num_note; k++)
            {
                int thisNote = music_array[k][0];
                int thisNotetime = music_array[k][1];
                
                int noteDurationMS = 1000/thisNotetime;
                
                tone(speakerPin, thisNote, noteDurationMS);
                delay(noteDurationMS * 1.30);
            }
        }
    }
    else //if nothing was typed in
    {
        //do nothing
    }    
}