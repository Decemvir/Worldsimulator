//*************************************************************************
/** \file
*  \brief Contains the implementation of class GodAdapter.
*/

#include "godAdapter.h"
#include <QString>
#include <random>

static std::random_device rd;
static std::mt19937_64 mt(rd());
static std::uniform_int_distribution<unsigned int> dist(0);

char* GodAdapter::godName = name;
unsigned int GodAdapter::maxNumberOfLFEs = 50;
unsigned int GodAdapter::minNumberOfLFEs = 10;

//******************************************************************************
//! Constructor of class GodAdapter
/*!
*	\param parent QT parent pointer.
*	\param godName name of the god.
*	\return none.
*/

GodAdapter::GodAdapter(QObject *parent, char* godname) : QObject(parent)
{
    if (godname) godName = godname;
    ourDestinyAdapter = DestinyAdapter::Instance(parent);
    ourUniverseEntity = UniverseEntity::Instance(parent);
    initialised = false;
    planetToObserve = nullptr;
}

//******************************************************************************
//! Deconstructor of class GodAdapter

GodAdapter::~GodAdapter()
{
    ourUniverseEntity->destroy();
}

//******************************************************************************
//! Creates predefined universe 
/*!
*	\param none.
*	\return none.
*/

void GodAdapter::createBigBang()
{
    if(!initialised)
    {
        PlanetEntity* mercury	= new PlanetEntity(parent(), "Mercury",	CartesianCoordAdapter(M_PI / 2, M_PI / 1.2, 1.3));
        PlanetEntity* venus		= new PlanetEntity(parent(), "Venus",	CartesianCoordAdapter(M_PI / 2, M_PI / 1.2, 1.6));
        PlanetEntity* earth		= new PlanetEntity(parent(), "Earth",	CartesianCoordAdapter(M_PI / 2, M_PI / 1.2, 2.1));
        PlanetEntity* moon		= new PlanetEntity(parent(), "Moon",	CartesianCoordAdapter(M_PI / 2, M_PI / 1.2, 0.15));
        PlanetEntity* mars		= new PlanetEntity(parent(), "Mars",	CartesianCoordAdapter(M_PI / 2, M_PI / 1.2, 2.5));
        PlanetEntity* phobos	= new PlanetEntity(parent(), "Phobos",	CartesianCoordAdapter(M_PI / 2, M_PI / 1.2, 0.1));
        PlanetEntity* deimos	= new PlanetEntity(parent(), "Deimos",	CartesianCoordAdapter(M_PI / 2, M_PI / 1.2, 0.15));
        PlanetEntity* jupiter	= new PlanetEntity(parent(), "Jupiter",	CartesianCoordAdapter(M_PI / 2, M_PI / 1.2, 4.5));
        PlanetEntity* saturn	= new PlanetEntity(parent(), "Saturn",	CartesianCoordAdapter(M_PI / 2, M_PI / 1.2, 7.0));
        PlanetEntity* uranus	= new PlanetEntity(parent(), "Uranus",	CartesianCoordAdapter(M_PI / 2, M_PI / 1.2, 7.7));
        PlanetEntity* neptune	= new PlanetEntity(parent(), "Neptune",	CartesianCoordAdapter(M_PI / 2, M_PI / 1.2, 8.4));
        PlanetEntity* triton    = new PlanetEntity(parent(), "Triton",  CartesianCoordAdapter(M_PI / 1.2, M_PI / 1.7, 0.2));

        PlanetEntity* saturnRing1 = new PlanetEntity(parent(), "SaturnRing1", CartesianCoordAdapter(M_PI / 1.5, M_PI / 1.2, 0.27));
        PlanetEntity* saturnRing2 = new PlanetEntity(parent(), "SaturnRing2", CartesianCoordAdapter(M_PI / 1.5, M_PI / 1.2, 0.28));
        PlanetEntity* saturnRing3 = new PlanetEntity(parent(), "SaturnRing3", CartesianCoordAdapter(M_PI / 1.5, M_PI / 1.2, 0.29));
        PlanetEntity* saturnRing4 = new PlanetEntity(parent(), "SaturnRing4", CartesianCoordAdapter(M_PI / 1.5, M_PI / 1.2, 0.3));
        PlanetEntity* saturnRing5 = new PlanetEntity(parent(), "SaturnRing5", CartesianCoordAdapter(M_PI / 1.5, M_PI / 1.2, 0.31));
        PlanetEntity* saturnRing6 = new PlanetEntity(parent(), "SaturnRing6", CartesianCoordAdapter(M_PI / 1.5, M_PI / 1.2, 0.32));
	
        mercury->setTextureFileName("mercury.jpg");
        venus->setTextureFileName("venus.jpg");
        earth->setTextureFileName("earth.jpg");
        moon->setTextureFileName("moon.jpg");
        mars->setTextureFileName("mars.jpg");
        phobos->setTextureFileName("fictional1.jpg");
        deimos->setTextureFileName("fictional2.jpg");
        jupiter->setTextureFileName("jupiter.jpg");
        saturn->setTextureFileName("saturn.jpg");
        uranus->setTextureFileName("uranus.jpg");
        neptune->setTextureFileName("neptune.jpg");
        triton->setTextureFileName("fictional3.jpg");

        earth->addSatellite(moon);
        mars->addSatellite(phobos);
        mars->addSatellite(deimos);
        neptune->addSatellite(triton);

        saturn->addSatellite(saturnRing1);
        saturn->addSatellite(saturnRing2);
        saturn->addSatellite(saturnRing3);
        saturn->addSatellite(saturnRing4);
        saturn->addSatellite(saturnRing5);
        saturn->addSatellite(saturnRing6);

        mercury->setVelocityInOrbit(62);
        venus->setVelocityInOrbit(40.7);
        earth->setVelocityInOrbit(32);
        moon->setVelocityInOrbit(95);
        mars->setVelocityInOrbit(22.1);
        phobos->setVelocityInOrbit(96);
        deimos->setVelocityInOrbit(80);
        jupiter->setVelocityInOrbit(4);
        saturn->setVelocityInOrbit(2.5);
        uranus->setVelocityInOrbit(2.0);
        neptune->setVelocityInOrbit(0.1);
        triton->setVelocityInOrbit(97);

        mercury->setOwnRotVelocity(0.1);
        venus->setOwnRotVelocity(-0.15);
        earth->setOwnRotVelocity(0.5);
        moon->setOwnRotVelocity(0.65);
        mars->setOwnRotVelocity(0.5);
        phobos->setOwnRotVelocity(0.6);
        deimos->setOwnRotVelocity(0.7);
        jupiter->setOwnRotVelocity(0.52);
        saturn->setOwnRotVelocity(0.7);
        uranus->setOwnRotVelocity(-0.8);
        neptune->setOwnRotVelocity(0.9);
        triton->setOwnRotVelocity(1.1);

        mercury->setPlanetRadius(0.05);
        venus->setPlanetRadius(0.095);
        earth->setPlanetRadius(0.1);
        moon->setPlanetRadius(0.035);
        mars->setPlanetRadius(0.06);
        phobos->setPlanetRadius(0.02);
        deimos->setPlanetRadius(0.025);
        jupiter->setPlanetRadius(0.4);
        saturn->setPlanetRadius(0.25);
        uranus->setPlanetRadius(0.2);
        neptune->setPlanetRadius(0.19);
        triton->setPlanetRadius(0.025);

        saturnRing1->setPlanetRadius(0);
        saturnRing2->setPlanetRadius(0);
        saturnRing3->setPlanetRadius(0);
        saturnRing4->setPlanetRadius(0);
        saturnRing5->setPlanetRadius(0);
        saturnRing6->setPlanetRadius(0);

        SolarSystemEntity* solarSystem = new SolarSystemEntity(parent(), CartesianCoordAdapter(0, 0, 0));
        solarSystem->add(mercury);
        solarSystem->add(venus);
        solarSystem->add(earth);
        solarSystem->add(mars);
        solarSystem->add(jupiter);
        solarSystem->add(saturn);
        solarSystem->add(uranus);
        solarSystem->add(neptune);

        ourUniverseEntity->add(solarSystem);

        LifeFormEntity* LFE1 = createLowDevLFE(parent());
        LifeFormEntity* LFE2 = createMidDevLFE(parent());
        LifeFormEntity* LFE3 = createHighDevLFE(parent());

        earth->addInhabitant(LFE1);
        earth->addInhabitant(LFE2);
        earth->addInhabitant(LFE3);

        planetToObserve = earth;

        initialised = true;
    }
}

