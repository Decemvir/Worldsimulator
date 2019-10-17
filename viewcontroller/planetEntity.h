//*************************************************************************
/** \file
*  \brief Contains the declaration of class PlanetEntity.
*/

#pragma once

#include "../model/god/planet.h"
#include "viewOfEntities.h"

class LifeFormEntity;

//*************************************************************************
/*!	\class PlanetEntity
*	\ingroup Adapter
*	\brief Member of pattern <b>Adapter</b> as <b>Adapter</b> and <b>Target</b>.
*	       Redefines and adds to the interface functionality inherited from the class Planet.
*		   Implements interface functionality from the class ViewOfEntities.
*		   This class defines a set of methods to render a planet with custom texture that
*		   is orbiting around a given center point, add/remove satellites and lifeforms and make
*		   the data accessible.   
*/

class PlanetEntity : public ViewOfEntities, private Planet
{
    public:
      PlanetEntity(QObject *parent,const char* name, CartesianCoordAdapter const &coord);
      ~PlanetEntity();
      void setVisibility(bool v);
      bool isVisible();
      void add(Entity* entity);
      void addSatellite(PlanetEntity* p);
      void addInhabitant(LifeFormEntity* lf);
      void remove(Entity* entity);
      void removeSatellite(PlanetEntity* p);
      void removeInhabitant(LifeFormEntity* lf);
      void clear();
      void clearSatellites();
      void clearInhabitants();
      void destroy();
      bool isEmpty();
      bool hasNoSatellites();
      bool hasNoInhabitants();
      bool contains(Entity* entity);
      bool containsSatellite(PlanetEntity* p);
      bool containsInhabitant(LifeFormEntity* lf);
      int getSize();
      int getSatelliteCount();
      int getInhabitantCount();
      Entity* getChild(int i);
      PlanetEntity* getSatellite(int i);
      LifeFormEntity* getInhabitant(int i);
      void init(QOpenGLShaderProgram * p);
      void draw();
      void calcNextStep();
      void setOrbitCenter(QVector3D c);
      void setPlanetRadius(double r);
      void setOwnRotVelocity(double v);
      void setVelocityInOrbit(double v);
      void setOrbitColor(QVector3D c);
      void setPlanetColor(QVector3D c);
      void setTextureFileName(QString filename);
      QString getName();
      QVector3D getCurrentPosition();
      QVector3D getOrbitCenter();
      QVector2D getOrbitRadii();
      double getOwnRotVelocity();
      double getRotAngle();
      double getVerlocitiyInOrbit();
      double getPlanetRadius();
      CartesianCoordAdapter getInitialPlanetPos();
    private:
      void calcRotAngles();
      void calcSphere(int lats, int longs);
      void calcEllipse(int num_segments);
      double orbitRadiusY;
      double orbitRadiusX;
      double sphereRadius;
      double currentPosXY[2];
      double orbitCenterPos[3];
      double ownRotVelocity;
      double currentRotAngle;
      double orbitVelocity;
      double rotAngleXY;
      double rotAngleYZ;
      QVector3D orbitColor;
      QVector3D planetColor;
      QMatrix4x4 model;
      QOpenGLTexture* texture;
      QString textureFileName;
      bool textureChanged;
      QVector<PlanetEntity*> satellites;
      QVector<LifeFormEntity*> inhabitants;
      QOpenGLVertexArrayObject sphereVAO;
      QOpenGLBuffer spherePositionVBO;
      QOpenGLBuffer sphereTexCoordVBO;
      QOpenGLBuffer sphereNormalVBO;
      QVector<QVector3D> sphereVert;
      QVector<QVector2D> sphereTexCoord;
      QOpenGLVertexArrayObject ellipseVAO;
      QOpenGLBuffer ellipsePositionVBO;
      QVector<QVector3D> ellipseVert;
      QString planetName;
};
