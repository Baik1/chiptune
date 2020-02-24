#include "PianoUI.h"
#include <QThread>

class PlayNotes :public QThread
{
	QAbstractButton* pianoTiles;
	Ui::PianoUI ui;

    void run() override
	{
        while (pianoTiles->isDown())
        {
            //... do some stuff here
        }
	}
public:
	PlayNotes(QAbstractButton* btn, Ui::PianoUI ui) : pianoTiles(btn), ui(ui) {}
};

PianoUI::PianoUI(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setButtonGroup();
	initEvents();
}

PianoUI::~PianoUI() = default;

void PianoUI::pressNote(int noteId)
{
	NOTES note = static_cast<NOTES>(noteId);
	ui.noteLabel->setText(notesToString[note]);
	PlayNotes* play_notes = new PlayNotes(pianoNotes->button(noteId), ui);
	connect(play_notes, &PlayNotes::finished, play_notes, &QObject::deleteLater);
	play_notes->start();
}


// TODO: There's probably a cleaner way to do this...
void PianoUI::setButtonGroup()
{
	pianoNotes = new QButtonGroup(this);
	pianoNotes->addButton(ui.NoteA3, A3);
	pianoNotes->addButton(ui.NoteA3Flat, A3Flat);
	pianoNotes->addButton(ui.NoteB3, B3);
	pianoNotes->addButton(ui.NoteC3, C3);
	pianoNotes->addButton(ui.NoteC3Flat, C3Flat);
	pianoNotes->addButton(ui.NoteD3, D3);
	pianoNotes->addButton(ui.NoteD3Flat, D3Flat);
	pianoNotes->addButton(ui.NoteE3, E3);
	pianoNotes->addButton(ui.NoteF3, F3);
	pianoNotes->addButton(ui.NoteF3Flat, F3Flat);
	pianoNotes->addButton(ui.NoteG3, G3);
	pianoNotes->addButton(ui.NoteG3Flat, G3Flat);
	pianoNotes->addButton(ui.NoteA4, A4);
	pianoNotes->addButton(ui.NoteA4Flat, A4Flat);
	pianoNotes->addButton(ui.NoteB4, B4);
	pianoNotes->addButton(ui.NoteC4, C4);
	pianoNotes->addButton(ui.NoteC4Flat, C4Flat);
	pianoNotes->addButton(ui.NoteD4, D4);
	pianoNotes->addButton(ui.NoteD4Flat, D4Flat);
	pianoNotes->addButton(ui.NoteE4, E4);
	pianoNotes->addButton(ui.NoteF4, F4);
	pianoNotes->addButton(ui.NoteF4Flat, F4Flat);
	pianoNotes->addButton(ui.NoteG4, G4);
	pianoNotes->addButton(ui.NoteG4Flat, G4Flat);
	pianoNotes->addButton(ui.NoteA5, A5);
	pianoNotes->addButton(ui.NoteA5Flat, A5Flat);
	pianoNotes->addButton(ui.NoteB5, B5);
	pianoNotes->addButton(ui.NoteC5, C5);
	pianoNotes->addButton(ui.NoteC5Flat, C5Flat);
	pianoNotes->addButton(ui.NoteD5, D5);
}

void PianoUI::initEvents()
{
	connect(pianoNotes, QOverload<int>::of(&QButtonGroup::buttonClicked),
		[=](int noteId) { pressNote(noteId); });
}
