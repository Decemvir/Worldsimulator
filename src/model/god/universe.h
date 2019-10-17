//*************************************************************************
/** \file
 *  \brief Contains the declaration of class Universe.
 */

#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include "planet.h"
//#include <windows.h>
#include <ctime>

 //******************************************************************************
 /*! \class Universe
  *  \ingroup SingletonTE
  *	\brief Member of pattern <b>Singleton</b>.
  *		   Member of pattern <b>Adapter</b> as <b>Adaptee</b>.
  *	       An instance of this class represents a universe.
  *	       In our system only one Universe may exists at a time.
  *				 It can contain a list of planets.
  */
class Universe
{
    protected:
      Universe();
      ~Universe();

      vector<Planet*>  planets;
      static Universe* ourUniverse;
      Planet*          actPlanet;

      unsigned long        __creation_time;
    public:
      static Universe* getUniverse();
      void             addNewPlanet(CartesianCoordAdapter);
      Planet*          getFirstPlanet();
      Planet*          getNextPlanet();
      Planet*          getLastPlanet();

      unsigned long    getTime();
};

#endif //UNIVERSE_H
