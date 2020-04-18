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
