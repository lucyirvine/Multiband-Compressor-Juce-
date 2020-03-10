/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Dafx_assignment_1AudioProcessor::Dafx_assignment_1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

Dafx_assignment_1AudioProcessor::~Dafx_assignment_1AudioProcessor()
{
}

//==============================================================================
const String Dafx_assignment_1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Dafx_assignment_1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Dafx_assignment_1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Dafx_assignment_1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Dafx_assignment_1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Dafx_assignment_1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Dafx_assignment_1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Dafx_assignment_1AudioProcessor::setCurrentProgram (int index)
{
}

const String Dafx_assignment_1AudioProcessor::getProgramName (int index)
{
    return {};
}

void Dafx_assignment_1AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Dafx_assignment_1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lowPassBool = false;
    bandPassBool = false;
    highPassBool = false;
    
    //numSamples =  getTotalNumInputChannels();
    lastSampleRate = sampleRate;
    M = round(getNumInputChannels()/2);
    bufferSize = getBlockSize();
    //low pass initialization
    lowPassL.setCoefficients(IIRCoefficients::makeLowPass(lastSampleRate, cutoffHP));
    lowPassR.setCoefficients(IIRCoefficients::makeLowPass(lastSampleRate, cutoffHP));
    lowPassL2.setCoefficients(IIRCoefficients::makeLowPass(lastSampleRate, cutoffHP));
    lowPassR2.setCoefficients(IIRCoefficients::makeLowPass(lastSampleRate, cutoffHP));
    
    
    //band pass initialization
    lowPassBL.setCoefficients(IIRCoefficients::makeLowPass(lastSampleRate, cutoffHP));
    lowPassBR.setCoefficients(IIRCoefficients::makeLowPass(lastSampleRate, cutoffHP));
    lowPassBL2.setCoefficients(IIRCoefficients::makeLowPass(lastSampleRate, cutoffHP));
    lowPassBR2.setCoefficients(IIRCoefficients::makeLowPass(lastSampleRate, cutoffHP));
    highPassBL.setCoefficients(IIRCoefficients::makeHighPass(lastSampleRate, cutoffLP));
    highPassBR.setCoefficients(IIRCoefficients::makeHighPass(lastSampleRate, cutoffLP));
    highPassBL2.setCoefficients(IIRCoefficients::makeHighPass(lastSampleRate, cutoffLP));
    highPassBR2.setCoefficients(IIRCoefficients::makeHighPass(lastSampleRate, cutoffLP));
    
    //high pass initialization
    highPassL.setCoefficients(IIRCoefficients::makeHighPass(lastSampleRate, cutoffLP));
    highPassR.setCoefficients(IIRCoefficients::makeHighPass(lastSampleRate, cutoffLP));
    highPassL2.setCoefficients(IIRCoefficients::makeHighPass(lastSampleRate, cutoffLP));
    highPassR2.setCoefficients(IIRCoefficients::makeHighPass(lastSampleRate, cutoffLP));
    // reset all variables used for compressor function
    resetAll();
    
}

void Dafx_assignment_1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Dafx_assignment_1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif








