//*************************************************************************
/** \file
*  \brief Contains the declaration of class SimulationWidget.
*/

#pragma once

#include "viewcontroller/simwidgetdatamodel.h"
#include "viewcontroller/simwidgetcontroller.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QVector3D>

//*************************************************************************
/*!	\class SimulationWidget
*	\brief Represents the View of the Model-View-Controller
*		   Sets the widgets OpenGL context + shader up and configurates it.
*		   Defines the basic view of the scene.
*		   Directly inherits from QOpenGLFunctions and passes the OpenGL events to the model.
*/

class SimulationWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

    public:
      SimulationWidget(QWidget *parent);
      ~SimulationWidget();
      QVector<QVector3D> getCameraPos();
      double getFOV();
      double getAspectRatio();
      double getNearClipPlanePos();
      double getFarClipPlanePos();
      void setCameraPos(QVector3D eyePos, QVector3D centerPos, QVector3D upPos);
      void setFOV(double f);
      void setNearClipPlanePos(double zn);
      void setFarClipPlanePos(double zf);
    protected:
      void initializeGL();
      void paintGL();
      void resizeGL(int width, int height);
    private:
      QMatrix4x4 projection;
      QMatrix4x4 view;
      QOpenGLShaderProgram *program;
      SimWidgetController *simC;
      SimWidgetDatamodel *simDM;
      QVector3D eye;
      QVector3D center;
      QVector3D up;
      double fov;
      double aspectRatio;
      double zNear;
      double zFar;
};
