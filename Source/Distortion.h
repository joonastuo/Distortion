/*
  ==============================================================================

    Distortion.h
    Created: 22 Feb 2019 3:58:00pm
    Author:  Joonas

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Identifiers.h"

//==============================================================================
/*
*/
class Distortion
{
public:
    Distortion(AudioProcessorValueTreeState& vt);
    ~Distortion();
	void prepare(dsp::ProcessSpec);
	void reset();
	void process(dsp::ProcessContextReplacing<float> block);
	void updateParameters();

private:
	AudioProcessorValueTreeState& mParameters;
	static constexpr size_t numWaveShapers = 1;
	dsp::WaveShaper<float> mWaveShapers[numWaveShapers];
	dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> mLowPassFilter, mHighPassFilter;
	std::unique_ptr<dsp::Oversampling<float>> mOversampling;
	dsp::Gain<float> mInputVolume, mOutputVolume;

	float mSampleRate = 44100.f;
	uint32 mMaxBlockSize = 512;
	uint32 mNumChannels = 2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Distortion)
};
