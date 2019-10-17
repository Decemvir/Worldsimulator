//*************************************************************************
/** \file 
 *  \brief Contains the implementation of class Jesus_Ex_Factory.
 */

#include "jesusExFactory.h"

//******************************************************************************
//! Creates an instance of god Jesus, if no god B was created before. Else it returns B.
/*!
 *  \param none
 *	\return A pointer to the god of our system.
 */
God* Jesus_Ex_Factory::createGod(void)
{
    printf("[Jesus_Ex_Factory::createGod]  Create a god called \"Jesus\"\n");

    Deus_Ex_Factory::setInstanceOfGod(new Jesus);
    return Deus_Ex_Factory::getInstanceOfGod();
}
