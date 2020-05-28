/*
  ==============================================================================
    SynthVoice.h
    Author:  MHENDER4
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "Filtered.h"

//==============================================================================

class SynthVoice : public SynthesiserVoice
{
public:
    SynthVoice()
    {
    //===== Setup Waveforms =====//
        // Sine
        for (int i = 0; i < wtSize; i++)
        {
            sineTable.insert(i, sin(2.0 * double_Pi * i / wtSize));
        }

        // Square
        for (int i = 0; i < wtSize; i++)
        {
            if (sin(2.0 * double_Pi * i / wtSize) > 0)
            {
                double val = (1 - 1) * (double_Pi / (2 * wtSize));
                squareTable.insert(i, 1);
            }
            else if (sin(2.0 * double_Pi * i / wtSize) < 0)
            {
                double val = (-1 - 1) * (double_Pi / (2 * wtSize));
                squareTable.insert(i, -1);
            }
            else
            {
                double val = (0 - 1) * (double_Pi / (2 * wtSize));
                squareTable.insert(i, 0);
            }
        }

        // Sawtooth
        double saw_increment = 2 / wtSize;
        double saw_count = 0;
        for (int i = 0; i < wtSize; i++)
        {
            sawTable.insert(i, (2 - saw_count) - 1);
            saw_count = saw_count + saw_increment;
        }

        // Triangle
        double tri_increment = 4 / wtSize;
        double tri_count = 0;
        for (int i = 0; i < wtSize; i++)
        {
            if (i < (wtSize / 2))
            {
                triTable.insert(i, tri_count - 1);
                tri_count = tri_count + tri_increment;
            }
            else if (i == (wtSize / 2))
            {
                triTable.insert(i, 1);
                tri_count = tri_count - tri_increment;
            }
            else
            {
                triTable.insert(i, tri_count - 1);
                tri_count = tri_count - tri_increment;
            }
        }

        // Sine to triangle
        for (int i = 0; i < wtSize; i++)
        {
            sine2tri.insert(i, triTable[i] - sineTable[i]);
        }

        // Triangle to square
        for (int i = 0; i < wtSize; i++)
        {
            tri2square.insert(i, squareTable[i] - triTable[i]);
        }

        // Square to saw
        for (int i = 0; i < wtSize; i++)
        {
            square2saw.insert(i, sawTable[i] - squareTable[i]);
        }                                   
    }

    void prepare(float blockSize, float sampleRate, float numChannels)
    {
    }

    bool canPlaySound(SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }

    //===== MIDI INFO =====//

    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        vel = velocity;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        osc1phase = 0.0;
        osc2phase = 0.0;
        getSampleRate();
        osc1increment = (frequency * osc1Pitch) * wtSize / sampleRate;
        osc2increment = (frequency * osc2Pitch) * wtSize / sampleRate;
        waveTable1.clear();
        waveTable2.clear();

        for (int i = 0; i < wtSize; i++)
        {
            // Wavetable 1
            if (osc1WtVal <= 100)
            {
                waveTable1.insert(i, (sineTable[i] + ((sine2tri[i] / 100) * osc1WtVal)) * osc1Gain);
            }
            else if (osc1WtVal <= 200)
            {
                waveTable1.insert(i, (triTable[i] + ((tri2square[i] / 100) * (osc1WtVal-100))) * osc1Gain);
            }
            else if (osc1WtVal <= 300)
            {
                waveTable1.insert(i, (squareTable[i] + ((square2saw[i] / 100) * (osc1WtVal-200))) * osc1Gain);
            }
            // Wavetable 2
            if (osc2WtVal <= 100)
            {
                waveTable2.insert(i, (sineTable[i] + ((sine2tri[i] / 100) * osc2WtVal)) * osc2Gain);
            }
            else if (osc2WtVal <= 200)
            {
                waveTable2.insert(i, (triTable[i] + ((tri2square[i] / 100) * (osc2WtVal-100))) * osc2Gain);
            }
            else if (osc2WtVal <= 300)
            {
                waveTable2.insert(i, (squareTable[i] + ((square2saw[i] / 100) * (osc2WtVal-200))) * osc2Gain);
            }
        }
        myADSR.noteOn();
    }

    void stopNote(float velocity, bool allowTailOff)
    {
        allowTailOff = true;
        myADSR.noteOff();

        if (velocity == 0)
        {
            clearCurrentNote();
        }
    }

    void pitchWheelMoved(int newPitchWheelValue)
    {
    }

    void controllerMoved(int controllerMoved, int newControllerValue)
    {
    }

    //===== PARAMETERS =====//

    void getOsc1(std::atomic<float>* gain, std::atomic<float>* wtVal, std::atomic<float>* oscpitch)
    {
        osc1GainRaw = *gain;
        osc1Gain = Decibels::decibelsToGain(osc1GainRaw);
        osc1WtVal = *wtVal;
        osc1Pitch = *oscpitch;
    }
    
    void getOsc2(std::atomic<float>* gain, std::atomic<float>* wtVal, std::atomic<float>* oscpitch)
    {
        osc2GainRaw = *gain;
        osc2Gain = Decibels::decibelsToGain(osc2GainRaw);
        osc2WtVal = *wtVal;
        osc2Pitch = *oscpitch;
    }

    void getMasterGain(std::atomic<float>* lastGain)
    {
        masterGainRaw = *lastGain;
        masterGain = Decibels::decibelsToGain(masterGainRaw);
    }

    void getEnvelopeParams(std::atomic<float>* attack, std::atomic<float>* decay, std::atomic<float>* sustain, std::atomic<float>* release)
    {
        adsrParams.attack = *attack;
        adsrParams.decay = *decay;
        adsrParams.sustain = *sustain;
        adsrParams.release = *release;
    }

    void setADSRSampleRate(double sampleRate)
    {
        myADSR.setSampleRate(sampleRate);
    }

    void setVoiceSampleRate(double lastSampleRate)
    {
        sampleRate = lastSampleRate;
    }

    void getFilt1(/*float* onoff, float* filt,*/ std::atomic<float>* cutoff)
    {
        //filt1OnOff = *onoff;
        //filt1Filt = *filt ;
        filt1Cutoff = *cutoff;
    }

        void getFilt2(/*float* onoff, float* filt,*/ std::atomic<float>* cutoff)
    {
        //filt1OnOff = *onoff;
        //filt1Filt = *filt ;
        filt2Cutoff = *cutoff;
    }

    void getDist1(std::atomic<float>* onoff, std::atomic<float>* inputGain, std::atomic<float>* outputGain, std::atomic<float>* drywet)
    {
        dist1OnOff = *onoff;
        dist1InputGainRaw = *inputGain;
        dist1OutputGainRaw = *inputGain;
        dist1InputGain = Decibels::decibelsToGain(dist1InputGainRaw);
        dist1OutputGain = Decibels::decibelsToGain(dist1OutputGainRaw);
        dist1DryWet = *drywet/100;
    }

    //===== RENDER OUTPUT =====//

    void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSample)
    {
        myADSR.setParameters(adsrParams);

        //===== MAIN AUDIO BLOCK =====//
        for (int sample = 0; sample < numSample; sample++)
        {
            for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
            {
                outputBuffer.addSample(channel, startSample, (myADSR.getNextSample() * vel * masterGain *
                    (waveTable1[(int)osc1phase] + waveTable2[(int)osc2phase])));
            }
            osc1phase = fmod((osc1phase + osc1increment), wtSize);
            osc2phase = fmod((osc2phase + osc2increment), wtSize);
            startSample++;
        }
        
        //===== APPLY FILTER =====//
        for (int sample = 0; sample < numSample; sample++) {
            outputBuffer.setSample(0, sample, processLoFilt.process(outputBuffer.getSample(0, sample), filt1Cutoff, 0));
            outputBuffer.setSample(1, sample, processLoFilt.process(outputBuffer.getSample(1, sample), filt1Cutoff, 0));
            outputBuffer.setSample(0, sample, processHiFilt.process(outputBuffer.getSample(0, sample), filt2Cutoff, 1));
            outputBuffer.setSample(1, sample, processHiFilt.process(outputBuffer.getSample(1, sample), filt2Cutoff, 1));
        }

        //===== APPLY DISTORTION =====//
        for (int sample = 0; sample < numSample; sample++) 
        {
            for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
            {
                float input_sample = outputBuffer.getSample(channel, sample);
                float cur_sample = input_sample;
                if (input_sample > 0)
                    cur_sample = 1 - exp(-(cur_sample * dist1InputGain));
                else
                    cur_sample = -1 + exp(cur_sample * dist1InputGain);
                cur_sample = (dist1DryWet * cur_sample) + ((1 - dist1DryWet) * input_sample);
                outputBuffer.setSample(channel, sample, cur_sample * dist1OutputGain);
            }
        } 
    }

private:
    // Master
    float masterGainRaw;
    float masterGain;
    double wtSize = 2048 * 8;

    // MIDI note
    double frequency;
    double osc1phase;
    double osc2phase;
    double osc1increment;
    double osc2increment;
    double vel;
    double sampleRate;

    // Wavetables
    Array<float> waveTable1;
    Array<float> waveTable2;
    Array<float> sineTable;
    Array<float> squareTable;
    Array<float> sawTable;
    Array<float> triTable;
    Array<float> sine2tri;
    Array<float> tri2square;
    Array<float> square2saw;

    // Osc
    float osc1WtVal;
    float osc2WtVal;
    float osc1GainRaw;
    float osc2GainRaw;
    float osc1Gain;
    float osc2Gain;
    float osc1Pitch;
    float osc2Pitch;

    // Filt
    float filt1Cutoff;
    float filt2Cutoff;

    // Dist
    bool dist1OnOff;
    float dist1InputGainRaw;
    float dist1OutputGainRaw;
    float dist1InputGain;
    float dist1OutputGain;
    float dist1DryWet;

    // ADSR
    ADSR myADSR;
    ADSR::Parameters adsrParams;
    Filtered processLoFilt;
    Filtered processHiFilt;
};