/*
  ==============================================================================

    Wavetable.cpp
    Author:  MikeHen

  ==============================================================================
*/

#include "Wavetable.h"

Wavetable::Wavetable()
{
}

Wavetable::~Wavetable()
{

}

void Wavetable::generateWavetable(std::array < dsp::Complex<float>, wavetableSize> naiveTable, int tableSize)
{
    const int wtSize = wavetableSize;
    dsp::FFT genFFT(12);

    static std::array<dsp::Complex<float>, wavetableSize> fftTable;
    genFFT.perform(naiveTable.data(), fftTable.data(), false);

    // Create list of harmonics to use
    std::array<int, 2> wavetableVals0;
    std::array<int, 2> wavetableVals1;
    std::array<int, 2> wavetableVals2;
    std::array<int, 2> wavetableVals3;
    std::array<int, 20> wavetableVals4;
    std::array<int, 32> wavetableVals5;
    std::array<int, 64> wavetableVals6;
    std::array<int, 128> wavetableVals7;
    std::array<int, 256> wavetableVals8;
    std::array<int, 3584> wavetableVals9;

    int a0 = 1;
    int b0 = 2;
    for (int i = a0; i < b0; i++)
    {
        wavetableVals0[i-a0] = i;
        wavetableVals0[wavetableVals0.size() - 1 - (i - a0)] = wavetableSize - 1 - i + 1;
    }
    int a1 = 2;
    int b1 = 3;
    for (int i = a1; i < b1; i++)
    {
        wavetableVals1[i - a1] = i;
        wavetableVals1[wavetableVals1.size() - 1 - (i - a1)] = wavetableSize - 1 - i + 1;
    }
    int a2 = 3;
    int b2 = 4;
    for (int i = a2; i < b2; i++)
    {
        wavetableVals2[i - a2] = i;
        wavetableVals2[wavetableVals2.size() - 1 - (i - a2)] = wavetableSize - 1 - i + 1;
    }
    int a3 = 4;
    int b3 = 5;
    for (int i = a3; i < b3; i++)
    {
        wavetableVals3[i - a3] = i;
        wavetableVals3[wavetableVals3.size() - 1 - (i - a3)] = wavetableSize - 1 - i + 1;
    }
    int a4 = 5;
    int b4 = wtSize/wt_16;
    for (int i = a4; i < b4; i++)
    {
        wavetableVals4[i - a4] = i;
        wavetableVals4[wavetableVals4.size() - 1 - (i - a4)] = wavetableSize - 1 - i + 1;
    }
    int a5 = wtSize / wt_16;
    int b5 = wtSize / wt_32;
    for (int i = a5; i < b5; i++)
    {
        wavetableVals5[i - a5] = i;
        wavetableVals5[wavetableVals5.size() - 1 - (i - a5)] = wavetableSize - 1 - i + 1;
    }
    int a6 = wtSize / wt_32;
    int b6 = wtSize / wt_64;
    for (int i = a6; i < b6; i++)
    {
        wavetableVals6[i - a6] = i;
        wavetableVals6[wavetableVals6.size() - 1 - (i - a6)] = wavetableSize - 1 - i + 1;
    }
    int a7 = wtSize / wt_64;
    int b7 = wtSize / wt_128;
    for (int i = a7; i < b7; i++)
    {
        wavetableVals7[i - a7] = i;
        wavetableVals7[wavetableVals7.size() - 1 - (i - a7)] = wavetableSize - 1 - i + 1;
    }
    int a8 = wtSize / wt_128;
    int b8 = wtSize / wt_256;
    for (int i = a8; i < b8; i++)
    {
        wavetableVals8[i - a8] = i;
        wavetableVals8[wavetableVals8.size() - 1 - (i - a8)] = wavetableSize - 1 - i + 1;
    }
    int a9 = wtSize / wt_256;
    int b9 = wtSize / 2;
    for (int i = a9; i < b9; i++)
    {
        wavetableVals9[i - a9] = i;
        wavetableVals9[wavetableVals9.size() - 1 - (i - a9)] = wavetableSize - 1 - i + 1;
    }

    // Create different wavetables and fill with zeros
    std::array<dsp::Complex<float>, wavetableSize> wavetable0;
    std::array<dsp::Complex<float>, wavetableSize> wavetable1;
    std::array<dsp::Complex<float>, wavetableSize> wavetable2;
    std::array<dsp::Complex<float>, wavetableSize> wavetable3;
    std::array<dsp::Complex<float>, wavetableSize> wavetable4;
    std::array<dsp::Complex<float>, wavetableSize> wavetable5;
    std::array<dsp::Complex<float>, wavetableSize> wavetable6;
    std::array<dsp::Complex<float>, wavetableSize> wavetable7;
    std::array<dsp::Complex<float>, wavetableSize> wavetable8;
    std::array<dsp::Complex<float>, wavetableSize> wavetable9;

    // Read wavetable values from FFT and store
    for (int i = 0; i < wavetableVals0.size(); i++)
    {
        int value0 = wavetableVals0[i];
        wavetable0[value0] = fftTable[value0];
    }
    for (int i = 0; i < wavetableVals1.size(); i++)
    {
        int value1 = wavetableVals1[i];
        wavetable1[value1] = fftTable[value1];
    }
    for (int i = 0; i < wavetableVals2.size(); i++)
    {
        int value2 = wavetableVals2[i];
        wavetable2[value2] = fftTable[value2];
    }
    for (int i = 0; i < wavetableVals3.size(); i++)
    {
        int value3 = wavetableVals3[i];
        wavetable3[value3] = fftTable[value3];
    }
    for (int i = 0; i < wavetableVals4.size(); i++)
    {
        int value4 = wavetableVals4[i];
        wavetable4[value4] = fftTable[value4];
    }
    for (int i = 0; i < wavetableVals5.size(); i++)
    {
        int value5 = wavetableVals5[i];
        wavetable5[value5] = fftTable[value5];
    }
    for (int i = 0; i < wavetableVals6.size(); i++)
    {

        int value6 = wavetableVals6[i];
        wavetable6[value6] = fftTable[value6];
    }
    for (int i = 0; i < wavetableVals7.size(); i++)
    {
        int value7 = wavetableVals7[i];
        wavetable7[value7] = fftTable[value7];
    }
    for (int i = 0; i < wavetableVals8.size(); i++)
    {
        int value8 = wavetableVals8[i];
        wavetable8[value8] = fftTable[value8];
    }
    for (int i = 0; i < wavetableVals9.size(); i++)
    {
        int value9 = wavetableVals9[i];
        wavetable9[value9] = fftTable[value9];
    }


    genFFT.perform(wavetable0.data(), wavetable0Ifft.data(), true);
    genFFT.perform(wavetable1.data(), wavetable1Ifft.data(), true);
    genFFT.perform(wavetable2.data(), wavetable2Ifft.data(), true);
    genFFT.perform(wavetable3.data(), wavetable3Ifft.data(), true);
    genFFT.perform(wavetable4.data(), wavetable4Ifft.data(), true);
    genFFT.perform(wavetable5.data(), wavetable5Ifft.data(), true);
    genFFT.perform(wavetable6.data(), wavetable6Ifft.data(), true);
    genFFT.perform(wavetable7.data(), wavetable7Ifft.data(), true);
    genFFT.perform(wavetable8.data(), wavetable8Ifft.data(), true);
    genFFT.perform(wavetable9.data(), wavetable9Ifft.data(), true);
}

