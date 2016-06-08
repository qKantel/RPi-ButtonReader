/**
 * @file    source.cpp 
 * @author  Matthew Robinson
 *
 * Can compile with:
 * g++ -std=c++14 source.cpp -o test -l bcm2835
 */
 
#include <iostream>
#include "button_interpreter.h"

int main() {
  PinReader pin_reader;
  ButtonInterpreter interpreter;

  pin_reader.ListenToPin(kPi2Pin11);
  pin_reader.ListenToPin(kPi2Pin13);
  pin_reader.ListenToPin(kPi2Pin15);

  interpreter.AttachReader(&pin_reader);
  interpreter.SetAlpha(0.01);

  while (true) {
    Pins pin = interpreter.GetButtonPressed();
    if (pin != kPinUnknown) {
      std::cout << static_cast<int>(pin) << std::endl;
    }
  }
  return 0;
}
