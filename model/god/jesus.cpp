//*************************************************************************
/** \file 
 *  \brief Contains the implementation of class Jesus.
 */

#include "jesus.h"

//******************************************************************************
//* The Creatures created by "Alah" - God will believe in "Alah" ("believerOf" - Member)
//* simulating different behavior of ConreteProducts (Gamma)

//******************************************************************************
/*!< Name of the god. */
char* Jesus::name = "Jesus";

//******************************************************************************
//! Returns the name of the instance of the class Jesus.
/*!
 *	\param none.
 *	\return name of Jesus.
 */
char* Jesus::getName(void)
{
    return Jesus::name;
}
