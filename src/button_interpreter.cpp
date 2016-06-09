/**
 * @file    button_interpreter.cpp
 * @author  Matthew Robinson
 * @status  Complete
 *          Testing required for new refactoring
 */

#include "button_interpreter.h"

ButtonInterpreter::ButtonInterpreter() :
  reader_(nullptr),
  unhandled_reader_change_(false),
  alpha_(0.5) {}
  // end constructor
  
ButtonInterpreter::ButtonInterpreter(PinReader * pin_reader) :
  reader_(pin_reader),
  unhandled_reader_change_(true),
  alpha_(0.5) {}

void ButtonInterpreter::AttachReader(PinReader * pin_reader) {
  reader_ = pin_reader;
  unhandled_reader_change_ = true;
}  // end AttachReader

Pins ButtonInterpreter::GetButtonPressed() {
  if (unhandled_reader_change_) {
    unhandled_reader_change_ = false;
    UpdateStoredPins();
  }

  UpdateAccumulators();

  return GetActivatedButton();
}  // end GetButtonReleased

/// Private Functions

void ButtonInterpreter::UpdateAccumulators() {
  std::vector<Pins> new_pins = reader_->GetUpdates();

  for (size_t i = 0; i < pin_accumulators_.size(); ++i) {
    // Check if any buttons are currently being pressed
    std::vector<Pins>::const_iterator it =
      std::find(new_pins.begin(), new_pins.end(), pin_accumulators_[i].pin);

    int new_val = 0;
    if (it != new_pins.end()) {
      new_val = 1;
    }

    // Update their accumulators accordingly
    double new_a = pin_accumulators_[i].accumulator;
    new_a = (alpha_ * new_val) + (1.0 - alpha_) * new_a;
    if (new_a < 0.00001) {  // Fix to not let the decimal travel forever.
      pin_accumulators_[i].accumulator = 0.0;
    } else if (new_a > 0.99999) {
      pin_accumulators_[i].accumulator = 1.0;
    } else {
      pin_accumulators_[i].accumulator = new_a;
    }
  }
}  // end UpdateAccumulators

Pins ButtonInterpreter::GetActivatedButton() {
  Pins pressed = Pins::kPinUnknown;

  for (size_t i = 0; i < pin_accumulators_.size(); ++i) {
    std::list<Pins>::iterator activated_it =
      std::find(activated_buttons_.begin(), activated_buttons_.end(), pin_accumulators_[i].pin);

    if (pin_accumulators_[i].accumulator == 1.0) {  // If pressed
      if (activated_it == activated_buttons_.end()) {  // and wasn't pressed before
        activated_buttons_.push_front(pin_accumulators_[i].pin);
        pressed = pin_accumulators_[i].pin;  // Newly pushed button
      }
      // if it was pressed before, do nothing.
    }
    else if(pin_accumulators_[i].accumulator == 0.0){
      if (activated_it != activated_buttons_.end()) {
        activated_buttons_.erase(activated_it);
      }
    }
  }

  return pressed;
}  // end GetActivatedButton

void ButtonInterpreter::UpdateStoredPins() {
  std::vector<Pins> reader_pins = reader_->GetPins();
  pin_accumulators_.clear();

  for (size_t i = 0; i < reader_pins.size(); ++i) {
    pin_accumulators_.push_back({reader_pins[i], 0});
  }
}  // end UpdateStoredPins
