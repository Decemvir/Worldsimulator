//*************************************************************************
/** \file
*  \brief Contains the implementation of class PlanetEntity.
*/

#include "planetEntity.h"
#include "lifeformEntity.h"

//******************************************************************************
//! Constructor of class PlanetEntity
/*!
*	\param parent QT parent pointer.
*	\param name of the life form.
*	\param initial starting position of the planet.
*	\return none.
*/

PlanetEntity::PlanetEntity(QObject *parent,
                           const char* name,
                           CartesianCoordAdapter const &coord) : ViewOfEntities(parent), Entity(parent), Planet(coord)
{
    planetName = name;
    orbitRadiusY = sqrt(pow(coords.getX(), 2) + pow(coords.getY(), 2) + pow(coords.getZ(), 2));
    orbitRadiusX = orbitRadiusY * 1.7;
    sphereRadius = 0.1f;
    currentPosXY[0] = 0;
    currentPosXY[1] = 1;
    orbitCenterPos[0] = 0;
    orbitCenterPos[1] = 0;
    orbitCenterPos[2] = 0;
    ownRotVelocity = 0.005f;
    currentRotAngle = 0.0f;
    orbitVelocity = 10000;
    orbitColor = QVector3D(1, 1, 1);
    planetColor = QVector3D(0, 0, 1);
    model.setToIdentity();
    calcRotAngles();
    texture = nullptr;
    textureChanged = false;
}

//******************************************************************************
//! Deconstructor of class PlanetEntity

PlanetEntity::~PlanetEntity()
{
    delete texture;
    texture = nullptr;
    sphereVAO.destroy();
    spherePositionVBO.destroy();
    sphereTexCoordVBO.destroy();
    sphereNormalVBO.destroy();
    ellipseVAO.destroy();
    ellipsePositionVBO.destroy();
}

//******************************************************************************
//! Sets the visibility for the planet
/*!
*	\param v visibility to be set
*	\return none.
*/

void PlanetEntity::setVisibility(bool v)
{
    ViewOfEntities::setVisibility(v);
}

//******************************************************************************
//! Returns the visibility of the planet
/*!
*	\param none.
*	\return current visibility.
*/

bool PlanetEntity::isVisible()
{
    return ViewOfEntities::isVisible();
}

//******************************************************************************
//! Adds entity to the planet
/*!
*	\param entity.
*	\return none.
*/

void PlanetEntity::add(Entity* entity)
{
    PlanetEntity* s = dynamic_cast<PlanetEntity*>(entity);
    if (s)
        addSatellite(s);
    else
    {
        LifeFormEntity* lf = dynamic_cast<LifeFormEntity*>(entity);
        if (lf) addInhabitant(lf);
    }
}

//******************************************************************************
//! Adds satellite to the planet
/*!
*	\param planet.
*	\return none.
*/

void PlanetEntity::addSatellite(PlanetEntity* p)
{
    if (p && !contains(p) && !p->contains(this) && p != this)
    {
        qDebug() << "[PlanetEntity::addSatellite]" << p->getName() << "was added as satellite to" << planetName;
        p->setOrbitCenter(this->getCurrentPosition());
        satellites.push_back(p);
        ViewOfEntities::add(p);
    }
}

//******************************************************************************
//! Adds inhabitant to the planet
/*!
*	\param life form.
*	\return none.
*/

void PlanetEntity::addInhabitant(LifeFormEntity* lf)
{
    if (lf && !containsInhabitant(lf) && (!lf->getHomePlanetEntity() || lf->getHomePlanetEntity() == this))
    {
        Planet::addLF((LifeForm*)lf);
        qDebug() << "[PlanetEntity::addInhabitant]" << lf->getName() << "was settled on planet" << planetName;
        inhabitants.push_back(lf);
        ViewOfEntities::add(lf);
        lf->inhabitPlanet(this);
    }
}

//******************************************************************************
//! Removes entity from the planet
/*!
*	\param entity.
*	\return none.
*/

