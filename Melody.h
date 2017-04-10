// Melody.h

struct Melody {
  int* notes;
  int* noteDurations;

  using size_t = unsigned long;
  size_t length;

  Melody(int* _notes, int* _noteDurations);
};