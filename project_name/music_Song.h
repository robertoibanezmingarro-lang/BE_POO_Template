#ifndef SONG_H
#define SONG_H

#include <Arduino.h>
#include <vector>

struct Note {
  int freq;
  int div; // 4=noire, 8=croche...
};

class Song {
public:
  Song& operator<<(const Note& n);
  const Note& operator[](size_t i) const;
  size_t size() const;

private:
  std::vector<Note> notes_;
};

#endif