void Dafx_assignment_1AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    bufferSize = buffer.getNumSamples();
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    //create empty buffers for the crossover filter
    AudioSampleBuffer lowPass;
    AudioSampleBuffer highPass;
    AudioSampleBuffer bandPass;
    
    //copy main buffer into each EQ band
    lowPass.makeCopyOf(buffer);
    highPass.makeCopyOf(buffer);
    bandPass.makeCopyOf(buffer);
    
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //low pass update
    lowPassL.setCoefficients(IIRCoefficients::makeLowPass(lastSampleRate, cutoffLP));
    lowPassL2.setCoefficients(IIRCoefficients::makeLowPass(lastSampleRate, cutoffLP));
    lowPassR.setCoefficients(IIRCoefficients::makeLowPass(lastSampleRate, cutoffLP));
    lowPassR2.setCoefficients(IIRCoefficients::makeLowPass(lastSampleRate, cutoffLP));
    
    //high pass update
    highPassL.setCoefficients(IIRCoefficients::makeHighPass(lastSampleRate, cutoffHP));
    highPassL2.setCoefficients(IIRCoefficients::makeHighPass(lastSampleRate, cutoffHP));
    highPassR.setCoefficients(IIRCoefficients::makeHighPass(lastSampleRate, cutoffHP));
    highPassR2.setCoefficients(IIRCoefficients::makeHighPass(lastSampleRate, cutoffHP));
    
    //band pass update
    lowPassBL.setCoefficients(IIRCoefficients::makeLowPass(lastSampleRate, cutoffHP));
    lowPassBL2.setCoefficients(IIRCoefficients::makeLowPass(lastSampleRate, cutoffHP));
    highPassBL.setCoefficients(IIRCoefficients::makeHighPass(lastSampleRate, cutoffLP));
    highPassBL2.setCoefficients(IIRCoefficients::makeHighPass(lastSampleRate, cutoffLP));
    lowPassBR.setCoefficients(IIRCoefficients::makeLowPass(lastSampleRate, cutoffHP));
    lowPassBR2.setCoefficients(IIRCoefficients::makeLowPass(lastSampleRate, cutoffHP));
    highPassBR.setCoefficients(IIRCoefficients::makeHighPass(lastSampleRate, cutoffLP));
    highPassBR2.setCoefficients(IIRCoefficients::makeHighPass(lastSampleRate, cutoffLP));
    
    
    
    //low pass process
    lowPassL.processSamples(lowPass.getWritePointer(0), buffer.getNumSamples());
    lowPassL2.processSamples(lowPass.getWritePointer(0), buffer.getNumSamples());
    lowPassR.processSamples(lowPass.getWritePointer(1), buffer.getNumSamples());
    lowPassR2.processSamples(lowPass.getWritePointer(1), buffer.getNumSamples());
    
    //band pass process
    lowPassBL.processSamples(bandPass.getWritePointer(0), bandPass.getNumSamples());
    lowPassBL2.processSamples(bandPass.getWritePointer(0), bandPass.getNumSamples());
    highPassBL.processSamples(bandPass.getWritePointer(0), bandPass.getNumSamples());
    highPassBL2.processSamples(bandPass.getWritePointer(0), bandPass.getNumSamples());
    
    lowPassBR.processSamples(bandPass.getWritePointer(1), bandPass.getNumSamples());
    lowPassBR2.processSamples(bandPass.getWritePointer(1), bandPass.getNumSamples());
    highPassBR.processSamples(bandPass.getWritePointer(1), bandPass.getNumSamples());
    highPassBR2.processSamples(bandPass.getWritePointer(1), bandPass.getNumSamples());
    
    //high pass process
    highPassL.processSamples(highPass.getWritePointer(0), buffer.getNumSamples());
    highPassL2.processSamples(highPass.getWritePointer(0), buffer.getNumSamples());
    highPassR.processSamples(highPass.getWritePointer(1), buffer.getNumSamples());
    highPassR2.processSamples(highPass.getWritePointer(1), buffer.getNumSamples());
    

  
    // send each EQ filter seperately to the compressor
    compressor(highPass,thresholdH,ratioH,tau_attackH,tau_releaseH,makeUpGainH, inlvlH, inGainH, outlvlH, outGainH, cntrlvlH, ylPrevH);
    compressor(lowPass,threshold,ratio,tau_attack,tau_release,makeUpGain, inlvlL, inGainL, outlvlL, outGainL, cntrlvlL, ylPrevL);
    compressor(bandPass,thresholdB,ratioB,tau_attackB,tau_releaseB,makeUpGainB, inlvlB, inGainB, outlvlB, outGainB, cntrlvlB, ylPrevB);

    //clear main buffer and add compressed bands back together
    buffer.clear();
    
    for(int channel = 0; channel<totalNumInputChannels; channel++){
        buffer.addFrom(channel, 0, lowPass, channel, 0, bufferSize,1.0/3.0);
        buffer.addFrom(channel, 0, bandPass, channel, 0, bufferSize, 1.0/3.0);
        buffer.addFrom(channel, 0, highPass, channel, 0, bufferSize,1.0/3.0);
        
    }
    
    
}



void Dafx_assignment_1AudioProcessor::compressor(AudioSampleBuffer &compressorBuffer, float threshold_, float ratio_, float tau_attack_, float tau_release_, float makeUpGain_, float inlvl, float inGain, float outlvl, float  outGain, float cntrlvl, float yLprev) {
   ///code adapted from Audio Effects: Theory, Implementation, and Applications by Joshua D. Reiss///
    
    
    //set attack and release times
    const auto alphaAttack = exp(-1/(0.001*lastSampleRate*tau_attack_));
    const auto alphaRelease =exp(-1/(0.001*lastSampleRate*tau_release_));
    int numSamples = compressorBuffer.getNumSamples();
    
    if(threshold_<0){
        for(int m = 0; m<M; ++m){

          
            for(int i = 0; i < numSamples; ++i)
            {   //level detection using peak detector
                if(fabs(compressorBuffer.getWritePointer(m)[i])<0.000001){ inGain=-120;}
                else{ inGain=20*log10(fabs(compressorBuffer.getWritePointer(m)[i]));}
                //Gain computer
                if(inGain>=threshold_){ outGain=threshold_+(inGain-threshold_)/ratio_;}
                else outGain = inGain;
                inlvl=inGain-outGain;
                
                //Smooth the gain
                if(inlvl>yLprev) outlvl=alphaAttack*yLprev+(1-alphaAttack)*inlvl;
                else outlvl=alphaRelease* yLprev+(1-alphaRelease)*inlvl;
                //find control
                cntrlvl=pow(10,(makeUpGain_-outlvl)/20);
                yLprev=outlvl;
            }
            for(int i = 0; i < bufferSize; i++)
            {
                //update values based on the control voltage
                compressorBuffer.getWritePointer(2*m+0)[i]*=cntrlvl;
                compressorBuffer.getWritePointer(2*m+1)[i]*=cntrlvl;
                
            }
     
            
        }
    }
   
    
}


void Dafx_assignment_1AudioProcessor::resetAll(){
    
    tau_attack=0;
    tau_release=0;
    threshold = 0;
    ratio = 1;
    makeUpGain = 0;

    
    inlvlH = 0;
    inGainH = 0;
    outlvlH= 0;
    outGainH = 0;
    cntrlvlH= 0;
    ylPrevH = 0;
    
    inlvlB = 0;
    inGainB = 0;
    outlvlB= 0;
    outGainB = 0;
    cntrlvlB= 0;
    ylPrevB = 0;
    
    inlvlL = 0;
    inGainL = 0;
    outlvlL= 0;
    outGainL = 0;
    cntrlvlL= 0;
    ylPrevL = 0;
    
}

//==============================================================================
bool Dafx_assignment_1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Dafx_assignment_1AudioProcessor::createEditor()
{
    return new Dafx_assignment_1AudioProcessorEditor (*this);
}

//==============================================================================
void Dafx_assignment_1AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Dafx_assignment_1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Dafx_assignment_1AudioProcessor();
}
