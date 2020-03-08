#include <cmath>
#include "MusicUtility.h"

float BASE_NOTE = 440;

float notes_frequency(NOTES note)
{
    return BASE_NOTE * pow(2, (float(note) / 12.f));
}