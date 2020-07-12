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
#include "Wavetable.h"
#include <complex> 
#define _USE_MATH_DEFINES
#include "math.h"

//==============================================================================

class SynthVoice : public SynthesiserVoice
{
public:
    SynthVoice()
    {
        osc1WtVal.store(-1);
        osc2WtVal.store(-1);
        //oversamp->initProcessing(480);
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
        float saw_increment = 2.0f / wtSize;
        float saw_count = 0;
        for (int i = 0; i < wtSize; i++)
        {
            sawTable[i] = (2 - saw_count) - 1;
            saw_count = saw_count + saw_increment;
        }

        // Triangle
        double tri_increment = 4.0f / wtSize;
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

    Array<float> getOsc1WaveShape()
    {
        Array<float> osc1WaveShape;
        for (int i = 0; i < wtSize; i++)
        {
            // Wavetable 1
            if (osc1WtVal <= 100)
            {
                osc1WaveShape.insert(i, (sineTable[i] + ((sine2tri[i] / 100) * osc1WtVal)));
            }
            else if (osc1WtVal <= 200)
            {
                osc1WaveShape.insert(i, (triTable[i] + ((tri2square[i] / 100) * (osc1WtVal - 100))));
            }
            else if (osc1WtVal <= 300)
            {
                osc1WaveShape.insert(i, (squareTable[i] + ((square2saw[i] / 100) * (osc1WtVal - 200))));
            }
        }
        return osc1WaveShape;
    }


    Array<float> getOsc2WaveShape()
    {
        Array<float> osc2WaveShape;
        for (int i = 0; i < wtSize; i++)
        {
            // Wavetable 1
            if (osc2WtVal <= 100)
            {
                osc2WaveShape.insert(i, (sineTable[i] + ((sine2tri[i] / 100) * osc2WtVal)));
            }
            else if (osc2WtVal <= 200)
            {
                osc2WaveShape.insert(i, (triTable[i] + ((tri2square[i] / 100) * (osc2WtVal - 100))));
            }
            else if (osc2WtVal <= 300)
            {
                osc2WaveShape.insert(i, (squareTable[i] + ((square2saw[i] / 100) * (osc2WtVal - 200))));
            }
        }
        return osc2WaveShape;
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
        osc1BLWT = osc1WT.selectWavetable(frequency);
        osc2BLWT = osc2WT.selectWavetable(frequency);
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
        osc1Gain = Decibels::decibelsToGain(gain->load());
        std::atomic<float> waveTable1Value;
        waveTable1Value.store(*wtVal);
        osc1Pitch.store(*oscpitch);
        if (waveTable1Value.load() != osc1WtVal)
        {
            osc1WtVal.store(*wtVal);
            for (int i = 0; i < wtSize; i++)
            {
                // Wavetable 1
                if (osc1WtVal <= 100)
                {
                    waveTable1[i] = (sineTable[i] + ((sine2tri[i] / 100) * osc1WtVal));
                }
                else if (osc1WtVal <= 200)
                {
                    waveTable1[i] = (triTable[i] + ((tri2square[i] / 100) * (osc1WtVal - 100)));
                }
                else if (osc1WtVal <= 300)
                {
                    waveTable1[i] = (squareTable[i] + ((square2saw[i] / 100) * (osc1WtVal - 200)));
                }
            }
            osc1WT.generateWavetable(waveTable1, wtSize);
        }
    }
    
    void getOsc2(std::atomic<float>* gain, std::atomic<float>* wtVal, std::atomic<float>* oscpitch)
    {
        osc2Gain = Decibels::decibelsToGain(gain->load());
        std::atomic<float> waveTable2Value;
        waveTable2Value.store(*wtVal);
        osc2Pitch.store(*oscpitch);
        if (waveTable2Value.load() != osc2WtVal)
        {
            osc2WtVal.store(*wtVal);
            for (int i = 0; i < wtSize; i++)
            {
                // Wavetable 2
                if (osc2WtVal <= 100)
                {
                    waveTable2[i] = (sineTable[i] + ((sine2tri[i] / 100) * osc2WtVal));
                }
                else if (osc2WtVal <= 200)
                {
                    waveTable2[i] = (triTable[i] + ((tri2square[i] / 100) * (osc2WtVal - 100)));
                }
                else if (osc2WtVal <= 300)
                {
                    waveTable2[i] = (squareTable[i] + ((square2saw[i] / 100) * (osc2WtVal - 200)));
                }
            }
            osc2WT.generateWavetable(waveTable2, wtSize);
        }
    }

    void getMasterGain(std::atomic<float>* lastGain)
    {
        masterGain = Decibels::decibelsToGain(lastGain->load());
    }

    void getEnvelopeParams(std::atomic<float>* attack, std::atomic<float>* decay, std::atomic<float>* sustain, std::atomic<float>* release)
    {
        adsrParams.attack = attack->load();
        adsrParams.decay = decay->load();
        adsrParams.sustain = sustain->load();
        adsrParams.release = release->load();
    }

    void setADSRSampleRate(double sampleRate)
    {
        myADSR.setSampleRate(sampleRate);
    }

    void setVoiceSampleRate(double lastSampleRate)
    {
        sampleRate = lastSampleRate;
    }

    void getFilt1(std::atomic<float>* cutoff)
    {
        filt1Cutoff.store(*cutoff);
    }
    void getDist1(/*std::atomic<float>* onoff,*/ std::atomic<float>* inputGain, std::atomic<float>* outputGain, std::atomic<float>* drywet, std::atomic<float>* distMethod)
    {
        //dist1OnOff.store(*onoff);
        dist1Method.store(*distMethod);
        dist1InputGain.store(Decibels::decibelsToGain(inputGain->load()));
        dist1OutputGain.store(Decibels::decibelsToGain(outputGain->load()));
        dist1DryWet.store(*drywet/100);
    }

    float applyDist1(float inputSample)
    {
        if (dist1Method == 1)
        {
            dist1CurSample = tanh(inputSample);
        }
        else if (dist1Method == 2)
        {
            dist1CurSample = erf((sqrt(M_PI) / 1) * inputSample);
        }
        else if (dist1Method == 3)
        {
            dist1CurSample = erf((sqrt(M_PI) / 0.5) * inputSample);
        }
        dist1CurSample = jlimit<float>(-dist1InputGain.load(), dist1InputGain.load(), dist1CurSample);
        dist1CurSample = (dist1DryWet.load() * dist1CurSample * dist1OutputGain.load()) + ((1 - dist1DryWet.load()) * inputSample);
        return dist1CurSample;
    }

    //===== RENDER OUTPUT =====//

    void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSample)
    {
        myADSR.setParameters(adsrParams);

        //int numOverSamples = numSample * oversampVal;
        //oversampleBuffer.setSize(2, numSample, false, true, true);
        //downsampleBuffer.setSize(2, numSample, false, true, true);

        //===== MAIN AUDIO BLOCK =====//
        for (int sample = 0; sample < numSample; sample++)
        {
            for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
            {
                //===== APPLY ADSR, VEL, Gain, Wavetable =====//
                if (osc1phase < 0)
                {
                    osc1phase = 0;
                }
                if (osc2phase < 0)
                {
                    osc2phase = 0;
                }
                if (std::floor(osc1phase) == osc1phase)
                {
                    osc1Interp = osc1BLWT[(int)osc1phase].real();
                }
                else if (std::floor(osc1phase) == osc1BLWT.size()-1)
                {
                    osc1Interp = osc1BLWT[(int)osc1phase].real();
                }
                else
                {
                    int osc1LowPhase = std::floor(osc1phase);
                    int osc1HighPhase = std::ceil(osc1phase);
                    osc1Interp = (osc1BLWT[osc1LowPhase].real() + osc1BLWT[osc1HighPhase].real()) / 2;
                }

                if (std::floor(osc2phase) == osc2phase)
                {
                    osc2Interp = osc2BLWT[(int)osc2phase].real();
                }
                else if (std::floor(osc2phase) == osc2BLWT.size() - 1)
                {
                    osc2Interp = osc2BLWT[(int)osc2phase].real();
                }
                else
                {
                    int osc2LowPhase = std::floor(osc2phase);
                    int osc2HighPhase = std::ceil(osc2phase);
                    osc2Interp = (osc2BLWT[osc2LowPhase].real() + osc2BLWT[osc2HighPhase].real()) / 2;
                }
                float nextSample = myADSR.getNextSample() * vel * masterGain * ((osc1Interp * osc1Gain) + (osc2Interp * osc2Gain));
                nextSample = applyDist1(nextSample);
                nextSample = processLoFilt.process(nextSample, filt1Cutoff.load(), 0);
                outputBuffer.addSample(channel, sample, nextSample);
            }
            osc1phase = fmod((osc1phase + osc1increment), wtSize);
            osc2phase = fmod((osc2phase + osc2increment), wtSize);
            startSample++;
        }

        //dsp::AudioBlock<float> oversampleBlock(oversampleBuffer);
        //oversamp->processSamplesUp(oversampleBlock);

        //dsp::AudioBlock<float> downsampleBlock(oversampleBuffer);
        //oversamp->processSamplesDown(downsampleBlock);
        //downsampleBlock.copyTo(outputBuffer);

        //dsp::AudioBlock<float> blockOut = overSampling->getOverSampleBuffer(targetBlock);
        //mWTsettings.bufferL = blockOut.getChannelPointer(0);
        //mWTsettings.bufferR = blockOut.getChannelPointer(1);
        //commonSoundGen(numSamples);
        //overSampling->downSample(targetBlock);
    }

private:
    // Master
    float masterGain;
    static const int wtSize = 4096;

