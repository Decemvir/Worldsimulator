//*************************************************************************
/** \file 
 *  \brief Contains the implementation of class HighDev_LF.
 */

#pragma warning(disable: 4800)

#include "highDevLF.h"
#include <time.h>
#include <QtDebug>

//******************************************************************************
/*!< The level of the lifeform (MidDev+1). */
int HighDev_LF::Dev_Level = MidDev_LF::Dev_Level+1;

//******************************************************************************
//! Constructor of class HighDev_LF
HighDev_LF::HighDev_LF() {}

//******************************************************************************
//! Constructor of class HighDev_LF - overloaded mathod 
/*!
 *	\param a name of the god
 */
HighDev_LF::HighDev_LF(char* godName) 
{
    this->believerOf = godName;
}

//******************************************************************************
//! Destructor of class HighDev_LF
HighDev_LF::~HighDev_LF() {}

//******************************************************************************
//! Get the development level of the liveform
/*!
 *	\param none.
 *	\return The development level.
 */
int HighDev_LF::getDevLvl(void)
{
    return this->HighDev_LF::Dev_Level;
}

//******************************************************************************
//! Here it will be decided, which method to choose to solve a problem.
/*!
 *	\param none.
 *	\return true, if problem solved. else, no.
 */
bool HighDev_LF::solveProblem(void)
{
    qDebug("[HighDev_LF::solveProblem]  Decide which method is to choose to solve a problem.\n");

    switch (rand()%7)
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
        case 4:
            return this->readBooks();
        case 5:
            return this->watchNature();
        case 6:
            return this->thinkNewMeme();
    }

    return false;
}

//******************************************************************************
//! One of the ways to solve a problem. (handle a request)
/*!
 *	\param none.
 *	\return true, if problem solved this way. else, no.
 */
bool HighDev_LF::thinkNewMeme(void)
{
    srand((unsigned)time(nullptr));
    qDebug("[HighDev_LF::thinkNewMeme]  A life form tries to solve a given problem by thinking a new meme.\n");
    return (bool) rand();
}

