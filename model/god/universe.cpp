//*************************************************************************
/** \file 
 *  \brief Contains the implementation of class Universe.
 */

#include "universe.h"
#include <QDebug>
#include <iterator>

using namespace std;

//******************************************************************************
/*!< Is set once, once getUniverse() is called. Only one Universe object are allowed. */
Universe* Universe::ourUniverse = nullptr;

//******************************************************************************
//! Constructor
Universe::Universe() 
{
    //__creation_time=GetTickCount();
    __creation_time = std::clock();
    printf("[Universe::Universe]  The universe has been created.\n");
}

//******************************************************************************
//! Destructor
Universe::~Universe()
{
    // Free all created planets
    for (unsigned long i = 0; i < planets.size(); ++i)
    {
        delete planets[i];
    }

}

//******************************************************************************
//! Gets the instance of the universe.\n
/*! 
 *	\param none.
 *	\return an instance of Universe.
 */
Universe* Universe::getUniverse(void)
{
    if (!ourUniverse)
        ourUniverse = new Universe();

    return ourUniverse;
}

//******************************************************************************
//! Adds a new Plant.
/*!
 *	\param a CartesianCoordAdapter.
 *	\return none
 */
void Universe::addNewPlanet(CartesianCoordAdapter coords)
{
    printf("[Universe::addNewPlanet]  A new planet is added to the universe.\n");

    Planet* planet = new Planet(coords);
    planets.push_back(planet);
    actPlanet = planet;
}

//******************************************************************************
//! Returns the first planet of the universe.
/*!
 *	\param none.
 *	\return the first planet.
 */
Planet* Universe::getFirstPlanet(void)
{
    Planet* retPlanet = 0;
    vector <Planet*>::iterator it;
    it = planets.begin();
    retPlanet = *it;
    actPlanet = retPlanet;

    return retPlanet;
}

//******************************************************************************
//! Returns the last planet of the universe.
/*!
 *	\param none.
 *	\return the last planet.
 */
Planet* Universe::getLastPlanet(void)
{
    Planet* retPlanet = 0;
    vector <Planet*>::iterator it;
    it = planets.end();
    retPlanet = *it;
    actPlanet = retPlanet;

    return retPlanet;
}

//******************************************************************************
//! Returns the next planet of the universe.
/*!
 *	\param none.
 *	\return  the next planet.
 */
Planet* Universe::getNextPlanet(void)
{
    //Special case: actPlanet == planets.end() -> return planets.begin()
    if (actPlanet == *planets.end())
    {
        actPlanet = *planets.begin();
        return actPlanet;
    }
    //else.. standard

    Planet* retPlanet = nullptr;
    vector <Planet*>::iterator it;
    it = planets.begin();
    while(*it != actPlanet)
        it++;

    it++;
    retPlanet = *it;
    actPlanet = retPlanet;

    return retPlanet;
}

//******************************************************************************
//! Returns the time of the universe.
/*!
 *	\param none.
 *	\return the time (DWORD).
 */
unsigned long Universe::getTime(void)
{
    //return GetTickCount()-__creation_time;
    return std::clock() - __creation_time;
}
