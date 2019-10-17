//*************************************************************************
/** \file
*  \brief Contains the implementation of class SimWidgetController.
*/

#include "simwidgetcontroller.h"
#include "simulationwidget.h"
#include "simwidgetdatamodel.h"
#include <random>

static std::random_device rd;
static std::mt19937_64 mt(rd());
static std::uniform_int_distribution<unsigned int> dist(0);

//******************************************************************************
//! Constructor of class SimWidgetController
/*!
*	\param SimulationWidget.
*	\param SimWidgetDatamodel.
*	\param parent QT parent pointer.
*	\return none.
*/

SimWidgetController::SimWidgetController(SimulationWidget *sw, SimWidgetDatamodel *dm, QObject *parent):QObject(parent)
{
    mDM = dm;
    mSimWidget = sw;
    mSimWidget->installEventFilter(this);
    fpsCount = 60;
    simTimer = new QTimer(parent);
    challengeTimer = new QTimer(parent);
    simTimer->setInterval(1000.0f/fpsCount);
    QObject::connect(simTimer, SIGNAL(timeout()), this, SLOT(advanceOneStep()));
    challengeTimer->setInterval(10000);
    QObject::connect(challengeTimer, SIGNAL(timeout()), this, SLOT(onChallengeTimer()));
    challengeTimer->start();
    simTimer->start();
    paused = false;
    stepMode = false;
}

//******************************************************************************
//! Deconstructor of class SimWidgetController

SimWidgetController::~SimWidgetController()
{
    mSimWidget->removeEventFilter(this);
    QObject::disconnect(simTimer, SIGNAL(timeout()), this, SLOT(advanceOneStep()));
    QObject::disconnect(challengeTimer, SIGNAL(timeout()), this, SLOT(onChallengeTimer()));
    challengeTimer->stop();
    simTimer->stop();
    delete challengeTimer;
    delete simTimer;
}

//******************************************************************************
//! Check if paused
/*!
*	\param none.
*	\return true if paused.
*/

bool SimWidgetController::isPaused()
{
    return paused;
}

//******************************************************************************
//! Check if any relevant input event was triggered
/*!
*	\param current QObject.
*	\param current event.
*	\return true if event was handled.
*/

bool SimWidgetController::eventFilter(QObject * obj, QEvent * ev)
{
    if (ev->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *pressEvent = static_cast<QMouseEvent*>(ev);
        if (pressEvent->x() != 0)
        {
            //NOT ASSIGNED
            return true;
        }
        else QObject::eventFilter(obj, ev);
    }
    else if (ev->type() == QEvent::KeyPress)
    {
        QKeyEvent *pressEvent = static_cast<QKeyEvent*>(ev);
        if (pressEvent->key() == Qt::Key_Space)
        {
            if(!stepMode)
            {
                if (!paused)
                {
                    paused = true;
                    qDebug() << "\n====== PAUSED ======\n";
                }
                else
                {
                    paused = false;
                    qDebug() << "\n===== UNPAUSED =====\n";
                }
            }
            return true;
        }
        else if (pressEvent->key() == Qt::Key_S)
        {
            if(!paused)
            {
                if(!stepMode)
                {
                    stepMode = true;
                    QObject::disconnect(simTimer, SIGNAL(timeout()), this, SLOT(advanceOneStep()));
                    QObject::disconnect(challengeTimer, SIGNAL(timeout()), this, SLOT(onChallengeTimer()));
                    qDebug() << "\n===== STEP MODE ACTIVATED =====";
                    qDebug() << "- 'A' TO SIMULATE A STEP ";
                    qDebug() << "- 'S' TO DEACTIVATE STEP MODE ";
                }
                else
                {
                    qDebug() << "===== STEP MODE DEACTIVATED =====\n";
                    QObject::connect(simTimer, SIGNAL(timeout()), this, SLOT(advanceOneStep()));
                    QObject::connect(challengeTimer, SIGNAL(timeout()), this, SLOT(onChallengeTimer()));
                    stepMode = false;
                }
            }
            return true;
        }
        else if (pressEvent->key() == Qt::Key_A)
        {
            if (!stepMode) for(int i = 0; i<5; i++) advanceOneStep();
            else advanceOneStep();
            return true;
        }
        else if (pressEvent->key() == Qt::Key_G)
        {
            onChallengeTimer();
            return true;
        }
        else if (pressEvent->key() == Qt::Key_H)
        {
            qDebug() << "\n======= HELP =======";
            qDebug() << "'SPACE'\t- PAUSE/UNPAUSE";
            qDebug() << "'S'\t- STEP MODE ON/OFF";
            qDebug() << "'A'\t- NORMAL MODE: HOLD TO ACCELERATE 5x";
            qDebug() << "   \t- STEP MODE:   SIMULATE A STEP";
            qDebug() << "'G'\t- TRIGGER GOD EVENT";
            qDebug() << "====== HELP_END ======\n";
            return true;
        }
        else
            return QObject::eventFilter(obj, ev);
    }
    return false;
}

//******************************************************************************
//! Advance one step by calculating the next step and updating the view with the new data
/*!
*	\param none.
*	\return none.
*/

void SimWidgetController::advanceOneStep()
{
    if(!paused)
    {
        mDM->calcNextStep();
        mSimWidget->update();
    }
}

//******************************************************************************
//! Trigger godly event and set the challenge timer interval to a random value
/*!
*	\param none.
*	\return none.
*/

void SimWidgetController::onChallengeTimer()
{
    if(!paused)
    {
        mDM->challengeLifeForms();
        challengeTimer->setInterval((dist(mt) % 10000) + 0);
    }
}


