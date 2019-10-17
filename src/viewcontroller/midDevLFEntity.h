//*************************************************************************
/** \file
*  \brief Contains the declaration of class MidDev_LFEntity.
*/

#pragma once

#include "lowDevLFEntity.h"
#include "../model/god/midDevLF.h"

//*************************************************************************
/*!	\class MidDev_LFEntity
*	\ingroup Adapter
*	\brief Member of pattern <b>Adapter</b> as <b>Adapter</b> and <b>Target</b>.
*		   Member of pattern <b>Adapter</b> as <b>Adaptee</b>.
*          Member of pattern <b>Command</b> as <b>Client</b> and <b>Receiver</b>.
*	       Redefines and adds to the interface functionality inherited from the classes LowDev_LFEntity and MidDev_LF.
*/

class MidDev_LFEntity : public LowDev_LFEntity, private MidDev_LF
{
    Q_OBJECT

    public:
      MidDev_LFEntity(QObject *parent, const char* name, const char* god, LifeFormEntity* father = nullptr, LifeFormEntity* mother = nullptr);
      MidDev_LFEntity(LifeFormEntity& copy);
      MidDev_LFEntity(MidDev_LFEntity& copy);
      ~MidDev_LFEntity();
      MidDev_LFEntity& operator= (MidDev_LFEntity& copy);

      virtual void setVisibility(bool v);
      virtual bool isVisible();
      virtual void init(QOpenGLShaderProgram *p);
      virtual void draw();
      virtual bool solveProblem(LifeFormEntity * lfThatReceives = nullptr);
      virtual int  getDevLvl();
      bool watchNature();
      bool readBooks();
};
