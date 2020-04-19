#include "Recorder.h"

int playback_tick(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
	double streamTime, RtAudioStreamStatus status, void* dataPointer)
{
	QTextStream(stdout) << "tick" << endl;
	/*auto* sine = static_cast<SquareWave*>(dataPointer);*/
	/*auto* samples = static_cast<StkFloat*>(outputBuffer);*/

	/*for (unsigned int i = 0; i < nBufferFrames; i++)
		*samples++ = sine->tick();*/

	return 1;
}

void Recorder::startRecord()
{
	active_ = true;
}

void Recorder::stopRecord()
{
	active_ = false;
}

bool Recorder::isRecording()
{
	return active_;
}

void Recorder::saveSamples(stk::StkFloat* samples, unsigned int nBufferFrames)
{
	samples_.insert(samples_.end(), &samples[0], &samples[nBufferFrames - 1]);
	recorded_notes_.push_back(last_played_note);
}

void Recorder::playback()
{
	RtAudio::StreamParameters parameters;
	parameters.deviceId = playback_->getDefaultOutputDevice();
	parameters.nChannels = 1;
	auto format = (sizeof(stk::StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
	auto bufferFrames = RT_BUFFER_SIZE;

	try {
		playback_->openStream(&parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &playback_tick, (void*)&samples_);
		playback_->startStream();
	}
	catch (RtAudioError & error) {
		throw error;
	}
}