void PlanetEntity::remove(Entity* entity)
{
    PlanetEntity* s = dynamic_cast<PlanetEntity*>(entity);
    if (s)
        removeSatellite(s);
    else
    {
        LifeFormEntity* lf = dynamic_cast<LifeFormEntity*>(entity);
        if (lf)
            removeInhabitant(lf);
    }
}

//******************************************************************************
//! Removes satellite from the planet
/*!
*	\param planet.
*	\return none.
*/

void PlanetEntity::removeSatellite(PlanetEntity* p)
{
    if (p && contains(p))
    {
        qDebug() << "[PlanetEntity::removeSatellite]" << p->getName() << "is not longer orbiting around" << planetName;
        satellites.removeOne(p);
        satellites.squeeze();
        ViewOfEntities::remove(p);
    }
}

//******************************************************************************
//! Removes inhabitant from the planet
/*!
*	\param life form.
*	\return none.
*/

void PlanetEntity::removeInhabitant(LifeFormEntity* lf)
{
    if (lf && contains(lf))
    {
        qDebug() << "[PlanetEntity::removeInhabitant]" << lf->getName() << "was removed from planet" << planetName;
        inhabitants.removeOne(lf);
        inhabitants.squeeze();
        ViewOfEntities::remove(lf);
    }
}

//******************************************************************************
//! Removes all entities from the planet
/*!
*	\param none.
*	\return none.
*/

void PlanetEntity::clear()
{
    clearSatellites();
    clearInhabitants();
    ViewOfEntities::clear();
}

//******************************************************************************
//! Removes all satellites from the planet
/*!
*	\param none.
*	\return none.
*/

void PlanetEntity::clearSatellites()
{
    QVector<PlanetEntity*>::iterator it = satellites.begin();
    while (it != satellites.end())
    {
        removeSatellite(*it);
        it = satellites.begin();
    }
    satellites.clear();
    satellites.squeeze();
}

//******************************************************************************
//! Removes all inhabitants from the planet
/*!
*	\param none.
*	\return none.
*/

void PlanetEntity::clearInhabitants()
{
    QVector<LifeFormEntity*>::iterator it = inhabitants.begin();
    while (it != inhabitants.end())
    {
        removeInhabitant(*it);
        it = inhabitants.begin();
    }
    inhabitants.clear();
    inhabitants.squeeze();
}

//******************************************************************************
//! Destroy all entities held by the planet
/*!
*	\param none.
*	\return none.
*/

void PlanetEntity::destroy()
{
    ViewOfEntities::destroy();
}

//******************************************************************************
//! Checks if planet holds no entities
/*!
*	\param none.
*	\return true if planet holds no entities.
*/

bool PlanetEntity::isEmpty()
{
    return ViewOfEntities::isEmpty();
}

//******************************************************************************
//! Checks if planet has no satellites
/*!
*	\param none.
*	\return true if planet has no satellites.
*/

bool PlanetEntity::hasNoSatellites()
{
    return satellites.isEmpty();
}

//******************************************************************************
//! Checks if planet has no inhabitants
/*!
*	\param none.
*	\return true if planet has no inhabitants.
*/

bool PlanetEntity::hasNoInhabitants()
{
    return inhabitants.empty();
}

//******************************************************************************
//! Checks if planet contains entity
/*!
*	\param entity.
*	\return true if planet contains entity.
*/

bool PlanetEntity::contains(Entity* entity)
{
    return ViewOfEntities::contains(entity);
}

//******************************************************************************
//! Checks if planet has satellite p
/*!
*	\param planet.
*	\return true if planet contains p.
*/

bool PlanetEntity::containsSatellite(PlanetEntity* p)
{
    if (p)
        return satellites.contains(p);

	return false;
}

//******************************************************************************
//! Checks if planet has inhabitant lf
/*!
*	\param lf.
*	\return true if planet contains lf.
*/

