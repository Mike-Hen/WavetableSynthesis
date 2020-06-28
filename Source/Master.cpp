/*
  ==============================================================================

    Master.cpp
    Created: 11 Jun 2020 5:47:03pm
    Author:  MHENDER4

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Master.h"

//==============================================================================
Master::Master(Wsynth_v1AudioProcessor& p) :
    processor(p)
{
    setSize(320, 140);

    //===== Master gain =====//
    gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    gainSlider.setTextBoxIsEditable(true);
    gainSlider.setColour(gainSlider.textBoxOutlineColourId, Colours::darkgrey);
    gainSlider.setNumDecimalPlacesToDisplay(1);
    gainSlider.setRange(-60.0, 6.0);
    gainSlider.setValue(-12.0);
    gainSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(gainSlider);

    masterLevelImageLeft = Image(juce::Image::ARGB, 15, 60, true);
    masterLevelImageRight = Image(juce::Image::ARGB, 15, 60, true);

    startTimer(1000 / 100);

}

Master::~Master()
{
}

void Master::timerCallback()
{
    repaint();
}

float Master::getLevelLeft()
{
    Array<float> levelLeft = processor.getMasterLevel(0);
    float sumLevel;
    double backupLevel = 0.00001;
    int countL = 0;
    for (int i = 0; i < levelLeft.size(); i++)
    {
        if (levelLeft[i] > 0)
        {
            sumLevel += levelLeft[i];
            countL++;
        }
        else
        {
            sumLevel += backupLevel;
            countL++;
        }
    }
    float dbLevel = Decibels::gainToDecibels(sumLevel / countL);
    return dbLevel;
}

float Master::getLevelRight()
{
    Array<float> levelRight = processor.getMasterLevel(1);
    float sumLevel;
    double backupLevel = 0.00001;
    int countR = 0;
    for (int i = 0; i < levelRight.size(); i++)
    {
        if (levelRight[i] > 0)
        {
            sumLevel += levelRight[i];
            countR++;
        }
        else
        {
            sumLevel += backupLevel;
            countR++;
        }
    }
    float dbLevel = Decibels::gainToDecibels(sumLevel / countR);
    return dbLevel;
}

void Master::paint (Graphics& g)
{
    // Text Font
    g.setFont(Font("Avenir", 20.0f, Font::bold));

    // Create Background
    juce::Rectangle <float> background(0, 0, getWidth(), getHeight());
    g.setColour(Colours::darkgrey);
    g.fillRect(background);

    // Create Title Background
    juce::Rectangle <float> titleBack(0, 0, getWidth(), 25);
    g.setColour(Colours::grey);
    g.fillRect(titleBack);

    // Create component title
    juce::Rectangle<int> titleArea(0, 5, getWidth(), 40);
    g.setColour(Colours::black);
    g.drawText("master", titleArea, Justification::centredTop);

    // Create component border
    juce::Rectangle <float> border(0, 0, getWidth(), getHeight());
    //g.setColour(Colours::maroon);
   // g.drawRect(border);

    // Draw master level border
    juce::Rectangle <float> levelLeft(100, 45, masterLevelImageLeft.getWidth(), masterLevelImageLeft.getHeight());
    g.setColour(Colours::black);
    g.fillRect(levelLeft);
    g.setColour(Colours::grey);
    g.drawRect(levelLeft);

    // Draw master level border
    juce::Rectangle <float> levelRight(118, 45, masterLevelImageRight.getWidth(), masterLevelImageRight.getHeight());
    g.setColour(Colours::black);
    g.fillRect(levelRight);
    g.setColour(Colours::grey);
    g.drawRect(levelRight);

    juce::Rectangle <float> gainLeftLow(100 + 2, 45 + 2, masterLevelImageLeft.getWidth() - 4, masterLevelImageLeft.getHeight() - 4);
    g.setColour(Colours::limegreen);
    g.fillRect(gainLeftLow);

    juce::Rectangle <float> gainLeftMid(100 + 2, 45 + 2, masterLevelImageLeft.getWidth() - 4, masterLevelImageLeft.getHeight() - 4 - 47);
    g.setColour(Colours::yellow);
    g.fillRect(gainLeftMid);

    juce::Rectangle <float> gainLeftHigh(100 + 2, 45 + 2, masterLevelImageLeft.getWidth() - 4, masterLevelImageLeft.getHeight() - 4 - 53);
    g.setColour(Colours::red);
    g.fillRect(gainLeftHigh);

    juce::Rectangle <float> gainRightLow(118 + 2, 45 + 2, masterLevelImageRight.getWidth() - 4, masterLevelImageRight.getHeight() - 4);
    g.setColour(Colours::limegreen);
    g.fillRect(gainRightLow);

    juce::Rectangle <float> gainRightMid(118 + 2, 45 + 2, masterLevelImageLeft.getWidth() - 4, masterLevelImageLeft.getHeight() - 4 - 47);
    g.setColour(Colours::yellow);
    g.fillRect(gainRightMid);

    juce::Rectangle <float> gainRightHigh(118 + 2, 45 + 2, masterLevelImageLeft.getWidth() - 4, masterLevelImageLeft.getHeight() - 4 - 53);
    g.setColour(Colours::red);
    g.fillRect(gainRightHigh);

    g.drawImageAt(masterLevelImageLeft, 100, 45);
    g.drawImageAt(masterLevelImageRight, 118, 45);

    float currentLevelLeft = getLevelLeft();
    if (currentLevelLeft > -60.0f)
    {
        juce::Rectangle <float> gainL(100 + 2, 45 + 2, masterLevelImageLeft.getWidth() - 4, -currentLevelLeft);
        g.setColour(Colours::black);
        g.fillRect(gainL);
    }
    else
    {
        juce::Rectangle <float> blankGainL(100 + 2, 45 + 2, masterLevelImageLeft.getWidth() - 4, masterLevelImageLeft.getHeight() - 4);
        g.setColour(Colours::black);
        g.fillRect(blankGainL);
    }

    float currentLevelRight = getLevelRight();
    if (currentLevelRight > -60.0f)
    {
        juce::Rectangle <float> gainR(118 + 2, 45 + 2, masterLevelImageRight.getWidth() - 4, -currentLevelRight);
        g.setColour(Colours::black);
        g.fillRect(gainR);
    }
    else
    {
        juce::Rectangle <float> blankGainR(118 + 2, 45 + 2, masterLevelImageRight.getWidth() - 4, masterLevelImageRight.getHeight() - 4);
        g.setColour(Colours::black);
        g.fillRect(blankGainR);
    }
}

void Master::resized()
{
    gainSlider.setBounds(5, 38, 75, 100);
}
