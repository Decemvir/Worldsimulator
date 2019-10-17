//*************************************************************************
/** \file
*  \brief Contains the implementation of class LowDev_LFEntity.
*/

#include "lowDevLFEntity.h"
#include <random>

static std::random_device rd;
static std::mt19937_64 mt(rd());
static std::uniform_int_distribution<unsigned int> dist(0);

//******************************************************************************
//! Constructor of class LowDev_LFEntity
/*!
*	\param parent QT parent pointer.
*	\param name of the life form.
*	\param name of the god that the life form believes in.
*	\param father of this life form.
*	\param mother of this life form.
*	\return none.
*/

LowDev_LFEntity::LowDev_LFEntity(QObject *parent,
                                 const char* name,
                                 const char* god,
                                 LifeFormEntity* father,
                                 LifeFormEntity* mother) : LifeFormEntity(parent, name, god, father, mother), Entity(parent)
{
    lfeColor = QVector3D(0, 1, 0);
}

//******************************************************************************
//! Copy constructor of class LowDev_LFEntity
/*!
*	\param life form to copy from.
*	\return none.
*/

LowDev_LFEntity::LowDev_LFEntity(LifeFormEntity& copy) : LifeFormEntity(copy), Entity(copy.parent())
{
}

//******************************************************************************
//! Copy constructor of class LowDev_LFEntity
/*!
*	\param life form to copy from.
*	\return none.
*/

LowDev_LFEntity::LowDev_LFEntity(LowDev_LFEntity& copy) : LifeFormEntity(copy), Entity(copy.parent())
{
    *this = copy;
}

//******************************************************************************
//! Deconstructor of class HighDev_LFEntity

LowDev_LFEntity::~LowDev_LFEntity()
{
}

//******************************************************************************
//! Overload of the operator =
/*!
*	\param life form to copy from.
*	\return reference of this.
*/

LowDev_LFEntity& LowDev_LFEntity::operator=(LowDev_LFEntity& copy)
{
    *static_cast<LifeFormEntity*>(this) = copy;
    return *this;
}

//******************************************************************************
//! Sets the visibility for the life form
/*!
*	\param v visibility to be set
*	\return none.
*/

void LowDev_LFEntity::setVisibility(bool v)
{
    LifeFormEntity::setVisibility(v);
}

//******************************************************************************
//! Returns the visibility of the life form
/*!
*	\param none.
*	\return current visibility.
*/

bool LowDev_LFEntity::isVisible()
{
    return LifeFormEntity::isVisible();
}

//******************************************************************************
//! Initialises the life form (method runs in current OpenGL context)
/*!
*	\param p shader program to be set.
*	\return none.
*/

void LowDev_LFEntity::init(QOpenGLShaderProgram * p)
{
    LifeFormEntity::init(p);
}

//******************************************************************************
//! Draw life form (method runs in current OpenGL context)
/*!
*	\param none.
*	\return none.
*/

void LowDev_LFEntity::draw()
{
    LifeFormEntity::draw();
}

//******************************************************************************
//! Randomly chooses how to solve the problem and adds an associated job to the job queue
/*!
*	\param life form that receives answer (Chain Of Responsibilities).
*	\return answer.
*/

bool LowDev_LFEntity::solveProblem(LifeFormEntity* lfThatReceives)
{
    qDebug() << "[LowDev_LFEntity::solveProblem]" << lfName << "decides which method is to choose to solve a problem.";

    bool answer = false;

    if (!lfThatReceives)
        lfThatReceives = this;

    switch (dist(mt)%4)
    {
    case 0:
        answer = LowDev_LF::guessSolution();
        ourJobHandler->addJob(this, new LFAnswerJob(this, lfThatReceives, answer, 2));
        break;
    case 1:
        answer = true;
        LowDev_LF::knowSolution();
        ourJobHandler->addJob(this, new LFAnswerJob(this, lfThatReceives, answer, 2));
        break;
    case 2:
        answer = LowDev_LF::askKnownLF();
        askKnownLFE(lfThatReceives);
        break;
    case 3:
        answer = false;
        LowDev_LF::ignoreProblem();
        break;
    }
    return answer;
}

//******************************************************************************
//! Returns development level of the life form
/*!
*	\param none.
*	\return development level.
*/

int LowDev_LFEntity::getDevLvl()
{
    return LowDev_LF::Dev_Level;
}

//******************************************************************************
//! Returns solution to a given problem by knowing the solution
/*!
*	\param none.
*	\return answer.
*/

void LowDev_LFEntity::knowSolution()
{
    LowDev_LF::knowSolution();
}

//******************************************************************************
//! Ignores the problem, just a message
/*!
*	\param none.
*	\return none.
*/

void LowDev_LFEntity::ignoreProblem()
{
    LowDev_LF::ignoreProblem();
}

//******************************************************************************
//! Returns solution to a given problem by guessing
/*!
*	\param none.
*	\return answer.
*/

bool LowDev_LFEntity::guessSolution()
{
    return LowDev_LF::guessSolution();
}
