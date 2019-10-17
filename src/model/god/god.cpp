//*************************************************************************
/** \file
 *  \brief Contains the implementation of class God.
 */

#include "god.h"
#include "../humanbreeder/human.h"
#include <ctime>
#include <unistd.h>

 //******************************************************************************
 /*!< Predefined name of god. */
char* God::name = "Thor";

//******************************************************************************
//! Constructor of class God
God::God() {}

//******************************************************************************
//! Destructor of class God
God::~God() {}

//******************************************************************************
//! Returns the name of god.
/*!
 *	\param none.
 *	\return The name of god.
 */
char* God::getName(void)
{
    return this->name;
}

//******************************************************************************
//! Creates a instance of a LowDev lifeform
/*!
 *	\param none.
 *	\return Instance of the new created lifeform.
 */
LowDev_LF* God::createLowDevLF(void)
{
    printf("[God::createLowDevLF]  %s created a low developed life form.\n", this->getName());
    return new LowDev_LF(this->getName());
}

//******************************************************************************
//! Creates a instance of a MidDev lifeform
/*!
 *	\param none
 *	\return Instance of the new created lifeform
 */
MidDev_LF* God::createMidDevLF(void)
{
    printf("[God::createMidDevLF]  %s created a mid developed life form.\n", this->getName());
    return new MidDev_LF(this->getName());
}

//******************************************************************************
//! Creates a instance of a HighDev lifeform
/*!
 *	\param none.
 *	\return Instance of the new created lifeform.
 */
HighDev_LF* God::createHighDevLF(void)
{
    printf("[God::createHighDevLF]  %s created a high developed life form.\n", this->getName());
    return new HighDev_LF(this->getName());
}

//******************************************************************************
//! Creates the destiny and universe. Main output/input routine.
/*!
 *	\param none.
 *	\return none.
 */
void God::createBigBang(void)
{
    HumanLifeChainIterator *iterator;
    HumanLifeChain         *list;
    HumanHandler           *handler;
    HumanHerold            *herold;
    Human                  *human;

    unsigned long           timer1 = 0;
    unsigned long           timer2 = 0;
    bool                    pause = false;
    int                     randTimes;
    int                     i;

    CartesianCoordAdapter coord1;

    ourDestiny = Destiny::getDestiny();
    ourUniverse = Universe::getUniverse();
	
    coord1 = CartesianCoordAdapter(0, 0, 1);

    ourUniverse->addNewPlanet(coord1);

    LF1 = *this->createLowDevLF();
    LF1.startLife(ourUniverse->getFirstPlanet());

    LF2 = *this->createMidDevLF();
    LF2.startLife(ourUniverse->getFirstPlanet());

    LF3 = *this->createHighDevLF();
    LF3.startLife(ourUniverse->getFirstPlanet());

    //*********************************************************

    //*** initialize the random numbers generator ***
    srand((unsigned)time(nullptr));
    //*** produce some random numbers because the generator is crap ***
    randTimes = int(10 * rand() / (RAND_MAX + 1.0));



    #pragma warning( push )
    #pragma warning( disable : 6031)
        for(i = 0; i < randTimes; i++) rand();
    #pragma warning( pop )

	printf("[God::createBigBang]  Clone Humans\n\n");

    herold = new HumanLifeHerold();
    herold->attachToSubject(HumanLifeChain::Instance());

    herold = new HumanDeathHerold();
    herold->attachToSubject(HumanLifeChain::Instance());

    handler = HumanHandler::Instance();

    //*** does not work - because there is not any living human ***
    handler->killOldest();

    // problematic block -> crash of program
    /*
	//*** build "EVA" ***
	handler->useClonePrototypeWoman();
	handler->cloneHuman();
	//*** kills the oldest human ***
	handler->killOldest();
	handler->cloneHuman();

	//*** build new human by having "sex"                ***
	//*** does not work - because there is no living man ***
	handler->createHumanNaturally();

	//*** build "ADAM" ***
	handler->useClonePrototypeMan();
	handler->cloneHuman();

	//*** build new human by having "sex" ***
	handler->createHumanNaturally();
	//*** build "" ***
	handler->cloneHuman();
    /*

	//*** build "" ***
	handler->useClonePrototypeWoman();
	handler->cloneHuman();

	//*** kills the oldest human ***
	handler->killOldest();

	//*** build "" ***
	handler->cloneHuman();
	//*** build new human by having "sex" ***
	handler->createHumanNaturally();
    */

    list = HumanLifeChain::Instance();
    iterator = new HumanLifeChainIterator(list);

    while(!iterator->isDone())
    {
        human = iterator->nextHuman();
        cout << "[God::createBigBang]  " << human->getEyeColor().data() << "\n";
    }

    while(true)
    {
        sleep(20);

        if(!pause)
        {
            // handle timer event 1
            if(timer1 < std::clock())
            {
                this->SimulateTimeStep();

                timer1 = std::clock() + rand() % 5000;
            }
            // handle timer event 2
            if(timer2 < std::clock())
            {
                printf("[God::createBigBang]  time of universe: %u\n", this->GetTimeOfUniverse());
                timer2 = std::clock() + 1000;
            }
        }
    }
}

//******************************************************************************
//! Simluates a single timestep - it is used for doing something...
/*!
 *	\param none.
 *	\return none.
 */
void God::SimulateTimeStep(void)
{
    printf("\n[God::SimulateTimeStep]  ---- new time step ----------------------------\n");
    if(ourUniverse)
        printf("[God::SimulateTimeStep]  time of universe: %u\n", GetTimeOfUniverse());

    printf("\n");

    ourDestiny->rendevouzTwoLF(&LF1, &LF2);
    ourDestiny->rendevouzTwoLF(&LF2, &LF3);

    //ourDestiny->createProblemForLifeForm(&LF1);
    ourDestiny->createProblemForLifeForm(&LF2);
    ourDestiny->createProblemForLifeForm(&LF3);
}

//******************************************************************************
//! Returns the time of the by god created universe.
/*!
 *	\param none.
 *	\return the time (DWORD).
 */
unsigned long God::GetTimeOfUniverse(void)
{
    return ourUniverse->getTime();
}

