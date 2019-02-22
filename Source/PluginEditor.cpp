/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionAudioProcessorEditor::DistortionAudioProcessorEditor (DistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), mParameter(p.getState())
{
	mGainLabel.setText("Gain", dontSendNotification);
	mGainLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mGainLabel);

	mGainSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mGainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 20);
	mGainAttachment.reset(new SliderAttachment(mParameter, "gain", mGainSlider));
	addAndMakeVisible(mGainSlider);

	mWetDryLabel.setText("Dry / Wet", dontSendNotification);
	mWetDryLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mWetDryLabel);

	mWetDrySlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mWetDrySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 20);
	mWetDryAttachment.reset(new SliderAttachment(mParameter, "wetDry", mWetDrySlider));
	addAndMakeVisible(mWetDrySlider);

    setSize (400, 200);
}

DistortionAudioProcessorEditor::~DistortionAudioProcessorEditor()
{
}

//==============================================================================
void DistortionAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void DistortionAudioProcessorEditor::resized()
{
	FlexBox gainBox;
	gainBox.alignContent = FlexBox::AlignContent::center;
	gainBox.justifyContent = FlexBox::JustifyContent::center;
	gainBox.flexDirection = FlexBox::Direction::column;
	gainBox.items.addArray({ makeLabel(mGainLabel),
							 makeRotarySlider(mGainSlider) });

	FlexBox wetDryBox;
	wetDryBox.alignContent = FlexBox::AlignContent::center;
	wetDryBox.justifyContent = FlexBox::JustifyContent::center;
	wetDryBox.flexDirection = FlexBox::Direction::column;
	wetDryBox.items.addArray({ makeLabel(mWetDryLabel),
							   makeRotarySlider(mWetDrySlider) });


	FlexBox masterBox;
	masterBox.alignContent = FlexBox::AlignContent::center;
	masterBox.justifyContent = FlexBox::JustifyContent::spaceAround;
	masterBox.flexDirection = FlexBox::Direction::row;
	masterBox.items.addArray({ FlexItem(gainBox).withFlex(1),
							   FlexItem(wetDryBox).withFlex(1) });

	masterBox.performLayout(getLocalBounds().toFloat());
}

FlexItem DistortionAudioProcessorEditor::makeRotarySlider(Component & c)
{
	return FlexItem(c).withMinWidth(sliderSize).withMinHeight(sliderSize);
}

FlexItem DistortionAudioProcessorEditor::makeLabel(Component & c)
{
	return FlexItem(c).withMinWidth(c.getWidth()).withMinHeight(20);
}