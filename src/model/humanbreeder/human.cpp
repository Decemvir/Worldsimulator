//*************************************************************************
/** \file 
 *  \brief Contains the implementations of the classes
 *         Human, Subject, Woman, Man, HumanBreeder, CloneAdmin, HumanLifeChainElement,
 *         HumanLifeChain, HumanLifeChainIterator, OldestPartnerFinderStrategy,
 *         RandomPartnerFinderStrategy, PartnerFinder, HumanHerold, HumanLifeHerold,
 *         HumanDeathHerold, Death, HumanHandler.
 */

//#include <windows.h>
#include "human.h"

//******************************************************************************
//! Constructor of class Human.
Human::Human() 
{
    //choose eye color
    int colorNr = int( mPossibleEyeColorsLength * rand() / (RAND_MAX + 1.0) );

    mEyeColor = mPossibleEyeColors[colorNr];
    View* v1 = new View("this is a view");
    mMindWorld = OwnMW::get_Instance(v1,"highest");
    mMindWorld->ToWrite();
}

//******************************************************************************
//! Destructor of class Human.
Human::~Human() {}

//******************************************************************************
/*!< Number of eye colours. */
int Human::mPossibleEyeColorsLength = 4;
/*!< Array of names of eye colours. */
string Human::mPossibleEyeColors[4] = {"green", "blue", "brown", "grey"};

//******************************************************************************
//! Returns the eye color of the human.
/*!
 *  \param none.
 *  \return the eye color (string).
*/
string Human::getEyeColor(void) 
{
    return mEyeColor;
}

//******************************************************************************
//! Sets the eye color of the human
/*!
 *  \param the eye color (string).
 *  \return none.
 */
void Human::setEyeColor(string str) 
{
    mEyeColor = str;
}

//******************************************************************************
//! Attaches an Observer.
/*!
 *  \param an Observer.
 *  \return none.
 */
void Subject::attachObserver(Observer *obs) 
{
    mObservers.insert(mObservers.end(),obs);
}

//******************************************************************************
//! Detaches an Observer.
/*! 
 *  \param an instance of as Observer.
 *  \return none.
 */
void Subject::detachObserver(Observer *obs) 
{
    vector<Observer*>::iterator it = mObservers.begin();

    while (it!=mObservers.end())
    {
        if (*it==obs) {
            mObservers.erase(it);
            break;
        }

        it++;
    }
}

//******************************************************************************
//! Should be called when the Subject changes. Calls update() of all attached Observers.
/*! 
 *  \param none.
 *  \return none.
 */
void Subject::notifyObservers(void) 
{
    vector<Observer*>::iterator it = mObservers.begin();
    while ( it != mObservers.end() )
    {
        (*it)->update();
        it++;
    }
}

//******************************************************************************
//! Constructor of class Woman.
Woman::Woman() {}

//******************************************************************************
//! Clones a human and builds a Woman.
/*!
 *  \param none.
 *  \return instance of cloned Woman.
 */
Human *Woman::clone(void) 
{
    Woman *theClone = new Woman();
    theClone->setEyeColor( getEyeColor() );
    return theClone;
}

//******************************************************************************
//!  Creates a new Woman or Man by using a Man (having sex). The product is chosen randomly. Its the have sex and getting pregnant stuff.
/*!
 *  \param man is a pointer to an instance of the man class.
 *  \return an instance of a Human.
 */
Human *Woman::createHuman(Man *man) 
{
    //creates int between 0 and 1
    int genderChoose = int( 2 * rand() / (RAND_MAX + 1.0) );
    if (genderChoose == 1)
        return new Woman();
    else
        return new Man();
}

//******************************************************************************
//! Constructor of class Man.
Man::Man() {}

//******************************************************************************
//! Clones a human and builds a Man.
/*!
 *  \param none.
 *  \return an instance of a Human.
 */
Human *Man::clone(void) 
{
    Man *theClone = new Man();
    theClone->setEyeColor( getEyeColor() );
    return theClone;
}

//******************************************************************************
//! Constructor of class  HumanBreeder.
HumanBreeder::HumanBreeder() {}

//******************************************************************************
//! Returns clone of the Human set by setPrototype(Human *human).Adds the cloned Human to the HumanLifeChain..
/*!
 *  \param none.
 *  \return the created Human.
 */
Human *HumanBreeder::createClone(void) 
{
    if (!mPrototype)
        return nullptr;

    Human *clone = mPrototype->clone();
    HumanLifeChain *lifeChain = HumanLifeChain::Instance();
    lifeChain->addNewBorn(clone);
    return clone;
}

