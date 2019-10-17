//*************************************************************************
/** \file
*  \brief Contains the declarations of classes LFJob, LFMoveJob, LFMeetJob, 
		  LFAskJob, LFAnswerJob, LFIdleJob, LFMateJob.
*/

#pragma once

#include <QObject>
#include <QVector>
#include <iostream>
#include <random>
#include "../model/god/cartesianCoordAdapter.h"
#include <QOpenGLShaderProgram>

class DestinyAdapter;
class LifeFormEntity;


//*************************************************************************
/*!	\class LFJob
*	\ingroup FacadeTE 
*	\brief Member of pattern <b>Facade</b> as <b>Subsystem classes</b>.
*          Member of pattern <b>Command</b> as <b>Command</b>.
*	       Defines an abstract job interface with minimal functionality so it can be
*		   used in a priority queue.
*		   It also has the basic functionality of working on it with returning true if the job is done
*		   and some methods to access or change the defined addresses and attributes.
*/

class LFJob
{
public:
	LFJob(LifeFormEntity* workLF, unsigned int prio = 1);
	LFJob(LFJob& copy);
	virtual ~LFJob();
	LifeFormEntity* getWorkingLF();
	unsigned int getPrio();
    static unsigned long long getJobCount();
	virtual void changeWorkingLF(LifeFormEntity* workLF);
	void setPrio(unsigned int prio);
	bool operator==(LFJob& j);
	bool operator!=(LFJob& j);
	bool operator<(LFJob& j);
	bool operator<=(LFJob& j);
	bool operator>(LFJob& j);
	bool operator>=(LFJob& j);
	LFJob& operator=(LFJob& copy);
	virtual bool workOnJob() = 0;
	virtual void changeParticipants(QVector<LifeFormEntity*> participants) = 0;
	virtual QVector<LifeFormEntity*> getParticipants() = 0;
protected:
	unsigned int jobPriority;
	LifeFormEntity* workingLF;
    static unsigned long long jobCounter;
};

//*************************************************************************
/*!	\class LFMoveJob
*	\brief Member of pattern <b>Command</b> as <b>ConcreteCommand</b>.
*          Defines a job that lets the working life form move towards a destination.
*/

class LFMoveJob : public virtual LFJob
{
public:
	//******************************************************************************
	//! Constructor of class LFMoveJob
	//!	\param life form that is working on the job. \param destination. \param priority. \return none.
	LFMoveJob(LifeFormEntity* workLF, CartesianCoordAdapter const &dest, unsigned int prio = 1) : destination(dest), LFJob(workLF, prio) { ++moveJobCounter; };
	LFMoveJob(LFJob& copy);
	LFMoveJob(LFMoveJob& copy);
	~LFMoveJob();	
    static unsigned long long getMoveJobCount();
	CartesianCoordAdapter getDestination();
	void changeDestination(CartesianCoordAdapter const &dest);
	void changeWorkingLF(LifeFormEntity* workLF);
	LFMoveJob& operator=(LFMoveJob& copy);
	bool workOnJob();
	void changeParticipants(QVector<LifeFormEntity*> participants);
	QVector<LifeFormEntity*> getParticipants();
private:
	CartesianCoordAdapter destination;
    static unsigned long long moveJobCounter;
};

//*************************************************************************
/*!	\class LFMeetJob
*	\brief Member of pattern <b>Command</b> as <b>ConcreteCommand</b>.
*          Defines a job that lets the working life form meet another life form.
*/

class LFMeetJob : public virtual LFJob
{
public:
	LFMeetJob(LifeFormEntity* workLF, LifeFormEntity* lfToMeet, unsigned int prio = 1);
	LFMeetJob(LFJob& copy);
	LFMeetJob(LFMeetJob& copy);
	~LFMeetJob();
    static unsigned long long getMeetJobCount();
	void changeWorkingLF(LifeFormEntity* workLF);
	LFMeetJob& operator=(LFMeetJob& copy);
	bool workOnJob();
	void changeParticipants(QVector<LifeFormEntity*> participants);
	QVector<LifeFormEntity*> getParticipants();
private:
	LifeFormEntity* LFToMeet;
	LFMoveJob* jMove;
    static unsigned long long meetJobCounter;
};

