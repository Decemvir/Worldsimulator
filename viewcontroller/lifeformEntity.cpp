//*************************************************************************
/** \file
*  \brief Contains the implementation of class LifeFormEntity.
*/

#include "lifeformEntity.h"

static std::random_device rd;
static std::mt19937_64 mt(rd());
static std::uniform_int_distribution<unsigned int> dist(0);

//******************************************************************************
//! Constructor of class LifeFormEntity
/*!
*	\param parent QT parent pointer.
*	\param name of the life form.
*	\param name of the god that the life form believes in.
*	\param father of this life form.
*	\param mother of this life form.
*	\return none.
*/

LifeFormEntity::LifeFormEntity(QObject *parent, const char* name, const char* god, LifeFormEntity* father, LifeFormEntity* mother) :Entity(parent)
{
	lfName = QString(name);
	homePlanet = nullptr;
	homePlanetEntity = nullptr;
	believerOf = god;
	currentRelativePos = calcRandDestination();
	lfeColor = QVector3D(1, 1, 1);
	model.setToIdentity();
	lifetimeInTicks = 0;
	if (father == this || mother == this || father == mother)
	{
		lfFather = nullptr;
		lfMother = nullptr;
	}
	{
		lfFather = father;
		lfMother = mother;
	}
	if(lfFather) gen = lfFather->getGeneration()+1;
	else gen = 0;
	ourDestinyAdapter = DestinyAdapter::Instance(parent);
	ourJobHandler = LFJobHandler::Instance(parent);
	ourJobHandler->createJobQueue(this);
}

//******************************************************************************
//! Copy constructor of class LifeFormEntity
/*!
*	\param life form to copy from.
*	\return none.
*/

LifeFormEntity::LifeFormEntity(LifeFormEntity& copy) : Entity(copy.parent())
{
	ourDestinyAdapter = DestinyAdapter::Instance(copy.parent());
	ourJobHandler = LFJobHandler::Instance(copy.parent());
	ourJobHandler->createJobQueue(this);
	*this = copy;
}

//******************************************************************************
//! Deconstructor of class DestinyAdapter

LifeFormEntity::~LifeFormEntity()
{
	qDebug() << "[LifeFormEntity::~LifeFormEntity]" << lfName << "died after" << lifetimeInTicks << "ticks of lifetime.";	
	ourDestinyAdapter->removeLFE(this);
	ourJobHandler->deleteJobQueue(this);
    if (homePlanetEntity)
        homePlanetEntity->removeInhabitant(this);

	lfVAO.destroy();
	lfPositionVBO.destroy();
}

//******************************************************************************
//! Overload of the operator =
/*!
*	\param life form to copy from.
*	\return reference of this.
*/

LifeFormEntity& LifeFormEntity::operator=(LifeFormEntity& copy)
{
	if(&copy != this)
	{ 
		this->setParent(copy.parent());
		lfName = copy.getName();
		homePlanet = nullptr;
		homePlanetEntity = nullptr;
		believerOf = qstrdup(qPrintable(copy.getGodName()));
		currentRelativePos = copy.getRelativePos();
		lfeColor = copy.getLFEColor();
		model.setToIdentity();
		currentRelativePos = copy.getRelativePos();
		lifetimeInTicks = copy.getLifetimeInTicks();
		knownLFEntities = copy.getKnownLFEntities();
        for (int i = 0; i < knownLFEntities.size(); i++)
            LifeForm::addKownLF((LifeForm*)knownLFEntities[i]);

		lfFather = copy.getFather();
		lfMother = copy.getMother();
		gen = copy.getGeneration();
		ourJobHandler->copyJobQueue(this, &copy);
	}
	return *this;
}

//******************************************************************************
//! Sets the visibility for the life form
/*!
*	\param v visibility to be set
*	\return none.
*/

void LifeFormEntity::setVisibility(bool v)
{
	Entity::setVisibility(v);
}

//******************************************************************************
//! Returns the visibility of the life form
/*!
*	\param none.
*	\return current visibility.
*/

bool LifeFormEntity::isVisible()
{
	return Entity::isVisible();
}

//******************************************************************************
//! Initialises the life form (method runs in current OpenGL context)
/*!
*	\param p shader program to be set.
*	\return none.
*/

