//*************************************************************************
/** \file
*  \brief Contains the declaration of class SolarSystemEntity.
*/

#pragma once

#include "viewOfEntities.h"
#include "planetEntity.h"

//*************************************************************************
/*!	\class SolarSystemEntity
*	\ingroup FacadeTE
*	\brief Member of pattern <b>Facade</b> as <b>Subsystem classes</b>.
*		   Implements interface functionality from the class ViewOfEntities.
*		   This class defines a set of methods to render a solar system with a sun 
*		   that emits light and add/remove planets.
*/

class SolarSystemEntity : public ViewOfEntities
{
    public:
      SolarSystemEntity(QObject *parent, CartesianCoordAdapter coord);
      ~SolarSystemEntity();
      void setVisibility(bool v);
      bool isVisible();
      void add(Entity* entity);
      void add(PlanetEntity* p);
      void remove(Entity* entity);
      void remove(PlanetEntity* p);
      void clear();
      void destroy();
      bool isEmpty();
      bool contains(Entity* entity);
      int getSize();
      Entity* getChild(int i);
      PlanetEntity* getPlanet(int i);
      void init(QOpenGLShaderProgram * p);
      void draw();
      void calcNextStep();
      void setSolarSystemCenter(QVector3D c);
      void setSunTextureFileName(QString filename);
      void setSunRadius(double r);
      void setSunEmissiveKoeff(double kE);
      QVector3D getSolarSystemCenter();
    private:
      PlanetEntity* sun;
      QVector<PlanetEntity*> planets;
      double emissiveKoeff;
};









