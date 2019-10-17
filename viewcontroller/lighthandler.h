//*************************************************************************
/** \file
*  \brief Contains the declaration of class LightHandler.
*/

#pragma once

#include <QObject>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector4D>

//*************************************************************************
/*!	\class LightHandler
*	\ingroup FacadeTE SingletonTE
*	\brief Member of pattern <b>Singleton</b>.
*		   Member of pattern <b>Facade</b> as <b>Facade</b>.
*	       Defines a handler that simplifies the creation of light sources in the scene
*		   and gives the functionality of configuring them as prefered.
*/

class LightHandler : public QObject
{
	Q_OBJECT

public:
	static LightHandler* Instance(QObject *parent);
	static const int maxLights = 8;
	void initLightHandler(QOpenGLShaderProgram* p);
	void setEyePosition(QVector3D eyePos);
	void setMaterialShininess(unsigned int sh);
	void setLightKoeffs(float emmissiveK, float ambientK, float specularK, float diffuseK);
	void setLightAttenuation(float constantAtt, float linearAtt, float quadraticAtt);
	unsigned int getMaterialShininess();
	QVector4D getLightKoeffs();
	QVector4D getEyePos();
	QVector3D getLightAttenuation();
	void addLightAt(QVector3D position);
	void removeLightAt(QVector3D position);
	void removeAll();
protected:
	explicit LightHandler(QObject *parent);
	~LightHandler();
	static LightHandler *ourLightHandler;
	static int activeLights;
	static QVector<QVector4D> lightPositions;
	QOpenGLShaderProgram *program;
	unsigned int materialShininess;
	QVector4D lightKoeffs;
	QVector4D eye;
	QVector3D lightAtt;
};
