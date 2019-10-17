//*************************************************************************
/** \file
*  \brief Contains the declaration of class LowDev_LFEntity.
*/

#pragma once

#include <QObject>
#include "lifeformEntity.h"
#include "../model/god/lowDevLF.h"

//*************************************************************************
/*!	\class LowDev_LFEntity
*	\ingroup Adapter
*	\brief Member of pattern <b>Adapter</b> as <b>Adapter</b> and <b>Target</b>.
*		   Member of pattern <b>Adapter</b> as <b>Adaptee</b>.
*          Member of pattern <b>Command</b> as <b>Client</b> and <b>Receiver</b>.
*	       Redefines and adds to the interface functionality inherited from the classes LifeFormEntity and LowDev_LF.
*/

class LowDev_LFEntity : public virtual LifeFormEntity, private LowDev_LF
{
    Q_OBJECT

    public:
      LowDev_LFEntity(QObject *parent, const char* name, const char* god, LifeFormEntity* father = nullptr, LifeFormEntity* mother = nullptr);
      LowDev_LFEntity(LifeFormEntity& copy);
      LowDev_LFEntity(LowDev_LFEntity& copy);
      ~LowDev_LFEntity();
      LowDev_LFEntity& operator= (LowDev_LFEntity& copy);
      virtual void setVisibility(bool v);
      virtual bool isVisible();
      virtual void init(QOpenGLShaderProgram *p);
      virtual void draw();
      virtual bool solveProblem(LifeFormEntity * lfThatReceives = nullptr);
      virtual int  getDevLvl();
      void knowSolution();
      void ignoreProblem();
      bool guessSolution();
};