bool PlanetEntity::containsInhabitant(LifeFormEntity* lf)
{
    if (lf)
        return inhabitants.contains(lf);

    return false;
}

//******************************************************************************
//! Returns amount of children
/*!
*	\param none.
*	\return amount of children.
*/

int PlanetEntity::getSize()
{
    return ViewOfEntities::getSize();
}

//******************************************************************************
//! Returns amount of satellites
/*!
*	\param none.
*	\return amount of satellites.
*/

int PlanetEntity::getSatelliteCount()
{
    return satellites.size();
}

//******************************************************************************
//! Returns amount of inhabitants
/*!
*	\param none.
*	\return amount of inhabitants.
*/

int PlanetEntity::getInhabitantCount()
{
    return inhabitants.size();
}

//******************************************************************************
//! Returns entity with index i
/*!
*	\param index.
*	\return entity with index i.
*/

Entity* PlanetEntity::getChild(int i)
{
    return children.at(i);
}

//******************************************************************************
//! Returns satellite with index i
/*!
*	\param index.
*	\return satellite  with index i.
*/

PlanetEntity* PlanetEntity::getSatellite(int i)
{
    return satellites.at(i);
}

//******************************************************************************
//! Returns inhabitant with index i
/*!
*	\param index.
*	\return inhabitant  with index i.
*/

LifeFormEntity* PlanetEntity::getInhabitant(int i)
{
    return inhabitants.at(i);
}

//******************************************************************************
//! Initialises the planet (method runs in current OpenGL context)
/*!
*	\param p shader program to be set.
*	\return none.
*/

void PlanetEntity::init(QOpenGLShaderProgram * p)
{
    program = p;
    if (program)
    {
        if (textureFileName.isEmpty())
            texture = new QOpenGLTexture(QImage(QDir::currentPath() + "/viewcontroller/Resources/Textures/earth.jpg").mirrored());
        else
            texture = new QOpenGLTexture(QImage(QDir::currentPath() + "/viewcontroller/Resources/Textures/" + textureFileName).mirrored());

		if (texture->isCreated())
        {
            texture->setMinificationFilter(QOpenGLTexture::Nearest);
            texture->setMagnificationFilter(QOpenGLTexture::Nearest);
            texture->allocateStorage();
        }

        ellipsePositionVBO.create();
        ellipsePositionVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);

        spherePositionVBO.create();
        spherePositionVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);

        sphereTexCoordVBO.create();
        sphereTexCoordVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);

        sphereNormalVBO.create();
        sphereNormalVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);

        calcSphere(180, 360);
        calcEllipse(100);

        ellipseVAO.create();
        ellipseVAO.bind();
        ellipsePositionVBO.bind();
        program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
        program->setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3);
        ellipsePositionVBO.release();
        ellipseVAO.release();

        sphereVAO.create();
        sphereVAO.bind();
        spherePositionVBO.bind();
        program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
        program->setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3);
        spherePositionVBO.release();
        sphereTexCoordVBO.bind();
        program->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
        program->setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 0, 2);
        sphereTexCoordVBO.release();
        sphereNormalVBO.bind();
        program->enableAttributeArray(PROGRAM_NORMAL_ATTRIBUTE);
        program->setAttributeBuffer(PROGRAM_NORMAL_ATTRIBUTE, GL_FLOAT, 0, 3);
        sphereNormalVBO.release();
        sphereVAO.release();
        ViewOfEntities::init(program);
    }
}

//******************************************************************************
//! Draw planet (method runs in current OpenGL context)
/*!
*	\param none.
*	\return none.
*/

