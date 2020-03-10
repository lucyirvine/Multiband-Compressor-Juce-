/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Dafx_assignment_1AudioProcessorEditor::Dafx_assignment_1AudioProcessorEditor(Dafx_assignment_1AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 800);
    
    setSlider(filterCutoffLP, frequencyLabel,"Cutoff LP");
    filterCutoffLP.setRange(20.0f, 600.0f);
    filterCutoffLP.setValue(200.0f);
    
    filterCutoffHP.setRange(2000.0f, 20000.0f);
    filterCutoffHP.setValue(750.0f);
    setSlider(filterCutoffHP, frequencyLabelH,"Cutoff HP");

    
    setSlider(threshold, thresholdLabel,"Threshold L");
    threshold.setRange(-60,0);
    threshold.setValue(0);

    setSlider(ratio, ratioLabel,"Ratio L");
    ratio.setRange(1,100);
    ratio.setValue(1);

    setSlider(tauAttack, tauAttackLabel,"Attack L");
    tauAttack.setRange(0.1,500);
    tauAttack.setValue(1);

    setSlider(tauRelease, tauReleaseLabel,"Release L");
    tauRelease.setRange(0.1,1000);
    tauRelease.setValue(100);

    setSlider(makeUpGain, makeUpGainLabel,"Gain L");
    makeUpGain.setRange(1,100);
    makeUpGain.setValue(0);

    setSlider(thresholdH, thresholdLabelH,"Threshold H");
    thresholdH.setRange(-60,0);
    thresholdH.setValue(0);

    setSlider(ratioH, ratioLabelH,"Ratio H");
    ratioH.setRange(1,100);
    ratioH.setValue(1);

    setSlider(tauAttackH, tauAttackLabelH,"Attack H");
    tauAttackH.setRange(0.1,500);
    tauAttackH.setValue(1);

    setSlider(tauReleaseH, tauReleaseLabelH,"Release H");
    tauReleaseH.setRange(0.1,1000);
    tauReleaseH.setValue(100);

    setSlider(makeUpGainH, makeUpGainLabelH,"Gain H");
    makeUpGainH.setRange(1,100);
    makeUpGainH.setValue(0);

    setSlider(thresholdB, thresholdLabelB,"Threshold B");
    thresholdB.setRange(-60,0);
    thresholdB.setValue(0);

    setSlider(ratioB, ratioLabelB,"Ratio B");
    ratioB.setRange(1,100);
    ratioB.setValue(1);

    setSlider(tauAttackB, tauAttackLabelB,"Attack B");
    tauAttackB.setRange(0.1,500);
    tauAttackB.setValue(1);
    
    setSlider(tauReleaseB, tauReleaseLabelB,"Release B");
    tauReleaseB.setRange(0.1,1000);
    tauReleaseB.setValue(100);


    setSlider(makeUpGainB, makeUpGainLabelB,"Make Up Gain B");
    makeUpGainB.setRange(1,100);
    makeUpGainB.setValue(0);
 
    
    getLookAndFeel().setColour(Slider::thumbColourId, Colours::azure);
    getLookAndFeel().setColour(Slider::rotarySliderOutlineColourId,Colours::royalblue);
}

void Dafx_assignment_1AudioProcessorEditor::setSlider(Slider &slider, Label &label, String text){
    slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(&slider);
    addAndMakeVisible(makeUpGainLabelB);
    label.setText(text, dontSendNotification);
    label.setJustificationType(Justification::centred);
    label.attachToComponent(&slider, false);
    
    slider.addListener(this);
}

Dafx_assignment_1AudioProcessorEditor::~Dafx_assignment_1AudioProcessorEditor()
{
}

//==============================================================================
void Dafx_assignment_1AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void Dafx_assignment_1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    const int border = 120;
    filterCutoffLP.setBounds (20, 50, 120, 120);
    threshold.setBounds (120, 50, 120, 120);
    ratio.setBounds (220, 50, 120, 120);
    makeUpGain.setBounds (20 , 200, 70, 70);
    tauAttack.setBounds (120 , 200, 70, 70);
    tauRelease.setBounds (220 , 200, 70, 70);
    
    thresholdH.setBounds (420, 50, 120, 120);
    ratioH.setBounds (520, 50, 120, 120);
    makeUpGainH.setBounds (420 , 200, 70, 70);
    tauAttackH.setBounds (520 , 200, 70, 70);
    tauReleaseH.setBounds (620 , 200, 70, 70);
    
    filterCutoffHP.setBounds (20, 300, 120, 120);
    thresholdB.setBounds (120, 300, 120, 120);
    ratioB.setBounds (220, 300, 120, 120);
    makeUpGainB.setBounds (20 , 500, 70, 70);
    tauAttackB.setBounds (120 , 500, 70, 70);
    tauReleaseB.setBounds (220 , 500, 70, 70);
    
}

void Dafx_assignment_1AudioProcessorEditor::sliderValueChanged(Slider* slider){

    processor.cutoffLP = filterCutoffLP.getValue();
    processor.threshold=threshold.getValue();
    processor.ratio=ratio.getValue();
    processor.makeUpGain=makeUpGain.getValue();
    processor.tau_attack=tauAttack.getValue();
    processor.tau_release=tauRelease.getValue();
    
    processor.cutoffHP = filterCutoffHP.getValue();
    processor.thresholdH=thresholdH.getValue();
    processor.ratioH=ratioH.getValue();
    processor.makeUpGainH=makeUpGainH.getValue();
    processor.tau_attackH=tauAttackH.getValue();
    processor.tau_releaseH=tauReleaseH.getValue();
    
    processor.thresholdB=thresholdB.getValue();
    processor.ratioB=ratioB.getValue();
    processor.makeUpGainB=makeUpGainB.getValue();
    processor.tau_attackB=tauAttackB.getValue();
    processor.tau_releaseB=tauReleaseB.getValue();
    
  
}

