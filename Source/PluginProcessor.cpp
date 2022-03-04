/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MyAudioPluginDemoAudioProcessor::MyAudioPluginDemoAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
/* Step 4 */           ), apvts(*this, nullptr, "Parameters", createParameters())   // createParameters() returns a ParameterLayout object so we can use it
#endif
{
}

MyAudioPluginDemoAudioProcessor::~MyAudioPluginDemoAudioProcessor()
{
}

//==============================================================================
const juce::String MyAudioPluginDemoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MyAudioPluginDemoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MyAudioPluginDemoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MyAudioPluginDemoAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MyAudioPluginDemoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MyAudioPluginDemoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MyAudioPluginDemoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MyAudioPluginDemoAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MyAudioPluginDemoAudioProcessor::getProgramName (int index)
{
    return {};
}

void MyAudioPluginDemoAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MyAudioPluginDemoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MyAudioPluginDemoAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MyAudioPluginDemoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void MyAudioPluginDemoAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool MyAudioPluginDemoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MyAudioPluginDemoAudioProcessor::createEditor()
{
    return new MyAudioPluginDemoAudioProcessorEditor (*this);
}

//==============================================================================
void MyAudioPluginDemoAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MyAudioPluginDemoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MyAudioPluginDemoAudioProcessor();
}

// step 3: implement function to give us our parameter layout
juce::AudioProcessorValueTreeState::ParameterLayout MyAudioPluginDemoAudioProcessor::createParameters()
{
    // A vector(list) of all the ranged audio parameters
    // pointers of the parameters
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // push_back method since its a vector
    // we have to allocate memory for this unique_pointer
    // AudioParameterFloat IS a type of RangedAudioParameter
    // Give it all its initialization arugments (see docs)
    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", 0.0f, 1.0f, 0.0f));
    
    // return iterator of vector using .begin() and .end() member functions
    return { params.begin(), params.end() };
}