//******************************************************************************
//! Returns name of the god
/*!
*	\param none.
*	\return name of the god.
*/

char * GodAdapter::getName()
{
    return godName;
}

//******************************************************************************
//! Challenges random life forms with a random task (gets called in a random amount of time)
/*!
*	\param none.
*	\return none.
*/

void GodAdapter::challengeLFEs()
{
    if(initialised)
    {
        qDebug() << "\n[GodAdapter::challengeLFEs]  -------------- GOD CHALLENGES RANDOM BELIEVERS --------------";
        qDebug() << "[GodAdapter::challengeLFEs] TIME OF UNIVERSE:" << ourUniverseEntity->getTimeinTicks();
        qDebug() << "[GodAdapter::challengeLFEs] ALIVE:" << ourDestinyAdapter->getNumberOfAliveLFEs()
                                             << "UNBORN:" << ourDestinyAdapter->getNumberOfUnbornLFEs()
                                             << "DEAD:" << ourDestinyAdapter->getNumberOfDeadLFEs();
	
        QVector<LifeFormEntity*> rLF;
        rLF.resize(2);

        while (rLF[0] == rLF[1])
        {
            rLF[0] = ourDestinyAdapter->chooseRandomLFE();
            rLF[1] = ourDestinyAdapter->chooseRandomLFE();
        }

        switch (dist(mt) % 10)
        {
        case 0:
        case 1:
        case 2:
            if (ourDestinyAdapter->getNumberOfAliveLFEs() + ourDestinyAdapter->getNumberOfUnbornLFEs() < maxNumberOfLFEs)
            {
                qDebug() << "[GodAdapter::challengeLFEs]"  << rLF[0]->getName() << "and" << rLF[1]->getName() << "were chosen to mate." << endl;
                ourDestinyAdapter->mateTwoLFE(rLF[0], rLF[1]);
            } else
                qDebug() << "[GodAdapter::challengeLFEs]" << rLF[0]->getName() << "and" << rLF[1]->getName() << "were chosen to mate but there are too many life forms on the planet." << endl;
            break;
        case 3:
        case 4:
            qDebug() << "[GodAdapter::challengeLFEs]" << rLF[0]->getName() << "and" << rLF[1]->getName() << "were chosen to meet." << endl;
            ourDestinyAdapter->rendevouzTwoLFEs(rLF[0], rLF[1]);
            break;
        case 5:
            if(ourDestinyAdapter->getNumberOfAliveLFEs() > minNumberOfLFEs)
            {
                qDebug() << "[GodAdapter::challengeLFEs]" << rLF[0]->getName() << "was chosen to die." << endl;
                ourDestinyAdapter->killLFE(rLF[0]);
            }
            else if (ourDestinyAdapter->getNumberOfAliveLFEs() + ourDestinyAdapter->getNumberOfUnbornLFEs() < maxNumberOfLFEs)
            {
                qDebug() << "[GodAdapter::challengeLFEs]" << rLF[0]->getName() << "was chosen to die but was not killed due to the lack of life forms." << endl;
                qDebug() << "[GodAdapter::challengeLFEs] Instead" << rLF[0]->getName() << "was chosen to mate with" << rLF[1]->getName();
                ourDestinyAdapter->mateTwoLFE(rLF[0], rLF[1]);
            }
            break;
        case 6:
            qDebug() << "[GodAdapter::challengeLFEs]" << rLF[0]->getName() << "was chosen to evolve." << endl;
            ourDestinyAdapter->evolveLFE(rLF[0]);
            break;
        case 7:
            qDebug() << "[GodAdapter::challengeLFEs]" << rLF[0]->getName() << "was chosen to devolve." << endl;
            ourDestinyAdapter->devolveLFE(rLF[0]);
            break;
        case 8:
        case 9:
            qDebug() << "[GodAdapter::challengeLFEs]" << rLF[0]->getName() << "was chosen to solve a problem." << endl;
            ourDestinyAdapter->createProblemForLFE(rLF[0]);
            break;
        }
    }
}

