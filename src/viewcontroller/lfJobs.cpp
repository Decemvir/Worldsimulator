//*************************************************************************
/** \file
*  \brief Contains the implementations of classes LFJob, LFMoveJob, LFMeetJob, 
		  LFAskJob, LFAnswerJob, LFIdleJob, LFMateJob.
*/

#include "lfJobs.h"
#include "lifeformEntity.h"
#include "lowDevLFEntity.h"
#include "midDevLFEntity.h"
#include "highDevLFEntity.h"
#include "destinyAdapter.h"

static std::random_device rd;
static std::mt19937_64 mt(rd());
static std::uniform_int_distribution<unsigned int> dist(0);

unsigned long long LFJob::jobCounter = 0;

//******************************************************************************
//! Constructor of class LFJob
/*!
*	\param life form that is working on the job.
*	\param priority.
*	\return none.
*/

LFJob::LFJob(LifeFormEntity* workLF, unsigned int prio)
{
	jobPriority = prio;
	workingLF = workLF;
	++jobCounter;
}

//******************************************************************************
//! Copy constructor of class LFJob
/*!
*	\param job to copy from.
*	\return none.
*/

LFJob::LFJob(LFJob& copy)
{
	*this = copy;
	++jobCounter;
}

//******************************************************************************
//! Deconstructor of class LFJob

LFJob::~LFJob()
{
	--jobCounter;
}

//******************************************************************************
//! Returns working life form
/*!
*	\param none.
*	\return workingLF.
*/

LifeFormEntity * LFJob::getWorkingLF()
{
	return workingLF;
}

//******************************************************************************
//! Returns job priority
/*!
*	\param none.
*	\return priority.
*/

unsigned int LFJob::getPrio()
{
	return jobPriority;
}

//******************************************************************************
//! Returns number of jobs
/*!
*	\param none.
*	\return jobCounter.
*/

unsigned long long LFJob::getJobCount()
{
	return jobCounter;
}

//******************************************************************************
//! Sets working life form
/*!
*	\param life form that will be working on the job.
*	\return none.
*/

void LFJob::changeWorkingLF(LifeFormEntity* workLF)
{
	workingLF = workLF;
}

//******************************************************************************
//! Sets the job priotity
/*!
*	\param priority.
*	\return none.
*/

void LFJob::setPrio(unsigned int prio)
{
	jobPriority = prio;
}

//******************************************************************************
//! Overload of the operator ==
/*!
*	\param job to compare with.
*	\return result of priority comparison.
*/

bool LFJob::operator==(LFJob& j) { if (jobPriority == j.jobPriority) return true; else return false; }

//******************************************************************************
//! Overload of the operator !=
/*!
*	\param job to compare with.
*	\return result of priority comparison.
*/

bool LFJob::operator!=(LFJob& j) { if (!(*this == j)) return true; else return false; }

//******************************************************************************
//! Overload of the operator <
/*!
*	\param job to compare with.
*	\return result of priority comparison.
*/

bool LFJob::operator<(LFJob& j) { if (jobPriority < j.jobPriority) return true; else return false; }

//******************************************************************************
//! Overload of the operator <=
/*!
*	\param job to compare with.
*	\return result of priority comparison.
*/

bool LFJob::operator<=(LFJob& j) { if (*this < j || *this == j) return true; else return false; }

//******************************************************************************
//! Overload of the operator >
/*!
*	\param job to compare with.
*	\return result of priority comparison.
*/

bool LFJob::operator>(LFJob& j) { if (!(*this <= j)) return true; else return false; }

//******************************************************************************
//! Overload of the operator >=
/*!
*	\param job to compare with.
*	\return result of priority comparison.
*/

bool LFJob::operator>=(LFJob& j) { if (!(*this < j)) return true; else return false; }

//******************************************************************************
//! Overload of the operator =
/*!
*	\param job to copy from.
*	\return reference of this.
*/

LFJob& LFJob::operator=(LFJob& copy)
{
	jobPriority = copy.getPrio();
	workingLF = copy.getWorkingLF();
	return *this;
}

unsigned long long LFMoveJob::moveJobCounter = 0;