void PlanetEntity::draw()
{
    if (program)
    {
        if (textureChanged)
        {
            delete texture;
            texture = nullptr;
            texture = new QOpenGLTexture(QImage(QDir::currentPath() + "/viewcontroller/Resources/Textures/" + textureFileName).mirrored());
            if (texture->isCreated())
            {
                texture->setMinificationFilter(QOpenGLTexture::Nearest);
                texture->setMagnificationFilter(QOpenGLTexture::Nearest);
                texture->allocateStorage();
            }
            textureChanged = false;
        }

        program->bind();

        model.setToIdentity();
        model.translate(orbitCenterPos[0], orbitCenterPos[1], orbitCenterPos[2]);
        model.rotate(rotAngleXY, 0, 0, 1);
        model.rotate(rotAngleYZ, 1, 0, 0);
        program->setUniformValue("normalEnabled", false);
        program->setUniformValue("textureEnabled", false);
        program->setUniformValue("modelMatrix", model);
        program->setUniformValue("color", orbitColor);

        ellipseVAO.bind();
        //glDrawArrays(GL_LINE_LOOP, 0, ellipseVert.size());
        ellipseVAO.release();

        model.setToIdentity();
        model.translate(orbitCenterPos[0], orbitCenterPos[1], orbitCenterPos[2]);
        model.rotate(rotAngleXY, 0, 0, 1);
        model.rotate(rotAngleYZ, 1, 0, 0);
        model.translate(currentPosXY[0] * orbitRadiusX, currentPosXY[1] * orbitRadiusY, 0);
        model.rotate(currentRotAngle, 0, 0, 1);
        program->setUniformValue("normalEnabled", true);

        if (texture->isCreated())
            program->setUniformValue("textureEnabled", true);
        else
            program->setUniformValue("textureEnabled", false);

        program->setUniformValue("modelMatrix", model);
        program->setUniformValue("color", planetColor);
        program->setUniformValue("texture", 0);

        sphereVAO.bind();

        if (texture->isCreated())
            texture->bind();

        //glDrawArrays(GL_TRIANGLE_STRIP, 0, sphereVert.size());
        if (texture->isCreated())
            texture->release();

        sphereVAO.release();

        program->release();
        ViewOfEntities::draw();
    }
}

//******************************************************************************
//! Calculates the next step for the planet on the orbit and sets the center of all satellites to the new position
//! Also calculates the next rotation step
/*!
*	\param none.
*	\return none.
*/

void PlanetEntity::calcNextStep()
{
    double theta = 2 * M_PI / orbitVelocity;
    double c = cos(theta);
    double s = sin(theta);
    double t;

    t = currentPosXY[0];
    currentPosXY[0] = (c * currentPosXY[0] - s * currentPosXY[1]);
    currentPosXY[1] = (s * t + c * currentPosXY[1]);

    currentRotAngle += ownRotVelocity * 360.0;
    currentRotAngle = fmod(currentRotAngle, 360.0);
    for (QVector<PlanetEntity*>::iterator it = satellites.begin(); it != satellites.end(); ++it)
        if(*it)
            (*it)->setOrbitCenter(this->getCurrentPosition());

    ViewOfEntities::calcNextStep();
}

//******************************************************************************
//! Sets new center for the orbit of the planet
/*!
*	\param center.
*	\return none.
*/

void PlanetEntity::setOrbitCenter(QVector3D c)
{
    orbitCenterPos[0] = c[0];
    orbitCenterPos[1] = c[1];
    orbitCenterPos[2] = c[2];
    for (QVector<PlanetEntity*>::iterator it = satellites.begin(); it != satellites.end(); ++it)
        if(*it)
            (*it)->setOrbitCenter(this->getCurrentPosition());
}

//******************************************************************************
//! Sets new radius for the planet
/*!
*	\param radius.
*	\return none.
*/

void PlanetEntity::setPlanetRadius(double r)
{
    sphereRadius = abs(r);
    for (QVector<LifeFormEntity*>::iterator it = inhabitants.begin(); it != inhabitants.end(); ++it) if(*it) (*it)->resetPlanetRadius();
    if (sphereVAO.isCreated()) calcSphere(180, 360);
}

//******************************************************************************
//! Sets rotation velocity for the planet
/*!
*	\param velocity [-100, 100].
*	\return none.
*/

