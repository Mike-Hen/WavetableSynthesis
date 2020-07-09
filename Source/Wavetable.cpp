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

std::array<dsp::Complex<float>, 4096> Wavetable::generateWavetable(std::array < dsp::Complex<float>, wavetableSize> naiveTable, int tableSize)
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
    //std::array<int, 20> wavetableVals4;
    //std::array<int, 32> wavetableVals5;
    //std::array<int, 64> wavetableVals6;
    //std::array<int, 128> wavetableVals7;
    //std::array<int, 256> wavetableVals8;
    //std::array<int, 512> wavetableVals9;
    int a0 = 1;
    int b0 = 2;
    for (int i = a0; i < b0; i++)
    {
        wavetableVals0[i-a0] = i;
        wavetableVals0[i - a0 + 1] = wavetableSize - 1 - i + 1;
    }
    int a1 = 2;
    int b1 = 3;
    for (int i = a1; i < b1; i++)
    {
        wavetableVals1[i - a1] = i;
        wavetableVals1[i - a1 + 1] = wavetableSize - 1 - i + 1;
    }
    int a2 = 3;
    int b2 = 4;
    for (int i = a2; i < b2; i++)
    {
        wavetableVals2[i - a2] = i;
        wavetableVals2[i - a2 + 1] = wavetableSize - 1 - i + 1;
    }
    int a3 = 4;
    int b3 = 5;
    for (int i = a3; i < b3; i++)
    {
        wavetableVals3[i - a3] = i;
        wavetableVals3[i - a3 + 1] = wavetableSize - 1 - i + 1;
    }
    //int a4 = 5;
    //int b4 = wtSize/wt_16;
    //for (int i = a4; i < b4; i++)
    //{
    //    wavetableVals4[i - a4] = i;
    //    wavetableVals4[i - a4 + 1] = wavetableSize - 1 - i + 1;
    //}
    //int a5 = wtSize / wt_16;
    //int b5 = wtSize / wt_32;
    //for (int i = a5; i < b5; i++)
    //{
    //    wavetableVals5[i - a5] = i;
    //    wavetableVals5[i - a5 + 1] = wavetableSize - 1 - i + 1;
    //}
    //int a6 = wtSize / wt_32;
    //int b6 = wtSize / wt_64;
    //for (int i = a6; i < b6; i++)
    //{
    //    wavetableVals6[i - a6] = i;
    //    wavetableVals6[i - a6 + 1] = wavetableSize - 1 - i + 1;
    //}
    //int a7 = wtSize / wt_64;
    //int b7 = wtSize / wt_128;
    //for (int i = a7; i < b7; i++)
    //{
    //    wavetableVals7[i - a7] = i;
    //    wavetableVals7[i - a7 + 1] = wavetableSize - 1 - i + 1;
    //}
    //int a8 = wtSize / wt_128;
    //int b8 = wtSize / wt_256;
    //for (int i = a8; i < b8; i++)
    //{
    //    wavetableVals8[i - a8] = i;
    //    wavetableVals8[i - a8 + 1] = wavetableSize - 1 - i + 1;
    //}

    // Create different wavetables and fill with zeros
    std::array<dsp::Complex<float>, wavetableSize> wavetable0;
    std::array<dsp::Complex<float>, wavetableSize> wavetable1;
    std::array<dsp::Complex<float>, wavetableSize> wavetable2;
    std::array<dsp::Complex<float>, wavetableSize> wavetable3;
    //std::array<dsp::Complex<float>, wavetableSize> wavetable4;
    //std::array<dsp::Complex<float>, wavetableSize> wavetable5;
    //std::array<dsp::Complex<float>, wavetableSize> wavetable6;
    //std::array<dsp::Complex<float>, wavetableSize> wavetable7;
    //std::array<dsp::Complex<float>, wavetableSize> wavetable8;

    // Read wavetable values from FFT and store
    for (int i = 0; i < 2; i++)
    {
        int value0 = wavetableVals0[i];
        wavetable0[value0] = fftTable[value0];
        int value1 = wavetableVals1[i];
        wavetable1[value1] = fftTable[value1];
        int value2 = wavetableVals2[i];
        wavetable2[value2] = fftTable[value2];
        int value3 = wavetableVals3[i];
        wavetable3[value3] = fftTable[value3];
        //int value4 = wavetableVals4[i];
        //wavetable4[value4] = fftTable[value4];
        //int value5 = wavetableVals5[i];
        //wavetable5[value5] = fftTable[value5];
        //int value6 = wavetableVals6[i];
        //wavetable6[value6] = fftTable[value6];
        //int value7 = wavetableVals7[i];
        //wavetable7[value7] = fftTable[value7];
        //int value8 = wavetableVals8[i];
        //wavetable8[value8] = fftTable[value8];
    }
 
    std::array<dsp::Complex<float>, wavetableSize> wavetable0Ifft;
    std::array<dsp::Complex<float>, wavetableSize> wavetable1Ifft;
    std::array<dsp::Complex<float>, wavetableSize> wavetable2Ifft;
    std::array<dsp::Complex<float>, wavetableSize> wavetable3Ifft;
    //std::array<dsp::Complex<float>, wavetableSize> wavetable4Ifft;
    //std::array<dsp::Complex<float>, wavetableSize> wavetable5Ifft;
    //std::array<dsp::Complex<float>, wavetableSize> wavetable6Ifft;
    //std::array<dsp::Complex<float>, wavetableSize> wavetable7Ifft;
    //std::array<dsp::Complex<float>, wavetableSize> wavetable8Ifft;

    genFFT.perform(wavetable0.data(), wavetable0Ifft.data(), true);
    genFFT.perform(wavetable1.data(), wavetable1Ifft.data(), true);
    genFFT.perform(wavetable2.data(), wavetable2Ifft.data(), true);
    genFFT.perform(wavetable3.data(), wavetable3Ifft.data(), true);
    //genFFT.perform(wavetable3.data(), wavetable4Ifft.data(), true);
    //genFFT.perform(wavetable3.data(), wavetable5Ifft.data(), true);
    //genFFT.perform(wavetable3.data(), wavetable6Ifft.data(), true);
    //genFFT.perform(wavetable3.data(), wavetable7Ifft.data(), true);
    //genFFT.perform(wavetable3.data(), wavetable8Ifft.data(), true);

    static std::array<dsp::Complex<float>, wavetableSize> wavetableBL;
    for (int i = 0; i < wtSize; i++)
    {
        wavetableBL[i] = wavetable0Ifft[i] + wavetable1Ifft[i] + wavetable2Ifft[i] + wavetable3Ifft[i];// + wavetable4Ifft[i] + wavetable5Ifft[i] + wavetable6Ifft[i] + wavetable7Ifft[i] + wavetable8Ifft[i];
    }

    return wavetableBL;
}
