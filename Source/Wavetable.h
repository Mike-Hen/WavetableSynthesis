/*
  ==============================================================================

    Wavetable.h
    Author:  MikeHen

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include <complex> 

class Wavetable
{
    public:
        Wavetable();
        ~Wavetable();

        static const int wavetableSize = 4096;
        float frequency;
        int sigLength;

        Array<float> naiveWavetable;
        Array<float> tables;
        Array<float> fft_table;
        std::complex<float> bandLimitWavetable[wavetableSize];

        static const int wt_4 = wavetableSize / 4;
        static const int wt_8 = wavetableSize / 8;
        static const int wt_16 = wavetableSize / 16;
        static const int wt_32 = wavetableSize / 32;
        static const int wt_64 = wavetableSize / 64;
        static const int wt_128 = wavetableSize / 128;
        static const int wt_256 = wavetableSize / 256;
        static const int wt_512 = wavetableSize / 512;
        static const int wt_1024 = wavetableSize / 1024;

        std::array<dsp::Complex<float>, wavetableSize> wavetable0Ifft;
        std::array<dsp::Complex<float>, wavetableSize> wavetable1Ifft;
        std::array<dsp::Complex<float>, wavetableSize> wavetable2Ifft;
        std::array<dsp::Complex<float>, wavetableSize> wavetable3Ifft;
        std::array<dsp::Complex<float>, wavetableSize> wavetable4Ifft;
        std::array<dsp::Complex<float>, wavetableSize> wavetable5Ifft;
        std::array<dsp::Complex<float>, wavetableSize> wavetable6Ifft;
        std::array<dsp::Complex<float>, wavetableSize> wavetable7Ifft;
        std::array<dsp::Complex<float>, wavetableSize> wavetable8Ifft;
        std::array<dsp::Complex<float>, wavetableSize> wavetable9Ifft;

        std::array<dsp::Complex<float>, 4096> wavetableBL;

        void Wavetable::generateWavetable(std::array < dsp::Complex<float>, wavetableSize> naiveTable, int tableSize);
        std::array<dsp::Complex<float>, wavetableSize> Wavetable::selectWavetable(float frequency);

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Wavetable)
};