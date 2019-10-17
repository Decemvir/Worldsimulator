//*************************************************************************
/** \file
*  \brief Contains the declaration of class SimWidgetDatamodel.
*/

#pragma once

#include "viewOfEntities.h"
#include <QObject>
#include <QOpenGLShaderProgram>
#include "universeEntity.h"
#include "godAdapter.h"
#include "../model/god/alahExFactory.h"
#include "../model/god/jesusExFactory.h"
#include "../model/god/veryHighDevLFExFactory.h"

class SimulationWidget;

//*************************************************************************
/*!	\class SimWidgetDatamodel 
*	\brief Represents the View of the Model-View-Controller
* 		   Builds the view chain and passes the OpenGL events from the view
*		   to the entities itself.
*/

class SimWidgetDatamodel : public QObject
{
    Q_OBJECT

    public:
      SimWidgetDatamodel(SimulationWidget* sw, QObject *parent);
      ~SimWidgetDatamodel();
      void calcNextStep();
      void draw();
      void init(QOpenGLShaderProgram *p);
      void challengeLifeForms();
    private:
      SimulationWidget* mSimWidget;
      UniverseEntity*	ourUniverseEntity;
      GodAdapter* god;
      void buildViewChain(QObject *parent);
};
