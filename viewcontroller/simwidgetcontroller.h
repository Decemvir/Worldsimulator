//*************************************************************************
/** \file
*  \brief Contains the declaration of class SimWidgetController.
*/

#pragma once

#include <QObject>
#include <QMouseEvent>
#include <QTimer>

class SimulationWidget;
class SimWidgetDatamodel;

//*************************************************************************
/*!	\class SimWidgetController 
*	\brief Represents the Controller of the Model-View-Controller
*		   Triggers the calculation of the next step, the update of the view and the godly challenges.
*		   Processes all input events.
*/

class SimWidgetController : public QObject
{
    Q_OBJECT

    public:
      SimWidgetController(SimulationWidget* sw, SimWidgetDatamodel *dm, QObject *parent);
      ~SimWidgetController();
    private:
      bool eventFilter(QObject *obj, QEvent *ev);
      bool isPaused();
      SimulationWidget* mSimWidget;
      SimWidgetDatamodel* mDM;
      QTimer* simTimer;
      QTimer* challengeTimer;
      bool paused;
      bool stepMode;
      double fpsCount;
    protected slots:
      void advanceOneStep();
      void onChallengeTimer();
};
