/*
  ==============================================================================

	LFO.cpp
	Created: 11 Jan 2018 2:31:07pm
	Author:  Joshua Hodge

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "LFO.h"

//==============================================================================
LFO::LFO(Wsynth_v1AudioProcessor& p) :
	processor(p)
{
	setSize(200, 160);
	
	lfoFreqSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	lfoFreqSlider.setRange(0.1, 2000.0);
	lfoFreqSlider.setValue(0.0);
	lfoFreqSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
	addAndMakeVisible(&lfoFreqSlider);

	lfoAmpSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	lfoAmpSlider.setRange(0.1, 2000.0);
	lfoAmpSlider.setValue(0.0);
	lfoAmpSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
	addAndMakeVisible(&lfoAmpSlider);
}

LFO::~LFO()
{
}

void LFO::paint(Graphics& g)
{
	juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

	g.fillAll(Colours::black);
	juce::Rectangle <float> area(0, 0, 150, 80);

	g.setColour(Colours::maroon);
	g.drawRect(area);
}

void LFO::initLFO(float sr, float wt)
{
	sampleRate = sr;
	wtSize = wt;
	for (int i = 0; i < wtSize; i++)
	{
		sineTable.insert(i, sin(2.0 * double_Pi * i / wtSize));
	}
	phase = 0.0;
}

float LFO::modulate(float input)
{
	increment = lfoFreqSlider.getValue() * wtSize / sampleRate;
	output = input * sineTable[(int)phase];
	phase = fmod((phase + increment), wtSize);
	return output;
}

void LFO::resized()
{
	lfoFreqSlider.setBounds(10, 0, 60, 100);
	lfoAmpSlider.setBounds(80, 0, 60, 100);
}