//******************************************************************************
//! Sets Human prototype to be cloned.
/*! 
 *  \param human prototype.
 *  \return none.
 */
void HumanBreeder::setPrototype(Human *human) 
{
    mPrototype = human;
}

//******************************************************************************
//! Creates new CloneAdmin. Use Instance() to get instance of CloneAdmin.
/*!
 *  \param none.
 *  \return The one and only CloneAdmin.
 */
CloneAdmin::CloneAdmin(void) 
{
    mBreeder        = new HumanBreeder();
    mPrototypeWoman = new Woman();
    mPrototypeMan   = new Man();
}

/*! Is set once, once CloneAdmin::Instance is called. This controls the restriction to number of CloneAdmin objects. */
CloneAdmin *CloneAdmin::mInstance = nullptr;

//******************************************************************************
//! Returns the single instance of CloneAdmin. Instantiates a HumanBreeder and a Woman and Man as "clone prototype".
/*!
 *  \param none.
 *  \return instance of CloneAdmin.
 */
CloneAdmin *CloneAdmin::Instance(void) 
{
    if (!mInstance) mInstance = new CloneAdmin();
    return mInstance;
}

//******************************************************************************
//! Let the HumanBreeder use the Woman as "clone prototype".
/*!
 *  \param none.
 *  \return none.
 */
void CloneAdmin::useClonePrototypeWoman(void) 
{
    //mBreeder->setPrototype(mPrototypeWoman);
}

//******************************************************************************
//! Let the HumanBreeder use the Man as "clone prototype".
/*!
 *  \param none.
 *  \return none.
 */
void CloneAdmin::useClonePrototypeMan(void) 
{
    //mBreeder->setPrototype(mPrototypeMan);
}

//******************************************************************************
//! Let the HumanBreeder clone the given "clone prototype".
/*!
 *  \param none.
 *  \return a pointer to a cloned Human.
 */
Human *CloneAdmin::createClone(void) 
{
    static Human *clone = mBreeder->createClone();
    return clone;
}

//******************************************************************************
//! Deletes a instance of Human
/*!
 *  \param none.
 *  \return none.
 */
void HumanLifeChainElement::deleteHuman(void)
{
    delete mHuman;
}

//******************************************************************************
//! Creates new HumanLifeChainElement. No empty element can exist..
/*!
 *  \param  human is the human to clone.
 *  \return a HumanLifeChainElement.
 */
HumanLifeChainElement::HumanLifeChainElement(Human *human) 
{
    mHuman = human;
    mNextElement = nullptr;
}

//******************************************************************************
//! Sets the next element of the chain.
/*!
 *  \param a pointer to a HumanLifeChainElement.
 *  \return none.
 */
void HumanLifeChainElement::setNextElement(HumanLifeChainElement *element) 
{
    mNextElement = element;
}

//******************************************************************************
//! Returns the next element of the chain.
/*!
 *  \param none.
 *  \return a pointer to a HumanLifeChainElement.
*/
HumanLifeChainElement *HumanLifeChainElement::getNextElement(void) 
{
    return mNextElement;
}

//******************************************************************************
//! Returns the Human given to the Constructor.
/*!
 *  \param none.
 *  \return Human given to the Constructor.
 */
Human *HumanLifeChainElement::getHuman(void) 
{
    return mHuman;
}

//******************************************************************************
//! Constructor of class HumanLifeChain
HumanLifeChain::HumanLifeChain() 
{
    mFirstElement=nullptr;
    mLastElement =nullptr;
}

//******************************************************************************
/*! Is set once, once HumanLifeChain::Instance is called. This controls the restriction to number of HumanLifeChain objects. */
HumanLifeChain *HumanLifeChain::mInstance = nullptr;

//******************************************************************************
//! Create and returns the single instance of HumanLifeChain (Pattern Singleton)
/*!
 *  \param none.
 *  \return instance of HumanLifeChain.
 */
HumanLifeChain *HumanLifeChain::Instance(void) 
{
    if (!mInstance)
        mInstance = new HumanLifeChain();

    return mInstance;
}

//******************************************************************************
//! Adds an Human to the list. It will be put on end of list. Creates an HumanLifeChainElement to store the Human.
/*!
 *  \param a pointer to Human.
 *  \return none.
 */
void HumanLifeChain::addNewBorn(Human *human) 
{
    HumanLifeChainElement *element = new HumanLifeChainElement(human);
    //test if no element in list
    if (mLastElement)
        mLastElement->setNextElement(element);
    else
        mFirstElement = element;

    mLastElement = element;
    notifyObservers();
}

