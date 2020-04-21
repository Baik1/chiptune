#pragma once
#include <RtAudio.h>
#include <vector>
#include "SquareWave.h"
#include <QTextStream>
#include <array>
#include <set>

/* Handles recording for a given track */
class Recorder
{
private:
	bool active_ = false;
	std::vector<std::array<int, 4>> recorded_notes_;
	std::set<int> last_played_notes;
public:
	Recorder() = default;
	~Recorder() = default;

	void setLastPlayedNote(int n);
	void resetNote(int n);

	std::vector<std::array<int, 4>> getRecordedNotes() { return recorded_notes_; };

	void startRecord();
	void stopRecord();
	bool isRecording();
	void saveSamples();
};

