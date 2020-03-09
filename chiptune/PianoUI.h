#pragma once
#include <QThread>
#include <RtAudio.h>
#include <SineWave.h>

#include "ui_PianoUI.h"
#include "Envelope.h"
#include "SignalGenerator.h"

class PianoUI : public QWidget
{
	Q_OBJECT
		class PlayNotes :public QThread
	{
		int noteId;
		PianoUI* piano;

		void run() override;
	public:
		PlayNotes(int note, PianoUI* piano) : noteId(note), piano(piano) {}
	};

public:
	PianoUI(QWidget* parent = Q_NULLPTR);
	~PianoUI() = default;
	Ui::PianoUI& ui() { return ui_; }
	const Ui::PianoUI& ui() const { return ui_; }

	RtAudio& audio() { return audio_; }
	const RtAudio& audio() const { return audio_; }

public slots:
	void PianoUI::pressNote(int noteId);

private:
	bool play_sounds = false;
	RtAudio audio_;
	SignalGenerator sounds_;

	Ui::PianoUI ui_;
	QButtonGroup* pianoNotes;

	void PianoUI::setButtonGroup();
	void PianoUI::initEvents();
};
