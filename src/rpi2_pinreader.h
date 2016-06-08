/**
 * @file    rpi2_pinreader.h
 * @author  Matthew Robinson
 * @status	Complete
 */

#ifndef EG_VIDEOPLAYER_RPI2_PINREADER_H_
#define EG_VIDEOPLAYER_RPI2_PINREADER_H_

#include <stdlib.h>   // exit, EXIT_FAILURE
#include <algorithm>
#include <vector>
#include "bcm2835.h"

enum Pins {
  kPinUnknown = 0,
  kPin8  = RPI_V2_GPIO_P1_03,
  kPin9  = RPI_V2_GPIO_P1_05,
  kPin7  = RPI_V2_GPIO_P1_07,     kPin15 = RPI_V2_GPIO_P1_08,
                                  kPin16 = RPI_V2_GPIO_P1_10,
  kPin0  = RPI_V2_GPIO_P1_11,     kPin1  = RPI_V2_GPIO_P1_12,
  kPin2  = RPI_V2_GPIO_P1_13,
  kPin3  = RPI_V2_GPIO_P1_15,     kPin4  = RPI_V2_GPIO_P1_16,
                                  kPin5  = RPI_V2_GPIO_P1_18,
  kPin12 = RPI_V2_GPIO_P1_19,
  kPin13 = RPI_V2_GPIO_P1_21,     kPin6  = RPI_V2_GPIO_P1_22,
  kPin14 = RPI_V2_GPIO_P1_23,     kPin10 = RPI_V2_GPIO_P1_24,
                                  kPin11 = RPI_V2_GPIO_P1_26,
  kPin21 = RPI_V2_GPIO_P1_29,
  kPin22 = RPI_V2_GPIO_P1_31,     kPin26 = RPI_V2_GPIO_P1_32,
  kPin23 = RPI_V2_GPIO_P1_33,
  kPin24 = RPI_V2_GPIO_P1_35,     kPin27 = RPI_V2_GPIO_P1_36,
  kPin25 = RPI_V2_GPIO_P1_37,     kPin38 = RPI_V2_GPIO_P1_38,
                                  kPin39 = RPI_V2_GPIO_P1_40
};

/**
 * PinReader class is easy to use class that uses functionality from bcm2835.h
 * It wraps functionality from bcm2835 into an easy to use and read interface.
 * For more customization and a better interface, visit http://www.airspayce.com/mikem/bcm2835/
 * The PinReader class can be constructed multiple times. If you no longer wish
 * to use a constructed PinReader, stop calling Update(). Destructing the
 * object is only useful if all PinReaders are destructed.
 *
 * NOTE: Raspberry Pi's internal pull up/down resistors are favorable, but there is
 * implementation if the client wishes to wire their own.
 */
class PinReader {
public:

  // RPis include internal pud resistors. If you would like it disabled,
  // use an external read type.
  enum PUDValues {
    EXTERNAL_READ = BCM2835_GPIO_PUD_OFF,  // Do not use to ListenToPin().
    PUD_DOWN = BCM2835_GPIO_PUD_DOWN,
    PUD_UP = BCM2835_GPIO_PUD_UP,
    EXTERNAL_DOWN = 0x03,
    EXTERNAL_UP = 0x04
  };

  /**
   * @info	  Constructor that creates a stopped pin reader.
   */
  PinReader(bool debug = false);

  /**
   * @info    Destructing a PinReader instance to reduce the number of active
   *          PinReaders. At 0 PinReaders, bcm2835 is closed.
   */
  ~PinReader();

  /**
   * @info    Add pin for reader to read.
   * @param   pin		Pin client wants to read
   *			    pud		Pull up or Pull down resistor type
   */
  void ListenToPin(Pins pin, PUDValues pud = PUD_UP);

  /**
   * @info    Checks for pins activated in comparison to resistor.
   */
  std::vector<Pins> GetUpdates() const;

  /**
   * @info    List of pins specified to listen to.
   */
  std::vector<Pins> GetPins() const;

private:
  struct PinData {
    Pins   pin;
    bcm2835PUDControl read_type;
  };

  static int instances_;  // Number of constructed PinReaders

  PinReader(const PinReader&) {}
  void operator=(const PinReader&) {}

  /// Functions
  std::vector<Pins> GetPinsActivated() const;

  /// Data Members
  std::vector<PinData> activated_pins_;
};

#endif  // !EG_VIDEOPLAYER_RPI2_PINREADER_H_