//******************************************************************************
//! Copy constructor of class LFMoveJob
/*!
*	\param job to copy from.
*	\return none.
*/

LFMoveJob::LFMoveJob(LFJob& copy) : LFJob(copy)
{
	LFMoveJob* moveCopy = dynamic_cast<LFMoveJob*>(&copy);
	if (moveCopy) *this = *moveCopy;
	++moveJobCounter;
}

//******************************************************************************
//! Copy constructor of class LFMoveJob
/*!
*	\param job to copy from.
*	\return none.
*/

LFMoveJob::LFMoveJob(LFMoveJob& copy) : LFJob(copy)
{
	*this = copy;
	++moveJobCounter;
}

//******************************************************************************
//! Deconstructor of class LFMoveJob

LFMoveJob::~LFMoveJob()
{
	--moveJobCounter;
}

//******************************************************************************
//! Returns number of move jobs
/*!
*	\param none.
*	\return moveJobCounter.
*/

unsigned long long LFMoveJob::getMoveJobCount()
{
	return moveJobCounter;
}

//******************************************************************************
//! Returns destination
/*!
*	\param none.
*	\return destination.
*/

CartesianCoordAdapter LFMoveJob::getDestination()
{
	return destination;
}

//******************************************************************************
//! Sets destination
/*!
*	\param destination.
*	\return none.
*/

void LFMoveJob::changeDestination(CartesianCoordAdapter const &dest)
{
	destination = dest;
}

//******************************************************************************
//! Sets working life form
/*!
*	\param life form that will be working on the job.
*	\return none.
*/

void LFMoveJob::changeWorkingLF(LifeFormEntity * workLF)
{
	LFJob::changeWorkingLF(workLF);
}

//******************************************************************************
//! Overload of the operator =
/*!
*	\param job to copy from.
*	\return reference of this.
*/

LFMoveJob& LFMoveJob::operator=(LFMoveJob& copy)
{
	*static_cast<LFJob*>(this) = copy;
	destination = copy.getDestination();
	return *this;
}

//******************************************************************************
//! Works on the job
/*!
*	\param none.
*	\return true if done.
*/

bool LFMoveJob::workOnJob()
{
	if (workingLF) return workingLF->moveTowardsDest(destination);
	return true;
}

//******************************************************************************
//! Sets life forms that are involved with the job
/*!
*	\param vector of life forms in the constructor parameter order of the job.
*	\return none.
*/

void LFMoveJob::changeParticipants(QVector<LifeFormEntity*> participants)
{

}

//******************************************************************************
//! Returns life forms that are involved with the job
/*!
*	\param none.
*	\return vector of life forms in the constructor parameter order of the job.
*/

QVector<LifeFormEntity*> LFMoveJob::getParticipants()
{
	return QVector<LifeFormEntity*>();
}

unsigned long long LFMeetJob::meetJobCounter = 0;

//******************************************************************************
//! Constructor of class LFMeet
/*!
*	\param life form that is working on the job.
*	\param life form to meet with.
*	\param priority.
*	\return none.
*/

LFMeetJob::LFMeetJob(LifeFormEntity* workLF, LifeFormEntity* lfToMeet, unsigned int prio) : LFJob(workLF, prio)
{
	jMove = nullptr;
	LFToMeet = nullptr;

	if (workingLF && lfToMeet)
	{
		LFToMeet = lfToMeet;
		jMove = new LFMoveJob(workingLF, LFToMeet->getRelativePos());
	}
	++meetJobCounter;
}

//******************************************************************************
//! Copy constructor of class LFMeetJob
/*!
*	\param job to copy from.
*	\return none.
*/

LFMeetJob::LFMeetJob(LFJob& copy) : LFJob(copy)
{
	jMove = nullptr;
	LFToMeet = nullptr;

	LFMeetJob* meetCopy = dynamic_cast<LFMeetJob*>(&copy);
	if (meetCopy) *this = *meetCopy;
	++meetJobCounter;
}

//******************************************************************************
//! Copy constructor of class LFMeetJob
/*!
*	\param job to copy from.
*	\return none.
*/

