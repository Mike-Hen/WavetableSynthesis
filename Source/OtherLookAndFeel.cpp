/*
  ==============================================================================

    OtherLookAndFeel.cpp
    Author:  MikeHen

  ==============================================================================
*/

#include "OtherLookAndFeel.h"

OtherLookAndFeel::OtherLookAndFeel()
{

}

OtherLookAndFeel::~OtherLookAndFeel()
{

}

void OtherLookAndFeel::drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider &slider)
{
    float diameter = jmin(width, height);
    float radius = diameter / 2;
    float centreX = x + width / 2;
    float centreY = y + height / 2;
    float rx = centreX - radius;
    float ry = centreY - radius;
    float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));

    Rectangle<float> dialArea(rx+2, ry+2, diameter-4, diameter-4);

    g.setColour(Colours::grey);
    g.fillEllipse(dialArea);

    g.setColour(Colours::white);
    g.drawEllipse(dialArea, 1);

    Path dialTick;
    dialTick.addRectangle(0, -radius+2, 2.0f, radius * 0.5);

    g.fillPath(dialTick, AffineTransform::rotation(angle).translated(centreX, centreY));

}

void OtherLookAndFeel::drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider &slider)
{
    float middle = width / 2;
    float barWidth = 3;
    float bar_x = middle - barWidth / 2;
    int partitions = 11;
    float partitionsVal = height / partitions;

    float lineWidth = 7;
    float lineHeight = 1;
    float lineStart = middle - lineWidth / 2;
    float thickLineWidth = 9;
    float thickLineHeight = 2;
    float thickLineStart = middle - thickLineWidth / 2;

    float topLine = y;
    float bottomLine = y + height - thickLineHeight;

    Rectangle<float> sliderArea(x, y, width, height);
    Rectangle<float> barArea(bar_x, y, barWidth, height);





    g.setColour(Colours::grey);
    g.fillRect(barArea);

    // Tick Lines
    g.setColour(Colours::black);
    for (int i = 0; i < partitions + 1; i++)
    {
        float currentLine = i * partitionsVal;
        g.fillRect(lineStart, y + currentLine, lineWidth, lineHeight);
    }

    g.setColour(Colours::black);
    g.fillRect(thickLineStart, topLine, thickLineWidth, thickLineHeight);
    g.fillRect(thickLineStart, bottomLine, thickLineWidth, thickLineHeight);

    float triP1_x = thickLineStart + barWidth;
    float triP1_y = sliderPos;
    float triP2_x = thickLineStart + barWidth + 8.0f;
    float triP2_y = sliderPos - 5.0f;
    float triP3_x = thickLineStart + barWidth + 8.0f;
    float triP3_y = sliderPos + 5.0f;
    
    Path sliderTick;
    sliderTick.addTriangle(Point<float>(triP1_x, triP1_y), Point<float>(triP2_x, triP2_y), Point<float>(triP3_x, triP3_y));
    g.setColour(Colours::lightgrey);
    g.fillPath(sliderTick);
}
