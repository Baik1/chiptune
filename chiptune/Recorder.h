#pragma once
#include <RtAudio.h>
#include <vector>
#include "SquareWave.h"
#include <QTextStream>

/* Handles recording for a given track */
/* TODO: Create this class as a singleton instead of a global static variable */
class Recorder
{
private:
	RtAudio* playback_ = new RtAudio();
	bool active_ = false;
	std::vector<stk::StkFloat> samples_;

	SquareWave* sounds_;
	std::vector<int> recorded_notes_;
	int last_played_note = NULL;
public:
	Recorder() = default;
	~Recorder() = default;

	void setLastPlayedNote(int n) { last_played_note = n; }
	void setSounds(SquareWave* s) { sounds_ = s; }

	std::vector<int> getRecordedNotes() { return recorded_notes_; };

	void startRecord();
	void stopRecord();
	bool isRecording();
	void saveSamples(stk::StkFloat* samples, unsigned int nBufferFrames);
};

