//*************************************************************************
/** \file
*  \brief Contains the implementation of class HighDev_LFEntity.
*/

#include "highDevLFEntity.h"
#include <random>

static std::random_device rd;
static std::mt19937_64 mt(rd());
static std::uniform_int_distribution<unsigned int> dist(0);

//******************************************************************************
//! Constructor of class HighDev_LFEntity
/*!
*	\param parent QT parent pointer.
*	\param name of the life form.
*	\param name of the god that the life form believes in.
*	\param father of this life form.
*	\param mother of this life form.
*	\return none.
*/

HighDev_LFEntity::HighDev_LFEntity(QObject *parent, const char* name, const char* god, LifeFormEntity* father, LifeFormEntity* mother) : MidDev_LFEntity(parent, name, god, father, mother), LifeFormEntity(parent, name, god, father, mother), Entity(parent)
{
    lfeColor = QVector3D(1, 0, 0);
}

//******************************************************************************
//! Copy constructor of class HighDev_LFEntity
/*!
*	\param life form to copy from.
*	\return none.
*/

HighDev_LFEntity::HighDev_LFEntity(LifeFormEntity& copy) : LifeFormEntity(copy), MidDev_LFEntity(copy), Entity(copy.parent())
{
}

//******************************************************************************
//! Copy constructor of class HighDev_LFEntity
/*!
*	\param life form to copy from.
*	\return none.
*/

HighDev_LFEntity::HighDev_LFEntity(HighDev_LFEntity& copy) : LifeFormEntity(copy), MidDev_LFEntity(copy), Entity(copy.parent())
{
    *this = copy;
}

//******************************************************************************
//! Deconstructor of class HighDev_LFEntity

HighDev_LFEntity::~HighDev_LFEntity()
{
}

//******************************************************************************
//! Overload of the operator =
/*!
*	\param life form to copy from.
*	\return reference of this.
*/

HighDev_LFEntity& HighDev_LFEntity::operator=(HighDev_LFEntity& copy)
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

void HighDev_LFEntity::setVisibility(bool v)
{
    LifeFormEntity::setVisibility(v);
}

//******************************************************************************
//! Returns the visibility of the life form
/*!
*	\param none.
*	\return current visibility.
*/

bool HighDev_LFEntity::isVisible()
{
    return LifeFormEntity::isVisible();
}

//******************************************************************************
//! Initialises the life form (method runs in current OpenGL context)
/*!
*	\param p shader program to be set.
*	\return none.
*/

void HighDev_LFEntity::init(QOpenGLShaderProgram * p)
{
    MidDev_LFEntity::init(p);
}

//******************************************************************************
//! Draw life form (method runs in current OpenGL context)
/*!
*	\param none.
*	\return none.
*/

void HighDev_LFEntity::draw()
{
    MidDev_LFEntity::draw();
}

//******************************************************************************
//! Randomly chooses how to solve the problem and adds an associated job to the job queue
/*!
*	\param life form that receives answer (Chain Of Responsibilities).
*	\return answer.
*/

bool HighDev_LFEntity::solveProblem(LifeFormEntity* lfThatReceives)
{
    qDebug() << "[HighDev_LFEntity::solveProblem]" << lfName << "decides which method is to choose to solve a problem.";

    bool answer = false;

    if (!lfThatReceives)
        lfThatReceives = this;

    switch (dist(mt) % 7)
    {
    case 0:
        answer = HighDev_LF::guessSolution();
        ourJobHandler->addJob(this, new LFAnswerJob(this, lfThatReceives, answer, 2));
        break;
    case 1:
        answer = true;
        HighDev_LF::knowSolution();
        ourJobHandler->addJob(this, new LFAnswerJob(this, lfThatReceives, answer, 2));
        break;
    case 2:
        answer = HighDev_LF::askKnownLF();
        askKnownLFE();
        break;
    case 3:
        answer = false;
        HighDev_LF::ignoreProblem();
        break;
    case 4:
        answer = HighDev_LF::readBooks();
        ourJobHandler->addJob(this, new LFAnswerJob(this, lfThatReceives, answer, 2));
        break;
    case 5:
        answer = HighDev_LF::watchNature();
        ourJobHandler->addJob(this, new LFAnswerJob(this, lfThatReceives, answer, 2));
        break;
    case 6:
        answer = HighDev_LF::thinkNewMeme();
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

int HighDev_LFEntity::getDevLvl()
{
    return HighDev_LF::Dev_Level;
}

//******************************************************************************
//! Returns solution to a given problem by thinking of a new meme
/*!
*	\param none.
*	\return answer.
*/

bool HighDev_LFEntity::thinkNewMeme()
{
    return HighDev_LF::thinkNewMeme();
}
