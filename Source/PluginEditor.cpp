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
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 500);

    //===== Setup Master =====//

    masterGainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    masterGainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    masterGainSlider.setTextBoxIsEditable(true);
    masterGainSlider.setNumDecimalPlacesToDisplay(1);
    masterGainSlider.setRange(-60.0, 0.0);
    masterGainSlider.setValue(-12.0);
    masterGainSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(masterGainSlider);

    //===== Setup Reg =====//

    reg1.setSize(80, 70);
    reg1.setClickingTogglesState(false);
    reg1.setButtonText("reg1");
    reg1.setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
    reg1.addListener(this);
    addAndMakeVisible(reg1);

    reg2.setSize(80, 70);
    reg2.setClickingTogglesState(false);
    reg2.setButtonText("reg2");
    reg2.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
    reg2.addListener(this);
    addAndMakeVisible(reg2);

    reg3.setSize(80, 70);
    reg3.setClickingTogglesState(false);
    reg3.setButtonText("reg3");
    reg3.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
    reg3.addListener(this);
    addAndMakeVisible(reg3);

    reg4.setSize(80, 70);
    reg4.setClickingTogglesState(false);
    reg4.setButtonText("reg4");
    reg4.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
    reg4.addListener(this);
    addAndMakeVisible(reg4);

    reg5.setSize(80, 70);
    reg5.setClickingTogglesState(false);
    reg5.setButtonText("reg5");
    reg5.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
    reg5.addListener(this);
    addAndMakeVisible(reg5);

    reg6.setSize(80, 70);
    reg6.setClickingTogglesState(false);
    reg6.setButtonText("reg6");
    reg6.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
    reg6.addListener(this);
    addAndMakeVisible(reg6);

    reg7.setSize(80, 70);
    reg7.setClickingTogglesState(false);
    reg7.setButtonText("reg7");
    reg7.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
    reg7.addListener(this);
    addAndMakeVisible(reg7);

    //====== Add Components =====//

    addAndMakeVisible(&envGui);
    addAndMakeVisible(&oscGui);
    addAndMakeVisible(&filt1);
    addAndMakeVisible(&filt2);
    addAndMakeVisible(&dist1);

    //===== Tracking GUI =====//

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

void Wsynth_v1AudioProcessorEditor::buttonClicked(Button* button)
{
    if (reg1.isMouseOver() == true)
    {
        reg1.setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
        reg2.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg3.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg4.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg5.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg6.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg7.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        envGui.setADSRValues(0.0f, 0.3f, 0.1f, 0.0f);
    }
    if (reg2.isMouseOver() == true)
    {
        reg1.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg2.setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
        reg3.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg4.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg5.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg6.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg7.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        envGui.setADSRValues(0.8f, 0.6f, 0.2f, 0.8f);
    }
    if (reg3.isMouseOver() == true)
    {
        reg1.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg2.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg3.setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
        reg4.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg5.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg6.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg7.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        envGui.setADSRValues(1.6f, 0.9f, 0.3f, 1.6f);
    }
    if (reg4.isMouseOver() == true)
    {
        reg1.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg2.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg3.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg4.setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
        reg5.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg6.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg7.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        envGui.setADSRValues(2.4f, 1.2f, 0.4f, 2.4f);
    }
    if (reg5.isMouseOver() == true)
    {
        reg1.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg2.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg3.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg4.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg5.setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
        reg6.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg7.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        envGui.setADSRValues(3.2f, 1.5f, 0.5f, 3.2f);
    }
    if (reg6.isMouseOver() == true)
    {
        reg1.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg2.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg3.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg4.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg5.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg6.setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
        reg7.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        envGui.setADSRValues(4.0f, 1.7f, 0.8f, 4.0f);
    }
    if (reg7.isMouseOver() == true)
    {
        reg1.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg2.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg3.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg4.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg5.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg6.setColour(TextButton::ColourIds::buttonColourId, Colours::black);
        reg7.setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
        envGui.setADSRValues(5.0f, 2.0f, 1.0f, 5.0f);
    }
}

//==============================================================================
void Wsynth_v1AudioProcessorEditor::paint (Graphics& g)
{
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
    masterGainSlider.setBounds(getWidth() - 100, 25, 75, 100);
    oscGui.setBounds(10,10, 170, 340);
    envGui.setBounds(getWidth() - 160, 320, 150, 150);
    filt1.setBounds(440, 10, 80, 200);
    filt2.setBounds(530, 10, 250, 200);
    dist1.setBounds(190, 10, 240, 170);

    reg1.setBounds(250, 370, 80, 70);
    reg2.setBounds(330, 370, 80, 70);
    reg3.setBounds(410, 370, 80, 70);
    reg4.setBounds(490, 370, 80, 70);
    reg5.setBounds(570, 370, 80, 70);
    reg6.setBounds(650, 370, 80, 70);
    reg7.setBounds(730, 370, 80, 70);
}