void LifeFormEntity::init(QOpenGLShaderProgram * p)
{
	program = p;
	if (program)
	{
		lfPositionVBO.create();
		lfPositionVBO.setUsagePattern(QOpenGLBuffer::DynamicDraw);

		lfVert << getAbsolutPosition();

		lfPositionVBO.bind();
		lfPositionVBO.allocate(lfVert.constData(), lfVert.size() * sizeof(QVector3D));
		lfPositionVBO.release();

		lfVAO.create();
		lfVAO.bind();
		lfPositionVBO.bind();
		program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
		program->setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3);
		lfPositionVBO.release();
		lfVAO.release();
	}
}

//******************************************************************************
//! Draw life form (method runs in current OpenGL context)
/*!
*	\param none.
*	\return none.
*/

void LifeFormEntity::draw()
{
	lfVert.clear();
	lfVert << getAbsolutPosition();

	lfPositionVBO.bind();
	lfPositionVBO.allocate(lfVert.constData(), lfVert.size() * sizeof(QVector3D));
	lfPositionVBO.release();

	if (program && homePlanetEntity)
	{
		program->bind();
		model.setToIdentity();
		program->setUniformValue("normalEnabled", false);
		program->setUniformValue("textureEnabled", false);
		program->setUniformValue("modelMatrix", model);
		program->setUniformValue("color", lfeColor);
		lfVAO.bind();
//		glDrawArrays(GL_POINTS, 0, lfVert.size());
		lfVAO.release();
		program->release();
	}
}

//******************************************************************************
//! Calculates the next step for the life form by working on the specific job queue
//! Adds filler job if there is no job in the queue (Idle or Move)
/*!
*	\param none.
*	\return none.
*/

void LifeFormEntity::calcNextStep()
{
	if (homePlanetEntity)
	{
		++lifetimeInTicks;
		if (ourJobHandler->workOnTopJob(this));
		else
		{
			if (dist(mt) % 2)
			{
				qDebug() << "[LifeFormEntity::calcNextStep]" << lfName << "is wandering around.";
				ourJobHandler->addJob(this, new LFMoveJob(this, calcRandDestination(), 0));
			}
			else
			{
				unsigned int rtickCount = dist(mt) % 5000;
				qDebug() << "[LifeFormEntity::calcNextStep]" << lfName << "is sleeping for" << rtickCount << "ticks.";
				ourJobHandler->addJob(this, new LFIdleJob(this, rtickCount, 0));
			}
		}
	}
}

//******************************************************************************
//! Adds AnswerJob to the job queue of the life form
/*!
*	\param life form that receives answer (Chain Of Responsibilities).
*	\return answer.
*/

bool LifeFormEntity::solveProblem(LifeFormEntity* lfThatReceives)
{
	bool answer = LifeForm::solveProblem();
	if (lfThatReceives) ourJobHandler->addJob(this, new LFAnswerJob(this, lfThatReceives, answer, 2));
	else ourJobHandler->addJob(this, new LFAnswerJob(this, this, answer, 2));
	return answer;
}

//******************************************************************************
//! Returns development level of the life form
/*!
*	\param none.
*	\return development level.
*/

int LifeFormEntity::getDevLvl()
{
	return LifeForm::Dev_Level;
}

//******************************************************************************
//! Adds lf to the list of known life forms
/*!
*	\param lf to be known.
*	\return none.
*/

void LifeFormEntity::addKnownLFE(LifeFormEntity* lf)
{
	if (lf && this != lf && isOnSamePlanetAs(lf) && !knows(lf))
	{
		qDebug() << "[LifeFormEntity::addKnownLFE]" << lfName << "got to know" << lf->getName();
		knownLFEntities.push_back(lf);
		LifeForm::addKownLF((LifeForm*)lf);
	}
}

//******************************************************************************
//! Removes lf from the list of known life forms
/*!
*	\param lf to be removed.
*	\return none.
*/