//*************************************************************************
/*!	\class LFAskJob
*	\brief Member of pattern <b>Command</b> as <b>ConcreteCommand</b>.
*          Defines a job that lets the working life form ask another life form.
*/

class LFAskJob : public virtual LFJob
{
public:
	LFAskJob(LifeFormEntity* workLF, LifeFormEntity* lfToAsk, LifeFormEntity* lfThatReceives, unsigned int prio = 1);
	LFAskJob(LFJob& copy);
	LFAskJob(LFAskJob& copy);
	~LFAskJob();
    static unsigned long long getAskJobCount();
	void changeWorkingLF(LifeFormEntity* workLF);
	LFAskJob& operator=(LFAskJob& copy);
	bool workOnJob();
	void changeParticipants(QVector<LifeFormEntity*> participants);
	QVector<LifeFormEntity*> getParticipants();
private:
	LifeFormEntity* LFToAsk;
	LifeFormEntity* LFThatReceives;
	LFMeetJob* jMeet;
    static unsigned long long askJobCounter;
};

//*************************************************************************
/*!	\class LFAnswerJob
*	\brief Member of pattern <b>Command</b> as <b>ConcreteCommand</b>.
*          Defines a job that lets the working life form give an answer to another life form.
*/

class LFAnswerJob : public virtual LFJob
{
public:
	LFAnswerJob(LifeFormEntity* workLF, LifeFormEntity* lfThatReceives, bool answer, unsigned int prio = 1);
	LFAnswerJob(LFJob& copy);
	LFAnswerJob(LFAnswerJob& copy);
	~LFAnswerJob();
    static unsigned long long getAnswerJobCount();
	bool getAnswer();
	void changeWorkingLF(LifeFormEntity* workLF);
	LFAnswerJob& operator=(LFAnswerJob& copy);
	bool workOnJob();
	void changeParticipants(QVector<LifeFormEntity*> participants);
	QVector<LifeFormEntity*> getParticipants();
private:
	LifeFormEntity* LFThatReceives;
	LFMeetJob* jMeet;
	bool result;
    static unsigned long long answerJobCounter;
};

//*************************************************************************
/*!	\class LFIdleJob
*	\brief Member of pattern <b>Command</b> as <b>ConcreteCommand</b>.
*          Defines a job that lets the working life form idle for a set amount of ticks.
*/

class LFIdleJob : public virtual LFJob
{
public:
	LFIdleJob(LifeFormEntity* workLF, unsigned int ticks, unsigned int prio = 1);
	LFIdleJob(LFJob& copy);
	LFIdleJob(LFIdleJob& copy);
	~LFIdleJob();
    static unsigned long long getIdleJobCount();
	unsigned int getTickCount();
	unsigned int getCurrentTick();
	void changeWorkingLF(LifeFormEntity* workLF);
	LFIdleJob& operator=(LFIdleJob& copy);
	bool workOnJob();
	void changeParticipants(QVector<LifeFormEntity*> participants);
	QVector<LifeFormEntity*> getParticipants();
private:
	unsigned int tickCount;
	unsigned int currentTick;
    static unsigned long long idleJobCounter;
};

//*************************************************************************
/*!	\class LFMateJob
*	\brief Member of pattern <b>Command</b> as <b>ConcreteCommand</b>.
*          Defines a job that lets the working life form mate with another life form.
*/

class LFMateJob : public virtual LFJob
{
public:
	LFMateJob(LifeFormEntity* workLF, LifeFormEntity* partnerLF, unsigned int prio = 1);
	LFMateJob(LFJob& copy);
	LFMateJob(LFMateJob& copy);
	~LFMateJob();
    static unsigned long long getMateJobCount();
	void changeWorkingLF(LifeFormEntity* workLF);
	LFMateJob& operator=(LFMateJob& copy);
	bool workOnJob();
	void changeParticipants(QVector<LifeFormEntity*> participants);
	QVector<LifeFormEntity*> getParticipants();
private:
	LifeFormEntity* createChild();
	LifeFormEntity* partner;
	LFMeetJob* jMeet;
	DestinyAdapter* ourDestinyAdapter;
    static unsigned long long mateJobCounter;
};



