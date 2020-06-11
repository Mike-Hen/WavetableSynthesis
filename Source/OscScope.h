/*
  ==============================================================================

    OscScope.h
    Author:  MikeHen

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class OscScope : public Component,
    public Timer
{
public:
    OscScope(Wsynth_v1AudioProcessor&);
    ~OscScope();

    void paint (Graphics&) override;
    void resized() override;

    void timerCallback() override;


    Image historyImage;
    ScopedPointer<Graphics> historyGraphic;


private:
    Wsynth_v1AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscScope)
};