void LifeFormEntity::forgetAboutLFE(LifeFormEntity* lf)
{
	if (lf && this != lf && knows(lf))
	{
		qDebug() << "[LifeFormEntity::forgetAboutLFE]" << lfName << "forgot about" << lf->getName();
		if (lf == lfFather) lfFather = nullptr;
		else if (lf == lfMother) lfMother = nullptr;
		knownLFEntities.removeOne(lf);
		for (vector<LifeForm*>::iterator it = knownLF.begin(); it != knownLF.end(); ++it)
		{
			if ((*it) == (LifeForm*)lf)
			{
				it = knownLF.erase(it);
				break;
			}
		}
		knownLF.shrink_to_fit();
		knownLFEntities.squeeze();
	}
}

//******************************************************************************
//! Adds AskJob to the job queue of the life form if a more developed life form is known
/*!
*	\param life form that receives answer (Chain Of Responsibilities).
*	\return none.
*/

void LifeFormEntity::askKnownLFE(LifeFormEntity* lfThatReceives)
{
	QVector<LifeFormEntity*> vec_higher_LF;
	unsigned int maxNum = 0;

	for (QVector<LifeFormEntity*>::iterator it = knownLFEntities.begin(); it != knownLFEntities.end(); ++it)
	{
		if (*it && (*it)->getHomePlanetEntity() && this->getDevLvl() < (*it)->getDevLvl())
		{
			vec_higher_LF.push_back(*it);
			maxNum++;
		}
	}

	if (maxNum == 0)
	{
		qDebug() << "[LifeFormEntity::askKnownLF]" << lfName << "tried to think of a friend that it could meet to help him with a problem, but without success.";
		return;
	}

	unsigned int random = dist(mt) % maxNum;

	QVector <LifeFormEntity*>::iterator selIt = vec_higher_LF.begin();
	for (unsigned int i = 0; i < random; i++) selIt += 1;
	LifeFormEntity* LFEtoAsk = *selIt;
	if (LFEtoAsk && LFEtoAsk->getHomePlanetEntity())
	{
		if (isOnSamePlanetAs(LFEtoAsk))
		{
			ourJobHandler->addJob(this, new LFAskJob(this, LFEtoAsk, lfThatReceives, 2));
            if(this == lfThatReceives)
                qDebug() << "[LifeFormEntity::askKnownLF]" << lfName << "will ask" << LFEtoAsk->getName() << "to get help with a problem.";
            else
                qDebug() << "[LifeFormEntity::askKnownLF]" << lfName << "will ask" << LFEtoAsk->getName() << "to help"<< lfThatReceives->getName() <<"with its problem.";
		}
        else
            qDebug() << "[LifeFormEntity::askKnownLF]" << lfName << "would ask" << LFEtoAsk->getName() << "but can not reach him.";
	}
    else
        qDebug() << "[LifeFormEntity::askKnownLF]" << lfName << "tried to think of a friend that it could meet to help him with a problem, but without success.";
}

//******************************************************************************
//! Adds MeetJob to the job queue of the life form 
/*!
*	\param life form to meet.
*	\return none.
*/

void LifeFormEntity::meetWith(LifeFormEntity* lf)
{
	if (lf && this != lf && isOnSamePlanetAs(lf))
	{
		qDebug() << "[LifeFormEntity::meetWith]" << lfName << "will meet" << lf->getName();
		ourJobHandler->addJob(this, new LFMeetJob(this, lf, 1));
	}
}

//******************************************************************************
//! Adds MateJob to the job queue of the life form 
/*!
*	\param life form to mate with.
*	\return none.
*/

void LifeFormEntity::mateWith(LifeFormEntity* lf)
{
	if (lf && this != lf && isOnSamePlanetAs(lf))
	{
		if (lf == lfFather || lf == lfMother)
		{
			qDebug() << "[LifeFormEntity::mateWith]" << lfName << "will not mate with one of its parents!";
			return;
		}

		qDebug() << "[LifeFormEntity::mateWith]" << lfName << "has the urge to mate with" << lf->getName();

		ourJobHandler->addJob(this, new LFMateJob(this, lf, 2));

	}
}

//******************************************************************************
//! Outputs console message if the life form receives an answer from lf
/*!
*	\param life form to receive from.
*	\param answer.
*	\return none.
*/

