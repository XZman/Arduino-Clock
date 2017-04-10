// Melody.cpp

#include "Melody.h"

Melody::Melody(int* _notes, int* _noteDurations) {
  notes = _notes;
  noteDurations = _noteDurations;
  length = sizeof(notes) / sizeof(int);
}
