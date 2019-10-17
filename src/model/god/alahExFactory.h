//*************************************************************************
/** \file 
 *  \brief Contains the declaration of class Alah_Ex_Factory.
 */

#ifndef ALAH_EX_FACTORY_H
#define ALAH_EX_FACTORY_H

#include "deusExFactory.h"
#include "alah.h"

//******************************************************************************
/*! \class Alah_Ex_Factory
 *  \ingroup Factory
 *  \brief Member of pattern <b>Factory</b> as <b>ConcreteCreator</b>. 
 *         This class can create an instance of class Alah.
 *         Alah_Ex_Factory is the factory for the concrete god Alah. If this class creates 
 *         a god, the static variable of Deus_Ex_Factory is set to the god created this way.\n
 */
class Alah_Ex_Factory : public Deus_Ex_Factory
{
    public:
      virtual God* createGod();
};

#endif //ALAH_EX_FACTORY_H
