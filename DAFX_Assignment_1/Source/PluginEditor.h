/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Dafx_assignment_1AudioProcessorEditor  : public AudioProcessorEditor,private Slider::Listener
{
public:
    Dafx_assignment_1AudioProcessorEditor (Dafx_assignment_1AudioProcessor&);
    ~Dafx_assignment_1AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Dafx_assignment_1AudioProcessor& processor;
    
    Slider filterCutoffLP;
    Slider filterCutoffHP;
    
    Slider threshold;
    Slider ratio;
    Slider tauAttack;
    Slider tauRelease;
    Slider makeUpGain;
    
    Label frequencyLabel;
    Label thresholdLabel;
    Label ratioLabel;
    Label tauAttackLabel;
    Label tauReleaseLabel;
    Label makeUpGainLabel;
    
    Slider thresholdH;
    Slider ratioH;
    Slider tauAttackH;
    Slider tauReleaseH;
    Slider makeUpGainH;
    
    Label frequencyLabelH;
    Label thresholdLabelH;
    Label ratioLabelH;
    Label tauAttackLabelH;
    Label tauReleaseLabelH;
    Label makeUpGainLabelH;
    
    Slider thresholdB;
    Slider ratioB;
    Slider tauAttackB;
    Slider tauReleaseB;
    Slider makeUpGainB;
    
    Label frequencyLabelB;
    Label thresholdLabelB;
    Label ratioLabelB;
    Label tauAttackLabelB;
    Label tauReleaseLabelB;
    Label makeUpGainLabelB;
    
    void sliderValueChanged (Slider* slider) override;
    void setSliders(Label label, const String text);
    void setSlider(Slider &slider, Label &label, String text);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Dafx_assignment_1AudioProcessorEditor)
};
