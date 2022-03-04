/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MyAudioPluginDemoAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MyAudioPluginDemoAudioProcessorEditor (MyAudioPluginDemoAudioProcessor&);
    ~MyAudioPluginDemoAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // step 5: create gain slider
    juce::Slider gainSlider;
    
    // Step 8:  creates top-down and deletes from bottom-up
    // FROM DOCS: When this object is deleted, the connection is broken. Make sure that your AudioProcessorValueTreeState and
    // Slider aren't deleted before this object!
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainSliderAttachment;
    
    // referring to that piece of memory (not allocating it!)
    MyAudioPluginDemoAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyAudioPluginDemoAudioProcessorEditor)
};
