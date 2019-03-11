/*
  ==============================================================================

    MyKnobs.h
    Created: 26 Feb 2019 8:30:04pm
    Author:  Joonas

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#define _USE_MATH_DEFINES
#include <math.h>

//==============================================================================
/*
*/
class KnobLookAndFeel : public LookAndFeel_V4
{
public:
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
	{
		// PARAMETERS ===================================================
		auto radius = jmin(width / 2, height / 2) - 10.0f;
		auto centreX = x + width * 0.5f;
		auto centreY = y + height * 0.5f;
		auto rx = centreX - radius;
		auto ry = centreY - radius;
		auto rw = radius * 2.0f;
		auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

		// SLIDER BACKGROUND =============================================
		// Set colour
		//Colour backgroundColour = findColour(0x1005700);
		Colour backgroundColour = Colours::red;
		// backgroundColour = backgroundColour.darker(.8f);
		backgroundColour = backgroundColour.brighter(.1f);
		g.setColour(backgroundColour);

		// Draw path
		Path backgroundArc;
		backgroundArc.addCentredArc(centreX, centreY, radius, radius, 0.0f, rotaryStartAngle, rotaryEndAngle, true);
		g.strokePath(backgroundArc, PathStrokeType(3.f, PathStrokeType::curved, PathStrokeType::rounded));

		// SLIDER FOREGROUND ==============================================
		// Set colour
		g.setColour(Colours::white);

		// Draw path
		Path foregroundArc;
		foregroundArc.addCentredArc(centreX, centreY, radius, radius, 0.0f, rotaryStartAngle, angle, true);
		g.strokePath(foregroundArc, PathStrokeType(3.6f, PathStrokeType::curved, PathStrokeType::rounded));

		// POINTER ========================================================
		// Set colour
		g.setColour(Colours::white);
		// Draw path
		Path p;
		auto pointerLength = radius * 1.f;
		auto pointerThickness = 3.0f;
		p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
		p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));
		g.fillPath(p);

		// CURRENT VALUE ==================================================
		// Set font
		g.setFont(12);
		// Set text
		String value = "";
		if (slider.getValue() > 1000)
			value = static_cast<String> (round(slider.getValue() / 10.f) / 100.f) + "k";
		else
			value = static_cast<String> (round(slider.getValue() * 100.f) / 100.f);

		// Draw text
		g.drawFittedText(value + slider.getTextValueSuffix(), centreX - 30.f, height - 10.f, 60.f, 10.f, Justification::centred, 1);
	}
};
