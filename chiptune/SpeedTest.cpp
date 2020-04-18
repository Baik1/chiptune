#include "SpeedTest.h"

void SpeedTest::startTimer()
{
	start_time = std::chrono::high_resolution_clock::now();
}

void SpeedTest::endTimer()
{
	auto current_time = std::chrono::high_resolution_clock::now();
	total_time = std::chrono::duration_cast<std::chrono::duration<time_t>>(current_time - start_time);
}

void SpeedTest::printTimeInMilliseconds()
{
	time_t time_in_sec = total_time.count();
	QTextStream(stdout) << "Elapsed time in seconds : " << time_in_sec << endl;
}
