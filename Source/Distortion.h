/*
  ==============================================================================
    Distortion.h
    Author:  MHENDER4
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "OtherLookAndFeel.h"

//==============================================================================

class Distortion : public Component,
    public ComboBox::Listener, public Slider::Listener
{
public:
    Distortion(Wsynth_v1AudioProcessor&);
    ~Distortion();

    void paint(Graphics&) override;
    void resized() override;

    void comboBoxChanged(ComboBox* combobox) override;
    void sliderValueChanged(Slider* slider) override;
    Array<float> getDistortionCurve(int distLength);

    // Create component objects
    Slider inputGainSlider;
    Slider outputGainSlider;
    Slider dryWetSlider;
    ComboBox methodSelect;
    TextButton distOnOff;

    Image distortionImage;
    ScopedPointer<Graphics> distortionGraphic;

    OtherLookAndFeel otherLookAndFeel;

private:
    Wsynth_v1AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Distortion)
};