std::array<dsp::Complex<float>, 4096> Wavetable::selectWavetable(float frequency)
{
    float maxHarmonic = 22000.0f / frequency;
    for (int i = 0; i < wavetableSize; i++)
    {
        if (maxHarmonic > (wavetableSize / wt_512))
        {
            wavetableBL[i] = wavetable0Ifft[i] + wavetable1Ifft[i] + wavetable2Ifft[i] + wavetable3Ifft[i] + wavetable4Ifft[i] + wavetable5Ifft[i] + wavetable6Ifft[i] + wavetable7Ifft[i] + wavetable8Ifft[i] + wavetable9Ifft[i];
        }
            if (maxHarmonic > (wavetableSize / wt_256) && maxHarmonic <= (wavetableSize / wt_512))
        {
            wavetableBL[i] = wavetable0Ifft[i] + wavetable1Ifft[i] + wavetable2Ifft[i] + wavetable3Ifft[i] + wavetable4Ifft[i] + wavetable5Ifft[i] + wavetable6Ifft[i] + wavetable7Ifft[i] + wavetable8Ifft[i];
        }
        else if (maxHarmonic > (wavetableSize / wt_128) && maxHarmonic <= wavetableSize / wt_256)
        {
            wavetableBL[i] = wavetable0Ifft[i] + wavetable1Ifft[i] + wavetable2Ifft[i] + wavetable3Ifft[i] + wavetable4Ifft[i] + wavetable5Ifft[i] + wavetable6Ifft[i] + wavetable7Ifft[i] + wavetable8Ifft[i];
        }
        else if (maxHarmonic > (wavetableSize / wt_64) && maxHarmonic <= wavetableSize / wt_128)
        {
            wavetableBL[i] = wavetable0Ifft[i] + wavetable1Ifft[i] + wavetable2Ifft[i] + wavetable3Ifft[i] + wavetable4Ifft[i] + wavetable5Ifft[i] + wavetable6Ifft[i] + wavetable7Ifft[i];
        }
        else if (maxHarmonic > (wavetableSize / wt_32) && maxHarmonic <= wavetableSize / wt_64)
        {
            wavetableBL[i] = wavetable0Ifft[i] + wavetable1Ifft[i] + wavetable2Ifft[i] + wavetable3Ifft[i] + wavetable4Ifft[i] + wavetable5Ifft[i] + wavetable6Ifft[i];
        }
        else if (maxHarmonic > (wavetableSize / wt_16) && maxHarmonic <= wavetableSize / wt_32)
        {
            wavetableBL[i] = wavetable0Ifft[i] + wavetable1Ifft[i] + wavetable2Ifft[i] + wavetable3Ifft[i] + wavetable4Ifft[i] + wavetable5Ifft[i];
        }
        else if (maxHarmonic > (wavetableSize / wt_8) && maxHarmonic <= wavetableSize / wt_16)
        {
            wavetableBL[i] = wavetable0Ifft[i] + wavetable1Ifft[i] + wavetable2Ifft[i] + wavetable3Ifft[i] + wavetable4Ifft[i];
        }
        else if (maxHarmonic >= 4 && maxHarmonic <= wavetableSize / wt_8)
        {
            wavetableBL[i] = wavetable0Ifft[i] + wavetable1Ifft[i] + wavetable2Ifft[i] + wavetable3Ifft[i];
        }
        else if (maxHarmonic >= 3 && maxHarmonic < 4)
        {
            wavetableBL[i] = wavetable0Ifft[i] + wavetable1Ifft[i] + wavetable2Ifft[i];
        }
        else if (maxHarmonic >= 2 && maxHarmonic < 3)
        {
            wavetableBL[i] = wavetable0Ifft[i] + wavetable1Ifft[i];
        }
        else if (maxHarmonic < 2)
        {
            wavetableBL[i] = wavetable0Ifft[i];
        }
    }
    return wavetableBL;
}
