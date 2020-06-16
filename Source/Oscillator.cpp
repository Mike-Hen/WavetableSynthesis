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
    setSize(650, 330); // Set component size

    // Design wavetable slider
    osc1WtSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    osc1WtSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
    osc1WtSlider.setTextBoxIsEditable(true);
    osc1WtSlider.addListener(this);
    osc1WtSlider.setColour(osc1WtSlider.textBoxOutlineColourId, Colours::darkgrey);
    osc1WtSlider.setNumDecimalPlacesToDisplay(1);
    osc1WtSlider.setRange(0.0, 300.0);
    osc1WtSlider.setValue(0.0);
    osc1WtSlider.setTextValueSuffix(" colour");
    addAndMakeVisible(&osc1WtSlider);

    // Design wavetable slider
    osc2WtSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    osc2WtSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
    osc2WtSlider.setTextBoxIsEditable(true);
    osc1WtSlider.addListener(this);
    osc2WtSlider.setColour(osc2WtSlider.textBoxOutlineColourId, Colours::darkgrey);
    osc2WtSlider.setNumDecimalPlacesToDisplay(1);
    osc2WtSlider.setRange(0.0, 300.0);
    osc2WtSlider.setValue(0.0);
    osc2WtSlider.setTextValueSuffix(" colour");
    addAndMakeVisible(&osc2WtSlider);

    // Design gain slider
    osc1GainSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    osc1GainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
    osc1GainSlider.setTextBoxIsEditable(true);
    osc1GainSlider.setColour(osc1GainSlider.textBoxOutlineColourId, Colours::darkgrey);
    osc1GainSlider.setNumDecimalPlacesToDisplay(1);
    osc1GainSlider.setRange(-60.0, 0.0);
    osc1GainSlider.setValue(-12.0);
    osc1GainSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(&osc1GainSlider);

    // Design gain slider
    osc2GainSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    osc2GainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
    osc2GainSlider.setTextBoxIsEditable(true);
    osc2GainSlider.setColour(osc2GainSlider.textBoxOutlineColourId, Colours::darkgrey);
    osc2GainSlider.setNumDecimalPlacesToDisplay(1);
    osc2GainSlider.setRange(-60.0, 0.0);
    osc2GainSlider.setValue(-12.0);
    osc2GainSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(&osc2GainSlider);

    // Design pitch slider
    osc1PitchSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    osc1PitchSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
    osc1PitchSlider.setTextBoxIsEditable(true);
    osc1PitchSlider.setColour(osc1PitchSlider.textBoxOutlineColourId, Colours::darkgrey);
    osc1PitchSlider.setNumDecimalPlacesToDisplay(1);
    osc1PitchSlider.setRange(0.0, 10.0);
    osc1PitchSlider.setValue(1.0);
    addAndMakeVisible(&osc1PitchSlider);

    // Design pitch slider
    osc2PitchSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    osc2PitchSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
    osc2PitchSlider.setTextBoxIsEditable(true);
    osc2PitchSlider.setColour(osc2PitchSlider.textBoxOutlineColourId, Colours::darkgrey);
    osc2PitchSlider.setNumDecimalPlacesToDisplay(1);
    osc2PitchSlider.setRange(0.0, 10.0);
    osc2PitchSlider.setValue(1.0);
    addAndMakeVisible(&osc2PitchSlider);

    osc1Image = Image(juce::Image::ARGB, getWidth() / 2 - 25, 230, true);
    osc1Graphic = new Graphics(osc1Image);

    osc2Image = Image(juce::Image::ARGB, getWidth() / 2 - 25, 230, true);
    osc2Graphic = new Graphics(osc2Image);
    
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

void Oscillator::sliderValueChanged(Slider* slider)
{
    repaint();
}

