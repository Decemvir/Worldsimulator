//*************************************************************************
/** \file
*  \brief Contains the implementation of class UniverseEntity.
*/

#include "universeEntity.h"

//******************************************************************************
//! Returns the unique UniverseEntity. (Singleton)
/*!
*  \param parent QT parent pointer.
*	\return The single instance of class UniverseEntity.
*/

UniverseEntity* UniverseEntity::Instance(QObject *parent)
{
    static UniverseEntity ourUniverseEntity(parent);
    return &ourUniverseEntity;
}

//******************************************************************************
//! Returns time of universe
/*!
*	\param none.
*	\return time.
*/

unsigned long UniverseEntity::getTime()
{
    return Universe::getUniverse()->getTime();
}

//******************************************************************************
//! Sets the visibility for the universe
/*!
*	\param v visibility to be set
*	\return none.
*/

void UniverseEntity::setVisibility(bool v)
{
    ViewOfEntities::setVisibility(v);
}

//******************************************************************************
//! Returns the visibility of the universe
/*!
*	\param none.
*	\return current visibility.
*/

bool UniverseEntity::isVisible()
{
    return ViewOfEntities::isVisible();
}

//******************************************************************************
//! Adds entity to the universe
/*!
*	\param entity.
*	\return none.
*/

void UniverseEntity::add(Entity* entity)
{
    SolarSystemEntity* s = dynamic_cast<SolarSystemEntity*>(entity);
    if (s)
        add(s);
}

//******************************************************************************
//! Adds solar system to the universe
/*!
*	\param solar system.
*	\return none.
*/

void UniverseEntity::add(SolarSystemEntity* s)
{
    if (s && !contains(s))
    {
        galaxy.push_back(s);
        ViewOfEntities::add(s);
    }
}

//******************************************************************************
//! Removes entity from the universe
/*!
*	\param entity.
*	\return none.
*/

void UniverseEntity::remove(Entity* entity)
{
    SolarSystemEntity* s = dynamic_cast<SolarSystemEntity*>(entity);
    if (s)
        remove(s);
}

//******************************************************************************
//! Removes solar system from the universe
/*!
*	\param solar system.
*	\return none.
*/

void UniverseEntity::remove(SolarSystemEntity* s)
{
    if (s)
    {
        galaxy.removeOne(s);
        galaxy.squeeze();
        ViewOfEntities::remove(s);
    }
}

//******************************************************************************
//! Removes all entities from the universe
/*!
*	\param none.
*	\return none.
*/

void UniverseEntity::clear()
{
    galaxy.clear();
    galaxy.squeeze();
    ViewOfEntities::clear();
}

//******************************************************************************
//! Destroy all entities held by the universe
/*!
*	\param none.
*	\return none.
*/

void UniverseEntity::destroy()
{
    ViewOfEntities::destroy();
}

//******************************************************************************
//! Check if there are no solar systems in the universe
/*!
*	\param none.
*	\return true if there are no solar systems in the universe
*/

bool UniverseEntity::isEmpty()
{
    return galaxy.isEmpty();
}

//******************************************************************************
//! Check if universe contains specific entity
/*!
*	\param entity.
*	\return true if the universe contains the entity.
*/

bool UniverseEntity::contains(Entity* entity)
{
    return ViewOfEntities::contains(entity);
}

//******************************************************************************
//! Returns number of solar systems in the universe
/*!
*	\param none.
*	\return number of solar systems.
*/

int UniverseEntity::getSize()
{
    return galaxy.size();
}

//******************************************************************************
//! Returns entity with index i
/*!
*	\param index i.
*	\return entity with index i.
*/

Entity* UniverseEntity::getChild(int i)
{
    return children.at(i);
}

//******************************************************************************
//! Returns solar system with index i
/*!
*	\param index i.
*	\return solar system with index i.
*/

SolarSystemEntity* UniverseEntity::getSolarSystem(int i)
{
    return galaxy.at(i);
}

//******************************************************************************
//! Returns time in ticks
/*!
*	\param none.
*	\return tickCount.
*/

unsigned long long UniverseEntity::getTimeinTicks()
{
    return timeInTicks;
}

//******************************************************************************
//! Initialises the universe (method runs in current OpenGL context)
/*!
*	\param p shader program to be set.
*	\return none.
*/

