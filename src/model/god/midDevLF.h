//*************************************************************************
/** \file 
 *  \brief Contains the declaration of class MidDev_LF.
 */

#ifndef MIDDEV_LF_H
#define MIDDEV_LF_H

#include "lowDevLF.h"

//******************************************************************************
/*! \class MidDev_LF
 *	\ingroup Chain
 *	\brief Member of pattern <b>ChainOfresponsibility</b> as <b>ConcreteHandler</b>.
 *		   Member of pattern <b>Adapter</b> as <b>Adaptee</b>.
 *         An instance of this class represents a middle developed life form.
 *	       This kind of life form is capable of all skills of a low developed life form.
 *	       Additional to this it is able to solve problems by reading books and watching
 *	       nature around him.
 */
class MidDev_LF : public LowDev_LF
{
    public:
      MidDev_LF();
      MidDev_LF(char*);
      ~MidDev_LF();

      virtual bool solveProblem();
      virtual int  getDevLvl();
        
      bool watchNature();
      bool readBooks();
    protected:
      static int Dev_Level;
};

#endif //MIDDEV_LF_H
