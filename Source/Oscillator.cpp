/*
  ==============================================================================
    Oscillator.cpp
    Author:  MHENDER4
  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(Wsynth_v1AudioProcessor& p) : processor(p)
{
    setSize(350, 300); // Set component size

    // Design wavetable slider
    osc1WtSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    osc1WtSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
    osc1WtSlider.setTextBoxIsEditable(true);
    osc1WtSlider.setNumDecimalPlacesToDisplay(1);
    osc1WtSlider.setRange(0.0, 300.0);
    osc1WtSlider.setValue(0.0);
    osc1WtSlider.setTextValueSuffix(" colour");
    addAndMakeVisible(&osc1WtSlider);

    // Design wavetable slider
    osc2WtSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    osc2WtSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
    osc2WtSlider.setTextBoxIsEditable(true);
    osc2WtSlider.setNumDecimalPlacesToDisplay(1);
    osc2WtSlider.setRange(0.0, 300.0);
    osc2WtSlider.setValue(0.0);
    osc2WtSlider.setTextValueSuffix(" colour");
    addAndMakeVisible(&osc2WtSlider);

    // Design gain slider
    osc1GainSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    osc1GainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
    osc1GainSlider.setTextBoxIsEditable(true);
    osc1GainSlider.setNumDecimalPlacesToDisplay(1);
    osc1GainSlider.setRange(-60.0, 0.0);
    osc1GainSlider.setValue(-12.0);
    osc1GainSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(&osc1GainSlider);

    // Design gain slider
    osc2GainSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    osc2GainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
    osc2GainSlider.setTextBoxIsEditable(true);
    osc2GainSlider.setNumDecimalPlacesToDisplay(1);
    osc2GainSlider.setRange(-60.0, 0.0);
    osc2GainSlider.setValue(-12.0);
    osc2GainSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(&osc2GainSlider);

    // Design pitch slider
    osc1PitchSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    osc1PitchSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
    osc1PitchSlider.setTextBoxIsEditable(true);
    osc1PitchSlider.setNumDecimalPlacesToDisplay(1);
    osc1PitchSlider.setRange(0.0, 10.0);
    osc1PitchSlider.setValue(1.0);
    addAndMakeVisible(&osc1PitchSlider);

    // Design pitch slider
    osc2PitchSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    osc2PitchSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
    osc2PitchSlider.setTextBoxIsEditable(true);
    osc2PitchSlider.setNumDecimalPlacesToDisplay(1);
    osc2PitchSlider.setRange(0.0, 10.0);
    osc2PitchSlider.setValue(1.0);
    addAndMakeVisible(&osc2PitchSlider);
    
    /* Waveform select combo box
    String wave1 = "sine";
    String wave2 = "square";
    String wave3 = "sawtooth";
    String wave4 = "triangle";
    waveformSelect.addItem(wave1, 1);
    waveformSelect.addItem(wave2, 2);
    waveformSelect.addItem(wave3, 3);
    waveformSelect.addItem(wave4, 4);
    waveformSelect.setSelectedItemIndex(0, true);
    addAndMakeVisible(waveformSelect);

    sends value of the sliders to the tree state in the processor
    oscGainVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "osc1gain", oscGainSlider);
    waveformVal = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "waveform1", waveformSelect);
    */

}

Oscillator::~Oscillator()
{
}

void Oscillator::paint(Graphics& g)
{
    // Create component title
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);
    g.fillAll(Colours::black);

    juce::Rectangle <float> area(0, 0, 400, 400);

    // Create component borders
    juce::Rectangle <float> box1area(0, 0, 80, 245);
    juce::Rectangle <float> box2area(90, 0, 80, 245);
    juce::Rectangle <float> box3area(0, 255, 170, 75);
    g.setColour(Colours::maroon);
    g.drawRect(box1area);
    g.drawRect(box2area);
    g.drawRect(box3area);
}

void Oscillator::resized()
{
    juce::Rectangle<int> area = getLocalBounds();

    // Position component variables
    //waveformSelect.setBounds(40, 60, 100, 50);
    osc1WtSlider.setBounds(10, 5, 60, 100);
    osc2WtSlider.setBounds(10, 120, 60, 100);
    osc1GainSlider.setBounds(100, 5, 60, 100);
    osc2GainSlider.setBounds(100, 120, 60, 100);
    osc1PitchSlider.setBounds(10, 265, 70, 40);
    osc2PitchSlider.setBounds(90, 265, 70, 40);
}
