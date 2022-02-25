#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{   
    addAndMakeVisible(convertButton);    
    addAndMakeVisible(resetButton);

    addAndMakeVisible(unitMenu);
    unitMenu.addItem("V to dBV", 1);
    unitMenu.addItem("V to dBu", 2);
    unitMenu.addItem("V to dBuV", 3);
    unitMenu.addItem("mV to dBmV", 4);
    unitMenu.addItem("uV to dBuV", 5);

    unitMenu.onChange = [this] 
    {
        unitMenuChanged(); 
    };
    unitMenu.setSelectedId(1);

    /*addAndMakeVisible(titleLabel);
    titleLabel.setFont(juce::Font(16.0f, juce::Font::bold));
    titleLabel.setText("Level Converter: V to dBV", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);*/
    
    addAndMakeVisible(unitMenuLabel);
    //unitMenuLabel.setFont(juce::Font(16.0f, juce::Font::bold));
    unitMenuLabel.setText("Decibel unit:", juce::dontSendNotification);
    unitMenuLabel.attachToComponent(&unitMenu, true);
    unitMenuLabel.setJustificationType(juce::Justification::right);
    
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
        convertButton.onClick = [this, levelValue]()
        {
            float dbValue = 20 * log10(levelValue / 1.0f); // dBV ref value 1V            
            outputDecibelsLabel.setText(juce::String{ dbValue }, juce::dontSendNotification);
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
    /*constexpr int titleLabelWidth = 260;
    constexpr int titleLabelHeight = 24;*/
    constexpr int textLabelsWidth = 100;
    constexpr int textLabelsHeight = 24;
    constexpr int inOutLabelsWidth = 100;
    constexpr int inOutLabelsHeight = 24;
    constexpr int buttonWidth = 100;
    constexpr int buttonHeight = 24;
    constexpr int numOfRows = 5;
    constexpr int verticalDistance = numOfRows + 1;
    int heightOffset = getHeight() / verticalDistance / 2;
        
    unitMenuLabel.setBounds(getWidth() / 2 - textLabelsWidth - inOutLabelsWidth / 2,
                            getHeight() / verticalDistance - heightOffset, 
                            textLabelsWidth,
                            textLabelsHeight);

    unitMenu.setBounds(getWidth() / 2 - inOutLabelsWidth / 2,
                       getHeight() / verticalDistance - heightOffset,
                       inOutLabelsWidth, 
                       inOutLabelsHeight);

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

void MainComponent::unitMenuChanged()
{
    switch (unitMenu.getSelectedId())
    {
    case 1:
        unitLevelLabel.setText("V", juce::dontSendNotification);
        unitDecibelsLabel.setText("dBV", juce::dontSendNotification);
        break;

    case 2: 
        unitLevelLabel.setText("V", juce::dontSendNotification);
        unitDecibelsLabel.setText("dBu", juce::dontSendNotification);
        break;

    case 3: 
        unitLevelLabel.setText("V", juce::dontSendNotification);
        unitDecibelsLabel.setText("dBuV", juce::dontSendNotification);
        break;

    case 4: 
        unitLevelLabel.setText("mV", juce::dontSendNotification);
        unitDecibelsLabel.setText("dBmV", juce::dontSendNotification);
        break;

    case 5: 
        unitLevelLabel.setText("uV", juce::dontSendNotification);
        unitDecibelsLabel.setText("dBuV", juce::dontSendNotification);
        break;

    default: break;
    }
}
