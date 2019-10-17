//*************************************************************************
/** \file 
 *  \brief Contains the implementation of class CartesianCoordAdapter.
 */

#include "cartesianCoordAdapter.h"


//******************************************************************************
//! Constructor of class CartesianCoordAdapter
CartesianCoordAdapter::CartesianCoordAdapter() {}

//******************************************************************************
//* Added some calculating Members that return 
//* cartesian coordinates to sphere coordinates.

//******************************************************************************
//! Constructor of class CartesianCoordAdapter - overloaded method
/*!
 *  \param horizontal angle
 *  \param vertical angle
 *  \param radius
 */
CartesianCoordAdapter::CartesianCoordAdapter(double horDegree, 
                                             double verDegree,
                                             double radius)
{
    this->setHorDeg(horDegree);
    this->setVerDeg(verDegree);
    this->setRad(radius);
}

//******************************************************************************
//! Destructor of class CartesianCoordAdapter
CartesianCoordAdapter::~CartesianCoordAdapter() {}

//******************************************************************************
//! Calculates the cartesian representation of a point in a 3-dimensional system.
/*!
 *  \param none
 *  \return The first (X) coordinate of the cartesian representation.
 */
double CartesianCoordAdapter::getX(void)
{
    return this->getRad() * cos(this->getHorDeg()) * sin(this->getVerDeg());
}

//******************************************************************************
//! Calculates the cartesian representation of a point in a 3-dimensional system.
/*!
 *  \param none
 *  \return The second (Y) coordinate of the cartesian representation.
 */
double CartesianCoordAdapter::getY(void)
{
    return this->getRad()*sin(this->getHorDeg())*sin(this->getVerDeg());
}

//******************************************************************************
//! Calculates the cartesian representation of a point in a 3-dimensional system.
/*!
 *  \param none
 *  \return The third (Z) coordinate of the cartesian representation.
 */
double CartesianCoordAdapter::getZ(void)
{
    return this->getRad()*cos(this->getVerDeg());
}

bool CartesianCoordAdapter::isEqualTo(CartesianCoordAdapter * other)
{
    if (other) if (horDeg == other->getHorDeg() && verDeg == other->getVerDeg() && rad == other->getRad()) return true;
    return false;
}
