#pragma once
#include <RtAudio.h>
#include "SquareWave.h"

/* Handles recording and playback for a given track */

/* TODO: Create this class as a singleton instead of a global static variable */
class Recorder
{
private:
	bool active_ = false;
	stk::StkFloat samples_[300];
public:
	Recorder() = default;
	~Recorder() = default;
	void startRecord();
	void stopRecord();
	bool isRecording();
};

