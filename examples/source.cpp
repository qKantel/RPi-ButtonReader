
#include <iostream>
#include "button_interpreter.h"

int main() {
  PinReader pin_reader;
  ButtonInterpreter interpreter;

  pin_reader.ListenToPin(kPin0);
  pin_reader.ListenToPin(kPin2);
  pin_reader.ListenToPin(kPin3);

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
