//*************************************************************************
/** \file 
 *  \brief Contains the implementation of class Coordinates.
 */

#include "coordinates.h"

//******************************************************************************
//! Constructor
Coordinates::Coordinates() {}

//******************************************************************************
//! Destructor
Coordinates::~Coordinates() {}

//******************************************************************************
//! Returns the horizontal angle.
/*!
 *  \param none.
 *  \return horizontal angle.
 */
double Coordinates::getHorDeg(void)
{
    return this->horDeg;
}

//******************************************************************************
//! Returns the vertical angle.
/*!
 *  \param none.
 *  \return vertical angle.
 */
double Coordinates::getVerDeg(void)
{
    return this->verDeg;
}

//******************************************************************************
//! Returns the radius.
/*!
 *  \param none.
 *  \return radius.
 */
double Coordinates::getRad(void)
{
    return this->rad;
}

//******************************************************************************
//! Sets the horizontal angle.
/*!
 *  \param horizontal degree.
 *  \return none.
 */
void Coordinates::setHorDeg(double _horDeg)
{
    this->horDeg=(_horDeg>360)?floor(_horDeg/360.0)*360:_horDeg;
}

//******************************************************************************
//! Sets the vertical angle.
/*!
 *  \param vertical degree.
 *  \return none.
 */
void Coordinates::setVerDeg(double _verDeg)
{
    this->verDeg=(_verDeg>360)?floor(_verDeg/360.0)*360:_verDeg;
}

//******************************************************************************
//! Sets the radius.
/*!
 *  \param radius.
 *  \return none.
 */
void Coordinates::setRad(double _rad)
{
    this->rad=_rad;
}

//******************************************************************************
//! Sets the coordinates.
/*!
 *  \param horizontal degree.
 *  \param vertical degree.
 *  \param radius.
 *  \return none.
 */
Coordinates::Coordinates(double horDegree,
                         double verDegree,
                         double radius)
{
    this->setHorDeg(horDegree);
    this->setVerDeg(verDegree);
    this->setRad(radius);
}
