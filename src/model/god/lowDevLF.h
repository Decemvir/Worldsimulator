//*************************************************************************
/** \file 
 *  \brief Contains the declaration of class LowDef_LF.
*/

#ifndef LOWDEV_LF_H
#define LOWDEV_LF_H

#include "lifeForm.h"
#include "coordinates.h"

//******************************************************************************
/*! \class LowDev_LF
 *  \ingroup Chain
 *  \brief Member of pattern <b>ChainOfresponsibility</b> as <b>ConcreteHandler</b>.
 *		   Member of pattern <b>Adapter</b> as <b>Adaptee</b>.
 *         An instance of this class represents a low developed life form.
 *         This kind of life form has a 4 possibilities to react on problems:
 *         it may know or the solution, ignore the problem or ask a known life from,
 *         which is higher developed.
 */
class LowDev_LF : public LifeForm
{
    public:
      LowDev_LF();
      LowDev_LF(char*);
      ~LowDev_LF();

      virtual bool solveProblem();
      virtual int  getDevLvl();
        
      void knowSolution();
      void ignoreProblem();
      bool guessSolution();
    protected:
      static int Dev_Level;
};

#endif //LOWDEV_LF_H
