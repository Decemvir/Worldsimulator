//*************************************************************************
/** \file 
 *  \brief Contains the declaration of class CartesianCoordAdapter.
 */

#ifndef CARTESIANCOORDADAPTER_H
#define CARTESIANCOORDADAPTER_H

#include "math.h"
#include "coordinates.h"

//******************************************************************************
/*! \class CartesianCoordAdapter
 *	\ingroup Adapter
 *	\brief Member of pattern <b>Adapter</b> as <b>Adapter</b> and <b>Target</b>.
 *	       This class can return polar coordinates and cartesian coordinates.
 *	       This class has all members of the superclass Coordinates and in addition 
 *         to this has functions to calculate coordinates of a cartesian system.
 */
class CartesianCoordAdapter : public Coordinates
{
    public:
      CartesianCoordAdapter();
      CartesianCoordAdapter(double, double, double);
      ~CartesianCoordAdapter();
    
      double getX();
      double getY();
      double getZ();

      bool isEqualTo(CartesianCoordAdapter *other);

};

#endif //CARTESIANCOORDADAPTER_H
