#include <ui_PianoUI.h>
#include <PianoUI.h>
#include <Stk.h>

using stk::Stk;

int main(int argc, char *argv[])
{
    // Set the global sample rate before creating class instances.
    Stk::setSampleRate(44100.0);
    QApplication app(argc, argv);
    int code = 0;
    try
    {
        PianoUI ui;
        ui.show();
        code = app.exec();
        ui.audio().closeStream();
    }
    catch (RtAudioError& error)
    {
        error.printMessage();
    }

    return code;
}
