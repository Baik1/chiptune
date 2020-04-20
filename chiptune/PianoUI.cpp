#include "PianoUI.h"
#include "MusicUtility.h"

using namespace stk;

int tick(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
	double streamTime, RtAudioStreamStatus status, void* dataPointer)
{
	auto* sine = static_cast<SquareWave*>(dataPointer);
    auto* samples = static_cast<StkFloat*>(outputBuffer);

	for (unsigned int i = 0; i < nBufferFrames; i++)
		*samples++ = sine->tick();

	if (r.isRecording())
	{
		r.saveSamples(samples, nBufferFrames);
	}

	return 0;
}

void PianoUI::GUI_board::run()
{
	speed_test_.startTimer();

    auto note = static_cast<NOTES>(noteId_);

	sounds_.keyOn();

	r.setLastPlayedNote(note);

	speed_test_.endTimer();
	speed_test_.printTimeInMilliseconds(notesToString[note]);

	while (pianoNotes_->button(noteId_)->isDown()) { /*On attend la fin*/ };
	sounds_.keyOff();

	r.setLastPlayedNote(NULL);

}

PianoUI::PianoUI(QWidget* parent)
	: QWidget(parent)
{
	ui().setupUi(this);
	setButtonGroup();
	initEvents();

	speed_test_ = SpeedTest();

	sounds_.setEnvelopeRate(0.01);
	RtAudio::StreamParameters parameters;
	parameters.deviceId = audio_.getDefaultOutputDevice();
	parameters.nChannels = 1;
    auto format = (sizeof(stk::StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    auto bufferFrames = RT_BUFFER_SIZE;

	try {
		audio_.openStream(&parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick, (void*)&sounds_);
		audio_.startStream();
	}
	catch (RtAudioError & error) {
		throw error;
	}

	r.setSounds(&sounds_);

}

void PianoUI::keyPressEvent(QKeyEvent* event)
{
	if (KeyToNotes.count(event->key()) > 0) {

		speed_test_.startTimer();
		
		auto note = KeyToNotes[event->key()];
		ui().noteLabel->setText(notesToString[note]);
		sounds_.setFrequency(notes_frequency(note));
		pianoNotes->button(note)->setDown(true);

		speed_test_.endTimer();
		speed_test_.printTimeInMilliseconds(notesToString[note]);

		sounds_.keyOn();

		/* save last note for recording */
		r.setLastPlayedNote(note);
	}
}

void PianoUI::keyReleaseEvent(QKeyEvent* event)
{
	if (KeyToNotes.count(event->key()) > 0) {
		auto note = KeyToNotes[event->key()];
		pianoNotes->button(note)->setDown(false);
	    sounds_.keyOff();

		/*save last note for recording */
		r.setLastPlayedNote(NULL);
	}
}

void PianoUI::pressNote(int noteId)
{
	auto note = static_cast<NOTES>(noteId);
	ui().noteLabel->setText(notesToString[note]);
	sounds_.setFrequency(notes_frequency(note));

	auto play_notes = new GUI_board(noteId, pianoNotes, sounds_, speed_test_);
	connect(play_notes, &GUI_board::finished, play_notes, &QObject::deleteLater);
	play_notes->start();
}

void PianoUI::toggleRecording() 
{
	if (r.isRecording()) 
	{
		r.stopRecord();
	}
	else 
	{
		r.startRecord();
	}
}

void PianoUI::startPlayback()
{
	const std::vector<int> playbackNotes = r.getRecordedNotes();

	int last_note = NULL;
	for (int i = 0; i < (playbackNotes.size()); ++i)
	{
		if (playbackNotes[i] != NULL && last_note != playbackNotes[i])
		{
			auto note = static_cast<NOTES>(playbackNotes[i]);
			pianoNotes->button(note)->animateClick(); /* press */
			Sleep(50); /* for delay between notes */
		}
	}
}

// Tentative with keyboard presses, this is not working well...
void PianoUI::startPlaybackKeyPresses()
{
	const std::vector<int> playbackNotes = r.getRecordedNotes();

	int last_note = NULL;
	for (int i = 0; i < (playbackNotes.size()); ++i)
	{
		if (playbackNotes[i] != NULL && last_note != playbackNotes[i])
		{
			auto note = static_cast<NOTES>(playbackNotes[i]);
			auto key = static_cast<Qt::Key>(NotesToKey[note]);
			QKeyEvent* keyPress = new QKeyEvent(QEvent::KeyPress, key, Qt::NoModifier);
			QCoreApplication::postEvent(this, keyPress);
		}
		else if (playbackNotes[i] == NULL && last_note != NULL)
		{
			auto note = static_cast<NOTES>(playbackNotes[i]);
			auto key = static_cast<Qt::Key>(NotesToKey[note]);
			QKeyEvent* keyReleased = new QKeyEvent(QEvent::KeyRelease, key, Qt::NoModifier);
			QCoreApplication::postEvent(this, keyReleased);
		}
		last_note = playbackNotes[i];
	}
}

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

	connect(ui().RecordButton, &QPushButton::released, this, &PianoUI::toggleRecording);
	connect(ui().PlaybackButton, &QPushButton::released, this, &PianoUI::startPlayback);
}