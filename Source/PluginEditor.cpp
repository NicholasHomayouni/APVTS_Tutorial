/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MyAudioPluginDemoAudioProcessorEditor::MyAudioPluginDemoAudioProcessorEditor (MyAudioPluginDemoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // step 6: give it some parameters
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);
    // make it child component of main component
    addAndMakeVisible(gainSlider);
    
    // step 9: allocate memory of unique pointer in constructor
    // this attaches (connects) our visible slider to the data sitting in the plugin processor
    gainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "GAIN", gainSlider);
    
    setSize (400, 300);
}

MyAudioPluginDemoAudioProcessorEditor::~MyAudioPluginDemoAudioProcessorEditor()
{
}

//==============================================================================
void MyAudioPluginDemoAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void MyAudioPluginDemoAudioProcessorEditor::resized()
{
    // step 7: give it a position
    // these numbers just put the slider in the middle of the screen
    gainSlider.setBounds(getWidth() / 2 - 100, getHeight() / 2 - 50, 200, 100);
}

