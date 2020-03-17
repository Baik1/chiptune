#include <QThread>
#include <RtAudio.h>
#include <QKeyEvent>

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

	return 0;
}

void PianoUI::GUI_board::run()
{
    auto note = static_cast<NOTES>(noteId_);
	sounds_.keyOn();
	while (pianoNotes_->button(noteId_)->isDown()) { /*On attend la fin*/ };
	sounds_.keyOff();
}

PianoUI::PianoUI(QWidget* parent)
	: QWidget(parent)
{
	ui().setupUi(this);
	setButtonGroup();
	initEvents();

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

}

// TODO: Find a cleaner and faster way to do this.
void PianoUI::keyPressEvent(QKeyEvent* event)
{
	if (KeyToNotes.count(event->key()) > 0) {
		auto note = KeyToNotes[event->key()];
		ui().noteLabel->setText(notesToString[note]);
		sounds_.setFrequency(notes_frequency(note));
		sounds_.keyOn();
	}
    /*
    int a = event->key();
	switch (event->key())
	{
	case Qt::Key_A:
		ui().NoteA3->animateClick();
		break;
	case Qt::Key_W:
		ui().NoteA3Flat->animateClick();
		break;
	case Qt::Key_S:
		ui().NoteB3->animateClick();
		break;
	case Qt::Key_E:
		ui().NoteC3->animateClick();
		break;
	case Qt::Key_D:
		ui().NoteC3Flat->animateClick();
		break;
	case Qt::Key_R:
		ui().NoteD3->animateClick();
		break;
	case Qt::Key_F:
		ui().NoteD3Flat->animateClick();
		break;
	case Qt::Key_T:
		ui().NoteE3->animateClick();
		break;
	case Qt::Key_G:
		ui().NoteF3->animateClick();
		break;
	case Qt::Key_Y:
		ui().NoteF3Flat->animateClick();
		break;
	case Qt::Key_H:
		ui().NoteG3->animateClick();
		break;
	case Qt::Key_U:
		ui().NoteG3Flat->animateClick();
		break;
	case Qt::Key_J:
		ui().NoteA4->animateClick();
		break;
	case Qt::Key_I:
		ui().NoteA4Flat->animateClick();
		break;
	case Qt::Key_K:
		ui().NoteB4->animateClick();
		break;
	case Qt::Key_O:
		ui().NoteC4->animateClick();
		break;
	case Qt::Key_L:
		ui().NoteC4Flat->animateClick();
		break;
	case Qt::Key_P:
		ui().NoteD4->animateClick();
		break;
	case Qt::Key_Z:
		ui().NoteD4Flat->animateClick();
		break;
	case Qt::Key_X:
		ui().NoteE4->animateClick();
		break;
	case Qt::Key_C:
		ui().NoteF4->animateClick();
		break;
	case Qt::Key_V:
		ui().NoteF4Flat->animateClick();
		break;
	case Qt::Key_B:
		ui().NoteG4->animateClick();
		break;
	case Qt::Key_N:
		ui().NoteG4Flat->animateClick();
		break;
	case Qt::Key_1:
		ui().NoteA5->animateClick();
		break;
	case Qt::Key_2:
		ui().NoteA5Flat->animateClick();
		break;
	case Qt::Key_3:
		ui().NoteB5->animateClick();
		break;
	case Qt::Key_4:
		ui().NoteC5->animateClick();
		break;
	case Qt::Key_5:
		ui().NoteC5Flat->animateClick();
		break;
	case Qt::Key_6:
		ui().NoteD5->animateClick();
		break;
	default:
		break;
	}*/
}

void PianoUI::keyReleaseEvent(QKeyEvent* event)
{
	if (KeyToNotes.count(event->key()) > 0) {
		sounds_.keyOff();
	}
}

void PianoUI::pressNote(int noteId)
{
	auto note = static_cast<NOTES>(noteId);
	ui().noteLabel->setText(notesToString[note]);
	sounds_.setFrequency(notes_frequency(note));

	auto play_notes = new GUI_board(noteId, pianoNotes, sounds_);
	connect(play_notes, &GUI_board::finished, play_notes, &QObject::deleteLater);
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