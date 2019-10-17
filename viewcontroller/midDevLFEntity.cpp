//*************************************************************************
/** \file
*  \brief Contains the implementation of class MidDev_LFEntity.
*/

#include "midDevLFEntity.h"
#include <random>

static std::random_device rd;
static std::mt19937_64 mt(rd());
static std::uniform_int_distribution<unsigned int> dist(0);

//******************************************************************************
//! Constructor of class MidDev_LFEntity
/*!
*	\param parent QT parent pointer.
*	\param name of the life form.
*	\param name of the god that the life form believes in.
*	\param father of this life form.
*	\param mother of this life form.
*	\return none.
*/

MidDev_LFEntity::MidDev_LFEntity(QObject *parent, const char* name, const char* god, LifeFormEntity* father, LifeFormEntity* mother) : LowDev_LFEntity(parent, name, god, father, mother), LifeFormEntity(parent, name, god, father, mother), Entity(parent)
{
    lfeColor = QVector3D(1, 1, 0);
}

//******************************************************************************
//! Copy constructor of class MidDev_LFEntity
/*!
*	\param life form to copy from.
*	\return none.
*/

MidDev_LFEntity::MidDev_LFEntity(LifeFormEntity& copy) : LifeFormEntity(copy), LowDev_LFEntity(copy), Entity(copy.parent())
{
}

//******************************************************************************
//! Copy constructor of class MidDev_LFEntity
/*!
*	\param life form to copy from.
*	\return none.
*/

MidDev_LFEntity::MidDev_LFEntity(MidDev_LFEntity& copy) : LifeFormEntity(copy), LowDev_LFEntity(copy), Entity(copy.parent())
{
    *this = copy;
}

//******************************************************************************
//! Deconstructor of class HighDev_LFEntity

MidDev_LFEntity::~MidDev_LFEntity()
{
}

//******************************************************************************
//! Overload of the operator =
/*!
*	\param life form to copy from.
*	\return reference of this.
*/

MidDev_LFEntity& MidDev_LFEntity::operator=(MidDev_LFEntity& copy)
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

void MidDev_LFEntity::setVisibility(bool v)
{
    LifeFormEntity::setVisibility(v);
}

//******************************************************************************
//! Returns the visibility of the life form
/*!
*	\param none.
*	\return current visibility.
*/

bool MidDev_LFEntity::isVisible()
{
    return LifeFormEntity::isVisible();
}

//******************************************************************************
//! Initialises the life form (method runs in current OpenGL context)
/*!
*	\param p shader program to be set.
*	\return none.
*/

void MidDev_LFEntity::init(QOpenGLShaderProgram * p)
{
    LowDev_LFEntity::init(p);
}

//******************************************************************************
//! Draw life form (method runs in current OpenGL context)
/*!
*	\param none.
*	\return none.
*/

void MidDev_LFEntity::draw()
{
    LowDev_LFEntity::draw();
}

//******************************************************************************
//! Randomly chooses how to solve the problem and adds an associated job to the job queue
/*!
*	\param life form that receives answer (Chain Of Responsibilities).
*	\return answer.
*/

bool MidDev_LFEntity::solveProblem(LifeFormEntity* lfThatReceives)
{
    qDebug()<< "[MidDev_LFEntity::solveProblem]" << lfName << "decides which method is to choose to solve a problem.";

    bool answer = false;

    if (!lfThatReceives)
        lfThatReceives = this;

    switch (dist(mt) % 6)
    {
    case 0:
        answer = MidDev_LF::guessSolution();
        ourJobHandler->addJob(this, new LFAnswerJob(this, lfThatReceives, answer, 2));
        break;
    case 1:
        answer = true;
        MidDev_LF::knowSolution();
        ourJobHandler->addJob(this, new LFAnswerJob(this, lfThatReceives, answer, 2));
        break;
    case 2:
        answer = MidDev_LF::askKnownLF();
        askKnownLFE(lfThatReceives);
        break;
    case 3:
        answer = false;
        MidDev_LF::ignoreProblem();
        break;
    case 4:
        answer = MidDev_LF::readBooks();
        ourJobHandler->addJob(this, new LFAnswerJob(this, lfThatReceives, answer, 2));
        break;
    case 5:
        answer = MidDev_LF::watchNature();
        ourJobHandler->addJob(this, new LFAnswerJob(this, lfThatReceives, answer, 2));
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

int MidDev_LFEntity::getDevLvl()
{
    return MidDev_LF::Dev_Level;
}

//******************************************************************************
//! Returns solution to a given problem by watching nature
/*!
*	\param none.
*	\return answer.
*/

bool MidDev_LFEntity::watchNature()
{
    return MidDev_LF::watchNature();
}

//******************************************************************************
//! Returns solution to a given problem by reading books
/*!
*	\param none.
*	\return answer.
*/

bool MidDev_LFEntity::readBooks()
{
    return MidDev_LF::readBooks();
}

