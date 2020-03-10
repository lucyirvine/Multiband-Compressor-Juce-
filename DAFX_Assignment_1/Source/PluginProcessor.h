/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class Dafx_assignment_1AudioProcessor  : public AudioProcessor
{
public:
    
    float cutoffLP;
    float cutoffHP;
    //compressor
    float threshold=0.0;
    float ratio = 1;
    float tau_attack = 1;
    float tau_release = 250;
    float makeUpGain;
    
    float thresholdH=0.0;
    float ratioH = 1;
    float tau_attackH = 1;
    float tau_releaseH = 250;
    float makeUpGainH;
    
    float thresholdB=0.0;
    float ratioB = 1;
    float tau_attackB = 1;
    float tau_releaseB = 250;
    float makeUpGainB;
    
    bool lowPassBool = false;
    bool bandPassBool = false;
    bool highPassBool = false;
    //==============================================================================
    Dafx_assignment_1AudioProcessor();
    ~Dafx_assignment_1AudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void calculateCoefficients(const double cFrequency, const double Q, const double lastSampleRate);

    void compressor(AudioSampleBuffer &compressorBuffer, float threshold_, float ratio_, float tau_attack_, float tau_release_, float makeUpGain_, float inlvl, float inGain, float outlvl, float  outGain, float cntrlvl, float yLprev);
    void resetAll();
    

private:
    
    //crossover filter
    float lastSampleRate;
    //float numSamples;
    //AudioSampleBuffer inputBufferLP_L;
    //AudioSampleBuffer inputBufferLP_R;

    float inlvlH;
    float inGainH;
    float outGainH;
    float outlvlH;
                        
    float cntrlvlH;
    float ylPrevH;
                        
    float inlvlB;
    float inGainB;
    float outGainB;
    float outlvlB;
                        
    float cntrlvlB;
    float ylPrevB;

    float inlvlL;
    float inGainL;
    float outGainL;
    float outlvlL;
                        
    float cntrlvlL;
    float ylPrevL;
    
    //float x1HP;
    //float x2HP;
    //float y1HP;
    //float y2HP;
    
    
    
    
    int M;
    float bufferSize;
    
    
    AudioBuffer<float> compressorBuffer;
    //HeapBlock<float> xg1, xl1, yg1, yl1;
    //HeapBlock<float> xg2, xl2, yg2, yl2;
    //HeapBlock<float> xg3, xl3, yg3, yl3;
    HeapBlock<float> c1;
    HeapBlock<float> c2;
    HeapBlock<float> c3;
    //float yLprev1;
    //float yLprev2;
    //float yLprev3;
    
    
    IIRFilter lowPassR;
    IIRFilter lowPassL;
    IIRFilter lowPassR2;
    IIRFilter lowPassL2;
    
    IIRFilter highPassR;
    IIRFilter highPassL;
    IIRFilter highPassR2;
    IIRFilter highPassL2;
    
    
    IIRFilter highPassBL;
    IIRFilter highPassBR;
    IIRFilter lowPassBL;
    IIRFilter lowPassBR;
    
    IIRFilter highPassBL2;
    IIRFilter highPassBR2;
    IIRFilter lowPassBL2;
    IIRFilter lowPassBR2;
    
    //float lastSamples[buffer.getNumSamples()];
    
   
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Dafx_assignment_1AudioProcessor)
};
