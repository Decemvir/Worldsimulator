//*************************************************************************
/** \file
*  \brief Contains the implementation of class Entity.
*/

#include "entity.h"

//******************************************************************************
//! Constructor of class Entity
/*!
*	\param parent QT parent pointer.
*	\return none.
*/

Entity::Entity(QObject* parent):QObject(parent)
{
	visible = true;
	program = nullptr;
}

//******************************************************************************
//! Deconstructor of class DestinyAdapter

Entity::~Entity()
{
}

//******************************************************************************
//! Sets the visibility
/*!
*	\param v visibility to be set
*	\return none.
*/

void Entity::setVisibility(bool v)
{
	visible = v;
}

//******************************************************************************
//! Returns the visibility
/*!
*	\param none.
*	\return current visibility.
*/

bool Entity::isVisible()
{
	return visible;
}