//******************************************************************************
//! Returns the first element of list. It contains the oldest Human.
/*!
 *  \param none.
 *  \return none.
 */
void HumanLifeChain::removeOldest(void) 
{
    HumanLifeChainElement *newFirstElement;
    //only one element in list
    if (mFirstElement == mLastElement)
        mLastElement = nullptr;

    if (mFirstElement)
    {
        newFirstElement = mFirstElement->getNextElement();
        Human *human = mFirstElement->getHuman();
        //delete human;
        delete mFirstElement;
        mFirstElement = newFirstElement;
    }

    notifyObservers();
}

//******************************************************************************
//! Returns the first element of list. It contains the oldest Human.
/*!
 *  \param none.
 *  \return a HumanLifeChainElement (the oldest Human).
 */
HumanLifeChainElement *HumanLifeChain::firstElement(void) 
{
    return mFirstElement;
}

//******************************************************************************
//! Returns the last element of list. It contains the youngest Human.
/*!
 *  \param none.
 *	\return The youngest Human.
 */
HumanLifeChainElement *HumanLifeChain::lastElement(void) 
{
    return mLastElement;
}

//******************************************************************************
//! Creates new HumanLifeChainIterator for the given HumanLifeChain. Sets current element to first element..
/*!
 *  \param a HumanLifeChain.
 */
HumanLifeChainIterator::HumanLifeChainIterator(HumanLifeChain *list) 
{
    mList = list;
    mCurrentElement = mList->firstElement();
}

//******************************************************************************
//! Returns the first stored Human and sets pointer to next elemet of list.
/*!
 *  \param none.
 *	\return oldest Human.
 */
Human *HumanLifeChainIterator::firstHuman(void) 
{
    mCurrentElement = mList->firstElement();
    return nextHuman();
}

//******************************************************************************
//! Returns stored Human of current element and sets current element to
/*!
 *  \param none.
 *	\return next element of the list (type Human).
 */
Human *HumanLifeChainIterator::nextHuman(void) 
{
    Human *human = mCurrentElement->getHuman();
    mCurrentElement = mCurrentElement->getNextElement();
    return human;
}

//******************************************************************************
//! Indicates the end of the list
/*!
 *  \param none.
 *	\return true if current element is in boundaries of list, false if current element points behind the end of list.
 */
bool HumanLifeChainIterator::isDone(void) 
{
    return mCurrentElement == nullptr;
}

//******************************************************************************
//! Searches the HumanLifeChain for the oldest Woman and Man.
//! It finds partners with similar age.
//! It calls createHuman() of Woman giving her the Man.
//! That creates an Human (Woman or Man randomly).
//! The Human is put into the HumanLifeChain and returned.
//! If no partners are found 0 is returned..
/*!
 *  \param none.
 *	\return instance of Human.
 */
Human *OldestPartnerFinderStrategy::searchPartnersAndCreateHuman(void) 
{
    HumanLifeChainIterator *it = new HumanLifeChainIterator(HumanLifeChain::Instance());
    Human *human = nullptr;
    Woman *woman = nullptr;
    Man   *man = nullptr;
    Woman *femalePartner = nullptr;
    Man   *malePartner = nullptr;
    bool  partnersFound = false;

    //more Elements in List or (Woman and Man found)
    while (( ! it->isDone()) && ( ! partnersFound))
    {
        human = it->nextHuman();
        woman = dynamic_cast<Woman*>(human);
        if (woman)
            femalePartner = woman;

        man = dynamic_cast<Man*>(human);
        if (man)
            malePartner = man;

        if (femalePartner && malePartner)
            partnersFound = true;
        
    }

    if (partnersFound) {
        human = woman->createHuman(man);
        HumanLifeChain *lifeChain = HumanLifeChain::Instance();
        lifeChain->addNewBorn(human);
        return human;
    }

    return nullptr;
}

//******************************************************************************
//! Searches the HumanLifeChain at random for a Woman and a Man.
//! It calls createHuman() of Woman giving her the Man.
//! That creates an Human (Woman or Man randomly).
//! The Human is put into the HumanLifeChain and returned.
//! If no partners are found 0 is returned..
/*!
 *  \param none.
 *	\return instance of Human.
 */
