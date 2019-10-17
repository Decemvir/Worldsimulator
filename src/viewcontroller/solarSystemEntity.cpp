//*************************************************************************
/** \file
*  \brief Contains the implementation of class SolarSystemEntity.
*/

#include "solarSystemEntity.h"
#include "lighthandler.h"

//******************************************************************************
//! Constructor of class SolarSystemEntity
/*!
*	\param parent QT parent pointer.
*	\param position of the sun.
*	\return none.
*/

SolarSystemEntity::SolarSystemEntity(QObject *parent,
                                     CartesianCoordAdapter coord) : ViewOfEntities(parent), Entity(parent)
{
    sun = new PlanetEntity(parent,"Sun", CartesianCoordAdapter(0, 0, 0));
    sun->setOrbitCenter(QVector3D(coord.getX(), coord.getY(), coord.getZ()));
    sun->setPlanetColor(QVector3D(1, 1, 0.5));
    sun->setTextureFileName("sun.jpg");
    sun->setOwnRotVelocity(0.0);
    sun->setPlanetRadius(0.8);
    emissiveKoeff = 1.5f;
}

//******************************************************************************
//! Deconstructor of class SolarSystemEntity

SolarSystemEntity::~SolarSystemEntity()
{
    LightHandler::Instance(parent())->removeLightAt(sun->getOrbitCenter());
    delete sun;
    sun = nullptr;
}

//******************************************************************************
//! Sets the visibility for the solar system
/*!
*	\param v visibility to be set
*	\return none.
*/

void SolarSystemEntity::setVisibility(bool v)
{
    ViewOfEntities::setVisibility(v);
}

//******************************************************************************
//! Returns the visibility of the solar system
/*!
*	\param none.
*	\return current visibility.
*/

bool SolarSystemEntity::isVisible()
{
    return ViewOfEntities::isVisible();
}

//******************************************************************************
//! Adds entity to the solar system
/*!
*	\param entity.
*	\return none.
*/

void SolarSystemEntity::add(Entity* entity)
{
    PlanetEntity* p = dynamic_cast<PlanetEntity*>(entity);
    if (p)
        add(p);
}

//******************************************************************************
//! Adds planet to the solar system
/*!
*	\param planet.
*	\return none.
*/

void SolarSystemEntity::add(PlanetEntity* p)
{
    if (p && !contains(p))
    {
        p->setOrbitCenter(sun->getOrbitCenter());
        planets.push_back(p);
        ViewOfEntities::add(p);
    }
}

//******************************************************************************
//! Remove entity from the solar system
/*!
*	\param entity.
*	\return none.
*/

void SolarSystemEntity::remove(Entity* entity)
{
    PlanetEntity* p = dynamic_cast<PlanetEntity*>(entity);
    if (p)
        remove(p);
}

//******************************************************************************
//! Remove planet from the solar system
/*!
*	\param planet.
*	\return none.
*/

void SolarSystemEntity::remove(PlanetEntity* p)
{
    if (p)
    {
        planets.removeOne(p);
        planets.squeeze();
        ViewOfEntities::remove(p);
    }
}

//******************************************************************************
//! Remove all entities from the solarsystem
/*!
*	\param none.
*	\return none.
*/

void SolarSystemEntity::clear()
{
    planets.clear();
    planets.squeeze();
    ViewOfEntities::clear();
}

//******************************************************************************
//! Destroy all entities held by the solarsystem
/*!
*	\param none.
*	\return none.
*/

void SolarSystemEntity::destroy()
{
    ViewOfEntities::destroy();
}

//******************************************************************************
//! Check if there are no planets in the solar system
/*!
*	\param none.
*	\return true if there are no planets in the solar system.
*/

bool SolarSystemEntity::isEmpty()
{
    return planets.isEmpty();
}

//******************************************************************************
//! Check if solar system contains specific entity
/*!
*	\param entity.
*	\return true if the solar system contains the entity.
*/

bool SolarSystemEntity::contains(Entity* entity)
{
    return ViewOfEntities::contains(entity);
}

//******************************************************************************
//! Returns number of planets in the solar system
/*!
*	\param none.
*	\return number of planets.
*/

int SolarSystemEntity::getSize()
{
    return planets.size();
}

//******************************************************************************
//! Returns entity with index i
/*!
*	\param index i.
*	\return entity with index i.
*/

Entity* SolarSystemEntity::getChild(int i)
{
    return children.at(i);
}

//******************************************************************************
//! Returns planet with index i
/*!
*	\param index i.
*	\return planet with index i.
*/

PlanetEntity* SolarSystemEntity::getPlanet(int i)
{
    return planets.at(i);
}

//******************************************************************************
//! Initialises the solar system (method runs in current OpenGL context)
/*!
*	\param p shader program to be set.
*	\return none.
*/

void SolarSystemEntity::init(QOpenGLShaderProgram * p)
{
    program = p;
    if (program)
    {
        LightHandler::Instance(parent())->initLightHandler(program);
        LightHandler::Instance(parent())->addLightAt(sun->getOrbitCenter());
        sun->init(program);
        ViewOfEntities::init(program);
    }
}

//******************************************************************************
//! Draw solar system (method runs in current OpenGL context)
/*!
*	\param none.
*	\return none.
*/

void SolarSystemEntity::draw()
{
    if (program)
    {
        QVector4D lightKoeffs = LightHandler::Instance(parent())->getLightKoeffs();
        LightHandler::Instance(parent())->setLightKoeffs(emissiveKoeff, 0, 0, 0);
        sun->draw();
        LightHandler::Instance(parent())->setLightKoeffs(lightKoeffs[0], lightKoeffs[1], lightKoeffs[2], lightKoeffs[3]);
        ViewOfEntities::draw();
    }
}

//******************************************************************************
//! Calculates the next step for the solar system
/*!
*	\param none.
*	\return none.
*/

void SolarSystemEntity::calcNextStep()
{
    ViewOfEntities::calcNextStep();
}

//******************************************************************************
//! Sets the center of the solar system
/*!
*	\param center.
*	\return none.
*/

void SolarSystemEntity::setSolarSystemCenter(QVector3D c)
{
    LightHandler::Instance(parent())->removeLightAt(sun->getOrbitCenter());
    sun->setOrbitCenter(c);
    LightHandler::Instance(parent())->addLightAt(sun->getOrbitCenter());
    for (QVector<PlanetEntity*>::iterator it = planets.begin(); it != planets.end(); ++it)
        (*it)->setOrbitCenter(c);
}

//******************************************************************************
//! Sets texture filename for the sun of the solar system
/*!
*	\param filename.
*	\return none.
*/

void SolarSystemEntity::setSunTextureFileName(QString filename)
{
    sun->setTextureFileName(filename);
}

//******************************************************************************
//! Sets the suns radius
/*!
*	\param radius.
*	\return none.
*/

void SolarSystemEntity::setSunRadius(double r)
{
    sun->setPlanetRadius(r);
}

//******************************************************************************
//! Sets the suns emissive koefficient
/*!
*	\param emissive koefficient.
*	\return none.
*/

void SolarSystemEntity::setSunEmissiveKoeff(double kE)
{
    if (kE > 0.0f)
        emissiveKoeff = kE;
}

//******************************************************************************
//! Returns current solar system center
/*!
*	\param none.
*	\return three dimensional vector.
*/

QVector3D SolarSystemEntity::getSolarSystemCenter()
{
    return sun->getOrbitCenter();
}









