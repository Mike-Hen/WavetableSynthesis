/*
  ==============================================================================

    OscScope.cpp
    Author:  MikeHen

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "OscScope.h"

//==============================================================================
OscScope::OscScope(Wsynth_v1AudioProcessor& p) :
    processor(p)
{
    startTimer(1000 / 100);

    historyImage = Image(juce::Image::ARGB, 500, 200, true);
    historyGraphic = new Graphics(historyImage);
}

OscScope::~OscScope()
{

}

void OscScope::timerCallback() 
{
    repaint();
}

void OscScope::paint (Graphics& g)
{
    juce::Rectangle <float> area(0, 0, historyImage.getWidth(), historyImage.getHeight());
    g.setColour(Colours::maroon);
    g.drawRect(area);

    // Osc
    Path p;
    float max = 0;
    Array<float> history = processor.getHistory();

    for (int i = 0; i < getWidth(); i++)
    {
        int scaledIndex = float(i*history.size()) / float(getWidth());
        float val = history[scaledIndex];
        val = jlimit<float>(-1, 1, val);

        if (i == 0)
        {
            p.startNewSubPath(0, 1);
            p.startNewSubPath(0, -1);
            p.startNewSubPath(0, val);
        }
        else p.lineTo(i, val);
    }
    //max = FloatVectorOperations::findMaximum(history.getRawDataPointer(), history.size());
    //max = jlimit<float>(0, 2, max);

    if (p.isEmpty()) return;
    if (p.getBounds().getWidth() < 0.01) return;
    if (p.getBounds().getWidth() != p.getBounds().getWidth()) return;

    p.scaleToFit(0, 0, historyImage.getWidth(), historyImage.getHeight(), false);

    historyImage.multiplyAllAlphas(0);

    historyGraphic->setColour(Colours::white);
    historyGraphic->strokePath(p, PathStrokeType(0.5f + max / 2));

    g.drawImageAt(historyImage, 0, 0);

}

void OscScope::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
