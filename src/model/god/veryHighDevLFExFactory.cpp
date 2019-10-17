//*************************************************************************
/** \file 
 *  \brief Contains the implementation of class VeryHighDevLF_Ex_Factory.
 */

#include "veryHighDevLFExFactory.h"

//******************************************************************************
//! Creates an instance of god VeryHighDev_LF, if no god B was created before. Else it returns B.
/*!
 *  \param none
 *	\return A pointer to the god of our system.
 */
God* VeryHighDevLF_Ex_Factory::createGod()
{
    printf("[VeryHighDevLF_Ex_Factory::createGod]  Create a \"VeryHighDev liveform\"\n");

    Deus_Ex_Factory::setInstanceOfGod(new VeryHighDev_LF);
    return Deus_Ex_Factory::getInstanceOfGod();
}

