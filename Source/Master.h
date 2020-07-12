/*
  ==============================================================================

    Master.h
    Author:  MHENDER4

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "OtherLookAndFeel.h"

//==============================================================================
/*
*/
class Master    : public Component,
    public Timer
{
public:
    Master(Wsynth_v1AudioProcessor&);
    ~Master();

    void paint (Graphics&) override;
    void resized() override;

    void timerCallback() override;
    float getLevelLeft();
    float getLevelRight();

    OtherLookAndFeel otherLookAndFeel;

    Slider gainSlider;
    Label volumeLabel;

    Image masterLevelImageLeft;
    Image masterLevelImageRight;

private:
    Wsynth_v1AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Master)
};
