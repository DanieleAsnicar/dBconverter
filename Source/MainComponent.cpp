#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{   
    addAndMakeVisible(convertButton);    
    addAndMakeVisible(resetButton);

    addAndMakeVisible(unitMenu);
    unitMenu.addItem("V to dBV", 1);
    unitMenu.addItem("V to dBu", 2);
    unitMenu.addItem("W to dBW", 3);
    unitMenu.addItem("mW to dBm", 4);
    unitMenu.setJustificationType(juce::Justification::centred);

    unitMenu.onChange = [this] 
    {
        unitMenuChanged(); 
    };
    unitMenu.setSelectedId(1);

    addAndMakeVisible(unitMenuLabel);
    unitMenuLabel.setText("Units:", juce::dontSendNotification);
    unitMenuLabel.attachToComponent(&unitMenu, true);
    unitMenuLabel.setJustificationType(juce::Justification::right);
    
    addAndMakeVisible(levelLabel);
    levelLabel.setText("Level:", juce::dontSendNotification);
    levelLabel.attachToComponent(&inputLevelLabel, true);    
    levelLabel.setJustificationType(juce::Justification::right);

    addAndMakeVisible(unitLevelLabel);
    unitLevelLabel.setText("V", juce::dontSendNotification);        
    unitLevelLabel.setJustificationType(juce::Justification::left);

    addAndMakeVisible(decibelsLabel);
    decibelsLabel.setText("Decibels:", juce::dontSendNotification);
    decibelsLabel.attachToComponent(&outputDecibelsLabel, true);    
    decibelsLabel.setJustificationType(juce::Justification::right);

    addAndMakeVisible(unitDecibelsLabel);
    unitDecibelsLabel.setText("dBV", juce::dontSendNotification);    
    unitDecibelsLabel.setJustificationType(juce::Justification::left);

    addAndMakeVisible(outputDecibelsLabel);
    outputDecibelsLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkslategrey);

    addAndMakeVisible(inputLevelLabel);
    inputLevelLabel.setEditable(true);
    inputLevelLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkslategrey);    
    inputLevelLabel.onTextChange = [this] ()
    {         
        float levelValue = inputLevelLabel.getText().getFloatValue();
        convertButton.onClick = [this, levelValue]()
        {
            calculateAndOutputConversion(levelValue);
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
    
    constexpr int textLabelsWidth = 80;
    constexpr int textLabelsHeight = 24;
    constexpr int inOutLabelsWidth = 120;
    constexpr int inOutLabelsHeight = 24;
    constexpr int buttonWidth = 120;
    constexpr int buttonHeight = 24;
    constexpr int numOfRows = 5;
    constexpr int numOfBlanks = numOfRows + 1;
    int heightOffset = getHeight() / numOfBlanks / 4;
        
    unitMenuLabel.setBounds(getWidth() / 2 - textLabelsWidth - inOutLabelsWidth / 2,
                            getHeight() / numOfBlanks - heightOffset, 
                            textLabelsWidth,
                            textLabelsHeight);

    unitMenu.setBounds(getWidth() / 2 - inOutLabelsWidth / 2,
                       getHeight() / numOfBlanks - heightOffset,
                       inOutLabelsWidth, 
                       inOutLabelsHeight);

    levelLabel.setBounds(getWidth() / 2 - textLabelsWidth - inOutLabelsWidth / 2, 
                         getHeight() / numOfBlanks * 2 - heightOffset, 
                         textLabelsWidth, 
                         textLabelsHeight);

    inputLevelLabel.setBounds(getWidth() / 2 - inOutLabelsWidth / 2,
                              getHeight() / numOfBlanks * 2 - heightOffset,
                              inOutLabelsWidth, 
                              inOutLabelsHeight);

    unitLevelLabel.setBounds(getWidth() / 2 + inOutLabelsWidth / 2, 
                             getHeight() / numOfBlanks * 2 - heightOffset, 
                             textLabelsWidth, 
                             textLabelsHeight);

    convertButton.setBounds(getWidth() / 2 - buttonWidth / 2, 
                             getHeight() / numOfBlanks * 3 - heightOffset, 
                             buttonWidth, 
                             buttonHeight);

    decibelsLabel.setBounds(getWidth() / 2 - textLabelsWidth - inOutLabelsWidth / 2,
                            getHeight() / numOfBlanks * 4 - heightOffset,
                            textLabelsWidth,
                            textLabelsHeight);

    outputDecibelsLabel.setBounds(getWidth() / 2 - inOutLabelsWidth / 2,
                                  getHeight() / numOfBlanks * 4 - heightOffset,
                                  inOutLabelsWidth, 
                                  inOutLabelsHeight);
    
    unitDecibelsLabel.setBounds(getWidth() / 2 + inOutLabelsWidth / 2,
                            getHeight() / numOfBlanks * 4 - heightOffset,
                            textLabelsWidth,
                            textLabelsHeight);
    
    resetButton.setBounds(getWidth() / 2 - buttonWidth / 2, 
                          getHeight() / numOfBlanks * 5 - heightOffset, 
                          buttonWidth, 
                          buttonHeight);
}

void MainComponent::calculateAndOutputConversion(float levelValue)
{    
    float dbValue = multiplierPowerVoltage * log10(levelValue / referenceValue);             
    outputDecibelsLabel.setText(juce::String{ dbValue }, juce::dontSendNotification);
}

void MainComponent::updateAndOutputConversion()
{    
    float levelValue = inputLevelLabel.getText().getFloatValue();
    calculateAndOutputConversion(levelValue);
}

void MainComponent::unitMenuChanged()
{
    switch (unitMenu.getSelectedId())
    {
    case 1:
        unitLevelLabel.setText("V", juce::dontSendNotification);
        unitDecibelsLabel.setText("dBV", juce::dontSendNotification);
        referenceValue = 1.0f;
        multiplierPowerVoltage = 20.0f;
        break;

    case 2: 
        unitLevelLabel.setText("V", juce::dontSendNotification);
        unitDecibelsLabel.setText("dBu", juce::dontSendNotification);
        referenceValue = 0.775f;
        multiplierPowerVoltage = 20.0f;
        break;

    case 3:
        unitLevelLabel.setText("W", juce::dontSendNotification);
        unitDecibelsLabel.setText("dBW", juce::dontSendNotification);
        referenceValue = 1.0f;
        multiplierPowerVoltage = 10.0f;
        break;

    case 4:
        unitLevelLabel.setText("mW", juce::dontSendNotification);
        unitDecibelsLabel.setText("dBm", juce::dontSendNotification);
        referenceValue = 1.0f;
        multiplierPowerVoltage = 10.0f;
        break;

    default: break;
    }
    updateAndOutputConversion();
}