//*************************************************************************
/** \file
*  \brief Contains the declaration of class LifeFormEntity.
*/

#pragma once

#include "../model/god/lifeForm.h"
#include <queue>
#include "entity.h"
#include "planetEntity.h"
#include "lfJobs.h"
#include "lfJobHandler.h"
#include "destinyAdapter.h"

//*************************************************************************
/*!	\class LifeFormEntity
*	\ingroup CompositePattern Adapter
*	\brief Member of pattern <b>Composite</b> as <b>Leaf</b>.
*		   Member of pattern <b>Adapter</b> as <b>Adapter</b> and <b>Target</b>.
*	       Redefines and adds to the interface functionality inherited from the class LifeForm.
*		   Implements interface functionality from the class Entity.
*		   This class defines a set of methods to create jobs for the life form specific job queue,
*		   start it's life and calculate the necessary three dimensional information to render it as a colored point.
*/

class LifeFormEntity : virtual public Entity, private LifeForm
{
	Q_OBJECT

public:
	LifeFormEntity(QObject *parent, const char* name, const char* god, LifeFormEntity* father, LifeFormEntity* mother);
	LifeFormEntity(LifeFormEntity& copy);
	virtual ~LifeFormEntity() = 0;
	LifeFormEntity& operator=(LifeFormEntity& copy);
	virtual void setVisibility(bool v);
	virtual bool isVisible();
	virtual void init(QOpenGLShaderProgram *p);
	virtual void draw();	
	void calcNextStep() final;
	virtual bool solveProblem(LifeFormEntity * lfThatReceives = nullptr);
	virtual int getDevLvl();
	void addKnownLFE(LifeFormEntity * lf);
	void forgetAboutLFE(LifeFormEntity * lf);
	void askKnownLFE(LifeFormEntity * lfThatReceives = nullptr); 
	void meetWith(LifeFormEntity* lf);
	void mateWith(LifeFormEntity* lf);
	void receiveAnswer(LifeFormEntity* lf, bool answer);
	bool moveTowardsDest(CartesianCoordAdapter dest);
	bool isOnSamePlanetAs(LifeFormEntity* lf);
	bool isParentOf(LifeFormEntity* lf);
	bool knows(LifeFormEntity* lf);
	QString getName();
	QString getGodName();
    unsigned long long getLifetimeInTicks();
	QVector3D getAbsolutPosition();
	CartesianCoordAdapter getRelativePos();
	QVector3D getHomePlanetPos();
    PlanetEntity* getHomePlanetEntity();
	LifeFormEntity* getFather();
	LifeFormEntity* getMother();
	QVector<LifeFormEntity*> getKnownLFEntities();
    unsigned long long getGeneration();
	QVector3D getLFEColor();
	void setLFEColor(QVector3D c);
	void inhabitPlanet(PlanetEntity* p, CartesianCoordAdapter* dest = nullptr);
	void resetPlanetRadius();
protected:
	CartesianCoordAdapter calcRandDestination();
	QString lfName;
	QVector3D lfeColor;
	QVector<QVector3D> lfVert;
	QOpenGLVertexArrayObject lfVAO;
	QOpenGLBuffer lfPositionVBO;
	QMatrix4x4 model;
	PlanetEntity* homePlanetEntity;
	QVector<LifeFormEntity*> knownLFEntities;
	CartesianCoordAdapter currentRelativePos;	
    unsigned long long lifetimeInTicks;
    unsigned long long gen;
	LifeFormEntity* lfFather;
	LifeFormEntity* lfMother;
	LFJobHandler* ourJobHandler;
	DestinyAdapter* ourDestinyAdapter;
};
