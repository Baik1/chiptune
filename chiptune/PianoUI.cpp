#include "PianoUI.h"

PianoUI::PianoUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

PianoUI::~PianoUI() = default;

void PianoUI::pressNote(QPushButton* button) {
	ui.noteLabel->setText("Test");
}
