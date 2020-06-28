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
    setSize(170, 150); // Set component size

    // Design attack slider
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 5.0f);
    attackSlider.setValue(0.1f);
    attackSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    attackSlider.setLookAndFeel(&otherLookAndFeel);
    addAndMakeVisible(&attackSlider);

    // Design decay slider
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.1f, 2.0f);
    decaySlider.setValue(0.8f);
    decaySlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    decaySlider.setLookAndFeel(&otherLookAndFeel);
    addAndMakeVisible(&decaySlider);

    // Design sustain slider
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.1f, 1.0f);
    sustainSlider.setValue(0.8f);
    sustainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    sustainSlider.setLookAndFeel(&otherLookAndFeel);
    addAndMakeVisible(&sustainSlider);

    // Design release slider
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.1f, 5.0f);
    releaseSlider.setValue(0.8f);
    releaseSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    releaseSlider.setLookAndFeel(&otherLookAndFeel);
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
    // Text Font
    g.setFont(Font("Avenir", 20.0f, Font::bold));

    // Create Background
    juce::Rectangle <float> background(0, 0, 170, 150);
    g.setColour(Colours::darkgrey);
    g.fillRect(background);

    // Create Title Background
    juce::Rectangle <float> titleBack(0, 0, 170, 25);
    g.setColour(Colours::grey);
    g.fillRect(titleBack);

    // Create component title
    juce::Rectangle<int> titleArea(5, 5, getWidth(), 150);
    g.setColour(Colours::black);
    g.drawText("envelope", titleArea, Justification::topLeft);

    // Position slider text
    g.drawText("A", 15, 130, 20, 20, Justification::centredTop);
    g.drawText("D", 54, 130, 20, 20, Justification::centredTop);
    g.drawText("S", 93, 130, 20, 20, Justification::centredTop);
    g.drawText("R", 132, 130, 20, 20, Justification::centredTop);

    // Position border
    juce::Rectangle <float> area(0, 0, 170, 150);
    //g.setColour(Colours::maroon);
    //g.drawRect(area);
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
    attackSlider.setBounds(13, 25, 25, 110);
    decaySlider.setBounds(52, 25, 25, 110);
    sustainSlider.setBounds(91, 25, 25, 110);
    releaseSlider.setBounds(130, 25, 25, 110);
}



