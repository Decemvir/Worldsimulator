//*************************************************************************
/** \file 
 *  \brief Contains the declaration of class VeryHighDefLF_Ex_Factory.
 */

#ifndef VERYHIGHDEVLF_EX_FACTORY_H
#define VERYHIGHDEVLF_EX_FACTORY_H

#include "deusExFactory.h"
#include "veryHighDevLF.h"

//******************************************************************************
/*! \class VeryHighDevLF_Ex_Factory
 *  \ingroup Factory
 *  \brief Member of pattern <b>Factory</b> as <b>ConcreteCreator</b>. 
 *	       This class can create an instance of class VeryHighDev_LF.
 *         VeryHighDev_LF_Ex_Factory is the factory for the concrete god "very high 
 *         developed life from". If this class creates a god, the static variable of 
 *         Deus_Ex_Factory is set to the god created this way.\n
 */
class VeryHighDevLF_Ex_Factory : public Deus_Ex_Factory
{
    public:
      virtual God* createGod();
};

#endif //VERYHIGHDEVLF_EX_FACTORY_H
