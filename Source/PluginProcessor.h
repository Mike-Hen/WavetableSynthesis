/*
  ==============================================================================
    PluginProcessor.h
    Author:  MHENDER4
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "SynthVoice.h"

//==============================================================================

class Wsynth_v1AudioProcessor  :    public AudioProcessor
{
public:

    Wsynth_v1AudioProcessor();
    ~Wsynth_v1AudioProcessor();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const String getName() const override;

    //==== MIDI Info ====//
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==== Program Info ====//
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==== State ====//
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==== Synth ====//
    SynthVoice* myVoice;    
    Synthesiser mySynth;

    //==== Synth Attributes ====//
    AudioProcessorValueTreeState tree;  // Value tree to hold synth parameter data
    double volume;                      // Main volume level
    double lastSampleRate;   

    //----- Scope -----//
    Array<float> history;
    int historyLength;
    Array<float> getHistory() 
    {
        return history;
    }

    Array<float> masterLevelLeft;
    Array<float> masterLevelRight;
    int masterLevelLength;
    Array<float> getMasterLevel(int channel)
    {
        if (channel == 0)
        {
            return masterLevelLeft;
        }
        else if (channel == 1)
        {
            return masterLevelRight;
        }
    }

    Array<float> osc1WaveShape;
    Array<float> returnOsc1WaveShape()
    {
        osc1WaveShape = myVoice->getOsc1WaveShape();
        return osc1WaveShape;
    }
    Array<float> osc2WaveShape;
    Array<float> returnOsc2WaveShape()
    {
        osc2WaveShape = myVoice->getOsc2WaveShape();
        return osc2WaveShape;
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Wsynth_v1AudioProcessor)
};
