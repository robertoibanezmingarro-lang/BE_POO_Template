#ifndef ACTUATOR_H
#define ACTUATOR_H

class Actuator {
public:
  virtual ~Actuator() = default;
  virtual void begin() = 0;
};

#endif
