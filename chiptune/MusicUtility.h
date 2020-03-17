#pragma once
#include <map>
#include <cmath>
/*

    Notes go from A to G, with 3 denoting the note's octave.
    A int value is automatically associated to each note.

*/

enum NOTES
{
    A3, A3Flat, B3, C3, C3Flat, D3, D3Flat, E3,
    F3, F3Flat, G3, G3Flat, A4, A4Flat, B4, C4,
    C4Flat, D4, D4Flat, E4, F4, F4Flat, G4, G4Flat,
    A5, A5Flat, B5, C5, C5Flat, D5
};

static std::map<NOTES, const int > notesToInt = {
   {A3, -12},
   {A3Flat, -11},
   {B3, -10},
   {C3, -9},
   {C3Flat, -8},
   {D3, -7},
   {D3Flat, -6},
   {E3, -5},
   {F3, -4},
   {F3Flat, -3},
   {G3, -2},
   {G3Flat, -1},
   {A4, 0},
   {A4Flat, 1},
   {B4, 2},
   {C4, 3},
   {C4Flat, 4},
   {D4, 5},
   {D4Flat, 6},
   {E4, 7},
   {F4, 8},
   {F4Flat, 9},
   {G4, 10},
   {G4Flat, 11},
   {A5, 12},
   {A5Flat, 13},
   {B5, 14},
   {C5, 15},
   {C5Flat, 16},
   {D5, 17},
};

static std::map<int, NOTES  > KeyToNotes = {
   {Qt::Key_Q, A3},
   {Qt::Key_2, A3Flat},
   {Qt::Key_W, B3},
   {Qt::Key_E, C3},
   {Qt::Key_4, C3Flat},
   {Qt::Key_R, D3},
   {Qt::Key_5, D3Flat},
   {Qt::Key_T, E3},
   {Qt::Key_Y, F3},
   {Qt::Key_7, F3Flat},
   {Qt::Key_U, G3},
   {Qt::Key_8, G3Flat},
   {Qt::Key_I, A4},
   {Qt::Key_9, A4Flat},
   {Qt::Key_O, B4},
   {Qt::Key_A, C4},
   {Qt::Key_Z, C4Flat},
   {Qt::Key_S, D4},
   {Qt::Key_X, D4Flat},
   {Qt::Key_D, E4},
   {Qt::Key_F, F4},
   {Qt::Key_V, F4Flat},
   {Qt::Key_G, G4},
   {Qt::Key_B, G4Flat},
   {Qt::Key_H, A5},
   {Qt::Key_N, A5Flat},
   {Qt::Key_J, B5},
   {Qt::Key_K, C5},
   {Qt::Key_Comma, C5Flat},
   {Qt::Key_L, D5},
};

static std::map<NOTES, const char* > notesToString = {
   {A3, "A3"},
   {A3Flat, "A3#"},
   {B3, "B3"},
   {C3, "C3"},
   {C3Flat, "C3#"},
   {D3, "D3"},
   {D3Flat, "D3#"},
   {E3, "E3"},
   {F3, "F3"},
   {F3Flat, "F3#"},
   {G3, "G3"},
   {G3Flat, "G3#"},
   {A4, "A4"},
   {A4Flat, "A4#"},
   {B4, "B4"},
   {C4, "C4"},
   {C4Flat, "C4#"},
   {D4, "D4"},
   {D4Flat, "D4#"},
   {E4, "E4"},
   {F4, "F4"},
   {F4Flat, "F4#"},
   {G4, "G4"},
   {G4Flat, "G4#"},
   {A5, "A5"},
   {A5Flat, "A5#"},
   {B5, "B5"},
   {C5, "C5"},
   {C5Flat, "C5#"},
   {D5, "D5"},
};

float notes_frequency(NOTES note)
{
    const double R = pow(2.0, 1 / 12.0);
    const double A4_Frequency = 440.0;
    return A4_Frequency * pow(R, double(notesToInt[note]));
}

float notes_frequency(int note)
{
    const double R = pow(2.0, 1 / 12.0);
    const double A4_Frequency = 440.0;
    return A4_Frequency * pow(R, note);
}