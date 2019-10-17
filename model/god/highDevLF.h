//*************************************************************************
/** \file 
 *  \brief Contains the declaration of class HighDef_LF.
 */

#ifndef HIGHDEV_LF_H
#define HIGHDEV_LF_H

#include "midDevLF.h"

//******************************************************************************
/*! \class HighDev_LF
 *  \ingroup Chain
 *  \brief Member of pattern <b>ChainOfresponsibility</b> as <b>ConcreteHandler</b>.
 *		   Member of pattern <b>Adapter</b> as <b>Adaptee</b>.
 *         An instance of this class represents a high developed life form.
 *         This kind of life form is capable of all skills of a middle developed life form.
 *         Additional to this it is able to solve problems by thinking a new meme.
 */
class HighDev_LF : public MidDev_LF
{
    public:
      HighDev_LF();
      HighDev_LF(char*);
      ~HighDev_LF();

      virtual int  getDevLvl();
      virtual bool solveProblem();
      bool         thinkNewMeme();
    protected:
      static int Dev_Level;
};

#endif //HIGHDEV_LF_H
