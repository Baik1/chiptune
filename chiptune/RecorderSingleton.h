#pragma once
#include <Recorder.h>

class RecorderSingleton
{
private:
	static Recorder* instance;
	RecorderSingleton();		// to prevent instancing
public:
	static Recorder* getInstance();
};

