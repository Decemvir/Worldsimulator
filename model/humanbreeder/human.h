//******************************************************************************
/** \file 
 *  \brief Contains the declarations of the classes 
 *         Human, Observer, Subject, Man, Woman, HumanBreeder, 
 *  	   HumanLifeChainElement, HumanLifeChain, HumanLifeChainIterator,
 *         CloneAdmin, PartnerFinderStrategy, OldestPartnerFinderStrategy, 
 *  	   RandomPartnerFinderStrategy, PartnerFinder, HumanHerold,
 *         HumanLifeHerold, HumanDeathHerold, Death, HumanHandler.
 */

#include <iterator>
#include <ctime>
#include "../implementations.h"

using namespace std;

//******************************************************************************
/*! \class Human
 *  \ingroup PrototypeTE IteratorTE
 *  \brief Member of pattern <b>Prototype</b> as <b>Prototype</b>. 
 *         Subclasses can be clonable ConcretePrototypes.\n
 *         Member of pattern <b>Iterator</b> as <b></b>.
 */
class Human
{
    public:
      Human();
      ~Human();
      virtual Human *clone() = 0;
      string        getEyeColor();
      void          setEyeColor(string str);
    private:
      OwnMW         *mMindWorld;
      static int    mPossibleEyeColorsLength;
      static string mPossibleEyeColors[];
      string        mEyeColor;
};

//******************************************************************************
/*! \class Observer
 *  \ingroup ObserverTE
 *  \brief Member of pattern <b>Observer</b> as <b>Observer</b>.
 *         Observes a Subject. Can be attached to it. Is notified by the observed
 *         Subject when it changes. Then update() is called.
 */
class Observer
{
    public:
      /*! Should be called by the observed Subject when it changes. */
      virtual void update() = 0;
};

//******************************************************************************
/*! \class Subject
 *  \ingroup ObserverTE
 *  \brief Member of pattern <b>Observer</b> as <b>Subject</b>. Can be observed.
 *         Observers can be attached and detached. When the Subject changes
 *         notifyObservers() should be called.
 */
class Subject
{
    public:
      virtual void attachObserver(Observer *obs);
      virtual void detachObserver(Observer *obs);
      virtual void notifyObservers();
    private:
      /*! Contains the observers.*/
      vector<Observer*> mObservers;
};

//******************************************************************************
/*! \class Man
 *  \ingroup PrototypeTE
 *  \brief Member of pattern <b>Prototype</b> as <b>ConcretePrototype</b>.
 *         Can be cloned to create new Man Objects.
 */
class Man : virtual public Human
{
    public:
      Man();
      Human *clone();
};

//******************************************************************************
/*! \class Woman
 *  \ingroup PrototypeTE
 *  \brief Member of pattern <b>Prototype</b> as <b>ConcretePrototype</b>.
 *         Can be cloned to create new Woman Objects with the same Properties.
 */
class Woman : virtual public Human
{
    public:
      Woman();
      Human *clone();
      Human *createHuman(Man *man);
};

//******************************************************************************
/*! \class HumanBreeder
 *  \ingroup PrototypeTE
 *  \brief Member of pattern <b>Prototype</b> as <b>Client</b>. 
 *         For cloning of a "Prototype" Human.
 *         The Human to clone can be set and cloned as often as desired.
 */
class HumanBreeder
{
    public:
      HumanBreeder();
      Human *createClone();
      void  setPrototype(Human *human);
    private:
      /*! The prototype to be cloned. */
      Human *mPrototype;
};

//******************************************************************************
/*! \class HumanLifeChainElement
 *  \ingroup IteratorTE SingletonTE
 *  \brief Member of pattern <b>Singleton</b>.\n
 *         Member of pattern <b>Iterator</b>. 
 *         Element of the HumanLifeChain. Stores one Human.
 *         Stores a pointer to the next element of the chain.
 */
class HumanLifeChainElement
{
    public:
      HumanLifeChainElement(Human *human);
      void                  setNextElement(HumanLifeChainElement *element);
      HumanLifeChainElement *getNextElement();
      Human                 *getHuman();
      void                  deleteHuman();
    private:
      //! Stores the next element of the chain.
      HumanLifeChainElement *mNextElement;
      //! Stores the Human given to the Constructor.
      Human                 *mHuman;
};

