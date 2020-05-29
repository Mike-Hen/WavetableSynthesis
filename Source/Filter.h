/*
  ==============================================================================
    Filter.h
    Author:  MHENDER4
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


class Filter : public Component,
    public Button::Listener
{
public:
    Filter(Wsynth_v1AudioProcessor&);
    ~Filter();

    void paint(Graphics&) override;
    void resized() override;

    void buttonClicked(Button* button) override;

    // Create components objects
    Slider cutoffSlider;
    ComboBox filterSelect;
    TextButton filtOnOff;

private:
    Wsynth_v1AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Filter)
};