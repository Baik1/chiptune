#pragma once
#include <chrono>
#include <QDebug>
#include <QTextStream>

/* Calculates the time from input to output in seconds */
class SpeedTest
{
private:
	std::chrono::high_resolution_clock::time_point start_time;
	std::chrono::duration<double> total_time;
public:
	SpeedTest() = default;
	~SpeedTest() = default;

	void startTimer();
	void endTimer();
	void printTimeInMilliseconds();
};