void LifeFormEntity::receiveAnswer(LifeFormEntity* lf, bool answer)
{
	if (lf)
	{
		if (lf != this) qDebug() << "[LifeFormEntity::receiveAnswer]" << lfName << "received from" << lf->getName() << answer << "as an answer.";
		else qDebug() << "[LifeFormEntity::receiveAnswer]" << lfName << "came to the conclusion that the answer is" << answer << ".";
	}
}

//******************************************************************************
//! Calculates the next movement step and checks if the life form has
//! a certain distance to the destination 
/*!
*	\param destination.
*	\return true if dest is reached.
*/

bool LifeFormEntity::moveTowardsDest(CartesianCoordAdapter dest)
{
	double eps = 0.001f;
	int cRPHor = (int)(currentRelativePos.getHorDeg()*(1 / eps));
	int cRPVer = (int)(currentRelativePos.getVerDeg()*(1 / eps));
	int cDHor = (int)(dest.getHorDeg()*(1 / eps));
	int cDVer = (int)(dest.getVerDeg()*(1 / eps));

	double intervalPer = 5.0f;
	int cDHorP = abs((int)(((double)cDHor / 100.0f)*intervalPer));
	int cDVerP = abs((int)(((double)cDVer / 100.0f)*intervalPer));

	if (!((cDHor - cDHorP <= cRPHor && cRPHor <= cDHor + cDHorP) && (cDVer - cDVerP <= cRPVer && cRPVer <= cDVer + cDVerP)))
	{
		if (cRPHor < cDHor) currentRelativePos.setHorDeg(currentRelativePos.getHorDeg() + eps);
		else if (cRPHor > cDHor) currentRelativePos.setHorDeg(currentRelativePos.getHorDeg() - eps);
		if (cRPVer < cDVer) currentRelativePos.setVerDeg(currentRelativePos.getVerDeg() + eps);
		else if (cRPVer > cDVer) currentRelativePos.setVerDeg(currentRelativePos.getVerDeg() - eps);
		return false;
	}
	qDebug() << "[LifeFormEntity::moveTowardsDest]" << lfName << "reached its destination.";
	return true;
}

//******************************************************************************
//! Checks if lf is on the same planet as this
/*!
*	\param life form to test for.
*	\return true if they are on the same planet.
*/

bool LifeFormEntity::isOnSamePlanetAs(LifeFormEntity* lf)
{
	return lf && homePlanetEntity && lf->getHomePlanetEntity() && homePlanetEntity == lf->getHomePlanetEntity();
}

//******************************************************************************
//! Checks if lf is parent of this
/*!
*	\param life form to test for.
*	\return true if lf is parent of this.
*/

bool LifeFormEntity::isParentOf(LifeFormEntity* lf)
{
	return lf && this != lf && (this == lf->getFather() || this == lf->getMother());
}

//******************************************************************************
//! Checks if lf is known by this
/*!
*	\param lf to test for.
*	\return true if lf is known by this.
*/

bool LifeFormEntity::knows(LifeFormEntity* lf)
{
	return knownLFEntities.contains(lf);
}

//******************************************************************************
//! Returns name of life form
/*!
*	\param none.
*	\return name.
*/

QString LifeFormEntity::getName()
{
	return lfName;
}

//******************************************************************************
//! Returns name of god that the life form believies in
/*!
*	\param none.
*	\return name of god.
*/

QString LifeFormEntity::getGodName()
{
	return QString(believerOf);
}

//******************************************************************************
//! Returns lifetime in ticks of life form
/*!
*	\param none.
*	\return tick count.
*/

unsigned long long LifeFormEntity::getLifetimeInTicks()
{
	return lifetimeInTicks;
}

//******************************************************************************
//! Returns absolute position of the life form
/*!
*	\param none.
*	\return three dimensional vector.
*/

QVector3D LifeFormEntity::getAbsolutPosition()
{
	if (homePlanetEntity)
	{
		QMatrix4x4 rot;
		rot.setToIdentity();
		rot.rotate(homePlanetEntity->getRotAngle(), 0, 1, 0);
		QVector3D ppos = homePlanetEntity->getCurrentPosition();
		QVector3D rppos = QVector3D(currentRelativePos.getX(), currentRelativePos.getY(), currentRelativePos.getZ());
		rppos = rot * rppos;
		return ppos + rppos;
	}
	return QVector3D();
}

