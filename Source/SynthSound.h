/*
  ==============================================================================
    SynthSound.h
    Author:  MHENDER4
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================

class SynthSound : public SynthesiserSound
{
public:
    bool appliesToNote(int /* midiNoteNumber */)
    {
        return true;
    }
    bool appliesToChannel(int /* midiChannel */)
    {
        return true;
    }
};
