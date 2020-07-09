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
    osc1WtSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    osc1WtSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
    osc1WtSlider.setTextBoxIsEditable(true);
    osc1WtSlider.addListener(this);
    osc1WtSlider.setColour(osc1WtSlider.textBoxOutlineColourId, Colours::darkgrey);
    osc1WtSlider.setNumDecimalPlacesToDisplay(0);
    osc1WtSlider.setRange(0.0, 300.0);
    osc1WtSlider.setValue(0.0);
    osc1WtSlider.setLookAndFeel(&otherLookAndFeel);
    addAndMakeVisible(&osc1WtSlider);

    // Design wavetable slider
    osc2WtSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    osc2WtSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
    osc2WtSlider.setTextBoxIsEditable(true);
    osc2WtSlider.addListener(this);
    osc2WtSlider.setColour(osc2WtSlider.textBoxOutlineColourId, Colours::darkgrey);
    osc2WtSlider.setNumDecimalPlacesToDisplay(0);
    osc2WtSlider.setRange(0.0, 300.0);
    osc2WtSlider.setValue(0.0);
    osc2WtSlider.setLookAndFeel(&otherLookAndFeel);
    addAndMakeVisible(&osc2WtSlider);

    // Design gain slider
    osc1GainSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    osc1GainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
    osc1GainSlider.setTextBoxIsEditable(true);
    osc1GainSlider.setColour(osc1GainSlider.textBoxOutlineColourId, Colours::darkgrey);
    osc1GainSlider.setNumDecimalPlacesToDisplay(1);
    osc1GainSlider.setRange(-60.0, 0.0);
    osc1GainSlider.setValue(-12.0);
    osc1GainSlider.setTextValueSuffix(" dB");
    osc1GainSlider.setLookAndFeel(&otherLookAndFeel);
    addAndMakeVisible(&osc1GainSlider);

    // Design gain slider
    osc2GainSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    osc2GainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
    osc2GainSlider.setTextBoxIsEditable(true);
    osc2GainSlider.setColour(osc2GainSlider.textBoxOutlineColourId, Colours::darkgrey);
    osc2GainSlider.setNumDecimalPlacesToDisplay(1);
    osc2GainSlider.setRange(-60.0, 0.0);
    osc2GainSlider.setValue(-12.0);
    osc2GainSlider.setTextValueSuffix(" dB");
    osc2GainSlider.setLookAndFeel(&otherLookAndFeel);
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

    // Design Osc 1 Pitch Cent Up Button
    osc1CentUp.setSize(15, 15);
    osc1CentUp.addListener(this);
    addAndMakeVisible(&osc1CentUp);
    osc1CentDown.setSize(15, 15);
    osc1CentDown.addListener(this);
    addAndMakeVisible(&osc1CentDown);

    // Design Osc 1 Pitch Fine Up Button
    osc1FineUp.setSize(15, 15);
    osc1FineUp.addListener(this);
    addAndMakeVisible(&osc1FineUp);
    osc1FineDown.setSize(15, 15);
    osc1FineDown.addListener(this);
    addAndMakeVisible(&osc1FineDown);

    // Design Osc 2 Pitch Cent Up Button
    osc2CentUp.setSize(15, 15);
    osc2CentUp.addListener(this);
    addAndMakeVisible(&osc2CentUp);
    osc2CentDown.setSize(15, 15);
    osc2CentDown.addListener(this);
    addAndMakeVisible(&osc2CentDown);

    // Design Osc 2 Pitch Fine Up Button
    osc2FineUp.setSize(15, 15);
    osc2FineUp.addListener(this);
    addAndMakeVisible(&osc2FineUp);
    osc2FineDown.setSize(15, 15);
    osc2FineDown.addListener(this);
    addAndMakeVisible(&osc2FineDown);

    // Osc 1 Fine and Cent text
    osc1Cent.setButtonText(String(osc1CentValue));
    osc1Cent.setSize(30, 30);
    addAndMakeVisible(&osc1Cent);
    osc1Fine.setButtonText(String(osc1FineValue));
    osc1Fine.setSize(30, 30);
    addAndMakeVisible(&osc1Fine);

    // Osc 2 Fine and Cent text
    osc2Cent.setButtonText(String(osc1CentValue));
    osc2Cent.setSize(30, 30);
    addAndMakeVisible(&osc2Cent);
    osc2Fine.setButtonText(String(osc2FineValue));
    osc2Fine.setSize(30, 30);
    addAndMakeVisible(&osc2Fine);

    float oscWidth = getWidth() / 2 - 25;
    float oscHeight = 230;
    osc1Image = Image(juce::Image::ARGB, oscWidth, oscHeight, true);
    osc1Graphic = new Graphics(osc1Image);

    osc2Image = Image(juce::Image::ARGB, oscWidth, oscHeight, true);
    osc2Graphic = new Graphics(osc2Image);

}

