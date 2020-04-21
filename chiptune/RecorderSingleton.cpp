#include "RecorderSingleton.h"

Recorder* RecorderSingleton::instance = 0;

Recorder* RecorderSingleton::getInstance()
{
    if (instance == 0)
    {
        instance = new Recorder();
    }
    return instance;
}
