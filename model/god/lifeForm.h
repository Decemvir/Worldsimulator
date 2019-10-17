//*************************************************************************
/** \file 
 *  \brief Contains the declaration of class LifeForm.
 */

#ifndef LIFEFORM_H
#define LIFEFORM_H

#include <vector>

#include "cartesianCoordAdapter.h"
#include <stdlib.h>
//#include <human.h>

class LowDev_LF;
class MidDev_LF;
class HighDev_LF;
class Planet;

using namespace std;

//******************************************************************************
/*! \class LifeForm
 *  \ingroup Chain
 *  \brief Member of pattern <b>ChainOfresponsibility</b> as <b>Handler</b>.
 *		   Member of pattern <b>Adapter</b> as <b>Adaptee</b>.
 *         An instance of this class represents a life form in general.
 *         This life form has the minimum set of members a life form needs
 *		   in our system.
 */
class LifeForm
{
    public:
      CartesianCoordAdapter getPos();

      virtual bool    solveProblem();
      virtual int     getDevLvl();

      void    addKownLF(LifeForm*);
      bool    askKnownLF();
      Planet* getHomePlanet();
      void    startLife(Planet*);
    protected:
      static int        Dev_Level;
      vector<LifeForm*> knownLF;
      Planet*           homePlanet;
      const char*       believerOf;
};

#endif //LIFEFORM_H 
