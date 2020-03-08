#include <QThread>
#include <RtAudio.h>

#include "PianoUI.h"
#include "MusicUtility.h"

using namespace stk;

int tick(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
	double streamTime, RtAudioStreamStatus status, void* dataPointer)
{
	SineWave* sine = (SineWave*)dataPointer;
	register StkFloat* samples = (StkFloat*)outputBuffer;

	for (unsigned int i = 0; i < nBufferFrames; i++)
		*samples++ = sine->tick();

	return 0;
}

void PianoUI::PlayNotes::run()
{
	NOTES note = static_cast<NOTES>(noteId);

    try {
		piano->audio().startStream();
	}
	catch (RtAudioError & error) {
		error.printMessage();
		return;
	}

	while (piano->pianoNotes->button(noteId)->isDown())
	{
		//... do some stuff here
	}

	try {
		piano->audio().stopStream();
	}
	catch (RtAudioError & error) {
		error.printMessage();
		return;
	}
}


PianoUI::PianoUI(QWidget* parent)
	: QWidget(parent), audio_()
{
	ui().setupUi(this);
	setButtonGroup();
	initEvents();

	RtAudio::StreamParameters parameters;
	parameters.deviceId = audio_.getDefaultOutputDevice();
	parameters.nChannels = 1;
	RtAudioFormat format = (sizeof(stk::StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
	unsigned int bufferFrames = RT_BUFFER_SIZE;

	try {
		audio_.openStream(&parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick, (void*)&sounds_);
	}
	catch (RtAudioError & error) {
		error.printMessage();
		return;
	}

}

void PianoUI::pressNote(int noteId)
{
	NOTES note = static_cast<NOTES>(noteId);
	ui().noteLabel->setText(notesToString[note]);

	sounds_.setFrequency(notes_frequency(note));

	PlayNotes* play_notes = new PlayNotes(noteId, this);
	connect(play_notes, &PlayNotes::finished, play_notes, &QObject::deleteLater);
	play_notes->start();
}


// TODO: There's probably a cleaner way to do this...
void PianoUI::setButtonGroup()
{
	pianoNotes = new QButtonGroup(this);
	pianoNotes->addButton(ui().NoteA3, A3);
	pianoNotes->addButton(ui().NoteA3Flat, A3Flat);
	pianoNotes->addButton(ui().NoteB3, B3);
	pianoNotes->addButton(ui().NoteC3, C3);
	pianoNotes->addButton(ui().NoteC3Flat, C3Flat);
	pianoNotes->addButton(ui().NoteD3, D3);
	pianoNotes->addButton(ui().NoteD3Flat, D3Flat);
	pianoNotes->addButton(ui().NoteE3, E3);
	pianoNotes->addButton(ui().NoteF3, F3);
	pianoNotes->addButton(ui().NoteF3Flat, F3Flat);
	pianoNotes->addButton(ui().NoteG3, G3);
	pianoNotes->addButton(ui().NoteG3Flat, G3Flat);
	pianoNotes->addButton(ui().NoteA4, A4);
	pianoNotes->addButton(ui().NoteA4Flat, A4Flat);
	pianoNotes->addButton(ui().NoteB4, B4);
	pianoNotes->addButton(ui().NoteC4, C4);
	pianoNotes->addButton(ui().NoteC4Flat, C4Flat);
	pianoNotes->addButton(ui().NoteD4, D4);
	pianoNotes->addButton(ui().NoteD4Flat, D4Flat);
	pianoNotes->addButton(ui().NoteE4, E4);
	pianoNotes->addButton(ui().NoteF4, F4);
	pianoNotes->addButton(ui().NoteF4Flat, F4Flat);
	pianoNotes->addButton(ui().NoteG4, G4);
	pianoNotes->addButton(ui().NoteG4Flat, G4Flat);
	pianoNotes->addButton(ui().NoteA5, A5);
	pianoNotes->addButton(ui().NoteA5Flat, A5Flat);
	pianoNotes->addButton(ui().NoteB5, B5);
	pianoNotes->addButton(ui().NoteC5, C5);
	pianoNotes->addButton(ui().NoteC5Flat, C5Flat);
	pianoNotes->addButton(ui().NoteD5, D5);
}

void PianoUI::initEvents()
{
	connect(pianoNotes, QOverload<int>::of(&QButtonGroup::buttonPressed),
		[=](int noteId) { pressNote(noteId); });
}