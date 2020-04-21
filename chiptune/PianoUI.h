#pragma once

#include <QThread>
#include <RtAudio.h>
#include "ui_PianoUI.h"

#include "SoundsManager.h";
#include "SquareWave.h"
#include <SpeedTest.h>
#include <Recorder.h>

#include <RecorderSingleton.h>

#include <QKeyEvent>

class PianoUI : public QWidget
{
	Q_OBJECT

	class GUI_board :public QThread
	{
		int noteId_;
		QButtonGroup* pianoNotes_;
		Sounds_Manager& sounds_;
		SpeedTest& speed_test_;

		void run() override;
	public:
		GUI_board(int note, QButtonGroup* pianoNotes, Sounds_Manager& sounds, SpeedTest& test) : noteId_(note), pianoNotes_(pianoNotes), sounds_(sounds), speed_test_(test) {}
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
	void PianoUI::toggleRecording();

	void startPlayback();
	
private:
	bool play_sounds = false;
	RtAudio audio_;
	Sounds_Manager sounds_;

	SpeedTest speed_test_;

	Ui::PianoUI ui_;
	QButtonGroup* pianoNotes;

	void PianoUI::setButtonGroup();
	void PianoUI::initEvents();
};
