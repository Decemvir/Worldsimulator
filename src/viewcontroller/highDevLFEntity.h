//*************************************************************************
/** \file
*  \brief Contains the declaration of class HighDev_LFEntity.
*/

#pragma once

#include "midDevLFEntity.h"
#include "../model/god/highDevLF.h"

//*************************************************************************
/*!	\class HighDev_LFEntity
*	\ingroup Adapter
*	\brief Member of pattern <b>Adapter</b> as <b>Adapter</b> and <b>Target</b>.
*		   Member of pattern <b>Adapter</b> as <b>Adaptee</b>.
*          Member of pattern <b>Command</b> as <b>Client</b> and <b>Receiver</b>.
*	       Redefines and adds to the interface functionality inherited from the classes MidDev_LFEntity and HighDev_LF.
*/

class HighDev_LFEntity : public MidDev_LFEntity, private HighDev_LF
{
    Q_OBJECT

    public:
      HighDev_LFEntity(QObject *parent, const char* name, const char* god, LifeFormEntity* father = nullptr, LifeFormEntity* mother = nullptr);
      HighDev_LFEntity(LifeFormEntity& copy);
      HighDev_LFEntity(HighDev_LFEntity& copy);
      ~HighDev_LFEntity();
      HighDev_LFEntity& operator= (HighDev_LFEntity& copy);

      virtual void setVisibility(bool v);
      virtual bool isVisible();
      virtual void init(QOpenGLShaderProgram *p);
      virtual void draw();
      virtual bool solveProblem(LifeFormEntity* lfThatReceives = nullptr);
      virtual int  getDevLvl();
      bool         thinkNewMeme();
	
};