void PlanetEntity::setOwnRotVelocity(double v)
{
    if (v >= 100.0)
        v = 100.0;
    else if (v <= -100.0)
        v = -100.0;

    ownRotVelocity = v / 100.0;
}

//******************************************************************************
//! Sets velocity in orbit for the planet
/*!
*	\param velocity [-100, 100].
*	\return none.
*/

void PlanetEntity::setVelocityInOrbit(double v)
{
    if (v == 0.0)
        orbitVelocity = 1.0;
    else if (abs(v) >= 100.0)
        orbitVelocity = std::copysign(1.0, v) * 100.0;
    else if (abs(v) == 1.0)
        orbitVelocity = v * 10000.0;
    else if (abs(v) < 1.0)
        orbitVelocity = std::copysign(1.0, v) * 10000.0;
    else
        orbitVelocity = v > 0 ? 10000.0 - (v - 1.0) * 100.0 : -(10000.0 - (abs(v) - 1.0) * 100.0);
}

//******************************************************************************
//! Sets orbit color
/*!
*	\param rgb vector.
*	\return none.
*/

void PlanetEntity::setOrbitColor(QVector3D c)
{
    orbitColor = c;
}

//******************************************************************************
//! Sets planet color
/*!
*	\param rgb vector.
*	\return none.
*/

void PlanetEntity::setPlanetColor(QVector3D c)
{
    planetColor = c;
}

//******************************************************************************
//! Sets filename (for example Earth.jpg) for the planet texture
/*!
*	\param filename.
*	\return none.
*/

void PlanetEntity::setTextureFileName(QString filename)
{
    textureFileName = filename;
    textureChanged = true;
}

//******************************************************************************
//! Returns name of the planet
/*!
*	\param none.
*	\return name.
*/

QString PlanetEntity::getName()
{
    return planetName;
}

//******************************************************************************
//! Returns absolut position of the planet
/*!
*	\param none.
*	\return three dimensional vector.
*/

QVector3D PlanetEntity::getCurrentPosition()
{
    QMatrix4x4 rot;
    QVector3D result(currentPosXY[0], currentPosXY[1], 0);

    rot.setToIdentity();
    rot.rotate(rotAngleXY, 0, 0, 1);
    rot.rotate(rotAngleYZ, 1, 0, 0);

    result *= QVector3D(orbitRadiusX, orbitRadiusY, 1);
    result = rot * result;
    result += QVector3D(orbitCenterPos[0], orbitCenterPos[1], orbitCenterPos[2]);

    return result;
}

//******************************************************************************
//! Returns center of the orbit
/*!
*	\param none.
*	\return three dimensional vector.
*/

QVector3D PlanetEntity::getOrbitCenter()
{
    return QVector3D(orbitCenterPos[0], orbitCenterPos[1], orbitCenterPos[2]);
}

//******************************************************************************
//! Returns orbit radii
/*!
*	\param none.
*	\return two dimensional vector.
*/

QVector2D PlanetEntity::getOrbitRadii()
{
    return QVector2D(orbitRadiusX, orbitRadiusY);
}

//******************************************************************************
//! Returns rot velocity of the planet
/*!
*	\param none.
*	\return velocity.
*/

double PlanetEntity::getOwnRotVelocity()
{
    return ownRotVelocity;
}

//******************************************************************************
//! Returns rot angle of the planet
/*!
*	\param none.
*	\return angle.
*/

double PlanetEntity::getRotAngle()
{
    return currentRotAngle;
}

//******************************************************************************
//! Returns velocity in orbit of the planet
/*!
*	\param none.
*	\return velocity.
*/

double PlanetEntity::getVerlocitiyInOrbit()
{
    return orbitVelocity;
}

//******************************************************************************
//! Returns planet radius
/*!
*	\param none.
*	\return radius.
*/

double PlanetEntity::getPlanetRadius()
{
    return sphereRadius;
}

//******************************************************************************
//! Returns initial planet position
/*!
*	\param none.
*	\return CartesianCoordAdapter.
*/

