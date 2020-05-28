/*
  ==============================================================================
    Envelope.h
    Author:  Joshua Hodge
  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================

class Envelope : public Component
{
public:
    Envelope(Wsynth_v1AudioProcessor&);
    ~Envelope();

    void paint(Graphics&) override;
    void resized() override;
    void setADSRValues(float attack, float decay, float sustain, float release);

    // ADSR Sliders
    Slider attackSlider;
    Slider decaySlider;
    Slider sustainSlider;
    Slider releaseSlider;

private:
    Wsynth_v1AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Envelope)
};
