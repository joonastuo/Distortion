/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionAudioProcessor::DistortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
		mParameters(*this, nullptr, Identifier("Distortion"),
			{
			  std::make_unique<AudioParameterFloat>(IDs::inputVolume,
													"DIST",
													NormalisableRange<float>(0.f, 60.f),
													0.f,
													" dB",
													AudioProcessorParameter::genericParameter,
													[](float value, int) {return static_cast<String>(round(value * 100.f) / 100.f); },
													nullptr
													),
			  std::make_unique<AudioParameterFloat>(IDs::outputVolume,
													"LEVEL",
													NormalisableRange<float>(-40.f, 40.f),
													0.f,
													" dB",
													AudioProcessorParameter::genericParameter,
													[](float value, int) {return static_cast<String>(round(value * 100.f) / 100.f); },
													nullptr
													),
			  std::make_unique<AudioParameterFloat>(IDs::HPFreq,
													"Pre Highpass Freq",
													NormalisableRange<float>(20.f, 20000.f, 0.01f, 0.2299f),
													0.f,
													" Hz",
													AudioProcessorParameter::genericParameter,
													[](float value, int) {return static_cast<String>(round(value * 100.f) / 100.f); },
													nullptr
													),
			  std::make_unique<AudioParameterFloat>(IDs::LPFreq,
													"Post Lowpass Freq",
													NormalisableRange<float>(20.f, 20000.f, 0.01f, 0.2299f),
													20000.f,
													" Hz",
													AudioProcessorParameter::genericParameter,
													[](float value, int) {return static_cast<String>(round(value * 100.f) / 100.f); },
													nullptr
													),
			  std::make_unique<AudioParameterFloat>(IDs::wetDry,
													"Mix",
													NormalisableRange<float>(0.f, 1.f),
													0.5,
													String(),
													AudioProcessorParameter::genericParameter,
													[](float value, int) {return static_cast<String>(round(value * 100.f * 100.f) / 100.f); },
													nullptr
													) 
			}),
		mDistortion(mParameters)
#endif
{
	//NormalisableRange<float> inputVolumeRange(0.0f, 60.0f, 0.0f, 1.0f);
	//NormalisableRange<float> highPassRange(20.f, 20000.f, 0.f, 0.5f);
	//NormalisableRange<float> lowPassRange(20.f, 20000.f, 0.f, 0.5f);
 //   NormalisableRange<float> outputVolumeRange(-40.0f, 40.0f, 0.0f, 1.0f );
	//NormalisableRange<float> wetDryRange(0.f, 1.f);

	//mParameters.createAndAddParameter(IDs::inputVolume, "DIST", "dB", inputVolumeRange, 0.0f, nullptr, nullptr);
	//mParameters.createAndAddParameter(IDs::HPFreq, "Pre Highpass Freq", "Hz", highPassRange, 20.f, nullptr, nullptr);
	//mParameters.createAndAddParameter(IDs::LPFreq, "Post Lowpass Freq", "Hz", lowPassRange, 20000.f, nullptr, nullptr);
 //   mParameters.createAndAddParameter(IDs::outputVolume, "LEVEL", "dB", outputVolumeRange, 0.0f, nullptr, nullptr);
	//mParameters.createAndAddParameter(IDs::wetDry, "WetDry", String(), wetDryRange, .5f, nullptr, nullptr);
	//
	//mParameters.state = ValueTree("Distortion");
}

DistortionAudioProcessor::~DistortionAudioProcessor()
{
}

//==============================================================================
const String DistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DistortionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DistortionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DistortionAudioProcessor::setCurrentProgram (int index)
{
}

const String DistortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void DistortionAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	dsp::ProcessSpec spec;
	spec.sampleRate = sampleRate;
	spec.maximumBlockSize = samplesPerBlock;
	spec.numChannels = getTotalNumOutputChannels();
	mDistortion.prepare(spec);
}

void DistortionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DistortionAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	auto numSamples = buffer.getNumSamples();

	for (auto i = jmin(2, totalNumInputChannels); i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, numSamples);

	mDistortion.updateParameters();

	dsp::AudioBlock<float> block(buffer);

	if (block.getNumChannels() > 2)
		block = block.getSubsetChannelBlock(0, 2);

	mDistortion.process(dsp::ProcessContextReplacing<float>(block));

}

//==============================================================================
bool DistortionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DistortionAudioProcessor::createEditor()
{
    return new DistortionAudioProcessorEditor (*this);
}

//==============================================================================
void DistortionAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	auto state = mParameters.copyState();
	std::unique_ptr<XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);
}

void DistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName(mParameters.state.getType()))
			mParameters.replaceState(ValueTree::fromXml(*xmlState));
}

AudioProcessorValueTreeState& DistortionAudioProcessor::getState()
{
	return mParameters;
}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DistortionAudioProcessor();
}
