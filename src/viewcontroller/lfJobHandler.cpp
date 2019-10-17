//*************************************************************************
/** \file
*  \brief Contains the implementation of class LFJobHandler.
*/

#include "lfJobHandler.h"
#include "lifeformEntity.h"

//******************************************************************************
//! Returns the unique LFJobHandler. (Singleton)
/*!
*  \param parent QT parent pointer.
*	\return The single instance of class LFJobHandler.
*/

LFJobHandler* LFJobHandler::Instance(QObject *parent)
{
	static LFJobHandler ourJobHandler(parent);
	return &ourJobHandler;
}

//******************************************************************************
//! Creates a job queue for a specific life form
/*!
*  \param address of life form
*	\return none.
*/

void LFJobHandler::createJobQueue(LifeFormEntity * lf)
{
	if (lf && !lifeforms.contains(lf))
	{
		jobQueues.push_back(new priority_queue<LFJob*>);
		lifeforms.push_back(lf);
	}
}

//******************************************************************************
//! Adds job to job queue of an specific life form
/*!
*  \param address of life form
*  \param job instance
*	\return none.
*/

void LFJobHandler::addJob(LifeFormEntity* lf, LFJob* j)
{
	if (lf && lf == j->getWorkingLF())
	{
		int index = lifeforms.indexOf(lf);
		if (index > -1)
		{
			priority_queue<LFJob*>* currentJobQueue = jobQueues[index];
			currentJobQueue->push(j);
		}
	}
}

//******************************************************************************
//! Deletes job queue for a specific life form
/*!
*  \param address of life form
*	\return none.
*/

void LFJobHandler::deleteJobQueue(LifeFormEntity* lf)
{
	if (lf)
	{
		int index = lifeforms.indexOf(lf);
		if (index > -1)
		{
			for (QVector<LifeFormEntity*>::iterator it = lifeforms.begin(); it != lifeforms.end(); ++it) removeJobsWithParticipant(*it, lf);
			priority_queue<LFJob*>* currentJobQueue = jobQueues[index];
			clearJobQueue(currentJobQueue);
			jobQueues.removeOne(currentJobQueue);
			delete currentJobQueue;
			lifeforms.removeOne(lf);
		}
	}
}

//******************************************************************************
//! Works on top priority job
/*!
*  \param address of life form
*	\return false if there are no jobs to work on.
*/

bool LFJobHandler::workOnTopJob(LifeFormEntity* lf)
{
	if (lf)
	{
		int index = lifeforms.indexOf(lf);
		if (index > -1)
		{
			priority_queue<LFJob*>* currentJobQueue = jobQueues[index];
			if (!currentJobQueue->empty())
			{
                if (currentJobQueue->top()->workOnJob())
                    removeTopJob(currentJobQueue);
				return true;
			}
		}
	}
	return false;
}

//******************************************************************************
//! Assigns job queue copy of sourceLF to targetLF 
/*!
*  \param address of target life form
*	\param address of source life form
*	\return none.
*/

void LFJobHandler::copyJobQueue(LifeFormEntity* targetLF, LifeFormEntity* sourceLF)
{
	if (targetLF && sourceLF && targetLF != sourceLF && lifeforms.contains(sourceLF))
	{
		int index = lifeforms.indexOf(targetLF);
		if (index > -1)
		{
			priority_queue<LFJob*>* currentJobQueue = jobQueues[index];
			clearJobQueue(currentJobQueue);
			delete currentJobQueue;
			currentJobQueue = getCopyOfJobQueue(sourceLF, targetLF);
			jobQueues[index] = currentJobQueue;
		}
	}
}

//******************************************************************************
//! Replaces all occurences of oldLFRef with newLFRef
/*!
*  \param address to be replaced.
*	\param new address.
*	\return none.
*/

void LFJobHandler::replaceLF(LifeFormEntity * oldLFRef, LifeFormEntity * newLFRef)
{
	if (oldLFRef && newLFRef && oldLFRef != newLFRef)
	{
		if (lifeforms.contains(newLFRef)) deleteJobQueue(newLFRef);
		for (QVector<priority_queue<LFJob*>*>::iterator it = jobQueues.begin(); it != jobQueues.end(); ++it)
		{
			priority_queue<LFJob*>* currentJobQueue = *it;
			priority_queue<LFJob*>* cache = new priority_queue<LFJob*>;
			int JQIndex = it - jobQueues.begin();
			if (lifeforms[JQIndex] == oldLFRef) lifeforms[JQIndex] = newLFRef;
			while (!currentJobQueue->empty())
			{
				LFJob* j = currentJobQueue->top();
				QVector<LifeFormEntity*> participants = j->getParticipants();
				if (j->getWorkingLF() == oldLFRef) j->changeWorkingLF(newLFRef);
				for (QVector<LifeFormEntity*>::iterator pIt = participants.begin(); pIt != participants.end(); ++pIt)
				{
					if (*pIt == oldLFRef) participants[pIt - participants.begin()] = newLFRef;
				}
				j->changeParticipants(participants);
				currentJobQueue->pop();
				cache->push(j);
			}
			delete currentJobQueue;
			currentJobQueue = cache;
			jobQueues[JQIndex] = currentJobQueue;
		}
	}
}

