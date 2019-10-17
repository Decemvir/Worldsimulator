//*************************************************************************
/** \file 
 *  \brief Contains the declaration of class Coordinates.
 */

#ifndef COORDINATES_H
#define COORDINATES_H

#include "math.h"

//******************************************************************************
/*! \class Coordinates
 *	\ingroup Adapter
 *	\brief Member of pattern <b>Adapter</b> as <b>Adaptee</b>.
 *	       An instance of this class represents a point in a 3 dimensional space. 
 *		   It is coded in sphere coordinates.
 */
class Coordinates
{
    protected:
      double horDeg;
      double verDeg;
      double rad;
    public:
      Coordinates();
      Coordinates(double horDegree, double verDegree, double radius);
      ~Coordinates();

      double getHorDeg();
      double getVerDeg();
      double getRad();

      void   setHorDeg(double);
      void   setVerDeg(double);
      void   setRad(double);
};

#endif //COORDINATES_H
