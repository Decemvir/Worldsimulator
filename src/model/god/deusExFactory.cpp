//*************************************************************************
/** \file 
 *  \brief Contains the implementation of class Deus_Ex_Factory.
 */

#include "deusExFactory.h"

//******************************************************************************
/*! Is set once, once createGod is called. This controls the restriction to number of gods. */
bool Deus_Ex_Factory::InstanceOfGodCreatedYN = false;

//******************************************************************************
/*! Is set once, once createGod is called. This controls the restriction to number of gods. */
God* Deus_Ex_Factory::instance = nullptr;

//******************************************************************************
//! Creates a god and sets the static instance member.
/*!
 *  \param none.
 *	\return Pointer on the god of our system.
 */
God* Deus_Ex_Factory::createGod(void)
{
    Deus_Ex_Factory::setInstanceOfGod(new God);
    return Deus_Ex_Factory::getInstanceOfGod();
}

//******************************************************************************
//! Sets the flag if a instance of class God was created.
/*!
 *  \param none.
 *	\return none.
 */
void Deus_Ex_Factory::setInstanceOfGodCreated(void)
{
    Deus_Ex_Factory::InstanceOfGodCreatedYN = true;
}

//******************************************************************************
//! Returns the flag if a instance of class God was created.
/*!
 *  \param none.
 *	\return True, if a instance of God was created, else False.
 */
bool Deus_Ex_Factory::getInstanceOfGodCreated(void)
{
    return Deus_Ex_Factory::InstanceOfGodCreatedYN;
}

//******************************************************************************
//! Returns the instance of class God.
/*!
 *  \param none.
 *	\return instance of class God.
 */
God* Deus_Ex_Factory::getInstanceOfGod(void)
{
    return instance;
}

//******************************************************************************
//! Sets a instance of a class God.
/*!
 *  \param a instance of a class God.
 *	\return none.
 */
void Deus_Ex_Factory::setInstanceOfGod(God* _god)
{
    if (!Deus_Ex_Factory::getInstanceOfGodCreated())
    {
        setInstanceOfGodCreated();
        instance = _god;
    }
}