Oscillator::~Oscillator()
{
}

void Oscillator::buttonClicked(Button* button)
{
    if (button == &osc1CentUp)
    {
        osc1CentValue = oscCentValueChange("up", osc1CentValue);
        osc1Cent.setButtonText(String(osc1CentValue));
    }
    else if (button == &osc1CentDown)
    {
        osc1CentValue = oscCentValueChange("down", osc1CentValue);
        osc1Cent.setButtonText(String(osc1CentValue));
    }
    else if (button == &osc1FineUp)
    {
        osc1FineValue = oscFineValueChange("up", &osc1Fine, &osc1CentValue, osc1FineValue);
        osc1Fine.setButtonText(String(osc1FineValue));
    }
    else if (button == &osc1FineDown)
    {
        osc1FineValue = oscFineValueChange("down", &osc1Fine, &osc1CentValue, osc1FineValue);
        osc1Fine.setButtonText(String(osc1FineValue));
    }
    else if (button == &osc2CentUp)
    {
        osc2CentValue = oscCentValueChange("up", osc2CentValue);
        osc2Cent.setButtonText(String(osc2CentValue));
    }
    else if (button == &osc2CentDown)
    {
        osc2CentValue = oscCentValueChange("down", osc2CentValue);
        osc2Cent.setButtonText(String(osc2CentValue));
    }
    else if (button == &osc2FineDown)
    {
        osc2FineValue = oscFineValueChange("up", &osc2Fine, &osc2CentValue, osc2FineValue);
        osc2Fine.setButtonText(String(osc2FineValue));
    }
    else if (button == &osc2FineDown)
    {
        osc2FineValue = oscFineValueChange("down", &osc2Fine, &osc2CentValue, osc2FineValue);
        osc2Fine.setButtonText(String(osc2FineValue));
    }
}

int Oscillator::oscCentValueChange(String command, int centVal)
{   
    if (command == "up")
    {
        if (centVal < 99)
        {
            centVal++;
        }
    }
    if (command == "down")
    {
        if (centVal > -99)
        {
            centVal--;
        }
    }
    return centVal;
}

int Oscillator::oscFineValueChange(String command, TextButton* cent, int* centVal, int fineVal)
{
    if (command == "up")
    {
        if (fineVal < 99)
        {
            fineVal++;
        }
        else
        {
            fineVal = 0;
            int currentCentVal = *centVal;
            int newCentVal = oscCentValueChange("up", currentCentVal);
            *centVal = newCentVal;
            cent->setButtonText(String(newCentVal));
        }
    }
    if (command == "down")
    {
        if (fineVal > -99)
        {
            fineVal--;
        }
        else
        {
            fineVal = 0;
            int currentCentVal = *centVal;
            int newCentVal = oscCentValueChange("down", currentCentVal);
            *centVal = newCentVal;
            cent->setButtonText(String(newCentVal));
        }
    }
    return fineVal;
}

void Oscillator::sliderValueChanged(Slider* slider)
{
    repaint();
}