void UniverseEntity::init(QOpenGLShaderProgram * p)
{
    program = p;
    if (program)
    {
        texture = new QOpenGLTexture(QImage(QDir::currentPath() + "/viewcontroller/Resources/Textures/skybox.jpg").mirrored());

        if (texture->isCreated())
        {
            texture->setMinificationFilter(QOpenGLTexture::Nearest);
            texture->setMagnificationFilter(QOpenGLTexture::Nearest);
            texture->setWrapMode(QOpenGLTexture::Repeat);
            texture->allocateStorage();
        }

        skyboxPositionVBO.create();
        skyboxPositionVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);

        skyboxTexCoordVBO.create();
        skyboxTexCoordVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);

        skyboxPositionVBO.bind();
        skyboxPositionVBO.allocate(skyboxVert.constData(), skyboxVert.size() * sizeof(QVector3D));
        skyboxPositionVBO.release();

        skyboxTexCoordVBO.bind();
        skyboxTexCoordVBO.allocate(skyboxTexCoord.constData(), skyboxTexCoord.size() * sizeof(QVector2D));
        skyboxTexCoordVBO.release();

        skyboxVAO.create();
        skyboxVAO.bind();
        skyboxPositionVBO.bind();
        program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
        program->setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3);
        skyboxPositionVBO.release();
        skyboxTexCoordVBO.bind();
        program->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
        program->setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 0, 2);
        skyboxTexCoordVBO.release();
        skyboxVAO.release();

        model.scale(scaleFactor);
        ViewOfEntities::init(program);
    }
}

//******************************************************************************
//! Draw universe (method runs in current OpenGL context)
/*!
*	\param none.
*	\return none.
*/

void UniverseEntity::draw()
{
    if (program)
    {
        program->bind();
        if (texture->isCreated())
            program->setUniformValue("textureEnabled", true);
        else
            program->setUniformValue("textureEnabled", false);

        model.rotate(0.0001, 0, 1);
        program->setUniformValue("normalEnabled", false);
        program->setUniformValue("modelMatrix", model);
        program->setUniformValue("color", skyboxColor);
        program->setUniformValue("texture", 0);

        skyboxVAO.bind();
        if (texture->isCreated())
            texture->bind();

        //for (int i = 0; i < 6; ++i)
            //glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);

        if (texture->isCreated())
            texture->release();

        skyboxVAO.release();

        program->release();
        ViewOfEntities::draw();
    }
}

//******************************************************************************
//! Calculates the next step for the universe
/*!
*	\param none.
*	\return none.
*/

void UniverseEntity::calcNextStep()
{
    ++timeInTicks;
    ViewOfEntities::calcNextStep();
}

//******************************************************************************
//! Sets skybox scaling factor
/*!
*	\param scale factor.
*	\return none.
*/

void UniverseEntity::setSkyboxScaleFactor(double s)
{
    QMatrix4x4 oldScale, rot;
    oldScale.setToIdentity();
    rot.setToIdentity();
    oldScale.scale(scaleFactor);
    scaleFactor = s;
    rot = oldScale.inverted() * model;
    if (!model.isIdentity())
    {
        model.setToIdentity();
        model.scale(scaleFactor);
        model *= rot;
    }
}

//******************************************************************************
//! Constructor of class UniverseEntity
/*!
*	\param parent QT parent pointer.
*	\return none.
*/

UniverseEntity::UniverseEntity(QObject *parent) :ViewOfEntities(parent), Entity(parent), Universe()
{
    texture = nullptr;
    skyboxColor = QVector3D(0.5, 0.5, 0.5);
    model.setToIdentity();
    scaleFactor = 500.0f;
    timeInTicks = 0;

    skyboxVert = {  QVector3D(1.0, -1.0, -1.0), QVector3D(-1.0, -1.0, -1.0), QVector3D(-1.0,  1.0, -1.0), QVector3D(1.0,  1.0, -1.0),
					QVector3D(1.0,  1.0, -1.0), QVector3D(-1.0,  1.0, -1.0), QVector3D(-1.0,  1.0,  1.0), QVector3D(1.0,  1.0,  1.0),
					QVector3D(1.0, -1.0,  1.0), QVector3D(1.0, -1.0, -1.0), QVector3D(1.0,  1.0, -1.0), QVector3D(1.0,  1.0,  1.0),
					QVector3D(-1.0, -1.0, -1.0), QVector3D(-1.0, -1.0,  1.0), QVector3D(-1.0,  1.0,  1.0), QVector3D(-1.0,  1.0, -1.0),
					QVector3D(1.0, -1.0,  1.0), QVector3D(-1.0, -1.0,  1.0), QVector3D(-1.0, -1.0, -1.0), QVector3D(1.0, -1.0, -1.0),
					QVector3D(-1.0, -1.0,  1.0), QVector3D(1.0, -1.0,  1.0), QVector3D(1.0,  1.0,  1.0), QVector3D(-1.0,  1.0,  1.0) };

    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 4; ++j)
            skyboxTexCoord << QVector2D(j == 0 || j == 3, j == 0 || j == 1);
}

//******************************************************************************
//! Deconstructor of class SolarSystemEntity

UniverseEntity::~UniverseEntity()
{
    delete texture;
    texture = nullptr;
    skyboxVAO.destroy();
    skyboxPositionVBO.destroy();
    skyboxTexCoordVBO.destroy();
}
