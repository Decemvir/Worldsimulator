//*************************************************************************
/** \file
*  \brief Contains the declaration of class LFJobHandler.
*/

#pragma once

#include <QObject>
#include <queue> 
#include "lfJobs.h"

class LifeFormEntity;

//*************************************************************************
/*!	\class LFJobHandler
*	\ingroup FacadeTE SingletonTE
*	\brief Member of pattern <b>Singleton</b>.
*		   Member of pattern <b>Facade</b> as <b>Facade</b>.
*          Member of pattern <b>Command</b> as <b>Caller</b>.
*	       Defines a handler that holds a job queue for every existing life form to
*		   easily deal with situations like the death/deletion of a life form instance
*		   in a centralized manner so they don't have to deal with job specific problems. 
*
*		   The main functionality of this class is to have the ability to replace references in jobs globally
*		   or remove jobs with a specific reference.
*
*		   The basic functionality of adding jobs and working on the top priority job of a life form is also given.
*/

class LFJobHandler : public QObject
{
	Q_OBJECT

public:
	static LFJobHandler* Instance(QObject *parent);
	void createJobQueue(LifeFormEntity* lf);
	void deleteJobQueue(LifeFormEntity* lf);
	void addJob(LifeFormEntity* lf, LFJob* j);
	bool workOnTopJob(LifeFormEntity* lf);
	void copyJobQueue(LifeFormEntity* targetLF, LifeFormEntity* sourceLF);
	void replaceLF(LifeFormEntity * oldLFRef, LifeFormEntity * newLFRef);
	void removeJobsWithParticipant(LifeFormEntity* targetLF, LifeFormEntity* pRef);
	void removeJobsMutual(LifeFormEntity* lf, LifeFormEntity* orherLF);
private:
	QVector<LifeFormEntity*> lifeforms;
	QVector<std::priority_queue<LFJob*>*> jobQueues;	
	std::priority_queue<LFJob*>* getCopyOfJobQueue(LifeFormEntity* targetLF, LifeFormEntity* workingLF = nullptr);
	void removeTopJob(std::priority_queue<LFJob*>* currentJobQueue);
	void clearJobQueue(std::priority_queue<LFJob*>* currentJobQueue);
	LFJobHandler(QObject *parent);
	~LFJobHandler();
};


