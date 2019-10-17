/** \file
 *  \brief Contains the implementation of class Decorator.
 */

#include "interfaces.h"

 //******************************************************************************
 //! Constructor of Decorator.
 /*!
  *	\param a instance of MindWorldComponent.
  */
Decorator::Decorator(MindWorldComponent* mwc)
{
	_mwc = mwc;
}

//******************************************************************************
//! Changes a MindWorldComponent.
/*!
 *	\param a text.
 *	\return none.
 */
void Decorator::change(char* text)
{
	_mwc->change(text);
}
