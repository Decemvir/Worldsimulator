//*************************************************************************
/** \file
*  \brief Contains the declaration of class GodAdapter.
*/

#pragma once

#include <QObject>
#include "../model/god/god.h"
#include <QString>
#include <QVector>
#include "universeEntity.h"
#include "planetEntity.h"
#include "destinyAdapter.h"
#include "lowDevLFEntity.h"
#include "midDevLFEntity.h"
#include "highDevLFEntity.h"

//*************************************************************************
/*!	\class GodAdapter
*	\ingroup CompositePattern Adapter
*	\brief Member of pattern <b>Composite</b> as <b>Client</b>.
*		   Member of pattern <b>Adapter</b> as <b>Adapter</b> and <b>Target</b>.
*		   Member of pattern <b>Adapter</b> as <b>Client</b>.
*	       Redefines and adds to the interface functionality inherited from the class God.
*			
*		   It gives the functionality to create a predefined universe,
*		   challenge a random life form with a random task from a given set of tasks,
*		   create "artificial" life forms and limit the amount of life forms that could develop.
*/

class GodAdapter : public QObject, private God
{
    Q_OBJECT

    public:
      GodAdapter(QObject *parent, char* godname = nullptr);
      virtual ~GodAdapter();
      static char* godName;

      virtual void          createBigBang();
      virtual char*         getName();
      virtual void          SimulateTimeStep();
      virtual unsigned long GetTimeOfUniverse();

      virtual LowDev_LFEntity*    createLowDevLFE(QObject *parent);
      virtual MidDev_LFEntity*    createMidDevLFE(QObject *parent);
      virtual HighDev_LFEntity*   createHighDevLFE(QObject *parent);

      virtual void challengeLFEs();

      bool          isInitialised();
      PlanetEntity* getPlanetToObserve();
      void          setMinNumberOfLFs(unsigned int min);
      void          setMaxNumberOfLFs(unsigned int max);
    protected:
      DestinyAdapter* ourDestinyAdapter;
      UniverseEntity* ourUniverseEntity;

      static unsigned int maxNumberOfLFEs;
      static unsigned int minNumberOfLFEs;

      PlanetEntity* planetToObserve;
      bool initialised;
};
