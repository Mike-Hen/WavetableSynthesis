/*
  ==============================================================================
    Oscillator.h
    Author:  MHENDER4
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


class Oscillator : public Component,
    public Slider::Listener
{
public:
    Oscillator(Wsynth_v1AudioProcessor&);
    ~Oscillator();

    void paint(Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider* slider) override;

    // Create components objects
    Slider osc1GainSlider;
    Slider osc2GainSlider;
    Slider osc1WtSlider;
    Slider osc2WtSlider;
    Slider osc1PitchSlider;
    Slider osc2PitchSlider;

    Image osc1Image;
    ScopedPointer<Graphics> osc1Graphic;

    Image osc2Image;
    ScopedPointer<Graphics> osc2Graphic;

private:
    Wsynth_v1AudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Oscillator)
};