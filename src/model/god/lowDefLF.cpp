//*************************************************************************
/** \file 
 *  \brief Contains the implementation of class LowDef_LF.
 */

#pragma warning(disable: 4804)
#pragma warning(disable: 4800)

#include "lowDevLF.h"
#include <QDebug>

//******************************************************************************
/*!< The level of the lifeform (LowDev). */
int LowDev_LF::Dev_Level = 1;

//******************************************************************************
//! Constructor of class LowDev_LF
LowDev_LF::LowDev_LF() {}

//******************************************************************************
//! Constructor of class LowDev_LF - overloaded mathod 
/*!
 *	\param a name of the god.
 */
LowDev_LF::LowDev_LF(char* godName) 
{
    this->believerOf = godName;
}

//******************************************************************************
//! Destructor of class LowDev_LF
LowDev_LF::~LowDev_LF() {}

//******************************************************************************
//! Get the development level of the liveform
/*!
 *	\param none.
 *	\return The development level.
 */
int LowDev_LF::getDevLvl(void)
{
    return this->LowDev_LF::Dev_Level;
}

//******************************************************************************
//! Here it will be decided, which method to choose to solve a problem.
/*!
 *	\param none
 *	\return true, if problem solved. else, no.
 */
bool LowDev_LF::solveProblem(void)
{
    qDebug("[LowDev_LF::solveProblem]  Decide which method is to choose to solve a problem.\n");

    switch (rand()%4)
    {
        case 0:
            return this->guessSolution();
        case 1:
            this->knowSolution();
            return true;
        case 2:
            return this->askKnownLF();
        case 3:
            this->ignoreProblem();
            break;
    }

    return false;
}

//******************************************************************************
//! One of the ways to solve a problem. (handle a request)
/*!
 *	\param none.
 *	\return true, if problem solved this way. else, no.
 */
bool LowDev_LF::guessSolution(void)
{
    qDebug("[LowDev_LF::guessSolution]  A life form tries to guess the solution of a given problem.\n");
    return (bool)rand()%2;
}

//******************************************************************************
//! A problem was not solved and got igonred by the life form.
/*!
 *	\param none.
 *	\return none.
 */
void LowDev_LF::ignoreProblem(void) 
{
    qDebug("[LowDev_LF::ignoreProblem]  A life form ignores a given problem.\n");
}

//******************************************************************************
//! The life form knows the solution of the problem.
/*!
 *	\param none.
 *	\return none.
 */
void LowDev_LF::knowSolution(void) 
{
    qDebug("[LowDev_LF::knowSolution]  A life form knows the solution for a given problem.\n");
}