//******************************************************************************
/*! \class HumanLifeChain
 *  	\ingroup IteratorTE ObserverTE SingletonTE
 *  	\brief Member of pattern <b>Singleton</b>.\n
 *  	       Member of pattern <b>Observer</b> as <b>ConcreteSubject</b>.\n
 *  	       Member of pattern <b>Iterator</b>. Is the list of Humans.
 *  	       All created Humans should be put into the List.
 *             Exceptions are clone prototypes for example. They are no "real" Humans.
 *             Extends Subject, so Observers can be attached.
 *             It will notify all Observers if an Human has been added or removed.
 *             It's the List for the Iterator HumanLifeChainIterator.
 *             Can exist only one time. This is realised using the Singleton Pattern.
 */
class HumanLifeChain : public Subject
{
    public:
      static HumanLifeChain *Instance();
      void   addNewBorn(Human *human);
      void   removeOldest();
    
      HumanLifeChainElement *firstElement();
      HumanLifeChainElement *lastElement();
    protected:
      HumanLifeChain();
    private:
      /*! Stores the single instance of HumanLifeChain. */
      static HumanLifeChain* mInstance;
      /*! Stores the first element of list. It contains the oldest Human. */
      HumanLifeChainElement *mFirstElement;
      /*! Stores the last element of list. It contains the youngest Human. */
      HumanLifeChainElement *mLastElement;
};

//******************************************************************************
/*! \class HumanLifeChainIterator
 * 	\ingroup IteratorTE
 *  \brief Member of pattern <b>Iterator</b> as <b>ConcreteIterator</b>. 
 *         Iterator for HumanLifeChain.
 *  
 *         Stores the List and the current element.
 *         Changing the List while using the Iterator can cause Problems.
 *         If the current element is removed from the list, you will get an error.
 */
class HumanLifeChainIterator
{
    public:
      HumanLifeChainIterator(HumanLifeChain *list);
      Human *firstHuman();
      Human *nextHuman();
      bool  isDone();
    private:
      //! The list this Iterator is for.
      //! HumanLifeChain is a Singelton but the intention is clearer that way.
      HumanLifeChain        *mList;
      //! The pointer to the current element.
      HumanLifeChainElement *mCurrentElement;
};

//******************************************************************************
/*! \class CloneAdmin
 *  \ingroup SingletonTE PrototypeTE
 *  \brief Member of pattern <b>Singleton</b>. Used to administrate an Singleton.\n
 *  			 Member of pattern <b>Prototype</b> as <b>Client</b>.
 *         Sets ConcretePrototype of the HumanBreeder.
 *         Stores a Woman and a Man as "clone prototype". They can be given to the breeder.
 *         Could be extended to administrate more than one HumanBreeder.
 *         Can exist only one time. This is realised using the Singleton Pattern.	
 */	
class CloneAdmin
{
    public:
      static CloneAdmin *Instance();
      void               useClonePrototypeWoman();
      void               useClonePrototypeMan();
      Human             *createClone();
    protected:
      CloneAdmin();
    private:
      //! The single instance of CloneAdmin.
      static CloneAdmin *mInstance;
      //! The administrated HumanBreeder.
      HumanBreeder      *mBreeder;
      //! The Woman "clone pattern".
      Woman             *mPrototypeWoman;
      //! The Man "clone pattern".
      Man               *mPrototypeMan;
};

//******************************************************************************
/*! \class PartnerFinderStrategy
 * 	\ingroup StrategyTE
 * 	\brief Member of pattern <b>Strategy</b> as <b>Strategy</b>.
 *         Can be implementes to provide an algorithm to find a Woman and a Man in
 *         the HumanLifeChain.
 */
class PartnerFinderStrategy
{
    public:
      //! Can be implemented to find a Woman and a Man.
      virtual Human *searchPartnersAndCreateHuman() = 0;
};           

//******************************************************************************
/*! \class OldestPartnerFinderStrategy
 *  \ingroup StrategyTE
 *  \brief Member of pattern <b>Strategy</b> as <b>ConcreteStrategy</b>. 
 *         Used to find a Woman and a Man for a Partnership.
 *         They are searched in the HumanLifeChain and a Human will be created with them.
 */
