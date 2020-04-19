#pragma once
#include <RtAudio.h>
#include <vector>
#include "SquareWave.h"
#include <QTextStream>

/* Handles recording and playback for a given track */

/* TODO: Create this class as a singleton instead of a global static variable */
class Recorder
{
private:
	RtAudio* playback_ = new RtAudio();
	bool active_ = false;
	std::vector<stk::StkFloat> samples_;
public:
	Recorder() = default;
	~Recorder() = default;
	void startRecord();
	void stopRecord();
	bool isRecording();
	void saveSamples(stk::StkFloat* samples, unsigned int nBufferFrames);
	void playback();
};

