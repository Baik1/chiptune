#pragma once


#include <QThread>
#include <RtAudio.h>
#include "ui_PianoUI.h"

#include "SquareWave.h"

class PianoUI : public QWidget
{
	Q_OBJECT

	class GUI_board :public QThread
	{
		int noteId_;
		QButtonGroup* pianoNotes_;
		SquareWave& sounds_;

		void run() override;
	public:
		GUI_board(int note, QButtonGroup* pianoNotes, SquareWave& sounds) : noteId_(note), pianoNotes_(pianoNotes), sounds_(sounds) {}
	};

public:
	PianoUI(QWidget* parent = Q_NULLPTR);
	~PianoUI() = default;
	Ui::PianoUI& ui() { return ui_; }
	const Ui::PianoUI& ui() const { return ui_; }

	RtAudio& audio() { return audio_; }
	const RtAudio& audio() const { return audio_; }

protected:
	void keyPressEvent(QKeyEvent*) override;
	void keyReleaseEvent(QKeyEvent*) override;

public slots:
	void PianoUI::pressNote(int noteId);
	
private:
	bool play_sounds = false;
	RtAudio audio_;
	SquareWave sounds_;

	Ui::PianoUI ui_;
	QButtonGroup* pianoNotes;

	void PianoUI::setButtonGroup();
	void PianoUI::initEvents();
};
