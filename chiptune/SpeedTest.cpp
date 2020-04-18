#include "SpeedTest.h"

void SpeedTest::startTimer()
{
	start_time = std::chrono::high_resolution_clock::now();
}

void SpeedTest::endTimer()
{
	auto current_time = std::chrono::high_resolution_clock::now();
	total_time = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - start_time);
}

void SpeedTest::printTimeInMilliseconds()
{
	double time_in_sec = total_time.count() * 1000;
	QTextStream(stdout) << "Latency for note X in milliseconds : " << time_in_sec << endl;
}
