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
Distortion::Distortion(AudioProcessorValueTreeState& vt)
	: mParameters(vt),
	  waveShapers{{ dsp::FastMathApproximations::tanh }}
{
	mOversampling.reset(new dsp::Oversampling<float>(2, 3, dsp::Oversampling<float>::filterHalfBandPolyphaseIIR, false));
}

Distortion::~Distortion()
{
}

void Distortion::prepare(dsp::ProcessSpec spec)
{
	// Initialize class variables
	mSampleRate = spec.sampleRate;
	mMaxBlockSize = spec.maximumBlockSize;
	mNumChannels = spec.numChannels;
	inputVolume.prepare(spec);
	outputVolume.prepare(spec);

	mOversampling->initProcessing(static_cast<size_t> (mMaxBlockSize));
	reset();
}

void Distortion::reset()
{
	mOversampling->reset();
}

void Distortion::process(dsp::ProcessContextReplacing<float> context)
{
	ScopedNoDenormals noDenormals;

	inputVolume.process(context);

	dsp::AudioBlock<float> oversampledBlock  = mOversampling -> processSamplesUp(context.getInputBlock());
	auto waveshaperContext = dsp::ProcessContextReplacing<float>(oversampledBlock);

	waveShapers[0].process(waveshaperContext);
	waveshaperContext.getOutputBlock() *= 0.7f;

	// downsample
	mOversampling->processSamplesDown(context.getOutputBlock());

	outputVolume.process(context);
}

void Distortion::updateParameters()
{
	inputVolume.setGainLinear(*mParameters.getRawParameterValue("gain"));
	outputVolume.setGainLinear(*mParameters.getRawParameterValue("volume"));
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
