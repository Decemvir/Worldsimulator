//*************************************************************************
/** \file 
 *  \brief Contains the implementation of class MidDev_LF.
 */

#pragma warning(disable: 4800)

#include "midDevLF.h"
#include <QDebug>

//******************************************************************************
/*!< The level of the lifeform (LowDev+1). */
int MidDev_LF::Dev_Level = LowDev_LF::Dev_Level+1;

//******************************************************************************
//! Constructor of class MidDev_LF - overloaded mathod 
MidDev_LF::MidDev_LF() {}

//******************************************************************************
//! Constructor of class MidDev_LF - overloaded mathod 
/*!
 *	\param a name of the god.
 */
MidDev_LF::MidDev_LF(char* godName) 
{
    this->believerOf = godName;
}

//******************************************************************************
//! Destructor of class MidDev_LF 
MidDev_LF::~MidDev_LF() {}

//******************************************************************************
//! Get the development level of the liveform
/*!
 *	\param none.
 *	\return The development level.
 */
int MidDev_LF::getDevLvl(void)
{
    return this->MidDev_LF::Dev_Level;
}

//******************************************************************************
//! Here it will be decided, which method to choose to solve a problem.
/*!
 *	\param none.
 *	\return true, if problem solved. else, no.
 */
bool MidDev_LF::solveProblem(void)
{
    qDebug("[MidDev_LF::solveProblem]  Decide which method is to choose to solve a problem.\n");

    switch (rand()%6) {
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
        case 4:
            return this->readBooks();
        case 5:
            return this->watchNature();
    }

    return false;
}

//******************************************************************************
//! One of the ways to solve a problem. (handle a request)
/*!
 *	\param none.
 *	\return true, if problem solved this way. else, no.
 */
bool MidDev_LF::readBooks(void)
{
    qDebug("[MidDev_LF::readBooks]  A life form tries to solve a given problem by reading books.\n");
    return rand()%2;
}

//******************************************************************************
//! One of the ways to solve a problem. (handle a request)
/*!
 *	\param none.
 *	\return true, if problem solved this way. else, no.
 */
bool MidDev_LF::watchNature(void)
{
    qDebug("[MidDev_LF::watchNature]  A life form tries to solve a given problem by watching nature.\n");
    return rand()%2;
}
