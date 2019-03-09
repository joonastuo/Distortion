/*
  ==============================================================================

    Distortion.cpp
    Created: 22 Feb 2019 3:58:00pm
    Author:  Joonas

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Distortion.h"

//==============================================================================
Distortion::Distortion(AudioProcessorValueTreeState& vt): mParameters(vt)
{
}

Distortion::~Distortion()
{
}

float Distortion::process(float sample)
{
	return expDistortion(sample);
}

float Distortion::expDistortion(float sample)
{
	auto gain = *mParameters.getRawParameterValue("gain");

	float wetOutput;
	if (sample > 0)
	{
		wetOutput = 1 - exp(-1 * (sample * gain));
	}
	else
	{
		wetOutput = -1 + exp(1 * (sample * gain));
	}
	return wetOutput;
}
