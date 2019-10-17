//*************************************************************************
/** \file 
 *  \brief Contains the declaration of class Destiny.
 */

#ifndef DESTINY_H
#define DESTINY_H

#include "lifeForm.h"
#include <stdlib.h>
#include "lowDevLF.h"
#include "midDevLF.h"
#include "highDevLF.h"

//******************************************************************************
/*! \class Destiny
 *	\ingroup Adapter Chain SingletonTE
 *	\brief Member of pattern <b>Adapter</b> as <b>Adaptee</b>.
		   Member of pattern <b>Singleton</b>.
 *	       Member of pattern <b>ChainOfresponsibility</b> as <b>Client</b>.
 *	       This class represents the Destiny in our Universe.
 *	       In our concept a system has only one instance of Destiny type.
 *	       It can manage two lifeforms becoming friends evolve and devolve 
 *		   lifeforms.
 *	       It's most important function is to create problems for life forms.
 */
class Destiny
{
    protected:
      Destiny();
      ~Destiny();

      static Destiny* ourDestiny;
    public:
      static Destiny* getDestiny();
      void            createProblemForLifeForm(LifeForm*);
      void            rendevouzTwoLF(LifeForm*, LifeForm*);
      bool            evolveLF(LifeForm*);
      bool            devolveLF(LifeForm*);
};

#endif //DESTINY_H
