//*************************************************************************
/** \file 
 *  \brief Contains the declaration of class Alah.
 */

#ifndef ALAH_H
#define ALAH_H

#include "god.h"

//******************************************************************************
/*! \class Alah 
 *	\ingroup Factory
 *	\brief Member of pattern <b>Factory</b> as <b>ConcreteProduct</b>. 
 *	       This class represents a god.
 *	       An instance of Alah can create a universe and lifeforms and a destiny.
 *	       It's difference to other gods is his name.\n
 */
class Alah : public God
{
    public:
      static  char* name;
      virtual char* getName();
};

#endif //ALAH_H
