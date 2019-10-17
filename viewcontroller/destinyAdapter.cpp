//*************************************************************************
/** \file
*  \brief Contains the implementation of class DestinyAdapter.
*/

#include "destinyAdapter.h"
#include <QDebug>
#include <QString>
#include <QVector>
#include "planetEntity.h"
#include "lowDevLFEntity.h"
#include "midDevLFEntity.h"
#include "highDevLFEntity.h"
#include <random>

static std::random_device rd;
static std::mt19937_64 mt(rd());
static std::uniform_int_distribution<unsigned int> dist(0);

const int DestinyAdapter::NUM_OF_CONCRETE_LIFEFORMS = 3;

//******************************************************************************
//! Returns the unique DestinyAdapter. (Singleton)
/*!
*  \param parent QT parent pointer.
*	\return The single instance of class DestinyAdapter.
*/

DestinyAdapter* DestinyAdapter::Instance(QObject *parent)
{
    static DestinyAdapter ourDestinyAdapter(parent);
    return &ourDestinyAdapter;
}

//******************************************************************************
//! Creates a problem for a specific life form.
/*!
*  \param lf life form that has to solve a problem.
*	\return none.
*/

void DestinyAdapter::createProblemForLFE(LifeFormEntity* lf)
{
    if (lf) lf->solveProblem(nullptr);
}

//******************************************************************************
//! The life form lf will meet otherLF and on arrival they add each other to there list of known life forms.
/*!
*	\param lf life form that is part of the rendevouz.
*	\param otherLF life form that is part of the rendevouz.
*	\return none.
*/

void DestinyAdapter::rendevouzTwoLFEs(LifeFormEntity* lf, LifeFormEntity* otherLF)
{
    if (lf && otherLF && lf != otherLF) lf->meetWith(otherLF);
}

//******************************************************************************
//! Specific life form gets killed
/*!
*	\param lf life form that dies.
*	\return none.
*/

void DestinyAdapter::killLFE(LifeFormEntity* lf)
{
    if (lf)
    {
        for (QVector<LifeFormEntity*>::iterator it = LFEs.begin(); it != LFEs.end(); ++it)
            if (*it != lf)
                (*it)->forgetAboutLFE(lf);

        delete lf;
        ++NumberOfDeadLFEs;
        LFEs.squeeze();
	}
}

//******************************************************************************
//! Specific life form gets killed
/*!
*	\param lf life form that dies.
*	\return none.
*/

void DestinyAdapter::mateTwoLFE(LifeFormEntity* lf, LifeFormEntity* otherLF)
{
    if (lf && otherLF && lf != otherLF) lf->mateWith(otherLF);
}

//******************************************************************************
//! Specific life form evolves by getting replaced with his higher developed form.
/*!
*	\param lf life form that evolves.
*	\return none.
*/

void DestinyAdapter::evolveLFE(LifeFormEntity* lf)
{
    if (lf)
    {
        LifeFormEntity* evolvedLF;
        PlanetEntity* homeP = lf->getHomePlanetEntity();
        CartesianCoordAdapter rPos = lf->getRelativePos();
        int ownDL = lf->getDevLvl();
        int newDL = (dist(mt) % NUM_OF_CONCRETE_LIFEFORMS) + 1;
        while (newDL < ownDL) newDL = (dist(mt) % NUM_OF_CONCRETE_LIFEFORMS) + 1;
        QVector<LifeFormEntity*> knownByLFEs;
        QString oldDLName;

        for (int i = 0; i < LFEs.size(); ++i)
            if (LFEs[i]->knows(lf)) knownByLFEs.push_back(LFEs[i]);

        switch (ownDL)
        {
        case 1:
            oldDLName = "low developed";
            break;
        case 2:
            oldDLName = "mid developed";
            break;
        case 3:
            oldDLName = "high developed";
            break;
        }

        qDebug() << "[DestinyAdapter::evolveLFE]" << lf->getName() << "leaves his old" << oldDLName << "form behind and evolves.";
        for (QVector<LifeFormEntity*>::iterator it = LFEs.begin(); it != LFEs.end(); ++it)
            if (*it != lf)
                (*it)->forgetAboutLFE(lf);
				
        switch (newDL)
        {
        case 1:
            evolvedLF = new LowDev_LFEntity(*lf);
            qDebug() << "[DestinyAdapter::evolveLFE]" << evolvedLF->getName() << "has become a low developed life form.";
            break;
        case 2:
            evolvedLF = new MidDev_LFEntity(*lf);
            qDebug() << "[DestinyAdapter::evolveLFE]" << evolvedLF->getName() << "has become a mid developed life form.";
            break;
        case 3:
            evolvedLF = new HighDev_LFEntity(*lf);
            qDebug() << "[DestinyAdapter::evolveLFE]" << evolvedLF->getName() << "has become a high developed life form.";
            break;
        }
        ourJobHandler->replaceLF(lf, evolvedLF);
        delete lf;
        evolvedLF->inhabitPlanet(homeP, &rPos);
        for (int i = 0; i < knownByLFEs.size(); ++i)
            knownByLFEs[i]->addKnownLFE(evolvedLF);
    }
}

//******************************************************************************
//! Specific life form devolves by getting replaced with his lower developed form.
/*!
*	\param lf life form that devolves.
*	\return none.
*/

