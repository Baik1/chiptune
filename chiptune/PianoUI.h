#pragma once

#include <QWidget>
#include "ui_PianoUI.h"
#include "notes_enum.cpp"

class PianoUI : public QWidget
{
	Q_OBJECT

public:
	PianoUI(QWidget *parent = Q_NULLPTR);
	~PianoUI();

public slots:
	void PianoUI::pressNote(int noteId);

private:
	Ui::PianoUI ui;
	QButtonGroup* pianoNotes;

	void PianoUI::setButtonGroup();
	void PianoUI::initEvents();
};