LFMeetJob::LFMeetJob(LFMeetJob& copy) : LFJob(copy)
{
	*this = copy;
	++meetJobCounter;
}

//******************************************************************************
//! Deconstructor of class LFMeetJob

LFMeetJob::~LFMeetJob()
{
	delete jMove;
	jMove = nullptr;
	--meetJobCounter;
}

//******************************************************************************
//! Returns number of meet jobs
/*!
*	\param none.
*	\return meetJobCounter.
*/

unsigned long long LFMeetJob::getMeetJobCount()
{
	return meetJobCounter;
}

//******************************************************************************
//! Sets working life form
/*!
*	\param life form that will be working on the job.
*	\return none.
*/

void LFMeetJob::changeWorkingLF(LifeFormEntity * workLF)
{
	LFJob::changeWorkingLF(workLF);
	if (jMove) jMove->changeWorkingLF(workLF);
}

//******************************************************************************
//! Overload of the operator =
/*!
*	\param job to copy from.
*	\return reference of this.
*/

LFMeetJob& LFMeetJob::operator=(LFMeetJob& copy)
{
	if(&copy != this)
	{
		LFToMeet = nullptr;
		jMove = nullptr;

		*static_cast<LFJob*>(this) = copy;

		if (workingLF && copy.getParticipants()[0])
		{ 
			LFToMeet = copy.getParticipants()[0];
			jMove = new LFMoveJob(workingLF, LFToMeet->getRelativePos());
		}
	}
	return *this;
}

//******************************************************************************
//! Works on the job
/*!
*	\param none.
*	\return true if done.
*/

bool LFMeetJob::workOnJob()
{
	if (workingLF && LFToMeet)
	{
		jMove->changeDestination(LFToMeet->getRelativePos());
		if (jMove->workOnJob())
		{
			workingLF->addKnownLFE(LFToMeet);
			LFToMeet->addKnownLFE(workingLF);
			return true;
		}
		return false;
	}
	return true;
}

//******************************************************************************
//! Sets life forms that are involved with the job
/*!
*	\param vector of life forms in the constructor parameter order of the job.
*	\return none.
*/

void LFMeetJob::changeParticipants(QVector<LifeFormEntity*> participants)
{
	if (participants.size() >= 1)
	{
		LFToMeet = participants[0];
		if (jMove) jMove->changeParticipants(participants);
	}
}

//******************************************************************************
//! Returns life forms that are involved with the job
/*!
*	\param none.
*	\return vector of life forms in the constructor parameter order of the job.
*/

QVector<LifeFormEntity*> LFMeetJob::getParticipants()
{
	QVector<LifeFormEntity*> pp;
	pp.push_back(LFToMeet);
	return pp;
}

unsigned long long LFAskJob::askJobCounter = 0;

//******************************************************************************
//! Constructor of class LFAskJob
/*!
*	\param life form that is working on the job.
*	\param life form to ask.
*	\param life form that receives the answer.
*	\param priority.
*	\return none.
*/

LFAskJob::LFAskJob(LifeFormEntity* workLF, LifeFormEntity* lfToAsk, LifeFormEntity* lfThatReceives, unsigned int prio) : LFJob(workLF, prio)
{
	jMeet = nullptr;
	LFToAsk = nullptr;
	LFThatReceives = nullptr;

	if (workingLF && lfToAsk)
	{
		LFToAsk = lfToAsk;
		LFThatReceives = lfThatReceives;
		jMeet = new LFMeetJob(workingLF, LFToAsk);
	}
	++askJobCounter;
}

//******************************************************************************
//! Copy constructor of class LFAskJob
/*!
*	\param job to copy from.
*	\return none.
*/

LFAskJob::LFAskJob(LFJob& copy) : LFJob(copy)
{
	jMeet = nullptr;
	LFToAsk = nullptr;
	LFThatReceives = nullptr;

	LFAskJob* askCopy = dynamic_cast<LFAskJob*>(&copy);
	if (askCopy) *this = *askCopy;
	++askJobCounter;
}

