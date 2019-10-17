//*************************************************************************
/** \file
*  \brief Contains the implementation of class ViewOfEntities.
*/

#include "viewOfEntities.h"
//#include <QtConcurrent\QtConcurrentRun>
#include <QtConcurrent/QtConcurrentRun>

//******************************************************************************
//! Constructor of class ViewOfEntities
/*!
*	\param parent QT parent pointer.
*	\return none.
*/

ViewOfEntities::ViewOfEntities(QObject* parent) :Entity(parent)
{
}

//******************************************************************************
//! Deconstructor of class ViewOfEntities

ViewOfEntities::~ViewOfEntities()
{
}

//******************************************************************************
//! Sets the visibility for the view
/*!
*	\param v visibility to be set
*	\return none.
*/

void ViewOfEntities::setVisibility(bool v)
{
    Entity::setVisibility(v);
}

//******************************************************************************
//! Returns the visibility of the view
/*!
*	\param none.
*	\return current visibility.
*/

bool ViewOfEntities::isVisible()
{
    return Entity::isVisible();
}

//******************************************************************************
//! Adds entity to the list of children
/*!
*	\param entity that gets added.
*	\return none.
*/

void ViewOfEntities::add(Entity* entity)
{
    if (entity && !children.contains(entity) && this != entity)
    {
        ViewOfEntities* view = dynamic_cast<ViewOfEntities*>(entity);

        if (!view || view && !view->contains(this))
        {
            children.push_back(entity);
            uninitialised.push_back(entity);
        }
    }
}

//******************************************************************************
//! Removes entity from the list of children
/*!
*	\param entity that gets removed.
*	\return none.
*/

void ViewOfEntities::remove(Entity* entity)
{
    if (entity)
    {
        children.removeOne(entity);
        uninitialised.removeOne(entity);
        children.squeeze();
        uninitialised.squeeze();
    }
}

//******************************************************************************
//! Clears the list of children 
/*!
*	\param none.
*	\return none.
*/

void ViewOfEntities::clear()
{
    children.clear();
    uninitialised.clear();
    children.squeeze();
    uninitialised.squeeze();
}

//******************************************************************************
//! Destroys all child instances currently held by the view
/*!
*	\param none.
*	\return none.
*/

void ViewOfEntities::destroy()
{
    QVector<Entity*>::iterator it = children.begin();
    while (it != children.end())
    {
        int oldSize = children.size();
        ViewOfEntities* currentChild = dynamic_cast<ViewOfEntities*>(*it);
        if (currentChild)
            currentChild->destroy();

        delete *it;
        if(oldSize == children.size())
        {
            *it = nullptr;
            it = children.erase(it);
        }
        else it = children.begin();
    }
}

//******************************************************************************
//! Returns true if this view has no children
/*!
*	\param none.
*	\return true if list of children is empty.
*/

bool ViewOfEntities::isEmpty()
{
    return children.isEmpty();
}

//******************************************************************************
//! Returns true if entity is part of this view or part of any subview contained by this view
/*!
*	\param entity to search for.
*	\return true if entity is contained by this.
*/

bool ViewOfEntities::contains(Entity* entity)
{	
    bool contains = false;
    if(entity)
    {
        contains = children.contains(entity);
        for (QVector<Entity*>::iterator it = children.begin(); !contains && it != children.end(); ++it)
        {
            ViewOfEntities* currentChild = dynamic_cast<ViewOfEntities*>(*it);
            if (currentChild)
                contains = currentChild->contains(entity);
        }
    }
    return contains;
}

//******************************************************************************
//! Returns children list size
/*!
*	\param none.
*	\return children list size.
*/

int ViewOfEntities::getSize()
{
    return children.size();
}

//******************************************************************************
//! Returns specific child at index i
/*!
*	\param i index.
*	\return entity with index i.
*/

Entity* ViewOfEntities::getChild(int i)
{
    return children.at(i);
}

//******************************************************************************
//! Initialises all children (method runs in current OpenGL context)
/*!
*	\param p shader program to be set.
*	\return none.
*/

void ViewOfEntities::init(QOpenGLShaderProgram * p)
{
    program = p;
    if (program)
    {
        for (QVector<Entity*>::iterator it = children.begin(); it != children.end(); ++it)
        {
            (*it)->init(p);
            uninitialised.removeOne(*it);
        }
        uninitialised.squeeze();
    }
}

//******************************************************************************
//! Draw the next frame for all children (method runs in current OpenGL context)
/*!
*	\param none.
*	\return none.
*/

void ViewOfEntities::draw()
{
    if (program)
    {
        if (!uninitialised.isEmpty())
        {
            QVector<Entity*>::iterator it = uninitialised.begin();
            while (it != uninitialised.end())
            {
                (*it)->init(program);
                it = uninitialised.erase(it);
            }
            uninitialised.squeeze();
        }
        for (QVector<Entity*>::iterator it = children.begin(); it != children.end() && Entity::visible; ++it)
            if ((*it)->isVisible())
                (*it)->draw();
    }
}

//******************************************************************************
//! Calculates the next step for every child
/*!
*	\param none.
*	\return none.
*/

void ViewOfEntities::calcNextStep()
{
    for (QVector<Entity*>::iterator it = children.begin(); it != children.end(); ++it)
    {
        if(uninitialised.isEmpty())
        {
            QFuture<void> future = QtConcurrent::run(*it, &Entity::calcNextStep);
            future.waitForFinished();
        }
        else
            break;
    }
}





