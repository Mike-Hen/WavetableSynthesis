/*
  ==============================================================================
    Filtered.cpp
    Author:  MHENDER4
  ==============================================================================
*/
# pragma once
#include "Filtered.h"

double Filtered::process(double inputValue, float cutoff, int mode) {
    buf0 += cutoff * (inputValue - buf0);
    buf1 += cutoff * (buf0 - buf1);
    if (mode == 0)
    {
        return buf1;
    }
    else if (mode == 1)
    {
        inputValue - buf1;
    }

}