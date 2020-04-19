#include "Recorder.h"

void Recorder::startRecord()
{
	active_ = true;
}

void Recorder::stopRecord()
{
	active_ = false;
}

bool Recorder::isRecording()
{
	return active_;
}

void Recorder::saveSamples(stk::StkFloat* samples, unsigned int nBufferFrames)
{
	samples_.insert(samples_.end(), &samples[0], &samples[nBufferFrames - 1]);
	recorded_notes_.push_back(last_played_note);
}