CartesianCoordAdapter PlanetEntity::getInitialPlanetPos()
{
    return coords;
}

//******************************************************************************
//! Calculate rotation angles to rotate the planet from the center of the world space
//! to the correct position
/*!
*	\param none.
*	\return none.
*/

void PlanetEntity::calcRotAngles()
{
    double planetAbsXY = sqrt(pow(coords.getX(), 2) + pow(coords.getY(), 2));
    if (planetAbsXY != 0)
        rotAngleXY = coords.getX() < 0 ? acos(coords.getY() / planetAbsXY)*(180.0 / M_PI) : -acos(coords.getY() / planetAbsXY)*(180.0 / M_PI);
    else
        rotAngleXY = 0;

    double scalarYZ = coords.getX() * coords.getX() + coords.getY() * coords.getY();
    double planetAbsYZ = sqrt(pow(coords.getX(), 2) + pow(coords.getY(), 2) + pow(coords.getZ(), 2));
    if (planetAbsXY * planetAbsYZ != 0)
        rotAngleYZ = coords.getZ() > 0 ? acos(scalarYZ / (planetAbsXY * planetAbsYZ))*(180.0 / M_PI) : -acos(scalarYZ / (planetAbsXY * planetAbsYZ))*(180.0 / M_PI);
    else
        rotAngleYZ = 0;
}

//******************************************************************************
//! Calculate sphere and texture coordinates
/*!
*	\param amount of latitudes the sphere has.
*	\param amount of longitudes the sphere has.
*	\return none.
*/

void PlanetEntity::calcSphere(int lats, int longs)
{
    sphereVert.clear();
    double texY1 = 0.0f / double(lats);
    for (int i = 0; i <= lats; ++i)
    {
        double texY0 = texY1;
        texY1 = double(i) / double(lats);
        double lat0 = M_PI * (-0.5 + (double)(i - 1) / lats);
        double zr0 = cos(lat0);

        double lat1 = M_PI * (-0.5 + (double)i / lats);
        double zr1 = cos(lat1);

        for (int j = 0; j <= longs; j++)
        {
            double texX = double(j) / double(longs) + 0.5f;
            double lng = 2 * M_PI * (double)(j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);

            QVector3D v0 = QVector3D(sphereRadius * x * zr0, sphereRadius * y * zr0, sphereRadius * sin(lat0));
            QVector3D v1 = QVector3D(sphereRadius * x * zr1, sphereRadius * y * zr1, sphereRadius * sin(lat1));

            sphereVert << v0 << v1;

            sphereTexCoord << QVector2D(texX, texY0) << QVector2D(texX, texY1);

        }

    }

    spherePositionVBO.bind();
    spherePositionVBO.allocate(sphereVert.constData(), sphereVert.size() * sizeof(QVector3D));
    spherePositionVBO.release();

    sphereTexCoordVBO.bind();
    sphereTexCoordVBO.allocate(sphereTexCoord.constData(), sphereTexCoord.size() * sizeof(QVector2D));
    sphereTexCoordVBO.release();

    sphereNormalVBO.bind();
    sphereNormalVBO.allocate(sphereVert.constData(), sphereVert.size() * sizeof(QVector3D));
    sphereNormalVBO.release();
}

//******************************************************************************
//! Calculate the orbit coordinates
/*!
*	\param amount of line segments the orbit contains of.
*	\return none.
*/

void PlanetEntity::calcEllipse(int num_segments)
{
    ellipseVert.clear();

    double theta = 2 * M_PI / double(num_segments);
    double c = cos(theta);
    double s = sin(theta);
    double t;

    double x = 1;
    double y = 0;

    for (int i = 0; i < num_segments; ++i)
    {
        ellipseVert << QVector3D(x * orbitRadiusX, y * orbitRadiusY, 0);
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }

    ellipsePositionVBO.bind();
    ellipsePositionVBO.allocate(ellipseVert.constData(), ellipseVert.size() * sizeof(QVector3D));
    ellipsePositionVBO.release();
}
