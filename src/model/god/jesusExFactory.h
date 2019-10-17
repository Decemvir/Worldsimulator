//*************************************************************************
/** \file 
 *  \brief Contains the declaration of class Jesus_Ex_Factory.
 */

#ifndef JESUS_EX_FACTORY_H
#define JESUS_EX_FACTORY_H

#include "deusExFactory.h"
#include "jesus.h"

//******************************************************************************
/*! \class Jesus_Ex_Factory
 *    \ingroup Factory
 *	  \brief Member of pattern <b>Factory</b> as <b>ConcreteCreator</b>. 
 *		     This class can create an instance of class Jesus.
 *	         Jesus_Ex_Factory is the factory for the concrete god Jesus. 
 *			 If this class creates a god, the static variable of Deus_Ex_Factory
 *			 is set to the god created this way.
 */
class Jesus_Ex_Factory : public Deus_Ex_Factory
{
    public:
      virtual God* createGod();
};

#endif //JESUS_EX_FACTORY_H
