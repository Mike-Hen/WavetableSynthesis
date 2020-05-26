#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "SynthVoice.h"

//==============================================================================
/**
*/
class Wsynth_v1AudioProcessor  :	public AudioProcessor
{
public:
    //==============================================================================
    Wsynth_v1AudioProcessor();
    ~Wsynth_v1AudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
	SynthVoice* myVoice;
	Synthesiser mySynth;
	double volume;
	AudioProcessorValueTreeState tree;
	//void createFilters();
	//juce::dsp::FIR::Filter<float> alias1Filt;
	//juce::dsp::FIR::Filter<float> alias2Filt;
	int overSampleVal = 2;
	double lastSampleRate;

private:
	//juce::dsp::Oversampling<float> overSamp{ 2, overSampleVal, dsp::Oversampling<float>::filterHalfBandPolyphaseIIR, false };
	//juce::dsp::AudioBlock<float> upBlock;
	//juce::dsp::AudioBlock<float> downBlock;
	//juce::dsp::FIR::Filter<float> alias1Filt
	//{ dsp::FilterDesign<float>::designFIRLowpassWindowMethod(20000.0f, 48000 * 2, 300, dsp::WindowingFunction<float>::blackman) };
	//juce::dsp::FIR::Filter<float> alias2Filt
	//{ dsp::FilterDesign<float>::designFIRLowpassWindowMethod(20000.0f, 48000 * 2, 300, dsp::WindowingFunction<float>::blackman) };
	//juce::dsp::FIR::Filter<float> gibbs1Filt
	//{ dsp::FilterDesign<float>::designFIRLowpassWindowMethod(10000.0f, 48000 * 2, 60, dsp::WindowingFunction<float>::hann) };
	//juce::dsp::FIR::Filter<float> gibbs2Filt
	//{ dsp::FilterDesign<float>::designFIRLowpassWindowMethod(10000.0f, 48000 * 2, 60, dsp::WindowingFunction<float>::hann) };
    
	//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Wsynth_v1AudioProcessor)
};
