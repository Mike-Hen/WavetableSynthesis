/*
  ==============================================================================

    SynthSound.h
    Created: 11 Jan 2020 10:38:05am
    Author:  MHENDER4

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound
{
public:
	bool appliesToNote(int /* midiNoteNumber*/)
	{
		return true;
	}
	bool appliesToChannel(int /* midiChannel*/)
	{
		return true;
	}
};