//******************************************************************************
//! Implements inherited god function for compatibility 
/*!
*	\param none.
*	\return none.
*/

void GodAdapter::SimulateTimeStep()
{
    challengeLFEs();
}

//******************************************************************************
//! Returns universe time
/*!
*	\param none.
*	\return universe time.
*/

unsigned long GodAdapter::GetTimeOfUniverse()
{
    return ourUniverseEntity->getTime();
}

//******************************************************************************
//! Returns "artificial" low developed life form with random name
/*!
*	\param parent QT parent pointer.
*	\return new LowDev_LFEntity.
*/

LowDev_LFEntity* GodAdapter::createLowDevLFE(QObject *parent)
{
    const char* lfName = qstrdup(qPrintable(ourDestinyAdapter->generateLFEName()));
    qDebug() << "[GodAdapter::createLowDevLFE]" << getName() << "created a low developed life form by the name of" << lfName;
    return new LowDev_LFEntity(parent, lfName, name);
}

//******************************************************************************
//! Returns "artificial" mid developed life form with random name
/*!
*	\param parent QT parent pointer.
*	\return new MidDev_LFEntity.
*/

MidDev_LFEntity* GodAdapter::createMidDevLFE(QObject *parent)
{
    const char* lfName = qstrdup(qPrintable(ourDestinyAdapter->generateLFEName()));
    qDebug() << "[GodAdapter::createMidDevLFE]" << getName() << "created a mid developed life form by the name of" << lfName;
    return new MidDev_LFEntity(parent, lfName, name);
}

