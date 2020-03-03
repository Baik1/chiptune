#pragma once
#include "ui_PianoUI.h"

class PianoUI : public QWidget
{
	Q_OBJECT

public:
	PianoUI(QWidget *parent = Q_NULLPTR);
	~PianoUI() = default;

public slots:
	void PianoUI::pressNote(int noteId);

private:
	Ui::PianoUI ui;
	QButtonGroup* pianoNotes;

	void PianoUI::setButtonGroup();
	void PianoUI::initEvents();
};
