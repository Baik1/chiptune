#pragma once
#include "RtAudio.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

/* Handles recording and playback for a given track */
class Recorder
{
private:
	RtAudio audio_;
	bool active = false;
	float active_file[30];
public:
	Recorder() = default;
	Recorder(RtAudio& audio) { audio_ = audio; }
	~Recorder() = default;
	int startRecord();
	int stopRecord();
};

