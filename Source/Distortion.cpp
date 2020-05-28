/*
  ==============================================================================
    Distortion.cpp
    Author:  MHENDER4
  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Distortion.h"

//==============================================================================

Distortion::Distortion(Wsynth_v1AudioProcessor& p) : processor(p)
{
    setSize(300, 200); // Set component size

    // Design input gain slider
    inputGainSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    inputGainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
    inputGainSlider.setTextBoxIsEditable(true);
    inputGainSlider.setNumDecimalPlacesToDisplay(1);
    inputGainSlider.setRange(-20.0, 20.0);
    inputGainSlider.setValue(0.0);
    inputGainSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(&inputGainSlider);

    // Design output gain slider
    outputGainSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    outputGainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
    outputGainSlider.setTextBoxIsEditable(true);
    outputGainSlider.setNumDecimalPlacesToDisplay(1);
    outputGainSlider.setRange(-20.0, 20.0);
    outputGainSlider.setValue(0.0);
    outputGainSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(&outputGainSlider);

    // Design dry/wet slider
    dryWetSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    dryWetSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
    dryWetSlider.setTextBoxIsEditable(true);
    dryWetSlider.setNumDecimalPlacesToDisplay(0);
    dryWetSlider.setRange(0.0, 100.0);
    dryWetSlider.setValue(0.0);
    dryWetSlider.setTextValueSuffix(" %");
    addAndMakeVisible(&dryWetSlider);
    
    // Design distortion on/off button
    //distOnOff.setSize(50, 50);
    //distOnOff.setClickingTogglesState(true);
    //distOnOff.setButtonText("Off");
    //distOnOff.setColour(TextButton::ColourIds::buttonColourId, Colours::red);
    //distOnOff.addListener(this);
    //addAndMakeVisible(distOnOff);
}

Distortion::~Distortion()
{
}

void Distortion::buttonClicked(Button* button)
{
    if (distOnOff.getToggleState() == true)
    {
        distOnOff.setButtonText("On");
        distOnOff.setColour(TextButton::ColourIds::buttonColourId, Colours::limegreen);
    }
    else if (distOnOff.getToggleState() == false)
    {
        distOnOff.setButtonText("Off");
        distOnOff.setColour(TextButton::ColourIds::buttonColourId, Colours::red);
    }
}

void Distortion::paint(Graphics& g)
{
    // Create component title
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);
    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.drawText("Distortion", titleArea, Justification::topRight);

    // Create component border
    juce::Rectangle <float> area(0, 0, 240, 120);
    g.setColour(Colours::maroon);
    g.drawRect(area);

}

void Distortion::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(50);

    // Position component variables
    //distOnOff.setBounds(10, 10, 100, 30);
    inputGainSlider.setBounds(10, 10, 60, 100);
    outputGainSlider.setBounds(90, 10, 60, 100);
    dryWetSlider.setBounds(170, 10, 60, 100);
}