void DestinyAdapter::devolveLFE(LifeFormEntity* lf)
{
    if (lf)
    {
        LifeFormEntity* devolvedLF;
        PlanetEntity* homeP = lf->getHomePlanetEntity();
        CartesianCoordAdapter rPos = lf->getRelativePos();
        int ownDL = lf->getDevLvl();
        int newDL = (dist(mt) % NUM_OF_CONCRETE_LIFEFORMS) + 1;
        while (newDL > ownDL) newDL = (dist(mt) % NUM_OF_CONCRETE_LIFEFORMS) + 1;
        QString oldDLName;
        QVector<LifeFormEntity*> knownByLFEs;

        for (int i = 0; i < LFEs.size(); ++i)
            if (LFEs[i]->knows(lf))
                knownByLFEs.push_back(LFEs[i]);

        switch (ownDL)
        {
        case 1:
            oldDLName = "low developed";
            break;
        case 2:
            oldDLName = "mid developed";
            break;
        case 3:
            oldDLName = "high developed";
            break;
        }

        qDebug() << "[DestinyAdapter::devolveLFE]" << lf->getName() << "leaves his old" << oldDLName << "form behind and devolves.";
        for (QVector<LifeFormEntity*>::iterator it = LFEs.begin(); it != LFEs.end(); ++it)
            if (*it != lf)
                (*it)->forgetAboutLFE(lf);
		
        switch (newDL)
        {
        case 1:
            devolvedLF = new LowDev_LFEntity(*lf);
            qDebug() << "[DestinyAdapter::devolveLFE]" << devolvedLF->getName() << "has become a low developed life form.";
            break;
        case 2:
            devolvedLF = new MidDev_LFEntity(*lf);
            qDebug() << "[DestinyAdapter::devolveLFE]" << devolvedLF->getName() << "has become a mid developed life form.";
            break;
        case 3:
            devolvedLF = new HighDev_LFEntity(*lf);
            qDebug() << "[DestinyAdapter::devolveLFE]" << devolvedLF->getName() << "has become a high developed life form.";
            break;
        }
        ourJobHandler->replaceLF(lf, devolvedLF);
        delete lf;
        devolvedLF->inhabitPlanet(homeP, &rPos);
        for (int i = 0; i < knownByLFEs.size(); ++i) knownByLFEs[i]->addKnownLFE(devolvedLF);
    }
}

//******************************************************************************
//! Adds lf to the pool of life form instances.
/*!
*	\param lf life form that gets added.
*	\return none.
*/

void DestinyAdapter::addLFE(LifeFormEntity* lf)
{
    if (lf && !LFEs.contains(lf))
        LFEs.push_back(lf);
}

//******************************************************************************
//! Remove lf from the pool of life form instances.
/*!
*	\param lf life form that gets removed.
*	\return none.
*/

void DestinyAdapter::removeLFE(LifeFormEntity * lf)
{
    if (lf && LFEs.contains(lf))
        LFEs.removeOne(lf);
}

//******************************************************************************
//! Returns number of life forms that are actually active and initialised
/*!
*	\param none.
*	\return number of living life forms.
*/

unsigned long long DestinyAdapter::getNumberOfAliveLFEs()
{
    unsigned long long aliveLFECount = 0;
    for (int i = 0; i < LFEs.size(); i++)
        if (LFEs[i]->getHomePlanetEntity())
            aliveLFECount++;

    return aliveLFECount;
}

//******************************************************************************
//! Returns number of life forms that are queued up to be created.
/*!
*	\param none.
*	\return number of active mating jobs over all life forms.
*/

unsigned long long DestinyAdapter::getNumberOfUnbornLFEs()
{
    return LFMateJob::getMateJobCount();
}

//******************************************************************************
//! Returns number of life forms that died.
/*!
*	\param none.
*	\return counted number of life forms that have been killed.
*/

unsigned long long DestinyAdapter::getNumberOfDeadLFEs()
{
    return NumberOfDeadLFEs;
}

//******************************************************************************
//! Returns an instance to an uniformly randomly chosen life form from the pool of life forms
/*!
*	\param none.
*	\return pointer to randomly chosen life form.
*/

LifeFormEntity* DestinyAdapter::chooseRandomLFE()
{
    if (!LFEs.isEmpty())
    {
        LifeFormEntity* result = LFEs[dist(mt) % LFEs.size()];
        return result;
    }
    else return nullptr;
}

//******************************************************************************
//! Returns a randomly generated 4 letter long name
/*!
*	\param none.
*	\return generated name.
*/

QString DestinyAdapter::generateLFEName()
{
    char vowels[] = { 'a','e','i','o','u' };
    char rName[]{ (char)((dist(mt) % 26) + 65), vowels[dist(mt) % 5], (char)((dist(mt) % 26) + 97), (char)((dist(mt) % 26) + 97)};
    return QString(rName);
}

//******************************************************************************
//! Constructor of class DestinyAdapter
/*!
*	\param parent QT parent pointer.
*	\return none.
*/

DestinyAdapter::DestinyAdapter(QObject *parent) : QObject(parent)
{
    NumberOfDeadLFEs = 0;
    ourJobHandler = LFJobHandler::Instance(parent);
}

//******************************************************************************
//! Deconstructor of class DestinyAdapter

DestinyAdapter::~DestinyAdapter()
{
}
