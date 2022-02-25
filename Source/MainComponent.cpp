#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{    
    /*unitToDbButton.onClick = [this]() 
    { 
        decibelsOutputLabel.setText(levelInputLabel.getText().toUpperCase(), juce::dontSendNotification);
    };*/

    /*stateButton.setColour(stateButton.buttonOnColourId, juce::Colours::darkolivegreen);
    stateButton.setClickingTogglesState(true);
    stateButton.onClick = [&]() {
        const char* const message = stateButton.getToggleState() ? "State On" : "State Off";
        std::cout << message << std::endl;
        stateButton.setButtonText(message);
    };*/

    addAndMakeVisible(unitToDbButton);
    addAndMakeVisible(dbToUnitButton);
    addAndMakeVisible(resetButton);

    addAndMakeVisible(titleLabel);
    titleLabel.setFont(juce::Font(16.0f, juce::Font::bold));
    titleLabel.setText("Click in the box to enter some text...", juce::dontSendNotification);
    //titleLabel.setColour(juce::Label::textColourId, juce::Colours::lightgreen);
    titleLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(levelLabel);
    levelLabel.setText("Level (V):", juce::dontSendNotification);
    levelLabel.attachToComponent(&levelInputLabel, true);
    //levelLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    levelLabel.setJustificationType(juce::Justification::right);

    addAndMakeVisible(decibelsLabel);
    decibelsLabel.setText("Decibels (dBV):", juce::dontSendNotification);
    decibelsLabel.attachToComponent(&decibelsOutputLabel, true);
    //decibelsLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    decibelsLabel.setJustificationType(juce::Justification::right);

    addAndMakeVisible(decibelsOutputLabel);
    decibelsOutputLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkslategrey);

    addAndMakeVisible(levelInputLabel);
    levelInputLabel.setEditable(true);
    levelInputLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkslategrey);
    //levelInputLabel.onTextChange = [this] { decibelsOutputLabel.setText(levelInputLabel.getText().toUpperCase(), juce::dontSendNotification); };
    levelInputLabel.onTextChange = [this] 
    {         
        float levelValue = levelInputLabel.getText().getFloatValue();
        float dbValue = 20 * log10(levelValue / 1.0f); // dBV ref value 1V
        juce::String dbValueStr{ dbValue };
       
        unitToDbButton.onClick = [this, dbValueStr]()
        {
            decibelsOutputLabel.setText(dbValueStr, juce::dontSendNotification);
        };
    };
           
    setSize (600, 400);
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
    titleLabel.setBounds(getWidth() / 2 - 150, getHeight() / 2 - 175, 300, 50);
    levelLabel.setBounds(20, getHeight() / 2 - 125, 100, 50);
    decibelsLabel.setBounds(20, getHeight() / 2 - 25, 100, 50);
    
    levelInputLabel.setBounds(150, getHeight() / 2 - 125, 200, 24);
    decibelsOutputLabel.setBounds(150, getHeight() / 2 - 25, 200, 24);
    
    unitToDbButton.setBounds(getWidth() / 2 + 100, getHeight() / 2 - 125, 100, 24);
    dbToUnitButton.setBounds(getWidth() / 2 + 100, getHeight() / 2 - 25, 100, 24);
    resetButton.setBounds(getWidth() / 2 + 100, getHeight() / 2 + 75, 100, 24);
}
