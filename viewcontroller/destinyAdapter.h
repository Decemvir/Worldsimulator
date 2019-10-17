//*************************************************************************
/** \file
*  \brief Contains the declaration of class DestinyAdapter.
*/

#pragma once

#include <QObject>
#include "../model/god/destiny.h"
#include "lifeformEntity.h"
#include "lfJobHandler.h"

//******************************************************************************
/*! \class DestinyAdapter
*	\ingroup Adapter Chain SingletonTE
*	\brief Member of pattern <b>Adapter</b> as <b>Adapter</b> and <b>Target</b>.
		   Member of pattern <b>Adapter</b> as <b>Client</b>.
*		   Member of pattern <b>Singleton</b>.
*	       Member of pattern <b>ChainOfresponsibility</b> as <b>Client</b>.
*		   This class holds the entirety of all life form instances that can be affected
*		   by a set of predefined actions, can give some basic quantitative informations
*		   and contains a few helper functions for the god.
*		   
*		   It can create problems for life form entities.
*		   It can manage to evolve or devolve life forms by replacing the object with a more or less developed form of itself.
*		   It can manage to kill a life form.
*		   It can manage two life forms mating with each other.
*		   It can manage two life forms meeting each other.
*		   
*		   It's most important function is beeing an instance pool of naturally/artificial created life forms
*		   so the the god can randomly pick and alter the state of a life form easily.
*/

class DestinyAdapter : public QObject, private Destiny
{
    Q_OBJECT

    public:
      static DestinyAdapter* Instance(QObject *parent);
      void createProblemForLFE(LifeFormEntity* lf);
      void rendevouzTwoLFEs(LifeFormEntity* lf, LifeFormEntity* otherLF);
      void killLFE(LifeFormEntity* lf);
      void mateTwoLFE(LifeFormEntity* lf, LifeFormEntity* otherLF);
      void evolveLFE(LifeFormEntity* lf);
      void devolveLFE(LifeFormEntity* lf);
      void addLFE(LifeFormEntity* lf);
      void removeLFE(LifeFormEntity* lf);
      unsigned long long getNumberOfAliveLFEs();
      unsigned long long getNumberOfUnbornLFEs();
      unsigned long long getNumberOfDeadLFEs();
      LifeFormEntity* chooseRandomLFE();
      QString generateLFEName();
    protected:
      DestinyAdapter(QObject *parent);
      ~DestinyAdapter();
      static const int NUM_OF_CONCRETE_LIFEFORMS;
      QVector<LifeFormEntity*> LFEs;
      unsigned long long NumberOfDeadLFEs;
      LFJobHandler* ourJobHandler;
};
