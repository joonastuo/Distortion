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
	mWaveShapers{ { std::tanh } },
	mLowPassFilter(dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100.f, 20000.f)),
	mHighPassFilter(dsp::IIR::Coefficients<float>::makeFirstOrderHighPass(44100.f, 20.f))
{
	mOversampling.reset(new dsp::Oversampling<float>(2, 3, dsp::Oversampling<float>::filterHalfBandPolyphaseIIR, false));
}

Distortion::~Distortion()
{
	// Empty destructor
}

void Distortion::prepare(dsp::ProcessSpec spec)
{
	// Initialize class variables
	mSampleRate = static_cast<float>(spec.sampleRate);
	mMaxBlockSize = spec.maximumBlockSize;
	mNumChannels = spec.numChannels;
	// Prepare
	mInputVolume.prepare(spec);
	mOutputVolume.prepare(spec);
	mLowPassFilter.prepare(spec);
	mHighPassFilter.prepare(spec);

	mOversampling->initProcessing(static_cast<size_t> (mMaxBlockSize));
	reset();
}

void Distortion::reset()
{
	mOversampling->reset();
	mLowPassFilter.reset();
	mHighPassFilter.reset();
}

void Distortion::process(dsp::ProcessContextReplacing<float> context)
{
	ScopedNoDenormals noDenormals;

	mInputVolume.process(context);

	mHighPassFilter.process(context);

	dsp::AudioBlock<float> oversampledBlock  = mOversampling -> processSamplesUp(context.getInputBlock());
	auto waveshaperContext = dsp::ProcessContextReplacing<float>(oversampledBlock);

	mWaveShapers[0].process(waveshaperContext);
	waveshaperContext.getOutputBlock() *= 0.7f;

	// downsample
	mOversampling->processSamplesDown(context.getOutputBlock());

	mLowPassFilter.process(context);

	mOutputVolume.process(context);
}

void Distortion::updateParameters()
{
	float inputVolume = *mParameters.getRawParameterValue(IDs::inputVolume);
	float outputVolume = *mParameters.getRawParameterValue(IDs::outputVolume);

	auto inputdB = Decibels::decibelsToGain(inputVolume);
	auto outputdB = Decibels::decibelsToGain(outputVolume);

	if (mInputVolume.getGainLinear() != inputdB)     mInputVolume.setGainLinear(inputdB);
	if (mOutputVolume.getGainLinear() != outputdB)   mOutputVolume.setGainLinear(outputdB);

	float freqLowPass = *mParameters.getRawParameterValue(IDs::LPFreq);
	*mLowPassFilter.state = *dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(mSampleRate, freqLowPass);
	float freqHighPass = *mParameters.getRawParameterValue(IDs::HPFreq);
	*mHighPassFilter.state = *dsp::IIR::Coefficients<float>::makeFirstOrderHighPass(mSampleRate, freqHighPass);
}
