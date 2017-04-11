// Melody.h
#define MELODY_H

struct Melody {
  int* notes;
  int* noteDurations;

  using size_t = unsigned long;
  size_t length;

  Melody(int* _notes, int* _noteDurations);
};