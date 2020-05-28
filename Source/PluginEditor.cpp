/*
  ==============================================================================
    PluginEditor.cpp
    Author:  MHENDER4
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Wsynth_v1AudioProcessorEditor::Wsynth_v1AudioProcessorEditor (Wsynth_v1AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), oscGui(p), filt1(p), filt2(p), dist1(p), envGui(p)
{
    setSize (1000, 500); // Set synth size

    //===== Master gain =====//
    masterGainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    masterGainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    masterGainSlider.setTextBoxIsEditable(true);
    masterGainSlider.setNumDecimalPlacesToDisplay(1);
    masterGainSlider.setRange(-60.0, 0.0);
    masterGainSlider.setValue(-12.0);
    masterGainSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(masterGainSlider);

    //===== Setup ADSR presets =====//
    presetADSR1.setSize(80, 70);
    presetADSR1.setClickingTogglesState(false);
    presetADSR1.setButtonText("presetADSR1");
    presetADSR1.setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
    presetADSR1.addListener(this);
    addAndMakeVisible(presetADSR1);

    presetADSR2.setSize(80, 70);
    presetADSR2.setClickingTogglesState(false);
    presetADSR2.setButtonText("presetADSR2");
    presetADSR2.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
    presetADSR2.addListener(this);
    addAndMakeVisible(presetADSR2);

    presetADSR3.setSize(80, 70);
    presetADSR3.setClickingTogglesState(false);
    presetADSR3.setButtonText("presetADSR3");
    presetADSR3.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
    presetADSR3.addListener(this);
    addAndMakeVisible(presetADSR3);

    presetADSR4.setSize(80, 70);
    presetADSR4.setClickingTogglesState(false);
    presetADSR4.setButtonText("presetADSR4");
    presetADSR4.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
    presetADSR4.addListener(this);
    addAndMakeVisible(presetADSR4);

    presetADSR5.setSize(80, 70);
    presetADSR5.setClickingTogglesState(false);
    presetADSR5.setButtonText("presetADSR5");
    presetADSR5.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
    presetADSR5.addListener(this);
    addAndMakeVisible(presetADSR5);

    presetADSR6.setSize(80, 70);
    presetADSR6.setClickingTogglesState(false);
    presetADSR6.setButtonText("presetADSR6");
    presetADSR6.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
    presetADSR6.addListener(this);
    addAndMakeVisible(presetADSR6);

    presetADSR7.setSize(80, 70);
    presetADSR7.setClickingTogglesState(false);
    presetADSR7.setButtonText("presetADSR7");
    presetADSR7.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
    presetADSR7.addListener(this);
    addAndMakeVisible(presetADSR7);

    //====== Add components =====//
    addAndMakeVisible(&envGui);
    addAndMakeVisible(&oscGui);
    addAndMakeVisible(&filt1);
    addAndMakeVisible(&filt2);
    addAndMakeVisible(&dist1);

    //===== Tracking GUI values =====//

    // Master
    masterGainVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "mastergain", masterGainSlider);
    
    // Oscillators
    osc1WtVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "osc1wt", oscGui.osc1WtSlider);
    osc1GainVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "osc1gain", oscGui.osc1GainSlider);
    osc2WtVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "osc2wt", oscGui.osc2WtSlider);
    osc2GainVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "osc2gain", oscGui.osc2GainSlider);
    osc1PitchVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "osc1pitch", oscGui.osc1PitchSlider);
    osc2PitchVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "osc2pitch", oscGui.osc2PitchSlider);
    
    // Envelope
    attackVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "attack", envGui.attackSlider);
    decayVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "decay", envGui.decaySlider);
    sustainVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "sustain", envGui.sustainSlider);
    releaseVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "release", envGui.releaseSlider);
    
    // Filters
    filt1OnOffVal = new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "filt1onoff", filt1.filtOnOff);
    filt1Val = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "filt1", filt1.filterSelect);
    filt1CutoffVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "filt1cutoff", filt1.cutoffSlider);
    filt2CutoffVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "filt2cutoff", filt2.cutoffSlider);
    
    // Distortion
    dist1OnOffVal = new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "dist1onoff", dist1.distOnOff);
    dist1InputGainVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "dist1inputgain", dist1.inputGainSlider);
    dist1OutputGainVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "dist1outputgain", dist1.outputGainSlider);
    dist1DryWetVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "dist1drywet", dist1.dryWetSlider);
}

Wsynth_v1AudioProcessorEditor::~Wsynth_v1AudioProcessorEditor()
{
}

//==== Tracking ADSR preset buttons ====//
void Wsynth_v1AudioProcessorEditor::buttonClicked(Button* button)
{
    if (presetADSR1.isMouseOver() == true)
    {
        presetADSR1.setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
        presetADSR2.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR3.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR4.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR5.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR6.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR7.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        envGui.setADSRValues(0.0f, 0.3f, 0.1f, 0.0f);
    }
    if (presetADSR2.isMouseOver() == true)
    {
        presetADSR1.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR2.setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
        presetADSR3.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR4.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR5.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR6.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR7.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        envGui.setADSRValues(0.8f, 0.6f, 0.2f, 0.8f);
    }
    if (presetADSR3.isMouseOver() == true)
    {
        presetADSR1.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR2.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR3.setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
        presetADSR4.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR5.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR6.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR7.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        envGui.setADSRValues(1.6f, 0.9f, 0.3f, 1.6f);
    }
    if (presetADSR4.isMouseOver() == true)
    {
        presetADSR1.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR2.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR3.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR4.setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
        presetADSR5.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR6.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR7.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        envGui.setADSRValues(2.4f, 1.2f, 0.4f, 2.4f);
    }
    if (presetADSR5.isMouseOver() == true)
    {
        presetADSR1.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR2.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR3.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR4.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR5.setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
        presetADSR6.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR7.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        envGui.setADSRValues(3.2f, 1.5f, 0.5f, 3.2f);
    }
    if (presetADSR6.isMouseOver() == true)
    {
        presetADSR1.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR2.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR3.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR4.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR5.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR6.setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
        presetADSR7.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        envGui.setADSRValues(4.0f, 1.7f, 0.8f, 4.0f);
    }
    if (presetADSR7.isMouseOver() == true)
    {
        presetADSR1.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR2.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR3.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR4.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR5.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR6.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        presetADSR7.setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
        envGui.setADSRValues(5.0f, 2.0f, 1.0f, 5.0f);
    }
}

void Wsynth_v1AudioProcessorEditor::paint (Graphics& g)
{
    // Set background
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.fillAll(Colours::black);
    g.setColour(Colours::white);

    juce::Rectangle<int> nameArea(getWidth() - 100, 15, 75, 100);
    g.drawText("Master Gain", nameArea, Justification::centredTop);

    juce::Rectangle <float> area(0, 0, getWidth(), getHeight());

    g.setColour(Colours::darkred);
    g.drawRect(area, 4.0f);
}

void Wsynth_v1AudioProcessorEditor::resized()
{
    // Position components
    masterGainSlider.setBounds(getWidth() - 100, 25, 75, 100);
    oscGui.setBounds(10,10, 170, 340);
    envGui.setBounds(getWidth() - 160, 320, 150, 150);
    filt1.setBounds(440, 10, 80, 200);
    filt2.setBounds(530, 10, 250, 200);
    dist1.setBounds(190, 10, 240, 170);

    // Position ADSR presets
    presetADSR1.setBounds(250, 370, 80, 70);
    presetADSR2.setBounds(330, 370, 80, 70);
    presetADSR3.setBounds(410, 370, 80, 70);
    presetADSR4.setBounds(490, 370, 80, 70);
    presetADSR5.setBounds(570, 370, 80, 70);
    presetADSR6.setBounds(650, 370, 80, 70);
    presetADSR7.setBounds(730, 370, 80, 70);
}