//******************************************************************************
//! Returns position relative to the planet the life form lives on
/*!
*	\param none.
*	\return three dimensional vector.
*/

CartesianCoordAdapter LifeFormEntity::getRelativePos()
{
	return currentRelativePos;
}

//******************************************************************************
//! Returns absolut position of the planet the life form lives on
/*!
*	\param none.
*	\return three dimensional vector.
*/

QVector3D LifeFormEntity::getHomePlanetPos()
{
    if (homePlanetEntity)
        return homePlanetEntity->getCurrentPosition();
    else
        return QVector3D();
}

//******************************************************************************
//! Returns address of the life forms home planet
/*!
*	\param none.
*	\return home planet entity.
*/

PlanetEntity* LifeFormEntity::getHomePlanetEntity()
{
	return homePlanetEntity;
}

//******************************************************************************
//! Returns adress of the life forms father
/*!
*	\param none.
*	\return father.
*/

LifeFormEntity* LifeFormEntity::getFather()
{
	return lfFather;
}

//******************************************************************************
//! Returns address of the life forms mother
/*!
*	\param none.
*	\return mother.
*/

LifeFormEntity* LifeFormEntity::getMother()
{
	return lfMother;
}

//******************************************************************************
//! Returns vector of all known life forms
/*!
*	\param none.
*	\return vector of known life forms.
*/

QVector<LifeFormEntity*> LifeFormEntity::getKnownLFEntities()
{
	return knownLFEntities;
}

//******************************************************************************
//! Returns generation of the life form
/*!
*	\param none.
*	\return generation.
*/

unsigned long long LifeFormEntity::getGeneration()
{
	return gen;
}

//******************************************************************************
//! Returns color of the life form
/*!
*	\param none.
*	\return rgb vector.
*/

QVector3D LifeFormEntity::getLFEColor()
{
	return lfeColor;
}

//******************************************************************************
//! Sets color of the life form
/*!
*	\param rgb vector.
*	\return none.
*/

void LifeFormEntity::setLFEColor(QVector3D c)
{
	lfeColor = c;
}

//******************************************************************************
//! Sets home planet and let's the life form begin it's life
/*!
*	\param planet to settle on.
*	\param destination on the planet where to start life.
*	\return none.
*/

void LifeFormEntity::inhabitPlanet(PlanetEntity* p, CartesianCoordAdapter* dest)
{
	if (p && !homePlanetEntity)
	{
		homePlanetEntity = p;
		homePlanet = (Planet*)p;
		if (dest)
		{
			currentRelativePos.setHorDeg(dest->getHorDeg());
			currentRelativePos.setVerDeg(dest->getVerDeg());
		}
		p->addInhabitant(this);
		resetPlanetRadius();
		ourDestinyAdapter->addLFE(this);
	}
}

//******************************************************************************
//! Sets the relative position radius (polar) to the radius of the currently set home planet
//! Used if radius of the planet could have changed
/*!
*	\param none.
*	\return none.
*/

void LifeFormEntity::resetPlanetRadius()
{
    if (homePlanetEntity)
        currentRelativePos.setRad(homePlanetEntity->getPlanetRadius());
}

//******************************************************************************
//! Calculates random destination on the home planet
/*!
*	\param none.
*	\return CartesianCoordAdapter.
*/

CartesianCoordAdapter LifeFormEntity::calcRandDestination()
{
	double randHorDeg = fmod(dist(mt), 2.0f*M_PI);
	double randVerDeg = fmod(dist(mt), 2.0f*M_PI);
	unsigned int sign = rd() % 3;
	switch (sign)
	{
	case 0:
		randHorDeg *= -1.0f;
		randVerDeg *= -1.0f;
		break;
	case 1:
		randHorDeg *= -1.0f;
		break;
	case 2:
		randVerDeg *= -1.0f;
		break;
	default:
		break;
	}

    if (homePlanetEntity)
        return CartesianCoordAdapter(randHorDeg, randVerDeg, homePlanetEntity->getPlanetRadius());
    else
        return CartesianCoordAdapter(randHorDeg, randVerDeg, 0);
}







