#include "viewcontroller/mindworldsgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MindWorldsGUI w;
    w.show();

    return a.exec();
}
