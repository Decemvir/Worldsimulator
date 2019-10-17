//*************************************************************************
/** \file
*  \brief Contains the declaration of class Entity.
*/
#pragma once

#include <QObject>
#include <QtMath> 
#include <QDebug>
#include <QDir>
#include <QString>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <QVector4D>
#include <QMatrix4x4>
#include "../model/god/cartesianCoordAdapter.h"
#include <iostream>
#include <memory>

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1
#define PROGRAM_NORMAL_ATTRIBUTE 2

//*************************************************************************
/*!	\class Entity
*	\ingroup CompositePattern 
*	\brief Member of pattern <b>Composite</b> as <b>Component</b>. 
*	       Defines an abstract graphical element that could be a part of a view.
*		   It gives the functionality of changing the visibility of the Entity itself and
*		   defines pure abstract functions for the standard OpenGL events and the calculation of the next step.
*/

class Entity : public QObject
{
	Q_OBJECT

public:
	Entity(QObject* parent);
	virtual ~Entity();	
	virtual void setVisibility(bool v);	
	virtual bool isVisible(); 
	virtual void init(QOpenGLShaderProgram *p) = 0; 
	virtual void draw() = 0;
	virtual void calcNextStep() = 0;
protected:
	bool visible; 
	QOpenGLShaderProgram *program;
};
