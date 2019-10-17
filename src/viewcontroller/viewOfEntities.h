//*************************************************************************
/** \file
*  \brief Contains the declaration of class ViewOfEntities.
*/


#pragma once

#include "entity.h"

//*************************************************************************
/*!	\class ViewOfEntities
*	\ingroup CompositePattern
*	\brief Member of pattern <b>Composite</b> as <b>Composite</b>.
*	       Defines an abstract graphical element that can contain other entities or views.
*		   It implements the basic functionality of Entity and adds additional features
*		   that affect every child it contains.
*
*		   It gives the functionality to add to, remove from, access, clear and destroy the list of children.
*		   
*/

class ViewOfEntities : virtual public Entity
{
    Q_OBJECT
		
    public:
      explicit ViewOfEntities(QObject* parent);
      virtual ~ViewOfEntities() = 0;
      virtual void setVisibility(bool v);
      virtual bool isVisible();
      virtual void add(Entity* entity);
      virtual void remove(Entity* entity);
      virtual void clear();
      virtual void destroy();
      virtual bool isEmpty();
      virtual bool contains(Entity* entity);
      virtual int getSize();
      virtual Entity* getChild(int i);
      virtual void init(QOpenGLShaderProgram *p);
      virtual void draw();
      virtual void calcNextStep();
    protected:
      QVector<Entity*> children;
      QVector<Entity*> uninitialised;
};

