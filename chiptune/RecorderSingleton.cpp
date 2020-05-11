#include "RecorderSingleton.h"



Recorder* RecorderSingleton::getInstance()
{
    static Recorder instance;
    return &instance;
}
