/*
  ==============================================================================
    PluginEditor.h
    Author:  MHENDER4
  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Envelope.h"
#include "Oscillator.h"
#include "Filter.h"
#include "Distortion.h"
#include "OscScope.h"
#include "Master.h"

//==============================================================================

class Wsynth_v1AudioProcessorEditor  : public AudioProcessorEditor,
    public Button::Listener
{
public:
    Wsynth_v1AudioProcessorEditor (Wsynth_v1AudioProcessor&);
    ~Wsynth_v1AudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;

private:
    Wsynth_v1AudioProcessor& processor;

    // Scope
    OscScope signalScope;

    // Master
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> masterGainVal;

    // Filter values
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> filt1OnOffVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filt1CutoffVal;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> filt1Val;
    //ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filt2CutoffVal;

    // Distortion values
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> dist1OnOffVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dist1InputGainVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dist1OutputGainVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dist1DryWetVal;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> dist1MethodVal;

    // Oscillator values
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc1WtVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc1GainVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc2WtVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc2GainVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc1PitchVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc2PitchVal;

    // Envelope values
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseVal;

    // Create synth components
    Master master;
    Filter filt1;
    //Filter filt2;
    Distortion dist1;
    Oscillator oscGui;
    Envelope envGui;

    // Create ADSR presets
    TextButton presetADSR1;
    TextButton presetADSR2;
    TextButton presetADSR3;
    TextButton presetADSR4;
    TextButton presetADSR5;
    TextButton presetADSR6;
    TextButton presetADSR7;
    
    void buttonClicked(Button* button) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Wsynth_v1AudioProcessorEditor)
};
