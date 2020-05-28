/*
  ==============================================================================
    Oscillator.h
    Author:  MHENDER4
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


class Oscillator : public Component
{
public:
    Oscillator(Wsynth_v1AudioProcessor&);
    ~Oscillator();
    void paint(Graphics&) override;
    void resized() override;

    Slider osc1GainSlider;
    Slider osc2GainSlider;
    Slider osc1WtSlider;
    Slider osc2WtSlider;
    Slider osc1PitchSlider;
    Slider osc2PitchSlider;

private:
    Wsynth_v1AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Oscillator)
};