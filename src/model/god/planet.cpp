//*************************************************************************
/** \file 
 *    \brief Contains the implementation of class Planet.
 */

#include "planet.h"
#include <QDebug>

//******************************************************************************
//! Constructor of class Plant
Planet::Planet() {}

//******************************************************************************
//! Constructor of class Plant - overloaded method
/*!
 *	\param a instance of a class CartesianCoordAdapter.
 */
Planet::Planet(CartesianCoordAdapter coord)
{
    this->coords = coord;
}

//******************************************************************************
//! Destructor
Planet::~Planet() {}

//******************************************************************************
//! Adds a lifeform to the planet.
/*!
 *	\param instance of a lifeform.
 *	\return True, if it is the first lifeform, else False.
 */
bool Planet::addLF(LifeForm* LF)
{
    printf("[Planet::addLF]  A lifeform is added to the lifeforms of the planet.\n");

    if (!LF->getHomePlanet())
    {
        this->Inhabitants.push_back(LF);
        LF->startLife(this);
        return true;
    }

    return false;
}
