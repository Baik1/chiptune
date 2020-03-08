#include <QApplication>
#include <qdebug.h>
#include <QtWidgets\qmainwindow.h>
#include <ui_PianoUI.h>
#include <PianoUI.h>
#include <Stk.h>

using stk::Stk;

int main(int argc, char *argv[])
{
    // Set the global sample rate before creating class instances.
    Stk::setSampleRate(44100.0);

    QApplication app(argc, argv);
    PianoUI ui;
    ui.show();

    int code = app.exec();

    // Shut down the output stream.
    try {
        ui.audio().closeStream();
    }
    catch (RtAudioError & error) {
        error.printMessage();
    }
    return code;
}
