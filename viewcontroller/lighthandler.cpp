//*************************************************************************
/** \file
*  \brief Contains the implementation of class LightHandler.
*/

#include "lighthandler.h"
#include <QDebug>

int LightHandler::activeLights = 0;
QVector<QVector4D> LightHandler::lightPositions;

//******************************************************************************
//! Returns the unique LightHandler. (Singleton)
/*!
*  \param parent QT parent pointer.
*	\return The single instance of class LightHandler.
*/

LightHandler* LightHandler::Instance(QObject *parent)
{
	static LightHandler ourLightHandler(parent);
	return &ourLightHandler;
}

//******************************************************************************
//! Initialises the light handler (method runs in current OpenGL context)
/*!
*	\param p shader program to be set.
*	\return none.
*/

void LightHandler::initLightHandler(QOpenGLShaderProgram * p)
{
	program = p;
	if (program)
	{ 
		materialShininess = 50;
		lightKoeffs = QVector4D( 0.0f, 0.1f, 5.0f, 5.0f );
		lightAtt = QVector3D( 1.0f, 0.3f, 0.1f );
		eye = QVector4D( 0, 0, 0, 1 );
		program->bind();
		program->setUniformValue("eye_position", eye);
		program->setUniformValue("material_shininess", materialShininess);
		program->setUniformValue("material_ke", lightKoeffs[0]);
		program->setUniformValue("material_ka", lightKoeffs[1]);
		program->setUniformValue("material_kd", lightKoeffs[2]);
		program->setUniformValue("material_ks", lightKoeffs[3]);
		program->setUniformValue("att_kC", lightAtt[0]);
		program->setUniformValue("att_kL", lightAtt[1]);
		program->setUniformValue("att_kQ", lightAtt[2]);
	}
}

//******************************************************************************
//! Sets the position of the eye
/*!
*	\param three dimensional vector
*	\return none.
*/

void LightHandler::setEyePosition(QVector3D eyePos)
{
	if (program)
	{
		eye = QVector4D(eyePos.x(), eyePos.y(), eyePos.z(), 1);
		program->bind();
		program->setUniformValue("eye_position", eye);
	}
}

//******************************************************************************
//! Sets the material shininess
/*!
*	\param shininess
*	\return none.
*/

void LightHandler::setMaterialShininess(unsigned int sh)
{
	if (program)
	{
		materialShininess = sh;
		program->bind();
		program->setUniformValue("material_shininess", materialShininess);
	}
}

//******************************************************************************
//! Sets the light koefficients
/*!
*	\param emmissive koefficient
*	\param ambient koefficient
*	\param specular koefficient
*	\param diffuse koefficient
*	\return none.
*/

void LightHandler::setLightKoeffs(float emmissiveK, float ambientK, float specularK, float diffuseK)
{
	if (program && emmissiveK >= 0.0f && ambientK >= 0.0f && specularK >= 0.0f && diffuseK >= 0.0f)
	{
		lightKoeffs = QVector4D(emmissiveK, ambientK, specularK, diffuseK);
		program->bind();
		program->setUniformValue("material_ke", lightKoeffs[0]);
		program->setUniformValue("material_ka", lightKoeffs[1]);	
		program->setUniformValue("material_ks", lightKoeffs[2]);
		program->setUniformValue("material_kd", lightKoeffs[3]);
	}
}

//******************************************************************************
//! Sets the light attenuation
/*!
*	\param constant attenuation
*	\param linear attenuation
*	\param quadratic attenuation
*	\return none.
*/

void LightHandler::setLightAttenuation(float constantAtt, float linearAtt, float quadraticAtt)
{
	if (program && constantAtt >= 0.0f && linearAtt >= 0.0f && quadraticAtt >= 0.0f)
	{
		lightAtt = QVector3D(constantAtt, linearAtt, quadraticAtt);
		program->bind();
		program->setUniformValue("att_kC", lightAtt[0]);
		program->setUniformValue("att_kL", lightAtt[1]);
		program->setUniformValue("att_kQ", lightAtt[2]);
	}
}

//******************************************************************************
//! Returns material shininess
/*!
*	\param none.
*	\return material shininess.
*/

unsigned int LightHandler::getMaterialShininess()
{
	return materialShininess;
}

//******************************************************************************
//! Returns koefficient vector
/*!
*	\param none.
*	\return koefficient vector.
*/

QVector4D LightHandler::getLightKoeffs()
{
	return lightKoeffs;
}

//******************************************************************************
//! Returns eye position
/*!
*	\param none.
*	\return three dimensional vector.
*/

QVector4D LightHandler::getEyePos()
{
	return eye;
}

//******************************************************************************
//! Returns attenuation vector
/*!
*	\param none.
*	\return attenuation vector.
*/

QVector3D LightHandler::getLightAttenuation()
{
	return lightAtt;
}

//******************************************************************************
//! Adds light at specific position if limit is not reached
/*!
*	\param position.
*	\return none.
*/

void LightHandler::addLightAt(QVector3D position)
{
	if (program)
	{
		if(activeLights < maxLights)
		{ 		
			program->bind();
			int currentLightIndex = activeLights;
			activeLights++;
			lightPositions[currentLightIndex] = QVector4D(position.x(), position.y(), position.z(), 1);
			program->setUniformValue("activeLightsCount", activeLights);
			program->setUniformValueArray("light_positions", lightPositions.constData(), maxLights);
		}
		else qDebug() << "\nWarning: maximal number of light sources reached!\n";
	} 
}

//******************************************************************************
//! Removes light at specific position 
/*!
*	\param position.
*	\return none.
*/

void LightHandler::removeLightAt(QVector3D position)
{
	if (program)
	{	
		for (int i = 0; i < activeLights; ++i)
		{
			if (lightPositions[i] == QVector4D(position.x(), position.y(), position.z(), 1))
			{
				program->bind();
				lightPositions[i] = lightPositions[activeLights-1];
				activeLights--;
				program->setUniformValue("activeLightsCount", activeLights);
				program->setUniformValueArray("light_positions", lightPositions.constData(), maxLights);
				break;
			}
		}
	}
}

//******************************************************************************
//! Removes all lights
/*!
*	\param none.
*	\return none.
*/

void LightHandler::removeAll()
{
	if (program)
	{
		program->bind();
		activeLights = 0;
		program->setUniformValue("activeLightsCount", activeLights);
	}
}

//******************************************************************************
//! Constructor of class LightHandler
/*!
*	\param parent QT parent pointer.
*	\return none.
*/

LightHandler::LightHandler(QObject *parent):QObject(parent)
{
	lightPositions.resize(LightHandler::maxLights);
	program = nullptr;
	materialShininess = 0;
}

//******************************************************************************
//! Deconstructor of class LightHandler

LightHandler::~LightHandler()
{

}




