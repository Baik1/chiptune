#pragma once

#include <QWidget>
#include "ui_PianoUI.h"

class PianoUI : public QWidget
{
	Q_OBJECT

public:
	PianoUI(QWidget *parent = Q_NULLPTR);
	~PianoUI();

private:
	Ui::PianoUI ui;
};
