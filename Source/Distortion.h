/*
  ==============================================================================

	Distortion.h
	Created: 12 Jan 2020 4:14:23pm
	Author:  MHENDER4

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


class Distortion : public Component,
	public Button::Listener
{
public:
	Distortion(Wsynth_v1AudioProcessor&);
	~Distortion();

	void paint(Graphics&) override;
	void resized() override;

	void buttonClicked(Button* button) override;

	Slider inputGainSlider;
	Slider outputGainSlider;
	Slider dryWetSlider;
	TextButton distOnOff;

private:
	Wsynth_v1AudioProcessor& processor;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Distortion)
};