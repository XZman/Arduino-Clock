// little_star.h
#define BIRTHDAY_SONG_H

#ifndef PITCHES_H
#include "pitches.h"
#endif

const Melody birthday_song = {
  29,
  new int[29] {
    NOTE_G4,//5
    NOTE_G4,//5
    NOTE_A4,//6
    NOTE_G4,//5
    NOTE_C5,//1.
    NOTE_B4,//7
    0,
    NOTE_G4,//5
    NOTE_G4,//5
    NOTE_A4,//6
    NOTE_G4,//5
    NOTE_D5,//2.
    NOTE_C5,//1.
    0,
    NOTE_G4,//5
    NOTE_G4,//5
    NOTE_G5,//5.
    NOTE_E5,//3.
    NOTE_C5,//1.
    NOTE_B4,//7
    NOTE_A4,//6
    0,
    NOTE_F5,//4.
    NOTE_F5,//4.
    NOTE_E5,//3.
    NOTE_C5,//1.
    NOTE_D5,//2.
    NOTE_C5,//1.
    0
  },
  new int[29] {
    8, 8, 4, 4, 4, 4,
    4,
    8, 8, 4, 4, 4, 4,
    4,
    8, 8, 4, 4, 4, 4, 2,
    8,
    8, 8, 4, 4, 4, 2,
    4
  }
};
