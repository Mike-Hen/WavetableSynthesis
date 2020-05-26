/*
  ==============================================================================

	Filter.h
	Created: 12 Jan 2020 4:14:23pm
	Author:  MHENDER4

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


class Filter : public Component,
	public Button::Listener
{
public:
	Filter(Wsynth_v1AudioProcessor&);
	~Filter();

	void paint(Graphics&) override;
	void resized() override;

	void buttonClicked(Button* button) override;

	Slider cutoffSlider;
	ComboBox filterSelect;
	TextButton filtOnOff;

private:
	Wsynth_v1AudioProcessor& processor;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Filter)
};