/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class DistortionAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    DistortionAudioProcessorEditor (DistortionAudioProcessor&);
    ~DistortionAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	FlexItem makeRotarySlider(Component& c);
	FlexItem makeLabel(Component& c);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DistortionAudioProcessor& processor;

	AudioProcessorValueTreeState& mParameter;

	typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

	Slider mGainSlider;
	Label mGainLabel;
	Slider mWetDrySlider;
	Label mWetDryLabel;

	int sliderSize = 100;

	std::unique_ptr<SliderAttachment> mGainAttachment;
	std::unique_ptr<SliderAttachment> mWetDryAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionAudioProcessorEditor)
};
