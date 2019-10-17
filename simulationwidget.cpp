//*************************************************************************
/** \file
*  \brief Contains the implementation of class SimulationWidget.
*/

#include "simulationwidget.h"
#include "viewcontroller/lighthandler.h"
#include <QMouseEvent>
#include <QMatrix4x4>
#include <QVector4D>
#include <QVector>
#include <QDebug>
#include <QDir>
#include <cmath>
//#include <conio.h>

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1
#define PROGRAM_NORMAL_ATTRIBUTE 2

//******************************************************************************
//! Constructor of class SimulationWidget
/*!
*	\param parent QT parent pointer.
*	\return none.
*/

SimulationWidget::SimulationWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    this->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
    program = new QOpenGLShaderProgram(context());
    simDM = new SimWidgetDatamodel(this, parent);
    simC = new SimWidgetController(this, simDM, parent);
    fov = 45;
    aspectRatio = double(width()) / double(height() ? height() : 1);
    zNear = 0.01;
    zFar = 1000.0;
    eye = QVector3D(0, 0, 8);
    center = QVector3D(0, 0, 0);
    up = QVector3D(0, 1, 0);
    projection.setToIdentity();
    projection.perspective(fov, aspectRatio, zNear, zFar);
    view.setToIdentity();
    view.lookAt(eye, center, up);
}

//******************************************************************************
//! Deconstructor of class SimulationWidget

SimulationWidget::~SimulationWidget()
{
    delete simC;
    simC = nullptr;
    delete simDM;
    simDM = nullptr;

    program->deleteLater();

    qDebug() << "\n[SimulationWidget::~SimulationWidget]  *** THE END ***\n\n";
    //_getch();
}

//******************************************************************************
//! Returns camera position
/*!
*	\param none.
*	\return eye, center and up vector in one.
*/

QVector<QVector3D> SimulationWidget::getCameraPos()
{
    QVector<QVector3D> CameraPos;
    CameraPos.push_back(eye);
    CameraPos.push_back(center);
    CameraPos.push_back(up);
    return CameraPos;
}

//******************************************************************************
//! Returns field of view
/*!
*	\param none.
*	\return fov.
*/

double SimulationWidget::getFOV()
{
    return fov;
}

//******************************************************************************
//! Returns aspect ratio
/*!
*	\param none.
*	\return aspect ratio.
*/

double SimulationWidget::getAspectRatio()
{
    return aspectRatio;
}

//******************************************************************************
//! Returns zNear of the clipping plane
/*!
*	\param none.
*	\return zNear.
*/

double SimulationWidget::getNearClipPlanePos()
{
    return zNear;
}

//******************************************************************************
//! Returns zFar of the clipping plane
/*!
*	\param none.
*	\return zFar.
*/

double SimulationWidget::getFarClipPlanePos()
{
    return zFar;
}

//******************************************************************************
//! Sets camera position
/*!
*	\param eye.
*	\param center.
*	\param up.
*	\return none.
*/

void SimulationWidget::setCameraPos(QVector3D eyePos, QVector3D centerPos, QVector3D upPos)
{
    eye = eyePos;
    center = centerPos;
    up = upPos;
}

//******************************************************************************
//! Sets field of view
/*!
*	\param fov.
*	\return none.
*/

void SimulationWidget::setFOV(double f)
{
    fov = f;
}

//******************************************************************************
//! Sets zNear of the clipping plane
/*!
*	\param zNear.
*	\return none.
*/

void SimulationWidget::setNearClipPlanePos(double zn)
{
    zNear = zn;
}

//******************************************************************************
//! Sets zFar of the clipping plane
/*!
*	\param zFar.
*	\return none.
*/

void SimulationWidget::setFarClipPlanePos(double zf)
{
    zFar = zf;
}

//******************************************************************************
//! OpenGL initialise event
/*!
*	\param none.
*	\return none.
*/

void SimulationWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, QDir::currentPath() + "/viewcontroller/Resources/Shaders/vshader.glsl");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, QDir::currentPath() + "/viewcontroller/Resources/Shaders/fshader.glsl");
    program->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    program->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    program->bindAttributeLocation("normal", PROGRAM_NORMAL_ATTRIBUTE);
    program->link();
    program->bind();
    program->setUniformValue("projectionMatrix", projection);
    program->setUniformValue("viewMatrix", view);

    LightHandler *lh = LightHandler::Instance(parent());
    lh->initLightHandler(program);
    lh->setEyePosition(eye);

    program->release();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);
    simDM->init(program);
}

//******************************************************************************
//! OpenGL paint event
/*!
*	\param none.
*	\return none.
*/

void SimulationWidget::paintGL()
{	
    view.setToIdentity();
    view.lookAt(eye, center, up);
    program->bind();
    program->setUniformValue("viewMatrix", view);
    program->release();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    simDM->draw();
    context()->swapBuffers(context()->surface());
    makeCurrent();
}

//******************************************************************************
//! OpenGL resize event
/*!
*	\param width of the widget.
*	\param height of the widget.
*	\return none.
*/

void SimulationWidget::resizeGL(int width, int height)
{	
    glViewport(0, 0, width, height);
    aspectRatio = double(width) / double(height ? height : 1);
    projection.setToIdentity();
    projection.perspective(fov, aspectRatio, zNear, zFar);
    view.setToIdentity();
    view.lookAt(eye, center, up);

    program->bind();
    program->setUniformValue("projectionMatrix", projection);
    program->setUniformValue("viewMatrix", view);
    program->release();
}





