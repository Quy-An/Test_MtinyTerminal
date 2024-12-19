#ifndef MKL_OneButton_H_
#define MKL_OneButton_H_

#include "OneButton.h"

class MKL_OneButton: public OneButton
{
  public:
  MKL_OneButton(const int pin, const boolean activeLow = true, const bool pullupActive = true):OneButton(pin, activeLow, pullupActive) {}
};

#endif