//******************************************************************************
//! Removes all jobs that contain pRef from targetLFs job queue
/*!
*  \param address of target life form
*	\param address that will get jobs removed
*	\return none.
*/

void LFJobHandler::removeJobsWithParticipant(LifeFormEntity* targetLF, LifeFormEntity* pRef)
{
	if (targetLF && pRef)
	{
		int index = lifeforms.indexOf(targetLF);
		if (index > -1)
		{
			priority_queue<LFJob*>* newJobQueue = new priority_queue<LFJob*>;
			priority_queue<LFJob*>* currentJobQueue = jobQueues[index];
			while (!currentJobQueue->empty())
			{
				LFJob* currentJob = currentJobQueue->top();
				QVector<LifeFormEntity*> participants = currentJob->getParticipants();
				if (!participants.contains(pRef)) newJobQueue->push(currentJob);
				else delete currentJob;
				currentJobQueue->pop();
			}
			delete currentJobQueue;
			currentJobQueue = newJobQueue;
			jobQueues[index] = currentJobQueue;
		}
	}
}

//******************************************************************************
//! Removes all jobs that contain otherLF from lfs job queue and the other way around.
/*!
*  \param address of life form
*	\param address of other life form
*	\return none.
*/

void LFJobHandler::removeJobsMutual(LifeFormEntity* lf, LifeFormEntity* orherLF)
{
	removeJobsWithParticipant(lf, orherLF);
	removeJobsWithParticipant(orherLF, lf);
}

//******************************************************************************
//! Returns exact copy of a job queue and replaces workingLF if specified
/*!
*  \param address of target life form
*	\param address of working life form
*	\return copy.
*/

priority_queue<LFJob*>* LFJobHandler::getCopyOfJobQueue(LifeFormEntity* targetLF, LifeFormEntity* workingLF)
{
	if (targetLF)
	{
		int index = lifeforms.indexOf(targetLF);
		if (index > -1)
		{
			priority_queue<LFJob*>* currentJobQueue = jobQueues[index];
			priority_queue<LFJob*>* copy = new priority_queue<LFJob*>;
			priority_queue<LFJob*>* cache = new priority_queue<LFJob*>;
			LFJob* jCopy = nullptr;

			while (!currentJobQueue->empty())
			{
				LFJob* j = currentJobQueue->top();
				LFMoveJob* moveJob = dynamic_cast<LFMoveJob*>(j);
				if (moveJob) jCopy = new LFMoveJob(*moveJob);
				else
				{
					LFMeetJob* meetJob = dynamic_cast<LFMeetJob*>(j);
					if (meetJob) jCopy = new LFMeetJob(*meetJob);
					else
					{
						LFMateJob* mateJob = dynamic_cast<LFMateJob*>(j);
						if (mateJob) jCopy = new LFMateJob(*mateJob);
						else
						{
							LFIdleJob* idleJob = dynamic_cast<LFIdleJob*>(j);
							if (idleJob) jCopy = new LFIdleJob(*idleJob);
							else
							{
								LFAskJob* askJob = dynamic_cast<LFAskJob*>(j);
								if (askJob) jCopy = new LFAskJob(*askJob);
								else
								{
									LFAnswerJob* answerJob = dynamic_cast<LFAnswerJob*>(j);
									if (answerJob) jCopy = new LFAnswerJob(*answerJob);
								}
							}
						}
					}
				}
				currentJobQueue->pop();
				cache->push(j);
				if (workingLF) jCopy->changeWorkingLF(workingLF);
				copy->push(jCopy);
			}
			delete currentJobQueue;
			currentJobQueue = cache;
			jobQueues[index] = currentJobQueue;
			return copy;
		}
	}
	return nullptr;
}

//******************************************************************************
//! Deletes top priority job from a job queue
/*!
*  \param job queue
*	\return none.
*/

void LFJobHandler::removeTopJob(std::priority_queue<LFJob*>* currentJobQueue)
{
	if (!currentJobQueue->empty())
	{
		delete currentJobQueue->top();
		currentJobQueue->pop();
	}
}

//******************************************************************************
//! Deletes all jobs of a job queue
/*!
*  \param job queue
*	\return none.
*/

void LFJobHandler::clearJobQueue(std::priority_queue<LFJob*>* currentJobQueue)
{
	while (!currentJobQueue->empty()) removeTopJob(currentJobQueue);
}

//******************************************************************************
//! Constructor of class LFJobHandler
/*!
*	\param parent QT parent pointer.
*	\return none.
*/

LFJobHandler::LFJobHandler(QObject *parent) : QObject(parent)
{

}

//******************************************************************************
//! Deconstructor of class LFJobHandler

LFJobHandler::~LFJobHandler()
{

}
