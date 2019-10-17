#ifndef MINDWORLDSGUI_H
#define MINDWORLDSGUI_H

#include <QMainWindow>

namespace Ui {
class MindWorldsGUI;
}

class MindWorldsGUI : public QMainWindow
{
    Q_OBJECT

    public:
      explicit MindWorldsGUI(QWidget *parent = nullptr);
      ~MindWorldsGUI();

    private:
      Ui::MindWorldsGUI *ui;
};

#endif // MINDWORLDSGUI_H