//******************************************************************************
//! Copy constructor of class LFAskJob
/*!
*	\param job to copy from.
*	\return none.
*/

LFAskJob::LFAskJob(LFAskJob& copy) : LFJob(copy)
{
	*this = copy;
	++askJobCounter;
}

//******************************************************************************
//! Deconstructor of class LFAskJob

LFAskJob::~LFAskJob()
{
	delete jMeet;
	jMeet = nullptr;
	--askJobCounter;
}

//******************************************************************************
//! Returns number of ask jobs
/*!
*	\param none.
*	\return askJobCounter.
*/

unsigned long long LFAskJob::getAskJobCount()
{
	return askJobCounter;
}

//******************************************************************************
//! Sets working life form
/*!
*	\param life form that will be working on the job.
*	\return none.
*/

void LFAskJob::changeWorkingLF(LifeFormEntity * workLF)
{
	LFJob::changeWorkingLF(workLF);
	if (jMeet) jMeet->changeWorkingLF(workLF);
}

//******************************************************************************
//! Overload of the operator =
/*!
*	\param job to copy from.
*	\return reference of this.
*/

LFAskJob& LFAskJob::operator=(LFAskJob& copy)
{
	if(&copy != this)
	{ 
		LFToAsk = nullptr;
		LFThatReceives = nullptr;
		jMeet = nullptr;

		*static_cast<LFJob*>(this) = copy;

		if (workingLF && copy.getParticipants()[0])
		{
			LFToAsk = copy.getParticipants()[0];
			LFThatReceives = copy.getParticipants()[1];
			jMeet = new LFMeetJob(workingLF, LFToAsk);
		}
	}
	return *this;
}

//******************************************************************************
//! Works on the job
/*!
*	\param none.
*	\return true if done.
*/

bool LFAskJob::workOnJob()
{
	if (workingLF && LFToAsk)
	{
		if (jMeet->workOnJob())
		{
            if (LFThatReceives)
                LFToAsk->solveProblem(LFThatReceives);
            else
                LFToAsk->solveProblem(workingLF);
			return true;
		}
		return false;
	}
	return true;
}

//******************************************************************************
//! Sets life forms that are involved with the job
/*!
*	\param vector of life forms in the constructor parameter order of the job.
*	\return none.
*/

void LFAskJob::changeParticipants(QVector<LifeFormEntity*> participants)
{
	if (participants.size() >= 2)
	{
		LFToAsk = participants[0];
		LFThatReceives = participants[1];
		if(jMeet) jMeet->changeParticipants(participants);
	}
}

//******************************************************************************
//! Returns life forms that are involved with the job
/*!
*	\param none.
*	\return vector of life forms in the constructor parameter order of the job.
*/

QVector<LifeFormEntity*> LFAskJob::getParticipants()
{
	QVector<LifeFormEntity*> pp;
	pp.push_back(LFToAsk);
	pp.push_back(LFThatReceives);
	return pp;
}

unsigned long long LFAnswerJob::answerJobCounter = 0;

//******************************************************************************
//! Constructor of class LFAnswerJob
/*!
*	\param life form that is working on the job.
*	\param life form that receives the answer.
*	\param answer.
*	\param priority.
*	\return none.
*/

LFAnswerJob::LFAnswerJob(LifeFormEntity* workLF, LifeFormEntity* lfThatReceives, bool answer, unsigned int prio) : LFJob(workLF, prio)
{
	jMeet = nullptr;
	LFThatReceives = nullptr;

	if (workingLF && lfThatReceives)
	{
		LFThatReceives = lfThatReceives;
		jMeet = new LFMeetJob(workingLF, LFThatReceives);
		result = answer;
	}
	++answerJobCounter;
}

//******************************************************************************
//! Copy constructor of class LFAnswerJob
/*!
*	\param job to copy from.
*	\return none.
*/

LFAnswerJob::LFAnswerJob(LFJob& copy) : LFJob(copy)
{
	jMeet = nullptr;
	LFThatReceives = nullptr;

	LFAnswerJob* answerCopy = dynamic_cast<LFAnswerJob*>(&copy);
	if (answerCopy) *this = *answerCopy;
	++answerJobCounter;
}

