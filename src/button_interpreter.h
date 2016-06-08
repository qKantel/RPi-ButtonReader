/**
 * @file    button_interpreter.h
 * @author  Matthew Robinson
 */

#ifndef EG_VIDEOPLAYER_BUTTON_INTERPRETER_H_
#define EG_VIDEOPLAYER_BUTTON_INTERPRETER_H_

#include "rpi2_pinreader.h"
#include <algorithm>
#include <list>
#include <vector>

/**
 * ButtonInterpreter is an easy to use class that converts readings from a
 * PinReader. The conversion assumes the pin is wired to a mechanism that a
 * human pushes with real life consequences, such as: press delay, pressing
 * multiple buttons, etc.
 */
class ButtonInterpreter {
public:
  ButtonInterpreter() :
    reader_(nullptr),
    unhandled_reader_change_(false),
    alpha_(0.5) {}
  ButtonInterpreter(PinReader * pin_reader) :
    reader_(pin_reader),
    unhandled_reader_change_(true),
    alpha_(0.5) {}
  
  ~ButtonInterpreter() { }
  
  /**
   * @info    The client gives the interpreter a constructed and set up
   *          PinReader. The interpreter calls the PinReader's update function.
   *          This class does not manage the life of pin_reader.
   *          Everytime the PinReader is changed, call this function again
   *          to update all needed data.
   * @param   pin_reader    Constructed PinReader object.
   */
  void AttachReader(PinReader * pin_reader);

  /**
   * @info    Alpha is the degree of weighting decrease.
   *          A higher alpha discounts older observations faster.
   *          Must be set to a value between 0.0 - 1.0
   */
  void SetAlpha(double alpha = 0.5) { alpha_ = alpha; }

  /**
   * @info    Returns the object specific alpha variable.
   */
  double GetAlpha() const { return alpha_; }
  
  /**
   * @info    This function returns the pin that was interpreted as a button
   *          pressed. This is a non-blocking function and calls the class'
   *          associated PinReader's update function.
   *          Undefined behavior if an invalid reader is attached.
   * @return  Returns single button pressed.
   */
  Pins GetButtonPressed();

private:
  struct PinAccumulatorType {
    Pins pin;
    double accumulator;
  };

  ButtonInterpreter(const ButtonInterpreter &) {}
  ButtonInterpreter& operator=(const ButtonInterpreter &) {}

  void UpdateAccumulators();
  Pins GetActivatedButton();
  void UpdateStoredPins();

  // reader_ is not managed by the objects created by this class.
  PinReader * reader_;
  double alpha_;
  bool unhandled_reader_change_;
  std::vector<PinAccumulatorType> pin_accumulators_;
  std::list<Pins> activated_buttons_;
};

#endif  // !EG_VIDEOPLAYER_BUTTON_INTERPRETER_H_