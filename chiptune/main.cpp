#include <QApplication>
#include <qdebug.h>
#include <QtWidgets\qmainwindow.h>
#include <ui_PianoUI.h>
#include <PianoUI.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    PianoUI ui;
    ui.show();
    return app.exec();
}
