//*************************************************************************
/** \file 
 *  \brief Contains the implementation of class Alah.
 */

#include "alah.h"

//******************************************************************************
//* The Creatures created by "Alah" - God will believe in "Alah" ("believerOf" - Member)
//* simulating the different behavior of different ConreteProducts (Gamma)
/*!< Name of the god. */
char* Alah::name = "Alah";

//******************************************************************************
//! Returns the name of the instance of the class Alah.
/*!
 *  \param none.
 *  \return name of Alah.
 */
char* Alah::getName(void)
{
    return Alah::name;
}