Human *RandomPartnerFinderStrategy::searchPartnersAndCreateHuman(void) 
{
    HumanLifeChainIterator *it = new HumanLifeChainIterator(HumanLifeChain::Instance());
    Human *human = nullptr;
    Woman *woman = nullptr;
    Man *man = nullptr;
    Woman *femalePartner = nullptr;
    Man *malePartner = nullptr;
    bool partnersFound = false;
    // get number of Humans in list
    int numberInList = 0;

    while ( ! it->isDone() )
    {
        it->nextHuman();
        numberInList++;
    }

    // specifies number of looks into the list
    int number = numberInList;
    // look number of times into the list to find a Woman and a Man
    for (int i = 0; i < number; i++)
    {
        // create random number in range of list
        int randNr = int( numberInList * rand() / (RAND_MAX + 1.0) );
        // get Human at position randNr
        human = it->firstHuman();

        for (int j = 0; j < randNr; j++)
            human = it->nextHuman();
        
        woman = dynamic_cast<Woman*>(human);
        if (woman)
            femalePartner = woman;
    
        man = dynamic_cast<Man*>(human);
        if (man)
            malePartner = man;
    
        if (femalePartner && malePartner)
            partnersFound = true;
       
        if (partnersFound)
        {
            human = woman->createHuman(man);
            HumanLifeChain *lifeChain = HumanLifeChain::Instance();
            lifeChain->addNewBorn(human);
            return human;
        }
    }
    // if no partners found
    return nullptr;
}

//******************************************************************************
//! Constructor of class PartnerFinder.
PartnerFinder::PartnerFinder() 
{
    mStrategy = nullptr;
}

//******************************************************************************
//! Calls searchPartnersAndCreateHuman() from the referenced PartnerFinderStrategy.
//! The strategy searches the HumanLifeChain for a Woman and a Man and creates
//! a Human with them. It will be returned.
//! If no PartnerFinderStrategy is referenced 0 is returned..
/*!
 *  \param none.
 *	\return instance of Human.
 */
Human *PartnerFinder::searchPartnersAndCreateHuman(void) 
{
    if (!mStrategy)
        return nullptr;
    else
        return mStrategy->searchPartnersAndCreateHuman();
}

//******************************************************************************
//! Sets the PartnerFinderStrategy..
/*!
 *  \param a pointer to a PartnerFinderStrategy.
 *	\return none.
 */
void PartnerFinder::setPartnerFinderStrategy(PartnerFinderStrategy* strategy) 
{
    mStrategy = strategy;
}

//******************************************************************************
//! Attach this to the given HumanLifeChain.
/*! 
 *  \param a HumanLifeChain.
 *	\return none.
 */
void HumanHerold::attachToSubject(HumanLifeChain *chain) 
{
    mChain = chain;
    mChain->attachObserver(this);
}

//******************************************************************************
//! Constructor of class HumanHerold
HumanLifeHerold::HumanLifeHerold(void) 
{
    mLastNewBorn = nullptr;
}

//******************************************************************************
//! Attaches the obsrever to a subject.
/*!
 *  \param a HumanLifeChain.
 *  \return none.
 */
void HumanLifeHerold::attachToSubject(HumanLifeChain *chain) 
{
    HumanHerold::attachToSubject(chain);
    mLastNewBorn = chain->lastElement()->getHuman();
}

//******************************************************************************
//! Should be called by the HumanLifeChain when it changes.
//! If a new Human is put into the HumanLifeChain since the last update()
//! it is considered newborn and print to the console..
/*! 
 *  \param none.
 *	\return none.
 */
void HumanLifeHerold::update(void) 
{
    HumanLifeChain        *chain = HumanLifeChain::Instance();
    HumanLifeChainElement *element = mChain->lastElement();
    Human                 *human = nullptr;

    if (element != nullptr) human = element->getHuman();

    if (human != mLastNewBorn && human != nullptr)
    {
        Woman *woman = nullptr;
        Man   *man = nullptr;
        string message = "Human";

        woman = dynamic_cast<Woman*>(human);
        if (woman)
            message = "Woman";
   
        man = dynamic_cast<Man*>(human);
        if (man)
            message = "Man";

        cout << "[HumanLifeHerold::update]  A " << human->getEyeColor().data() <<"eyed "<< message.data() <<" is born!\n";
    }

    mLastNewBorn = human;
}

//******************************************************************************
//! Constructor of class HumanDeathHerold.
HumanDeathHerold::HumanDeathHerold() 
{
    mNextToDie = nullptr;
}

//******************************************************************************
//! Attaches an observer to a subject.
/*!
 *	\param a an integer.
 *	\return none.
 */
void HumanDeathHerold::attachToSubject(HumanLifeChain *chain) 

