//*************************************************************************
/** \file
 *  \brief Contains the declaration of class God.
 */

#ifndef GOD_H
#define GOD_H

#include "destiny.h"
#include "universe.h"

 //******************************************************************************
 /*! \class God
  *	\ingroup Factory
  *	\brief Member of pattern <b>Factory</b> as <b>Product</b>.
  *		   Member of pattern <b>Adapter</b> as <b>Adaptee</b>.
  *	       This is the interface for all gods.
  *	       This is the abstraction of a god and its minimum of general characteristics.
  *	       Every concrete subclass has no more than this methods and variables.
  */
class God
{
    protected:
      Destiny*	ourDestiny;
      Universe*	ourUniverse;

      LowDev_LF LF1;
      MidDev_LF LF2;
      MidDev_LF LF3;
      //HighDev_LF LF3;
    public:
      static char* name;
      God();
      virtual ~God();

      virtual void          createBigBang();
      virtual char*         getName();
      virtual void          SimulateTimeStep();
      virtual unsigned long GetTimeOfUniverse();

      virtual LowDev_LF*    createLowDevLF();
      virtual MidDev_LF*    createMidDevLF();
      virtual HighDev_LF*   createHighDevLF();
};

#endif //ABSTRACTGOD_H
