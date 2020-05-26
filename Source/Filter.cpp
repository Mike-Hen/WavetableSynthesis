/*
  ==============================================================================

	Filter.cpp
	Created: 12 Jan 2020 4:14:15pm
	Author:  MHENDER4

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

//==============================================================================
Filter::Filter(Wsynth_v1AudioProcessor& p) : processor(p)
{
	setSize(200, 200);

	cutoffSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	cutoffSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 200, 25);
	cutoffSlider.setTextBoxIsEditable(true);
	cutoffSlider.setNumDecimalPlacesToDisplay(0);
	cutoffSlider.setRange(0.0, 1.0);
	cutoffSlider.setValue(0.5);
	cutoffSlider.setTextValueSuffix(" ");
	addAndMakeVisible(&cutoffSlider);

	//String filter1 = "lo-pass";
	//String filter2 = "hi-pass";
	//filterSelect.addItem(filter1, 1);
	//filterSelect.addItem(filter2, 2);
	//filterSelect.setSelectedItemIndex(0, true);
	//addAndMakeVisible(filterSelect);

	//filtOnOff.setSize(50, 50);
	//filtOnOff.setClickingTogglesState(true);
	//filtOnOff.setButtonText("Off");
	//filtOnOff.setColour(TextButton::ColourIds::buttonColourId, Colours::red);
	//filtOnOff.addListener(this);
	//addAndMakeVisible(filtOnOff);
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
	juce::Rectangle<int> titleArea(0, 10, 120, 20);

	g.fillAll(Colours::black);
	g.setColour(Colours::white);
	g.drawText("Filter", titleArea, Justification::centredTop);

	juce::Rectangle <float> area(0, 0, 80, 120);

	g.setColour(Colours::maroon);
	g.drawRect(area);

}

void Filter::resized()
{
	juce::Rectangle<int> area = getLocalBounds().reduced(50);

	int sliderWidth = 75;
	int sliderHeight = 100;

	//draw sliders by reducing area from rectangle above
	//filtOnOff.setBounds(10, 10, 100, 30);
	//filterSelect.setBounds(10, 60, 100, 50);
	cutoffSlider.setBounds(10, 10, 60, 100);
	
}

//===============================================================