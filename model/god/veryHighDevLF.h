//*************************************************************************
/** \file 
 *  \brief Contains the declaration of class VeryHighDef_LF.
 */

#ifndef VERYHIGHDEV_LF_H
#define VERYHIGHDEV_LF_H

#include "god.h"
#include <string>

//******************************************************************************
/*! \class VeryHighDev_LF 
 *	\ingroup Factory
 *	\brief Member of pattern <b>Factory</b> as <b>ConcreteProduct</b>. 
 *	       This class represents a god.
 *	       An instance of VeryHighDev_LF (very high developed life form) can create a 
 *	       universe and lifeforms and a destiny.
 *	       It's difference to other gods is his name.
 */
class VeryHighDev_LF : public God
{
    public:
      //VeryHighDev_LF();
      //~VeryHighDev_LF();
      static  char* name;
      virtual char* getName();
};

#endif //VERYHIGHDEV_LF_H
