#include "music_Song.h"

Song& Song::operator<<(const Note& n) {
  notes_.push_back(n);
  return *this;
}

const Note& Song::operator[](size_t i) const {
  if (notes_.empty()) { static Note dummy{0,4}; return dummy; }
  if (i >= notes_.size()) return notes_[0]; // fallback
  return notes_[i];
}

size_t Song::size() const {
  return notes_.size();
}
