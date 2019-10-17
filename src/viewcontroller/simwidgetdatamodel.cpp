//*************************************************************************
/** \file
*  \brief Contains the implementation of class SimWidgetDatamodel.
*/

#define _USE_MATH_DEFINES
#include "simwidgetdatamodel.h"
#include "simulationwidget.h"
#include <QVector3D>
#include <cmath>

//******************************************************************************
//! Constructor of class SimWidgetDatamodel
/*!
*	\param SimulationWidget.
*	\param parent QT parent pointer.
*	\return none.
*/

SimWidgetDatamodel::SimWidgetDatamodel(SimulationWidget* sw, QObject *parent) : QObject(parent)
{
    mSimWidget = sw;
    buildViewChain(parent);
}

//******************************************************************************
//! Build view chain
/*!
*	\param parent QT parent pointer.
*	\return none.
*/

void SimWidgetDatamodel::buildViewChain(QObject *parent)
{
    Deus_Ex_Factory* _factory;
    God*             _god;

    qDebug() << "[SimWidgetDatamodel::buildViewChain]  Begin: Define which god will be created.\n";

    srand((unsigned)time(NULL));
    switch (rand() % 3)
    {
    case 0:
        _factory = new Alah_Ex_Factory;
        break;
    case 1:
        _factory = new Jesus_Ex_Factory;
        break;
    case 2:
        _factory = new VeryHighDevLF_Ex_Factory;
        break;
    default:
        _factory = new VeryHighDevLF_Ex_Factory;
        break;
    }

    qDebug() << "[SimWidgetDatamodel::buildViewChain]  Create the choosen god...\n";

    _god = _factory->createGod();

    qDebug() << "\n[SimWidgetDatamodel::buildViewChain]  *** THE BEGINNING ***\n\n";

    god = new GodAdapter(parent, _god->getName());
    ourUniverseEntity = UniverseEntity::Instance(parent);
    god->createBigBang();

    delete _factory;
    delete _god;
    _factory = nullptr;
    _god = nullptr;
}

//******************************************************************************
//! Deconstructor of class SimWidgetDatamodel

SimWidgetDatamodel::~SimWidgetDatamodel()
{
    delete god;
    god = nullptr;
}

//******************************************************************************
//! Calculate next step for the whole universe
/*!
*	\param none.
*	\return none.
*/

void SimWidgetDatamodel::calcNextStep()
{
    ourUniverseEntity->calcNextStep();
    PlanetEntity* planetToObserve = god->getPlanetToObserve();
    if (planetToObserve)
    {
        QVector3D curPlanetPos = planetToObserve->getCurrentPosition();
        mSimWidget->setCameraPos(QVector3D(curPlanetPos[0], curPlanetPos[1], curPlanetPos[2]+2), curPlanetPos, QVector3D(0, 1, 0));
    }
}

//******************************************************************************
//! Redraw the whole universe
/*!
*	\param none.
*	\return none.
*/

void SimWidgetDatamodel::draw()
{
    ourUniverseEntity->draw();
}

//******************************************************************************
//! Initialise the whole universe
/*!
*	\param none.
*	\return none.
*/

void SimWidgetDatamodel::init(QOpenGLShaderProgram * p)
{
    ourUniverseEntity->init(p);
}

//******************************************************************************
//! Calling the challenge life forms method of the current god
/*!
*	\param none.
*	\return none.
*/

void SimWidgetDatamodel::challengeLifeForms()
{ 
    god->challengeLFEs();
}



