//*************************************************************************
/** \file 
 *  \brief Contains the declaration of class Jesus.
 */

#ifndef JESUS_H
#define JESUS_H

#include "god.h"
#include <string>

//******************************************************************************
/*! \class Jesus 
 * 	\ingroup Factory
 *  \brief Member of pattern <b>Factory</b> as <b>ConcreteProduct</b>. 
 *	       This class represents a god.
 *         An instance of Jesus can create a universe and lifeforms and 
 *		   a destiny. It's difference to other gods is his name.
 */
class Jesus : public God
{
    public:
      static  char* name;
      virtual char* getName();
};

#endif //JESUS_H
