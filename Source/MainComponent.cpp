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
    
    addAndMakeVisible(levelLabel);
    levelLabel.setText("Level:", juce::dontSendNotification);
    levelLabel.attachToComponent(&inputLevelLabel, true);    
    levelLabel.setJustificationType(juce::Justification::right);

    addAndMakeVisible(unitLevelLabel);
    unitLevelLabel.setText("V", juce::dontSendNotification);
    //unitLevelLabel.attachToComponent(&inputLevelLabel, true);    
    unitLevelLabel.setJustificationType(juce::Justification::left);

    addAndMakeVisible(decibelsLabel);
    decibelsLabel.setText("Decibels:", juce::dontSendNotification);
    decibelsLabel.attachToComponent(&outputDecibelsLabel, true);    
    decibelsLabel.setJustificationType(juce::Justification::right);

    addAndMakeVisible(unitDecibelsLabel);
    unitDecibelsLabel.setText("dBV", juce::dontSendNotification);
    //unitDecibelsLabel.attachToComponent(&outputDecibelsLabel, true);    
    unitDecibelsLabel.setJustificationType(juce::Justification::left);

    addAndMakeVisible(outputDecibelsLabel);
    outputDecibelsLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkslategrey);

    addAndMakeVisible(inputLevelLabel);
    inputLevelLabel.setEditable(true);
    inputLevelLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkslategrey);    
    inputLevelLabel.onTextChange = [this] ()
    {         
        float levelValue = inputLevelLabel.getText().getFloatValue();
        float dbValue = 20 * log10(levelValue / 1.0f); // dBV ref value 1V
        juce::String dbValueStr{ dbValue };
       
        convertButton.onClick = [this, dbValueStr]()
        {
            outputDecibelsLabel.setText(dbValueStr, juce::dontSendNotification);
        };
    };
           
    resetButton.onClick = [this]() 
    { 
        inputLevelLabel.setText(juce::String{ "" }, juce::dontSendNotification);
        outputDecibelsLabel.setText(juce::String{ "" }, juce::dontSendNotification);
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
    constexpr int textLabelsWidth = 100;
    constexpr int textLabelsHeight = 24;
    constexpr int inOutLabelsWidth = 100;
    constexpr int inOutLabelsHeight = 24;
    constexpr int buttonWidth = 100;
    constexpr int buttonHeight = 24;
    constexpr int numOfRows = 5;
    constexpr int verticalDistance = numOfRows + 1;
    int heightOffset = getHeight() / verticalDistance / 2;

    titleLabel.setBounds(getWidth() / 2 - titleLabelWidth / 2, 
                         getHeight() / verticalDistance - heightOffset, 
                         titleLabelWidth, 
                         titleLabelHeight);

    levelLabel.setBounds(getWidth() / 2 - textLabelsWidth - inOutLabelsWidth / 2, 
                         getHeight() / verticalDistance * 2 - heightOffset, 
                         textLabelsWidth, 
                         textLabelsHeight);

    inputLevelLabel.setBounds(getWidth() / 2 - inOutLabelsWidth / 2,
                              getHeight() / verticalDistance * 2 - heightOffset,
                              inOutLabelsWidth, 
                              inOutLabelsHeight);

    unitLevelLabel.setBounds(getWidth() / 2 + inOutLabelsWidth / 2, 
                             getHeight() / verticalDistance * 2 - heightOffset, 
                             textLabelsWidth, 
                             textLabelsHeight);

    convertButton.setBounds(getWidth() / 2 - buttonWidth / 2, 
                             getHeight() / verticalDistance * 3 - heightOffset, 
                             buttonWidth, 
                             buttonHeight);

    decibelsLabel.setBounds(getWidth() / 2 - textLabelsWidth - inOutLabelsWidth / 2,
                            getHeight() / verticalDistance * 4 - heightOffset,
                            textLabelsWidth,
                            textLabelsHeight);

    outputDecibelsLabel.setBounds(getWidth() / 2 - inOutLabelsWidth / 2,
                                  getHeight() / verticalDistance * 4 - heightOffset,
                                  inOutLabelsWidth, 
                                  inOutLabelsHeight);
    
    unitDecibelsLabel.setBounds(getWidth() / 2 + inOutLabelsWidth / 2,
                            getHeight() / verticalDistance * 4 - heightOffset,
                            textLabelsWidth,
                            textLabelsHeight);
    
    resetButton.setBounds(getWidth() / 2 - buttonWidth / 2, 
                          getHeight() / verticalDistance * 5 - heightOffset, 
                          buttonWidth, 
                          buttonHeight);
}