{
    HumanHerold::attachToSubject(chain);
    mNextToDie = chain->firstElement()->getHuman();
}

//******************************************************************************
//! Should be called by the HumanLifeChain when it changes.
//! If a Human left the HumanLifeChain since the last update() it is
//! considered died and print to the console. Only the oldest Human can die..
/*! 
 *  \param none.
 *	\return none.
 */
void HumanDeathHerold::update(void) 
{
    HumanLifeChain        *chain   = HumanLifeChain::Instance();
    HumanLifeChainElement *element = mChain->firstElement();
    Human                 *human   = nullptr;
    Woman                 *woman   = nullptr;
    Man                   *man     = nullptr;

    if (element)
        human = element->getHuman();

    //if mNextToDie is someoneelse than the oldest (human), he must have died
    //if mNextToDie is 0, nobody was living before, so nobody could have died
    //mNextToDie is already deleted, it cant be read
    if (human != mNextToDie && mNextToDie)
    {
        cout << "[HumanDeathHerold::update]  A " << mMessage.data() << " has died.\n";
    }

    mNextToDie = human;
    woman = dynamic_cast<Woman*>(human);
    if (woman)
        mMessage = "Woman";

    man = dynamic_cast<Man*>(human);
    if (man)
        mMessage = "Man";
    }

//******************************************************************************
//! Constructor of Death. Use Instance() to get instance of Death.
Death::Death() {}

//******************************************************************************
/*! Is set once, once Death::Instance is called. This controls the restriction to number of Death objects. */
Death *Death::mInstance = nullptr;

//******************************************************************************
//! Returns the single Instance of Death.
/*! 
 *  \param none.
 *	\return instance of Death.
 */
Death *Death::Instance(void) 
{
    if (!mInstance)
        mInstance = new Death();

    return mInstance;
}

//******************************************************************************
//! Deletes the oldest Human and the storing \n HumanLifeChainElement from HumanLifeChain.
/*!
 *  \param none.
 *	\return none.
 */
void Death::killOldest(void) 
{
    HumanLifeChain::Instance()->removeOldest();
}

//******************************************************************************
//! Constructor of HumanHandler. Use Instance() to get instance of HumanHandler.
HumanHandler::HumanHandler() {}

//******************************************************************************
/*! Is set once, once HumanHandler::Instance is called. This controls the restriction to number of HumanHandler objects. */
HumanHandler *HumanHandler::mInstance = nullptr;

//******************************************************************************
//! Returns the single instance of HumanHandler.
/*! 
 *  \param none.
 *	\return single instance of HumanHandler.
 */
HumanHandler *HumanHandler::Instance(void) 
{
    if (!mInstance)
        mInstance = new HumanHandler();

    return mInstance;
}

//******************************************************************************
//! Sets the "clone prototype" to Woman. See also CloneAdmin.
/*!
 *  \param none.
 *	\return none.
 */
void HumanHandler::useClonePrototypeWoman(void) 
{
    CloneAdmin *cloneadmin;

    cloneadmin=CloneAdmin::Instance();
    if (cloneadmin)
        cloneadmin->useClonePrototypeWoman();
}

//******************************************************************************
//! Sets the "clone prototype" to Man. See also CloneAdmin.
/*!
 *  \param none.
 *	\return none.
 */
void HumanHandler::useClonePrototypeMan(void) 
{
    CloneAdmin *cloneadmin;

    cloneadmin=CloneAdmin::Instance();
    if (cloneadmin)
        cloneadmin->useClonePrototypeMan();
}

//******************************************************************************
//! Clones Human. See also CloneAdmin.
/*!
 *  \param none.
 *	\return none.
 */
void HumanHandler::cloneHuman(void) 
{
    CloneAdmin::Instance()->createClone();
}

//******************************************************************************
//! Creates a Human - having sex. See also PartnerFinder.
/*!
 *  \param none.
 *	\return none.
 */
void HumanHandler::createHumanNaturally(void) 
{
    PartnerFinder *finder = new PartnerFinder();
    // the strategy OldestPartnerFinderStrategy could also be used here
    PartnerFinderStrategy *strategy = new RandomPartnerFinderStrategy();

    finder->setPartnerFinderStrategy(strategy);
    Human *human = finder->searchPartnersAndCreateHuman();
}

//******************************************************************************
//! Kills oldest Human. See also Death.
/*!
 *  \param none.
 *	\return none.
 */
void HumanHandler::killOldest(void) 
{
    Death::Instance()->killOldest();
}
