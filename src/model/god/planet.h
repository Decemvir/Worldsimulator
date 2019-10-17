//*************************************************************************
/** \file 
 *  \brief Contains the declaration of class Planet.
 */

#ifndef PLANET_H
#define PLANET_H

#include "cartesianCoordAdapter.h"
#include "lifeForm.h"
#include <vector>

class LifeForm;

//******************************************************************************
/*! \class Planet
 *	\ingroup Adapter
 *	\brief Member of pattern <b>Adapter</b> as <b>Client</b>.
 *		   Member of pattern <b>Adapter</b> as <b>Adaptee</b>.
 *         An instance of this class represents a planet.
 *         Our planet system includes a localization system that uses cartesian coordinates.
 */	
class Planet
{
    public:
      CartesianCoordAdapter coords;

      Planet(CartesianCoordAdapter);
      virtual ~Planet();
	      
      bool addLF(LifeForm*);
    protected:
      vector<LifeForm*> Inhabitants;
      Planet();
};

#endif //PLANET_H
