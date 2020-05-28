/*
  ==============================================================================
    LFO.h
    Author:  Joshua Hodge
  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class LFO : public Component
{
public:
    LFO(Wsynth_v1AudioProcessor&);
    ~LFO();

    void paint(Graphics&) override;
    void resized() override;
    void initLFO(float sr, float wt);
    float modulate(float input);

    Slider lfoFreqSlider;
    Slider lfoAmpSlider;

    float sampleRate;
    float increment;
    int wtSize;
    float phase;
    float output;
    Array<float> sineTable;

private:
    Wsynth_v1AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LFO)
};