class OldestPartnerFinderStrategy : public PartnerFinderStrategy
{
    public:
      Human *searchPartnersAndCreateHuman();
};        

//******************************************************************************
/*! \class RandomPartnerFinderStrategy
 *  \ingroup StrategyTE
 *  \brief Member of pattern <b>Strategy</b> as <b>ConcreteStrategy</b>. 
 *         Used to find a Woman and a Man for a Partnership.
 *         They are searched in the HumanLifeChain and a Human will be created with them.
 */
class RandomPartnerFinderStrategy : public PartnerFinderStrategy
{
    public:
      Human *searchPartnersAndCreateHuman();
};        

//******************************************************************************
/*! \class PartnerFinder
 *  \ingroup StrategyTE
 *  \brief Member of pattern <b>Strategy</b> as <b>Context</b>. 
 *         Used to find a Woman and a Man for a Partnership.
 *         Uses its PartnerFinderStrategy to find them and create a Human with them.
 */
class PartnerFinder
{
    public:
      PartnerFinder();
      Human *searchPartnersAndCreateHuman();
      void  setPartnerFinderStrategy(PartnerFinderStrategy* strategy);
    private:
      //! The PartnerFinderStrategy used to find a Woman and a Man.
				/** @link aggregation
				    @supplierCardinality 0..* */
      PartnerFinderStrategy *mStrategy;
};      

//******************************************************************************
/*! \class HumanHerold
 *  \ingroup ObserverTE
 *  \brief Member of pattern <b>Observer</b> as <b>Observer</b>. 
 *         Abstract Observer for HumanLifeChain.
 */
class HumanHerold : public Observer
{
    public:
      void attachToSubject(HumanLifeChain *chain);
      //! Should be called by the HumanLifeChain when it changes
      void update() = 0;
    protected:
      //! The HumanLifeChain this is attached to.
      HumanLifeChain *mChain;
};  

//******************************************************************************
/*! \class HumanLifeHerold
 *  \ingroup ObserverTE
 *  \brief Member of pattern <b>Observer</b> as <b>ConcreteObserver</b>. 
 *         Prints a newborn Human to the console.
 */
class HumanLifeHerold : public HumanHerold
{
    public:
      void attachToSubject(HumanLifeChain *chain);
      HumanLifeHerold();
      void update();
    private:
      //! Stores the last newborn Human. Needed to determine if a new Human was born.
      Human *mLastNewBorn;
};   

//******************************************************************************
/*! \class HumanDeathHerold
 *  \ingroup ObserverTE
 * 	\brief Member of pattern <b>Observer</b> as <b>ConcreteObserver</b>. 
 *         Prints to the console that a Human died.
 */
class HumanDeathHerold:public HumanHerold
{
    public:
      HumanDeathHerold();
      void attachToSubject(HumanLifeChain *chain);
      void update();
    private:
      //! Stores the oldest Human of HumanLifeChain.
      Human  *mNextToDie;
      //! Stores the gender (Woman, Man) of the oldest Human to print it.
      string mMessage;
};   

//******************************************************************************
/*! \class Death
 *  \ingroup SingletonTE
 *  \brief Member of pattern <b>Singleton</b>. Used to kill the oldest Human.\n
 *  
 *         Deletes the oldest Human and its HumanLifeChainElement from HumanLifeChain.
 *  	   Can exist only one time. This is realised using the Singleton Pattern.
 *         One Death should be enough. Imagine there were more...
 */
class Death
{
    public:
      static Death *Instance();
      void         killOldest();
    protected:
      Death();
    private:
      //! Stores the single instance.
      static Death *mInstance;
};

//******************************************************************************
/*! \class HumanHandler
 *  \ingroup FacadeTE SingletonTE
 *  \brief Member of pattern <b>Singleton</b>.\n 
 *         Member of pattern <b>Facade</b> as <b>Facade</b>. 
 *  			 Its used as Interface for the Human subsystem.
 */
class HumanHandler
{
    public:
      static HumanHandler *Instance();
      //HumanLifeChain *getHumanLifeChain();
      void  useClonePrototypeWoman();
      void  useClonePrototypeMan();
      void  cloneHuman();
      void  createHumanNaturally();
      void  killOldest();
    protected:
      HumanHandler();
    private:
      //! The single instance of HumanHandler.
      static HumanHandler *mInstance;
};

