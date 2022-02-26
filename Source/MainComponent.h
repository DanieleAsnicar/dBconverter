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
    void calculateAndOutputConversion(float dbValue);
    void updateAndOutputConversion();
    void unitMenuChanged();
    
private:
    //==============================================================================
    // Your private member variables go here...
    juce::TextButton convertButton{ "Convert" };    
    juce::TextButton resetButton{ "Reset" };

    juce::ComboBox unitMenu;
    float referenceValue = 0.0f;
    float multiplierPowerVoltage = 0.0f;
    bool isPower = false;
    
    //juce::Label titleLabel;
    juce::Label unitMenuLabel;
    juce::Label levelLabel;
    juce::Label decibelsLabel;
    juce::Label unitLevelLabel;
    juce::Label unitDecibelsLabel;
    juce::Label inputLevelLabel;
    juce::Label outputDecibelsLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
