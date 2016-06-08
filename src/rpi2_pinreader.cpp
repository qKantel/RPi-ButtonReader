/**
 * @file    rpi2_pinreader.cpp
 * @author  Matthew Robinson
 * @status  Complete
 */

#include "rpi2_pinreader.h"

int PinReader::instances_ = 0;

PinReader::PinReader(bool debug) {
  if (instances_ == 0) {
    if(debug)
      bcm2835_set_debug(1);
    
    if (!bcm2835_init()) {
      exit(EXIT_FAILURE);
    } 
  }
  
  instances_++;
}  // end constructor

PinReader::~PinReader() {
  if (instances_ == 1) {
    bcm2835_close();
  }
  
  instances_--;
}  // end destructor

void PinReader::ListenToPin(Pins pin, PUDValues pud) {
  // Pullup will give readtype of 0, pulldown gives readtype of 1
  activated_pins_.push_back({pin, static_cast<bcm2835PUDControl>(pud % 2)});

  if (pud > 0x02)
    pud = EXTERNAL_READ;

  bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_set_pud(pin, pud);
}  // end ListenToPin

std::vector<Pins> PinReader::GetUpdates() const {
  return GetPinsActivated();
}  // end GetUpdates

std::vector<Pins> PinReader::GetPins() const {
  std::vector<Pins> pin_list;

  for (size_t i = 0; i < activated_pins_.size(); i++) {
    pin_list.push_back(activated_pins_[i].pin);
  }

  return pin_list;
}  // end GetPins

/// Private Functions

std::vector<Pins> PinReader::GetPinsActivated() const {
  std::vector<Pins> held_pins;
  
  for (size_t i = 0; i < activated_pins_.size(); i++) {
    if (bcm2835_gpio_lev(activated_pins_[i].pin) ==
        static_cast<uint8_t>(activated_pins_[i].read_type)) {
          held_pins.push_back(activated_pins_[i].pin);
    }
  }
  
  return held_pins;
}  // end GetPinsHeld
