#pragma once

#include <atomic>
#include <concurrent_unordered_map.h>
#include "MusicUtility.h"
#include "SquareWave.h"

class Sounds_Manager
{
    using container = Concurrency::concurrent_unordered_map<NOTES, SquareWave>;
    SquareWave test;
    container pianoNotes;
    std::atomic<int> pressedNotes;
    int maxNotes;

public:
    Sounds_Manager()
    {
        pianoNotes = container();
        pressedNotes = 0;
        maxNotes = 3;
    }

    int getMaxNote()
    {
        return maxNotes;
    }
    void setMaxNote(int max)
    {
        maxNotes = max;
    }

    bool CanPress()
    {
        return pressedNotes < maxNotes;
    }


    void keyOn(NOTES note)
    {
        if (pianoNotes.find(note) == pianoNotes.end())
            pianoNotes[note] = SquareWave(notes_frequency(note), 0.01);
        pianoNotes[note].keyOn();
        ++pressedNotes;
    }

    void keyOff(NOTES note)
    {
        test.keyOff();
        pianoNotes[note].keyOff();
        --pressedNotes;
    }

    StkFloat tick()
    {
        double val = 0.0;
        for(auto& it : pianoNotes)
            val += it.second.tick();
        val /= maxNotes;
        return val > 1 ? 1 : val;
    }
};