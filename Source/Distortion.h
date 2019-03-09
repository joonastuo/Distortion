/*
  ==============================================================================

    Distortion.h
    Created: 22 Feb 2019 3:58:00pm
    Author:  Joonas

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Distortion
{
public:
    Distortion(AudioProcessorValueTreeState& vt);
    ~Distortion();
	float process(float sample);
	float expDistortion(float sample);

private:
	AudioProcessorValueTreeState& mParameters;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Distortion)
};
