/*
  ==============================================================================
    Envelope.cpp
    Author:  Joshua Hodge
  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(Wsynth_v1AudioProcessor& p) :
    processor(p)
{
    setSize(200, 160);

    // Design attack slider
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 5.0f);
    attackSlider.setValue(0.1f);
    attackSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&attackSlider);

    // Design decay slider
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.1f, 2.0f);
    decaySlider.setValue(0.8f);
    decaySlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&decaySlider);

    // Design sustain slider
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.1f, 1.0f);
    sustainSlider.setValue(0.8f);
    sustainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&sustainSlider);

    // Design release slider
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.1f, 5.0f);
    releaseSlider.setValue(0.8f);
    releaseSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&releaseSlider);

    //sends value of the sliders to the tree state in the processor
//    attackVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "attack", attackSlider);
//    decayVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "decay", decaySlider);
//    sustainVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "sustain", sustainSlider);
//    releaseVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "release", releaseSlider);
}

Envelope::~Envelope()
{
}

void Envelope::paint(Graphics& g)
{
    // Set component size
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    // Colour & name component
    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.drawText("Envelope", titleArea, Justification::centredTop);

    // Position slider text
    g.drawText("A", 37, 150, 20, 20, Justification::centredTop);
    g.drawText("D", 72, 150, 20, 20, Justification::centredTop);
    g.drawText("S", 107, 150, 20, 20, Justification::centredTop);
    g.drawText("R", 142, 150, 20, 20, Justification::centredTop);

    // Position border
    juce::Rectangle <float> area(0, 0, 150, 150);
    g.setColour(Colours::maroon);
    g.drawRect(area);
}

void Envelope::setADSRValues(float attack, float decay, float sustain, float release)
{
    // Set slider values
    attackSlider.setValue(attack);
    decaySlider.setValue(decay);
    sustainSlider.setValue(sustain);
    releaseSlider.setValue(release);
}

void Envelope::resized()
{
    // Position ADSR controls
    attackSlider.setBounds(10, 15, 25, 120);
    decaySlider.setBounds(45, 15, 25, 120);
    sustainSlider.setBounds(80, 15, 25, 120);
    releaseSlider.setBounds(115, 15, 25, 120);
}



