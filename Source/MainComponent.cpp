#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{   
    addAndMakeVisible(convertButton);    
    addAndMakeVisible(resetButton);

    addAndMakeVisible(titleLabel);
    titleLabel.setFont(juce::Font(16.0f, juce::Font::bold));
    titleLabel.setText("Level Converter: V to dBV", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);
    //titleLabel.setColour(juce::Label::textColourId, juce::Colours::lightgreen);

    addAndMakeVisible(levelLabel);
    levelLabel.setText("Level (V):", juce::dontSendNotification);
    levelLabel.attachToComponent(&levelInputLabel, true);    
    levelLabel.setJustificationType(juce::Justification::right);

    addAndMakeVisible(decibelsLabel);
    decibelsLabel.setText("Decibels (dBV):", juce::dontSendNotification);
    decibelsLabel.attachToComponent(&decibelsOutputLabel, true);    
    decibelsLabel.setJustificationType(juce::Justification::right);

    addAndMakeVisible(decibelsOutputLabel);
    decibelsOutputLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkslategrey);

    addAndMakeVisible(levelInputLabel);
    levelInputLabel.setEditable(true);
    levelInputLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkslategrey);    
    levelInputLabel.onTextChange = [this] ()
    {         
        float levelValue = levelInputLabel.getText().getFloatValue();
        float dbValue = 20 * log10(levelValue / 1.0f); // dBV ref value 1V
        juce::String dbValueStr{ dbValue };
       
        convertButton.onClick = [this, dbValueStr]()
        {
            decibelsOutputLabel.setText(dbValueStr, juce::dontSendNotification);
        };
    };
           
    resetButton.onClick = [this]() 
    { 
        levelInputLabel.setText(juce::String{ "" }, juce::dontSendNotification);
        decibelsOutputLabel.setText(juce::String{ "" }, juce::dontSendNotification);
    };

    setSize (400, 300);
}

MainComponent::~MainComponent()
{    
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    constexpr int titleLabelWidth = 260;
    constexpr int titleLabelHeight = 24;
    constexpr int leftLabelsWidth = 100;
    constexpr int leftLabelsHeight = 24;
    constexpr int inOutLabelsWidth = 100;
    constexpr int inOutLabelsHeight = 24;
    constexpr int buttonWidth = 100;
    constexpr int buttonHeight = 24;
    int heightOffset = getHeight() / 6 / 2;

    titleLabel.setBounds(getWidth() / 2 - titleLabelWidth / 2, 
                         getHeight() / 6 - heightOffset, 
                         titleLabelWidth, 
                         titleLabelHeight);

    levelLabel.setBounds(getWidth() / 2 - leftLabelsWidth - inOutLabelsWidth / 2, 
                         getHeight() / 6 * 2 - heightOffset, 
                         leftLabelsWidth, 
                         leftLabelsHeight);

    decibelsLabel.setBounds(getWidth() / 2 - leftLabelsWidth - inOutLabelsWidth / 2,
                            getHeight() / 6 * 4 - heightOffset,
                            leftLabelsWidth,
                            leftLabelsHeight);
    
    levelInputLabel.setBounds(getWidth() / 2 - inOutLabelsWidth / 2,
                              getHeight() / 6 * 2 - heightOffset,
                              inOutLabelsWidth, 
                              inOutLabelsHeight);

    decibelsOutputLabel.setBounds(getWidth() / 2 - inOutLabelsWidth / 2,
                                  getHeight() / 6 * 4 - heightOffset,
                                  inOutLabelsWidth, 
                                  inOutLabelsHeight);
    
    convertButton.setBounds(getWidth() / 2 - buttonWidth / 2, 
                             getHeight() / 6 * 3 - heightOffset, 
                             buttonWidth, 
                             buttonHeight);

    resetButton.setBounds(getWidth() / 2 - buttonWidth / 2, 
                          getHeight() / 6 * 5 - heightOffset, 
                          buttonWidth, 
                          buttonHeight);
}
