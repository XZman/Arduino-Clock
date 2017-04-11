// Melody.cpp

#include "Melody.h"

Melody::Melody(unsigned len, int* _notes, int* _noteDurations) {
  notes = _notes;
  noteDurations = _noteDurations;
  length = len;
}