//******************************************************************************
//! Copy constructor of class LFAnswerJob
/*!
*	\param job to copy from.
*	\return none.
*/

LFAnswerJob::LFAnswerJob(LFAnswerJob& copy) : LFJob(copy)
{
	*this = copy;
	++answerJobCounter;
}

//******************************************************************************
//! Deconstructor of class LFAnswerJob

LFAnswerJob::~LFAnswerJob()
{
	delete jMeet;
	jMeet = nullptr;
	--answerJobCounter;
}

//******************************************************************************
//! Returns number of answer jobs
/*!
*	\param none.
*	\return answerJobCounter.
*/

unsigned long long LFAnswerJob::getAnswerJobCount()
{
	return answerJobCounter;
}

//******************************************************************************
//! Returns answer
/*!
*	\param none.
*	\return answer.
*/

bool LFAnswerJob::getAnswer()
{
	return result;
}

//******************************************************************************
//! Sets working life form
/*!
*	\param life form that will be working on the job.
*	\return none.
*/

void LFAnswerJob::changeWorkingLF(LifeFormEntity * workLF)
{
	LFJob::changeWorkingLF(workLF);
	if (jMeet) jMeet->changeWorkingLF(workLF);
}

//******************************************************************************
//! Overload of the operator =
/*!
*	\param job to copy from.
*	\return reference of this.
*/

LFAnswerJob& LFAnswerJob::operator=(LFAnswerJob& copy)
{
	if(&copy != this)
	{ 
		jMeet = nullptr;
		LFThatReceives = nullptr;

		*static_cast<LFJob*>(this) = copy;

		if (workingLF && copy.getParticipants()[0])
		{
			LFThatReceives = copy.getParticipants()[0];
			jMeet = new LFMeetJob(workingLF, LFThatReceives);
			result = copy.getAnswer();
		}
	}
	return *this;
}

//******************************************************************************
//! Works on the job
/*!
*	\param none.
*	\return true if done.
*/

bool LFAnswerJob::workOnJob()
{
	if (workingLF && LFThatReceives)
	{
		if (jMeet->workOnJob())
		{
			LFThatReceives->receiveAnswer(workingLF, result);
			return true;
		}
		return false;
	}
	return true;
}

//******************************************************************************
//! Sets life forms that are involved with the job
/*!
*	\param vector of life forms in the constructor parameter order of the job.
*	\return none.
*/

void LFAnswerJob::changeParticipants(QVector<LifeFormEntity*> participants)
{
	if (participants.size() >= 1)
	{
		LFThatReceives = participants[0];
		if(jMeet) jMeet->changeParticipants(participants);
	}
}

//******************************************************************************
//! Returns life forms that are involved with the job
/*!
*	\param none.
*	\return vector of life forms in the constructor parameter order of the job.
*/

QVector<LifeFormEntity*> LFAnswerJob::getParticipants()
{
	QVector<LifeFormEntity*> pp;
	pp.push_back(LFThatReceives);
	return pp;
}

unsigned long long LFIdleJob::idleJobCounter = 0;

//******************************************************************************
//! Constructor of class LFIdleJob
/*!
*	\param life form that is working on the job.
*	\param ticks.
*	\param priority.
*	\return none.
*/

LFIdleJob::LFIdleJob(LifeFormEntity* workLF, unsigned int ticks, unsigned int prio) : LFJob(workLF, prio)
{
	tickCount = ticks;
	currentTick = 0;
	++idleJobCounter;
}

//******************************************************************************
//! Copy constructor of class LFIdleJob
/*!
*	\param job to copy from.
*	\return none.
*/

LFIdleJob::LFIdleJob(LFJob& copy) : LFJob(copy)
{
	tickCount = 0;
	currentTick = 0;

	LFIdleJob* idleCopy = dynamic_cast<LFIdleJob*>(&copy);
	if (idleCopy) *this = *idleCopy;
	++idleJobCounter;
}

//******************************************************************************
//! Copy constructor of class LFIdleJob
/*!
*	\param job to copy from.
*	\return none.
*/

