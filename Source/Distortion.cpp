/*
  ==============================================================================
    Distortion.cpp
    Author:  MHENDER4
  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Distortion.h"
#define _USE_MATH_DEFINES
#include "math.h"

//==============================================================================

Distortion::Distortion(Wsynth_v1AudioProcessor& p) : processor(p)
{
    setSize(300, 300); // Set component size

    // Design input gain slider
    inputGainSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    inputGainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 15);
    inputGainSlider.setTextBoxIsEditable(true);
    inputGainSlider.setColour(inputGainSlider.textBoxOutlineColourId, Colours::darkgrey);
    inputGainSlider.setNumDecimalPlacesToDisplay(1);
    inputGainSlider.setRange(-60.0, 0);
    inputGainSlider.setValue(0.0);
    inputGainSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(&inputGainSlider);

    // Design output gain slider
    outputGainSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    outputGainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 15);
    outputGainSlider.setTextBoxIsEditable(true);
    outputGainSlider.setColour(outputGainSlider.textBoxOutlineColourId, Colours::darkgrey);
    outputGainSlider.setNumDecimalPlacesToDisplay(1);
    outputGainSlider.setRange(-20.0, 20.0);
    outputGainSlider.setValue(0.0);
    outputGainSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(&outputGainSlider);

    // Design dry/wet slider
    dryWetSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    dryWetSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 15);
    dryWetSlider.setTextBoxIsEditable(true);
    dryWetSlider.setColour(dryWetSlider.textBoxOutlineColourId, Colours::darkgrey);
    dryWetSlider.setNumDecimalPlacesToDisplay(0);
    dryWetSlider.setRange(0.0, 100.0);
    dryWetSlider.setValue(0.0);
    dryWetSlider.setTextValueSuffix(" %");
    addAndMakeVisible(&dryWetSlider);
    
    // method select combo box
    String method1 = "soft";
    String method2 = "mid";
    String method3 = "hard";
    methodSelect.addItem(method1, 1);
    methodSelect.addItem(method2, 2);
    methodSelect.addItem(method3, 3);
    methodSelect.setSelectedItemIndex(0, true);
    addAndMakeVisible(methodSelect);

    // Design distortion on/off button
    //distOnOff.setSize(50, 50);
    //distOnOff.setClickingTogglesState(true);
    //distOnOff.setButtonText("Off");
    //distOnOff.setColour(TextButton::ColourIds::buttonColourId, Colours::red);
    //distOnOff.addListener(this);
    //addAndMakeVisible(distOnOff);

    startTimer(1000/20);

    distortionImage = Image(juce::Image::ARGB, 220, 100, true);
    distortionGraphic = new Graphics(distortionImage);
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

void Distortion::timerCallback()
{
    repaint();
}

Array<float> Distortion::getDistortionCurve(int distLength)
{
    Array<float> curve;
    if (methodSelect.getSelectedId() == 1)
    {
        for (int i = distLength; i > 0; i--)
        {
            curve.add(tanh(-2.5 + 0.005 * i));
        }
    }
    else if (methodSelect.getSelectedId() == 2)
    {
        for (int i = distLength; i > 0; i--)
        {
            double value = erf((sqrt(M_PI) / 1) * (-2.5 + 0.005 * i));
            curve.add(value);
        }
    }
    else if (methodSelect.getSelectedId() == 3)
    {
        for (int i = distLength; i > 0; i--)
        {
            double value = erf((sqrt(M_PI) / 0.5) * (-2.5 + 0.005 * i));
            curve.add(value);
        }
    }
    return curve;
}

void Distortion::paint(Graphics& g)
{
    // Create Background
    juce::Rectangle <float> background(0, 0, 320, 220);
    g.setColour(Colours::darkgrey);
    g.fillRect(background);

    // Create Title Background
    juce::Rectangle <float> titleBack(0, 0, 320, 25);
    g.setColour(Colours::grey);
    g.fillRect(titleBack);

    // Create component title
    juce::Rectangle<int> titleArea(0, 5, getWidth(), 40);
    g.setColour(Colours::black);
    g.drawText("Distortion", titleArea, Justification::centredTop);

    // Create component border
    juce::Rectangle <float> border(0, 0, 320, 220);
    g.setColour(Colours::maroon);
    g.drawRect(border);

    // Draw distortion curve border
    juce::Rectangle <float> scope(10, 110, distortionImage.getWidth(), distortionImage.getHeight());
    g.setColour(Colours::black);
    g.fillRect(scope);

    // Draw Grid Lines
    juce::Line <float> xaxis(juce::Point<float>(10, (110 + (distortionImage.getHeight() / 2))), juce::Point<float>(10 + distortionImage.getWidth(), (110 + (distortionImage.getHeight() / 2))));
    juce::Line <float> yaxis(juce::Point<float>(10 + (distortionImage.getWidth() / 2), 110), juce::Point<float>(10 + (distortionImage.getWidth() / 2), (110 + distortionImage.getHeight())));
    g.setColour(Colours::white);
    g.drawLine(xaxis, 0.3f);
    g.drawLine(yaxis, 0.3f);
    g.setColour(Colours::grey);
    g.drawRect(scope);

    Path p;
    float max = 0;
    Array<float> distCurve = getDistortionCurve(1000);
    
    for (int i = 0; i < distortionImage.getWidth(); i++)
    {
        int scaledIndex = float(i*distCurve.size()) / float(distortionImage.getWidth());
        float val = distCurve[scaledIndex];
        float distThreshold = Decibels::decibelsToGain(inputGainSlider.getValue());
        val = jlimit<float>(-distThreshold, distThreshold, val);

        if (i == 0)
        {
            p.startNewSubPath(0, 1);
            p.startNewSubPath(0, -1);
            p.startNewSubPath(0, val);
        }
        else p.lineTo(i, val);
    }

    p.scaleToFit(0, .05*distortionImage.getHeight(), distortionImage.getWidth(), .9*distortionImage.getHeight(), false);

    distortionImage.multiplyAllAlphas(0);

    distortionGraphic->setColour(Colours::white);
    distortionGraphic->strokePath(p, PathStrokeType(1.0f + max / 2));
    
    g.drawImageAt(distortionImage, 10, 110);

}

void Distortion::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(50);

    // Position component variables
    //distOnOff.setBounds(10, 10, 100, 30);
    inputGainSlider.setBounds(30, 30, 60, 70);
    dryWetSlider.setBounds(150, 30, 60, 70);
    outputGainSlider.setBounds(240, 140, 60, 70);
    methodSelect.setBounds(240, 110, 65, 25);
}

