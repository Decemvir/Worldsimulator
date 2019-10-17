//*************************************************************************
/** \file
 *  \brief Contains the implementation of class LifeForm.
 */

#include "lifeForm.h"
#include <QDebug>

 //******************************************************************************
 /*!< The level of the lifeform (0). */
int LifeForm::Dev_Level = 0;

//******************************************************************************
//! Get the development level of the liveform
/*!
 *	\param none.
 *	\return The development level.
 */
int LifeForm::getDevLvl(void)
{
    return this->Dev_Level;
}

//******************************************************************************
//! Solves a given problem..
/*!
 *	\param none.
 *	\return a status.
 */
bool LifeForm::solveProblem(void)
{
    return false;
}

//******************************************************************************
//! A life form is added to the list of friends, the calling object has.
/*!
 *	\param LF life form to add to the friend list.
 *  \return none.
 */
void LifeForm::addKownLF(LifeForm* LF)
{
    knownLF.push_back(LF);
}

//******************************************************************************
//! Returns the home planet of the lifeform.
/*!
 *	\param none.
 *	\return The Planet-Object (Client).
 */
Planet* LifeForm::getHomePlanet(void)
{
    return this->homePlanet;
}

//******************************************************************************
//! The life begins on a planet.
/*!
 *	\param the planet.
 *	\return none.
 */
void LifeForm::startLife(Planet* planet)
{
    qDebug("[LifeForm::startLife]  A life form was settled on a planet by %s.\n", this->believerOf);
    this->homePlanet = planet;
}

//******************************************************************************
//! One of the ways to solve a problem. The problem is "forwarded" to a higher life form.
/*!
 *  \param none.
 *	\return TRUE, if problem solved this way - else FALSE.
 */
bool LifeForm::askKnownLF(void)
{
    char* className = "LowDev_LF";
    vector <LifeForm*> vec_higher_LF;
    vector <LifeForm*>::iterator it = knownLF.begin();

    int maxNum = 0;

    for(it; it != knownLF.end(); it++)
    {
        LifeForm* LF = *it;
        //the iterator element has a higher Development than calling object
        if(this->getDevLvl() < LF->getDevLvl())
        {
            vec_higher_LF.push_back(LF);
            maxNum++;
        }
    }

    if(maxNum == 0)
    {
        //printf("[LifeForm::askKnownLF]  A life form tried to asked a friend to help him with a problem, but did not find one.\n");
        return false;
    }
    int random = rand() % (maxNum + 1);
    int i = 0;

    vector <LifeForm*>::iterator selIt = vec_higher_LF.begin();
    for(i; i < random; random++) selIt++;
        LifeForm* LFtoAsk = *selIt;

    //printf("A life form asked a friend to help him with a problem\n");
    return (LFtoAsk->solveProblem());
}