LFIdleJob::LFIdleJob(LFIdleJob& copy) : LFJob(copy)
{
	*this = copy;
	++idleJobCounter;
}

//******************************************************************************
//! Deconstructor of class LFIdleJob

LFIdleJob::~LFIdleJob()
{
	--idleJobCounter;
}

//******************************************************************************
//! Returns number of idle jobs
/*!
*	\param none.
*	\return idleJobCounter.
*/

unsigned long long LFIdleJob::getIdleJobCount()
{
    return idleJobCounter;
}

//******************************************************************************
//! Returns number of ticks to idle
/*!
*	\param none.
*	\return tickCount.
*/

unsigned int LFIdleJob::getTickCount()
{
	return tickCount;
}

//******************************************************************************
//! Returns current idle tick
/*!
*	\param none.
*	\return currentTick.
*/

unsigned int LFIdleJob::getCurrentTick()
{
	return currentTick;
}

//******************************************************************************
//! Sets working life form
/*!
*	\param life form that will be working on the job.
*	\return none.
*/

void LFIdleJob::changeWorkingLF(LifeFormEntity * workLF)
{
	LFJob::changeWorkingLF(workLF);
}

//******************************************************************************
//! Overload of the operator =
/*!
*	\param job to copy from.
*	\return reference of this.
*/

LFIdleJob& LFIdleJob::operator=(LFIdleJob& copy)
{
	tickCount = 0;
	currentTick = 0;

	*static_cast<LFJob*>(this) = copy;
	tickCount = copy.getTickCount();
	currentTick = copy.getCurrentTick();

	return *this;
}

//******************************************************************************
//! Works on the job
/*!
*	\param none.
*	\return true if done.
*/

bool LFIdleJob::workOnJob()
{
	if (currentTick == tickCount) return true;
	currentTick++;
	return false;
}

//******************************************************************************
//! Sets life forms that are involved with the job
/*!
*	\param vector of life forms in the constructor parameter order of the job.
*	\return none.
*/

void LFIdleJob::changeParticipants(QVector<LifeFormEntity*> participants)
{

}

//******************************************************************************
//! Returns life forms that are involved with the job
/*!
*	\param none.
*	\return vector of life forms in the constructor parameter order of the job.
*/

QVector<LifeFormEntity*> LFIdleJob::getParticipants()
{
	return QVector<LifeFormEntity*>();
}

unsigned long long LFMateJob::mateJobCounter = 0;

//******************************************************************************
//! Constructor of class LFMateJob
/*!
*	\param life form that is working on the job.
*	\param life form to mate with.
*	\param priority.
*	\return none.
*/

LFMateJob::LFMateJob(LifeFormEntity* workLF, LifeFormEntity* partnerLF, unsigned int prio) : LFJob(workLF, prio)
{
	jMeet = nullptr;
	partner = nullptr;
	ourDestinyAdapter = nullptr;

	if (workingLF && partnerLF && workingLF != partnerLF)
	{
		partner = partnerLF;
		ourDestinyAdapter = DestinyAdapter::Instance(workingLF->parent());
		jMeet = new LFMeetJob(workingLF, partner);
	}
	++mateJobCounter;
}

//******************************************************************************
//! Copy constructor of class LFMateJob
/*!
*	\param job to copy from.
*	\return none.
*/

LFMateJob::LFMateJob(LFJob& copy) : LFJob(copy)
{
	jMeet = nullptr;
	partner = nullptr;
	ourDestinyAdapter = nullptr;

	LFMateJob* mateCopy = dynamic_cast<LFMateJob*>(&copy);
	if (mateCopy) *this = *mateCopy;
	++mateJobCounter;
}

//******************************************************************************
//! Copy constructor of class LFMateJob
/*!
*	\param job to copy from.
*	\return none.
*/

LFMateJob::LFMateJob(LFMateJob& copy) : LFJob(copy)
{
	*this = copy;
	++mateJobCounter;
}

//******************************************************************************
//! Deconstructor of class LFMateJob

LFMateJob::~LFMateJob()
{
	delete jMeet;
	jMeet = nullptr;
	--mateJobCounter;
}