//******************************************************************************
//! Returns "artificial" high developed life form with random name
/*!
*	\param parent QT parent pointer.
*	\return new HighDev_LFEntity.
*/

HighDev_LFEntity* GodAdapter::createHighDevLFE(QObject *parent)
{
    const char* lfName = qstrdup(qPrintable(ourDestinyAdapter->generateLFEName()));
    qDebug() << "[GodAdapter::createHighDevLFE]" << getName() << "created a high developed life form by the name of" << lfName;
    return new HighDev_LFEntity(parent, lfName, name);
}

//******************************************************************************
//! Returns true if the big bang already happened
/*!
*	\param none.
*	\return true if initialised.
*/

bool GodAdapter::isInitialised()
{
    return initialised;
}

//******************************************************************************
//! Returns predefined planet that should be observed
/*!
*	\param none.
*	\return planet to observe.
*/

PlanetEntity * GodAdapter::getPlanetToObserve()
{
    return planetToObserve;
}

//******************************************************************************
//! Sets min as minimum number of life forms
/*!
*	\param minimum.
*	\return none.
*/

void GodAdapter::setMinNumberOfLFs(unsigned int min)
{
    if (min < 2)
        minNumberOfLFEs = 2;
    else
        minNumberOfLFEs = min;
}

//******************************************************************************
//! Sets max as maximum number of life forms
/*!
*	\param maximum.
*	\return none.
*/

void GodAdapter::setMaxNumberOfLFs(unsigned int max)
{
    if (max < minNumberOfLFEs)
        maxNumberOfLFEs = minNumberOfLFEs;
    else
        maxNumberOfLFEs = max;
}