void Oscillator::paint(Graphics& g)
{
    // Text Font
    g.setFont(Font("Franklin Gothic", 20.0f, Font::bold));

    // Create component borders
    juce::Rectangle <float> box1area(0, 0, getWidth() / 2 - 5, getHeight());
    juce::Rectangle <float> box2area(getWidth() / 2 + 5, 0, getWidth() / 2 - 5, getHeight());
    juce::Rectangle <float> box1title(0, 0, getWidth() / 2 - 5, 25);
    juce::Rectangle <float> box2title(getWidth() / 2 + 5, 0, getWidth() / 2 - 5, 25);
    g.setColour(Colours::darkgrey);
    g.fillRect(box1area);
    g.fillRect(box2area);
    g.setColour(Colours::grey);
    g.fillRect(box1title);
    g.fillRect(box2title);
    g.setColour(Colours::maroon);
    g.drawRect(box1area);
    g.drawRect(box2area);

    // Create component title
    juce::Rectangle<int> title1Area(0, 5, getWidth() / 2 - 5, 40);
    juce::Rectangle<int> title2Area(getWidth() / 2 + 5, 5, getWidth() / 2 - 5, 40);
    g.setColour(Colours::black);
    g.drawText("OSC 1", title1Area, Justification::centredTop);
    g.drawText("OSC 2", title2Area, Justification::centredTop);

    juce::Rectangle <float> osc1(10, 35, osc1Image.getWidth(), osc1Image.getHeight());
    g.setColour(Colours::black);
    g.fillRect(osc1);

    juce::Rectangle <float> osc2(getWidth() / 2 + 15, 35, osc2Image.getWidth(), osc2Image.getHeight());
    g.setColour(Colours::black);
    g.fillRect(osc2);

    // Draw Grid Lines
    juce::Line <float> osc1xaxis(juce::Point<float>(10, (35 + (osc1Image.getHeight() / 2))), juce::Point<float>(10 + osc1Image.getWidth(), (35 + (osc1Image.getHeight() / 2))));
    juce::Line <float> osc1yaxis(juce::Point<float>(10 + (osc1Image.getWidth() / 2), 35), juce::Point<float>(10 + (osc1Image.getWidth() / 2), (35 + osc1Image.getHeight())));
    g.setColour(Colours::white);
    g.drawLine(osc1xaxis, 0.3f);
    g.drawLine(osc1yaxis, 0.3f);

    // Draw Grid Lines
    juce::Line <float> osc2xaxis(juce::Point<float>(getWidth() / 2 + 15, (35 + (osc2Image.getHeight() / 2))), juce::Point<float>(getWidth() / 2 + 15 + osc2Image.getWidth(), (35 + (osc2Image.getHeight() / 2))));
    juce::Line <float> osc2yaxis(juce::Point<float>(getWidth() / 2 + 15 + (osc2Image.getWidth() / 2), 35), juce::Point<float>(getWidth() / 2 + 15 + (osc2Image.getWidth() / 2), (35 + osc2Image.getHeight())));
    g.setColour(Colours::white);
    g.drawLine(osc2xaxis, 0.3f);
    g.drawLine(osc2yaxis, 0.3f);

    g.setColour(Colours::maroon);
    g.drawRect(osc1);

    g.setColour(Colours::maroon);
    g.drawRect(osc2);

    Path p1;
    float max = 0;
    Array<float> osc1WaveShape = processor.returnOsc1WaveShape();

    for (int i = 0; i < osc1.getWidth(); i++)
    {
        int scaledIndex = float(i*osc1WaveShape.size()) / float(osc1.getWidth());
        float val = osc1WaveShape[scaledIndex];
        val = jlimit<float>(-1, 1, val);

        if (i == 0)
        {
            p1.startNewSubPath(0, 1);
            p1.startNewSubPath(0, -1);
            p1.startNewSubPath(0, val);
        }
        else p1.lineTo(i, val);
    }

    if (p1.isEmpty()) return;
    if (p1.getBounds().getWidth() < 0.01) return;
    if (p1.getBounds().getWidth() != p1.getBounds().getWidth()) return;

    p1.scaleToFit(0, 0, osc1Image.getWidth(), osc1Image.getHeight(), false);

    osc1Image.multiplyAllAlphas(0);

    osc1Graphic->setColour(Colours::white);
    osc1Graphic->strokePath(p1, PathStrokeType(0.5f + max / 2));

    Path p2;
    Array<float> osc2WaveShape = processor.returnOsc2WaveShape();

    for (int i = 0; i < osc2.getWidth(); i++)
    {
        int scaledIndex = float(i*osc2WaveShape.size()) / float(osc2.getWidth());
        float val = osc2WaveShape[scaledIndex];
        val = jlimit<float>(-1, 1, val);

        if (i == 0)
        {
            p2.startNewSubPath(0, 1);
            p2.startNewSubPath(0, -1);
            p2.startNewSubPath(0, val);
        }
        else p2.lineTo(i, val);
    }

    if (p2.isEmpty()) return;
    if (p2.getBounds().getWidth() < 0.01) return;
    if (p2.getBounds().getWidth() != p2.getBounds().getWidth()) return;

    p2.scaleToFit(0, 0, osc2Image.getWidth(), osc2Image.getHeight(), false);

    osc2Image.multiplyAllAlphas(0);

    osc2Graphic->setColour(Colours::white);
    osc2Graphic->strokePath(p2, PathStrokeType(0.5f + max / 2));
    
    g.drawImageAt(osc1Image, 10, 35);
    g.drawImageAt(osc2Image, getWidth() / 2 + 15, 35);
}

void Oscillator::resized()
{
    juce::Rectangle<int> area = getLocalBounds();

    // Position component variables
    //waveformSelect.setBounds(40, 60, 100, 50);
    osc1WtSlider.setBounds(30, 255, 60, 100);
    osc2WtSlider.setBounds(getWidth() - 30 - 60, 255, 60, 100);
    osc1GainSlider.setBounds(120, 255, 60, 100);
    osc2GainSlider.setBounds(getWidth() - 120 - 60, 255, 60, 100);
    osc1PitchSlider.setBounds(210, 285, 70, 40);
    osc2PitchSlider.setBounds(getWidth() - 210 - 70, 285, 70, 40);
}
