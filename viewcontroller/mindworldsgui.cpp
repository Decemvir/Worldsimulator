#include "mindworldsgui.h"
#include "ui_mindworldsgui.h"

MindWorldsGUI::MindWorldsGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MindWorldsGUI)
{
    ui->setupUi(this);
}

MindWorldsGUI::~MindWorldsGUI()
{
    delete ui;
}
