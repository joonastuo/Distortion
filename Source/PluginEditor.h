/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "MyKnobs.h"
#include "Identifiers.h"

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
	void initialiseGUI();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DistortionAudioProcessor& processor;
	AudioProcessorValueTreeState& mParameter;

	typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

	// Sliders
	Slider mInputVolumeSlider;
	Slider mHighPassSlider;
	Slider mLowPassSlider;
    Slider mOutputVolumeSlider;
	Slider mWetDrySlider;

	// Labels
	Label mInputVolumeLabel;
	Label mHighPassLabel;
	Label mLowPassLabel;
    Label mOutputVolumeLabel;
	Label mWetDryLabel;

    // LAF 
    KnobLookAndFeel knobLookAndFeel;
    
	int mSliderSize = 70;
	int mTextBoxHeight = 14;
	int mTextBoxWidth = 120;

	std::unique_ptr<SliderAttachment> mInputVolumeAttachment;
	std::unique_ptr<SliderAttachment> mHighPassAttachment;
	std::unique_ptr<SliderAttachment> mLowPassAttachment;
    std::unique_ptr<SliderAttachment> mOutputVolumeAttachment;
	std::unique_ptr<SliderAttachment> mWetDryAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionAudioProcessorEditor)
};
