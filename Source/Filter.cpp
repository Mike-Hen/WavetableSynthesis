/*
  ==============================================================================
    Filter.cpp
    Author:  MHENDER4
  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

//==============================================================================
Filter::Filter(Wsynth_v1AudioProcessor& p) : processor(p)
{
    setSize(320, 120); // Set component size

    // Design cutoff slider
    cutoffSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    cutoffSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
    cutoffSlider.setTextBoxIsEditable(true);
    cutoffSlider.setColour(cutoffSlider.textBoxOutlineColourId, Colours::darkgrey);
    cutoffSlider.setNumDecimalPlacesToDisplay(0);
    cutoffSlider.setRange(0.0, 1.0);
    cutoffSlider.setValue(0.5);
    cutoffSlider.setTextValueSuffix(" ");
    addAndMakeVisible(&cutoffSlider);

    /* Filter select combo box
    String filter1 = "lo-pass";
    String filter2 = "hi-pass";
    filterSelect.addItem(filter1, 1);
    filterSelect.addItem(filter2, 2);
    filterSelect.setSelectedItemIndex(0, true);
    addAndMakeVisible(filterSelect);
    */

    /* Filter on/off button
    filtOnOff.setSize(50, 50);
    filtOnOff.setClickingTogglesState(true);
    filtOnOff.setButtonText("Off");
    filtOnOff.setColour(TextButton::ColourIds::buttonColourId, Colours::red);
    filtOnOff.addListener(this);
    addAndMakeVisible(filtOnOff);
    */
}

Filter::~Filter()
{
}

void Filter::buttonClicked(Button* button)
{
    if (filtOnOff.getToggleState() == true)
    {
        filtOnOff.setButtonText("On");
        filtOnOff.setColour(TextButton::ColourIds::buttonColourId, Colours::limegreen);
    }
    else if (filtOnOff.getToggleState() == false)
    {
        filtOnOff.setButtonText("Off");
        filtOnOff.setColour(TextButton::ColourIds::buttonColourId, Colours::red);
    }
}

void Filter::paint(Graphics& g)
{
    // Text Font
    g.setFont(Font("Franklin Gothic", 20.0f, Font::bold));

    // Create Background
    juce::Rectangle <float> background(0, 0, 320, 120);
    g.setColour(Colours::darkgrey);
    g.fillRect(background);

    // Create Title Background
    juce::Rectangle <float> titleBack(0, 0, 320, 25);
    g.setColour(Colours::grey);
    g.fillRect(titleBack);

    // Create component title
    juce::Rectangle<int> titleArea(0, 5, 320, 40);
    g.setColour(Colours::black);
    g.drawText("Filter", titleArea, Justification::centredTop);

    // Create component border
    juce::Rectangle <float> area(0, 0, 320, 120);
    g.setColour(Colours::maroon);
    g.drawRect(area);

}

void Filter::resized()
{
    // Position component variables
    //filtOnOff.setBounds(10, 10, 100, 30);
    //filterSelect.setBounds(10, 60, 100, 50);
    cutoffSlider.setBounds(10, 30, 60, 80);
}