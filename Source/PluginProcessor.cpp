/*
  ==============================================================================
    PluginProcessor.cpp
    Author:  MHENDER4
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Wsynth_v1AudioProcessor::Wsynth_v1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    )
    , tree(*this, nullptr, "PARAMETERS",
        {    
            // ADSR
            std::make_unique<AudioParameterFloat>("attack", "Attack", NormalisableRange<float>(0.1f, 5.0f), 0.1f),
            std::make_unique<AudioParameterFloat>("decay", "Decay", NormalisableRange<float>(0.1f, 2.0f), 0.8f),
            std::make_unique<AudioParameterFloat>("sustain", "Sustain", NormalisableRange<float>(0.1f, 1.0f), 0.8f),
            std::make_unique<AudioParameterFloat>("release", "Release", NormalisableRange<float>(0.1f, 5.0f), 0.1f),
            // Gain
            std::make_unique<AudioParameterFloat>("mastergain", "MasterGain", -60.0f, 0.0f, -12.0f),
            // Oscillators
            std::make_unique<AudioParameterFloat>("osc1wt", "Osc1Wt", 0.0f, 300.0f, 0.0f),
            std::make_unique<AudioParameterFloat>("osc1gain", "Osc1Gain",  -60.0f, 0.0f, -12.0f),
            std::make_unique<AudioParameterFloat>("osc1pitch", "Osc1Pitch", 0.0f, 10.0f, 1.0f),
            std::make_unique<AudioParameterFloat>("osc2wt", "Osc2Wt", 0.0f, 300.0f, 0.0f),
            std::make_unique<AudioParameterFloat>("osc2gain", "Osc2Gain",  -60.0f, 0.0f, -60.0f),
            std::make_unique<AudioParameterFloat>("osc2pitch", "Osc2Pitch",  0.0f, 10.0f, 1.0f),
            // Filters
            std::make_unique<AudioParameterFloat>("filt1cutoff", "Filt1Cutoff",  0.1f, 1.0f, 1.0f),
            std::make_unique<AudioParameterFloat>("filt2cutoff", "Filt2Cutoff",  0.1f, 1.0f, 1.0f),

            std::make_unique<AudioParameterBool>("dist1onoff", "Dist1OnOff", false),
            std::make_unique<AudioParameterFloat>("dist1inputgain", "Dist1InputGain",  -20.0f, 20.0f, 0.0f),
            std::make_unique<AudioParameterFloat>("dist1outputgain", "Dist1OutputGain",  -20.0f, 20.0f, 0.0f),
            std::make_unique<AudioParameterFloat>("dist1drywet", "Dist1DryWet",  0.0f, 100.0f, 0.0f),
        })
#endif
{
    mySynth.clearVoices();

    for (int i = 0; i < 5; i++)
    {
        mySynth.addVoice(new SynthVoice());
    }

    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
}

Wsynth_v1AudioProcessor::~Wsynth_v1AudioProcessor()
{
}

//==============================================================================
const String Wsynth_v1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Wsynth_v1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Wsynth_v1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Wsynth_v1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Wsynth_v1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Wsynth_v1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Wsynth_v1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Wsynth_v1AudioProcessor::setCurrentProgram (int index)
{
}

const String Wsynth_v1AudioProcessor::getProgramName (int index)
{
    return {};
}

void Wsynth_v1AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Wsynth_v1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
    myVoice->prepare(samplesPerBlock, sampleRate, 2);
}

void Wsynth_v1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Wsynth_v1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Wsynth_v1AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
        {
            myVoice->setVoiceSampleRate(lastSampleRate);
            myVoice->setADSRSampleRate( lastSampleRate);

            myVoice->getEnvelopeParams( tree.getRawParameterValue("attack"),
                                        tree.getRawParameterValue("decay"),
                                        tree.getRawParameterValue("sustain"),
                                        tree.getRawParameterValue("release"));

            myVoice->getMasterGain(     tree.getRawParameterValue("mastergain"));

            myVoice->getOsc1(           tree.getRawParameterValue("osc1gain"), 
                                        tree.getRawParameterValue("osc1wt"), 
                                        tree.getRawParameterValue("osc1pitch"));

            myVoice->getOsc2(           tree.getRawParameterValue("osc2gain"), 
                                        tree.getRawParameterValue("osc2wt"), 
                                        tree.getRawParameterValue("osc2pitch"));
            myVoice->getFilt1(          tree.getRawParameterValue("filt1cutoff"));

            myVoice->getFilt2(          tree.getRawParameterValue("filt2cutoff"));

            myVoice->getDist1(          tree.getRawParameterValue("dist1onoff"), 
                                        tree.getRawParameterValue("dist1inputgain"),
                                        tree.getRawParameterValue("dist1outputgain"), 
                                        tree.getRawParameterValue("dist1drywet"));
        }
    }
    
    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool Wsynth_v1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Wsynth_v1AudioProcessor::createEditor()
{
    return new Wsynth_v1AudioProcessorEditor (*this);
}

//==============================================================================
void Wsynth_v1AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Wsynth_v1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Wsynth_v1AudioProcessor();
}