    // MIDI note
    double frequency;
    double osc1phase;
    double osc2phase;
    double osc1increment;
    double osc2increment;
    double vel;
    double sampleRate;

    // Wavetables
    std::array<dsp::Complex<float>, wtSize> waveTable1;
    std::array<dsp::Complex<float>, wtSize> osc1BLWT;
    Wavetable osc1WT;
    std::array<dsp::Complex<float>, wtSize> waveTable2;
    std::array<dsp::Complex<float>, wtSize> osc2BLWT;
    Wavetable osc2WT;
    Array<float> sineTable;
    Array<float> squareTable;
    std::array<float, 4096> sawTable;
    Array<float> triTable;
    Array<float> sine2tri;
    Array<float> tri2square;
    Array<float> square2saw;

    // Osc
    std::atomic<float> osc1WtVal;
    std::atomic<float> osc2WtVal;
    std::atomic<float> osc1Gain;
    std::atomic<float> osc2Gain;
    std::atomic<float> osc1Pitch;
    std::atomic<float> osc2Pitch;
    float osc1Interp;
    float osc2Interp;

    // Filt
    std::atomic<float> filt1Cutoff;

    // Dist
    std::atomic<bool> dist1OnOff;
    std::atomic<float> dist1Method;
    std::atomic<float> dist1InputGain;
    std::atomic<float> dist1OutputGain;
    std::atomic<float> dist1DryWet;
    std::atomic<float> dist1CurSample;

    // ADSR
    ADSR myADSR;
    ADSR::Parameters adsrParams;
    Filtered processLoFilt;

    //Oversamp
    //AudioBuffer<float> oversampleBuffer;
    //AudioBuffer<float> downsampleBuffer;
    //const int oversampVal = 2;
    //dsp::Oversampling<float>* oversamp = new dsp::Oversampling<float>(2, oversampVal/2, dsp::Oversampling<float>::filterHalfBandFIREquiripple, false);
};