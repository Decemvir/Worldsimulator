//*************************************************************************
/** \file
*  \brief Contains the declaration of class UniverseEntity.
*/

#pragma once

#include <QObject>
#include "../model/god/universe.h"
#include "viewOfEntities.h"
#include "solarSystemEntity.h"

//*************************************************************************
/*!	\class UniverseEntity
*	\ingroup Adapter SingletonTE
*	\brief Member of pattern <b>Adapter</b> as <b>Adapter</b> and <b>Target</b>.
*		   Member of pattern <b>Singleton</b>.
*	       Redefines and adds to the interface functionality inherited from the class Universe.
*		   Implements interface functionality from the class ViewOfEntities.
*		   This class defines a set of methods to render a skybox and add/remove solar systems.
*/

class UniverseEntity : public ViewOfEntities, private Universe
{
    Q_OBJECT

    public:
      static UniverseEntity* Instance(QObject *parent);
      unsigned long getTime();
      void setVisibility(bool v);
      bool isVisible();
      void add(Entity* entity);
      void add(SolarSystemEntity* s);
      void remove(Entity* entity);
      void remove(SolarSystemEntity* s);
      void clear();
      void destroy();
      bool isEmpty();
      bool contains(Entity* entity);
      int getSize();
      Entity* getChild(int i);
      SolarSystemEntity* getSolarSystem(int i);
      unsigned long long getTimeinTicks();
      void init(QOpenGLShaderProgram * p);
      void draw();
      void calcNextStep();
      void setSkyboxScaleFactor(double s);
    protected:
      UniverseEntity(QObject *parent);
      ~UniverseEntity();
      QVector<QVector3D> skyboxVert;
      QVector<QVector2D> skyboxTexCoord;
      QOpenGLTexture* texture;
      QOpenGLVertexArrayObject skyboxVAO;
      QOpenGLBuffer skyboxPositionVBO;
      QOpenGLBuffer skyboxTexCoordVBO;
      QVector3D skyboxColor;
      QMatrix4x4 model;
      QVector<SolarSystemEntity*> galaxy;
      double scaleFactor;
      unsigned long long timeInTicks;
};