//******************************************************************************
//! Returns number of mate jobs
/*!
*	\param none.
*	\return mateJobCounter.
*/

unsigned long long LFMateJob::getMateJobCount()
{
	return mateJobCounter;
}

//******************************************************************************
//! Sets working life form
/*!
*	\param life form that will be working on the job.
*	\return none.
*/

void LFMateJob::changeWorkingLF(LifeFormEntity * workLF)
{
	LFJob::changeWorkingLF(workLF);
	if (jMeet) jMeet->changeWorkingLF(workLF);
}

//******************************************************************************
//! Overload of the operator =
/*!
*	\param job to copy from.
*	\return reference of this.
*/

LFMateJob& LFMateJob::operator=(LFMateJob& copy)
{
	if(&copy != this)
	{ 
		partner = nullptr;
		jMeet = nullptr;
		ourDestinyAdapter = nullptr;

		*static_cast<LFJob*>(this) = copy;
		if (workingLF && copy.getParticipants()[0] && workingLF != copy.getParticipants()[0])
		{
			partner = copy.getParticipants()[0];
			ourDestinyAdapter = DestinyAdapter::Instance(workingLF->parent());
			jMeet = new LFMeetJob(workingLF, partner);
		}
	}
	return *this;
}

//******************************************************************************
//! Works on the job
/*!
*	\param none.
*	\return true if done.
*/

bool LFMateJob::workOnJob()
{
	if (workingLF && partner)
	{
		if (jMeet->workOnJob())
		{
			LifeFormEntity* child = createChild();
            PlanetEntity* workHomePlanetEntity = workingLF->getHomePlanetEntity();
            CartesianCoordAdapter workRelativePos = workingLF->getRelativePos();

            child->inhabitPlanet(workHomePlanetEntity, &workRelativePos);
			qDebug() << "[LFMateJob::workOnJob] ===" << "[ G" << child->getGeneration() << "]" << child->getName() << "with development level" << child->getDevLvl() << "was born. ===";
			child->addKnownLFE(workingLF);
			child->addKnownLFE(partner);
			workingLF->addKnownLFE(child);
			partner->addKnownLFE(child);
			return true;
		}
		return false;
	}
	return true;
}

//******************************************************************************
//! Sets life forms that are involved with the job
/*!
*	\param vector of life forms in the constructor parameter order of the job.
*	\return none.
*/

void LFMateJob::changeParticipants(QVector<LifeFormEntity*> participants)
{
	if (participants.size() >= 1)
	{
		partner = participants[0];
		if(jMeet) jMeet->changeParticipants(participants);
	}
}

//******************************************************************************
//! Returns life forms that are involved with the job
/*!
*	\param none.
*	\return vector of life forms in the constructor parameter order of the job.
*/

QVector<LifeFormEntity*> LFMateJob::getParticipants()
{
	QVector<LifeFormEntity*> pp;
	pp.push_back(partner);
	return pp;
}

//******************************************************************************
//! Returns new life form instance created from attributes of parents
/*!
*	\param none.
*	\return child.
*/

LifeFormEntity * LFMateJob::createChild()
{
	LifeFormEntity* child;
	int newDL = (dist(mt) % 2) ? workingLF->getDevLvl() : partner->getDevLvl();

	QString newName = qstrdup(qPrintable(ourDestinyAdapter->generateLFEName()));;
	const char* newNameConst = qstrdup(qPrintable(newName));
	const char* newGodNameConst = (dist(mt) % 2) ? qstrdup(qPrintable(workingLF->getGodName())) : qstrdup(qPrintable(partner->getGodName()));

	switch (newDL)
	{
	case 1:
		child = new LowDev_LFEntity(workingLF->parent(), newNameConst, newGodNameConst, workingLF, partner);
		break;
	case 2:
		child = new MidDev_LFEntity(workingLF->parent(), newNameConst, newGodNameConst, workingLF, partner);
		break;
	case 3:
		child = new HighDev_LFEntity(workingLF->parent(), newNameConst, newGodNameConst, workingLF, partner);
		break;
	}
	return child;
}


