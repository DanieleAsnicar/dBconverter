#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    //==============================================================================
    // Your private member variables go here...
    juce::TextButton convertButton{ "Convert" };    
    juce::TextButton resetButton{ "Reset" };
    
    juce::Label titleLabel;
    juce::Label levelLabel;
    juce::Label decibelsLabel;
    juce::Label levelInputLabel;
    juce::Label decibelsOutputLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};