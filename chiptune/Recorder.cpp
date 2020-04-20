#include "Recorder.h"

void Recorder::startRecord()
{
	recorded_notes_.empty();
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

void Recorder::saveSamples()
{
	recorded_notes_.push_back(last_played_note);
}
