//*************************************************************************
/** \file 
 *  \brief Contains the implementation of class Alah_Ex_Factory.
 */

#include "alahExFactory.h"
#include <QDebug>

//******************************************************************************
//! Creates an instance of god Alah, if no god B was created before. Else it returns B.
/*!
 *  \param none
 *  \return A pointer to the god of our system.
 */
God* Alah_Ex_Factory::createGod(void)
{
    qDebug("[Alah_Ex_Factory::createGod]  Create a god called \"Alah\"\n");

    Deus_Ex_Factory::setInstanceOfGod(new Alah);
    return Deus_Ex_Factory::getInstanceOfGod();
}

