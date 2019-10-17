//*************************************************************************
/** \file
 *  \brief Contains the declaration of class Deus_Ex_Factory.
 */

#ifndef DEUS_EX_FACTORY_H
#define DEUX_EX_FACTORY_H

#pragma once

#include "god.h"

 //******************************************************************************
 /*! \class Deus_Ex_Factory
  *  \ingroup Factory
  *  \brief Member of pattern <b>Factory</b> as <b>Creator</b>.
  *         This class can create an instance of a god.
  *         This factory has all member needed for the controlled creation
  *			of a god.
  */
class Deus_Ex_Factory
{
    private:
      static bool InstanceOfGodCreatedYN;
      static God* instance;
    public:
      virtual God* createGod();
      static bool  getInstanceOfGodCreated();
      static void  setInstanceOfGodCreated();
      static God*  getInstanceOfGod();
      static void  setInstanceOfGod(God*);
};

#endif //DEUS_EX_FACTORY_H