void Oscillator::paint(Graphics& g)
{
    // Text Font
    g.setFont(Font("Avenir", 20.0f, Font::bold));

    // Create component borders
    juce::Rectangle <float> box1area(0, 0, getWidth() / 2 - 1.5f, getHeight());
    juce::Rectangle <float> box2area(getWidth() / 2 + 1.5f, 0, getWidth() / 2 - 1.5f, getHeight());
    juce::Rectangle <float> box1title(0, 0, getWidth() / 2 - 1.5f, 25);
    juce::Rectangle <float> box2title(getWidth() / 2 + 1.5f, 0, getWidth() / 2 - 1.5f, 25);
    g.setColour(Colours::darkgrey);
    g.fillRect(box1area);
    g.fillRect(box2area);
    g.setColour(Colours::grey);
    g.fillRect(box1title);
    g.fillRect(box2title);
    //g.setColour(Colours::maroon);
    //g.drawRect(box1area);
    //g.drawRect(box2area);

    // Create component title
    juce::Rectangle<int> title1Area(5, 5, getWidth() / 2 - 5, 40);
    juce::Rectangle<int> title2Area(getWidth() / 2 + 5 + 5, 5, getWidth() / 2 - 5, 40);
    g.setColour(Colours::black);
    g.drawText("osc 1", title1Area, Justification::topLeft);
    g.drawText("osc 2", title2Area, Justification::topLeft);

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

    //g.setColour(Colours::maroon);
    //g.drawRect(osc1);

    //g.setColour(Colours::maroon);
    //g.drawRect(osc2);

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

    p1.scaleToFit(.005*osc1Image.getWidth(), .025*osc1Image.getHeight(), .99*osc1Image.getWidth(), .95*osc1Image.getHeight(), false);

    osc1Image.multiplyAllAlphas(0);

    osc1Graphic->setColour(Colours::white);
    osc1Graphic->strokePath(p1, PathStrokeType(1.0f + max / 2));

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

    p2.scaleToFit(.005*osc2Image.getWidth(), .025*osc2Image.getHeight(), .99*osc2Image.getWidth(), .95*osc2Image.getHeight(), false);

    osc2Image.multiplyAllAlphas(0);

    osc2Graphic->setColour(Colours::white);
    osc2Graphic->strokePath(p2, PathStrokeType(1.0f + max / 2));
    
    g.drawImageAt(osc1Image, 10, 35);
    g.drawImageAt(osc2Image, getWidth() / 2 + 15, 35);
}

void Oscillator::resized()
{
    juce::Rectangle<int> area = getLocalBounds();

    // Position component variables
    //waveformSelect.setBounds(40, 60, 100, 50);
    osc1WtSlider.setBounds(30, 270, 55, 60);
    osc2WtSlider.setBounds(getWidth() - 30 - 60, 270, 55, 60);
    osc1GainSlider.setBounds(120, 270, 55, 60);
    osc2GainSlider.setBounds(getWidth() - 120 - 60, 270, 55, 60);
    //osc1PitchSlider.setBounds(210, 285, 70, 40);
    osc1CentUp.setBounds(250, 265, 70, 40);
    osc1Cent.setBounds(240, 280, 70, 40);
    osc1CentDown.setBounds(250, 313, 70, 40);
    osc1FineUp.setBounds(285, 265, 70, 40);
    osc1Fine.setBounds(275, 280, 70, 40);
    osc1FineDown.setBounds(285, 313, 70, 40);
    //osc2PitchSlider.setBounds(getWidth() - 210 - 70, 285, 70, 40);
    osc2CentUp.setBounds(getWidth() - 200 - 70, 265, 70, 40);
    osc2Cent.setBounds(getWidth() - 210 - 70, 280, 70, 40);
    osc2CentDown.setBounds(getWidth() - 200 - 70, 313, 70, 40);
    osc2FineUp.setBounds(getWidth() - 165 - 70, 265, 70, 40);
    osc2Fine.setBounds(getWidth() - 175 - 70, 280, 70, 40);
    osc2FineDown.setBounds(getWidth() - 165 - 70, 313, 70, 40);
}

