#include "Recorder.h"

/* Max number of simultaneous registered notes are 4, to handle most typical piano chords */
void Recorder::setLastPlayedNote(int n)
{
	if (last_played_notes.size() < 4) 
	{
		last_played_notes.insert(n);
	}
}

void Recorder::resetNote(int n)
{
	auto it = last_played_notes.find(n);
	if (it != last_played_notes.end()) 
	{
		last_played_notes.erase(n);
	}
}

void Recorder::startRecord()
{
	recorded_notes_.clear();
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
	std::array<int, 4>notes_array = { NULL, NULL, NULL, NULL };
	int idx = 0;
	for (auto it = last_played_notes.begin(); it != last_played_notes.end(); ++it) {
		notes_array[idx] = *it;
		idx++;
	}
	recorded_notes_.push_back(notes_array);
}
