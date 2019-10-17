//*************************************************************************
/** \file 
 *  \brief Contains the implementation of class Destiny.
 */

#include "destiny.h"
#include <QDebug>

//******************************************************************************
/*! Is set once, once getDestiny is called.(Singleton) */
Destiny* Destiny::ourDestiny = nullptr;

//******************************************************************************
//! Constructor of class Destiny
Destiny::Destiny() {}

//******************************************************************************
//! Destructor of class Destiny
Destiny::~Destiny() {}

//******************************************************************************

const int NUM_OF_CONCRETE_LIFEFORMS = 3;

//******************************************************************************
//! Create a problem for life form LF.
/*!
 *	\param LF the life form for which problem is created.
 *	\return none.
 */
void Destiny::createProblemForLifeForm(LifeForm* LF)
{
    LF->solveProblem();
}

//******************************************************************************
//! Creates a new lifeform
/*!
 *	\param a pointer of a lifeform.
 *	\return FALSE.
 */
bool Destiny::devolveLF(LifeForm* LF)
{
    int     ownDev=LF->getDevLvl();
    int     newDev;
    Planet* homePlan;

    srand(NUM_OF_CONCRETE_LIFEFORMS);
    newDev=rand();

    while (newDev>=ownDev)
        newDev=rand();

    homePlan=LF->getHomePlanet();

    //Apply Changes here, when new LifeForms are created
    switch (newDev) {
        case 1:
            LF=new LowDev_LF();
            break;
        case 2:
            LF=new MidDev_LF();
            break;
        case 3:
            LF=new HighDev_LF();
            break;
    }

    LF->startLife(homePlan);
    return false;
}

//******************************************************************************
//! Creates a new lifeform
/*!
 *	\param a pointer of a lifeform.
 *	\return FALSE.
 */
bool Destiny::evolveLF(LifeForm* LF)
{
    int     ownDev=LF->getDevLvl();
    int     newDev;
    Planet* homePlan;

    srand(NUM_OF_CONCRETE_LIFEFORMS);
    newDev=rand();

    while (newDev>=ownDev)
        newDev=rand();

    homePlan=LF->getHomePlanet();

    //Apply Changes here, when new LifeForms are created
    switch (newDev) {
        case 1:
            LF=new LowDev_LF();
            break;
        case 2:
            LF=new MidDev_LF();
            break;
        case 3:
            LF=new HighDev_LF();
            break;
    }

    LF->startLife(homePlan);
    return false;
}

//******************************************************************************
//! Adds life form LF2 to the list of known life forms of LF1 and the other way around..
/*!
 *	\param LF1 life form that is part of the rendevouz.
 *	\param LF2 life form that is part of the rendevouz.
 *	\return none.
 */
void Destiny::rendevouzTwoLF(LifeForm* LF1, LifeForm* LF2)
{
    qDebug("[Destiny::rendevouzTwoLF]  Two Lifeforms meet and get to know each other.\n");
    LF1->addKownLF(LF2);
    LF2->addKownLF(LF1);
}

//******************************************************************************
//! Returns the unique Destiny. (Singleton)
/*!
 *  \param none.
 *	\return The single instance of class Destiny.
 */
Destiny* Destiny::getDestiny(void)
{
    if (!ourDestiny) ourDestiny=new Destiny();
    return ourDestiny;
}
