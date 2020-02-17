/*

	Notes go from A to G, with 3 denoting the note's octave.
	A int value is automatically associated to each note.

*/

#include <map>
enum NOTES
{ A3, A3Flat, B3, C3, C3Flat, D3, D3Flat, E3,
	F3, F3Flat, G3, G3Flat, A4, A4Flat, B4, C4,
	C4Flat, D4, D4Flat, E4, F4, F4Flat, G4, G4Flat,
	A5, A5Flat, B5, C5, C5Flat, D5
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
