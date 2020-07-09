/*
  ==============================================================================
    Oscillator.h
    Author:  MHENDER4
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "OtherLookAndFeel.h"
#include "Wavetable.h"


class Oscillator : public Component,
    public Slider::Listener, public Button::Listener
{
public:
    Oscillator(Wsynth_v1AudioProcessor&);
    ~Oscillator();

    void paint(Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider* slider) override;
    void buttonClicked(Button* button) override;

    int oscCentValueChange(String command, int centVal);
    int oscFineValueChange(String command, TextButton* cent, int* centVal, int fineVal);

    //std::array<dsp::Complex<float>, 4096> osc1BLWT();

    // Create components objects
    Slider osc1GainSlider;
    Slider osc2GainSlider;
    Slider osc1WtSlider;
    Slider osc2WtSlider;
    Slider osc1PitchSlider;
    Slider osc2PitchSlider;

    int osc1CentValue = 0;
    TextButton osc1Cent;
    int osc1FineValue = 0;
    TextButton osc1Fine;
    int osc2CentValue = 0;
    TextButton osc2Cent;
    int osc2FineValue = 0;
    TextButton osc2Fine;
 
    ArrowButton osc1CentUp{ "osc1CentUp", 0.75f, Colours::black };
    ArrowButton osc1CentDown{ "osc1CentDown", 0.25f, Colours::black };
    ArrowButton osc1FineUp{ "osc1FineUp", 0.75f, Colours::black };
    ArrowButton osc1FineDown{ "osc1FineDown", 0.25f, Colours::black };
    ArrowButton osc2CentUp{ "osc2CentUp", 0.75f, Colours::black };
    ArrowButton osc2CentDown{ "osc2CentDown", 0.25f, Colours::black };
    ArrowButton osc2FineUp{ "osc2FineUp", 0.75f, Colours::black };
    ArrowButton osc2FineDown{ "osc2FineDown", 0.25f, Colours::black };

    Image osc1Image;
    ScopedPointer<Graphics> osc1Graphic;

    Image osc2Image;
    ScopedPointer<Graphics> osc2Graphic;

    OtherLookAndFeel otherLookAndFeel;

private:
    Wsynth_v1AudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Oscillator)
};