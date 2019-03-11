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
	Slider mGainSlider;
	Slider mWetDrySlider;
    Slider mVolumeSlider;
	Slider mLowPassSlider;
	Slider mHighPassSlider;

	// Labels
	Label mGainLabel;
	Label mWetDryLabel;
    Label mVolumeLabel;
	Label mLowPassLabel;
	Label mHighPassLabel;

   // LAF 
    KnobLookAndFeel knobLookAndFeel;
    
	int sliderSize = 60;

	std::unique_ptr<SliderAttachment> mGainAttachment;
	std::unique_ptr<SliderAttachment> mWetDryAttachment;
    std::unique_ptr<SliderAttachment> mVolumeAttachment;
	std::unique_ptr<SliderAttachment> mLowPassAttachment;
	std::unique_ptr<SliderAttachment> mHighPassAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionAudioProcessorEditor)
};
