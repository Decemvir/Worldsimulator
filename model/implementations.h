//*************************************************************************
/** \file 
 *  \brief Contains the declarations of the classes 
 *         View, Thought, Feeling, MindWorld, OwnMW, 
 *  			 Explainable, ChangeCommand, BadThoughtBuilder, 
 *  			 GoodThoughtBuilder, CreatedThought, CreatedThoughtProxy.
 */

#include "interfaces.h"

//*************************************************************************
/*!	\class View Interfaces.h
 *	\ingroup CompositePattern DecoratorPattern
 *	\brief Member of pattern <b>Composite</b> as <b>Leaf</b>. Is a view of an human.\n
 *         Member of pattern <b>Decorator</b> as <b>ConcreteComponent</b>. 
 *	       The view can be changed, change(char* text), and it can be written out, (ToWrite()). 
 */
class View : public MindWorldComponent
{
    public:
      View(char* view);
      void  ToWrite();
      void  change(char* text);
      char* get_type(void);
    private:
      char* _view;
};

//*************************************************************************

class ChangeCommand;

//*************************************************************************
/*!	\class Thought Interfaces.h
 *	\ingroup CompositePattern CommandPattern DecoratorPattern
 *	\brief Member of pattern <b>Composite</b> as <b>Leaf</b>. Is a thought of an human.\n
 *         Member of pattern <b>Decorator</b> as <b>ConcreteComponent</b>.\n
 *         Member of pattern <b>Command</b> as <b>Receiver</b> and also as <b>Invoker</b>. 
 *
 *	       Thoughts can be changed, change(char* text), and they can get back to old values. 
 *         This is realized through the UnDo() and ReDo() functionality. Each ChangeCommand 
 *         is stored into the vector _commands, and UnDo() and ReDo() operates on this vector.
 */
class Thought : public MindWorldComponent
{
    public:
      Thought(char* thought);
      void  ToWrite();
      void  change(char* text);
      char* get_type(void);
      void  set_thought(char* new_value);
      void  UnDo(void);
      void  ReDo(void);
    private:
      char* _thought;
				/** @link aggregation
				    @supplierCardinality 0..* */
      std::vector<ChangeCommand*>           _commands;
      std::vector<ChangeCommand*>::iterator _command_pos;
};

//*************************************************************************
/*!	\class Feeling Interfaces.h
 *	\ingroup CompositePattern DecoratorPattern
 *	\brief Member of pattern <b>Composite</b> as <b>Leaf</b>. Is a feeling of an human.\n
 *         Member of pattern <b>Decorator</b> as <b>ConcreteComponent</b>. 
 *         The feeling can be changed thru change(char* text), and it can be written out thru ToWrite(). 
 */
class Feeling : public MindWorldComponent
{
    public:
      Feeling(char* feeling);
      void  ToWrite();
      void  change(char* text);
      char* get_type();
    private:
      char* _feeling;
};

//*************************************************************************
/*!	\class MindWorld Interfaces.h
 *	\ingroup CompositePattern ChainOfResponsibilityPattern BuilderPattern DecoratorPattern
 *	\brief Member of pattern <b>Composite</b> as <b>Composite</b>.\n
 *         Member of pattern <b>ChainOfresponsibility</b> as <b>Client</b> and as <b>ConcreteHandler</b>.\n
 *         Member of pattern <b>Builder</b> as <b>Director</b>.\n
 *         Member of pattern <b>Decorator</b> as <b>ConcreteComponent</b>.
 *  	   Is one MindWworld, which the OwnMW of each Human cosnists of.
 *         Is the container of Thinkable objects on every level other than first level
 */
class MindWorld : public MindWorldComponent
{
    public:
      MindWorld(MindWorldComponent* dwc, char* quality, MindWorld* mw = 0);
      ~MindWorld();

      virtual void  ToWrite();
      virtual char* get_type();
      void          change(char* text);
      void          add(MindWorldComponent* mwc);
      void          write_target(std::string type, int min_count);
      bool          can_write(std::string type, int min_count);
      void          create_thought(ThoughtBuilder* builder);
      char*         get_quality() {return _quality;}

      std::vector<MindWorldComponent*>& get_mwc() {return _mwc;}
    private:
            /** @link aggregation
                @supplierCardinality 0..* */
      std::vector<MindWorldComponent*> _mwc;
      char*         _quality;

      /*! is successor, needed for the Chain of Responsibility Pattern. */
            /** @link aggregation
                @supplierCardinality 0..* */
      MindWorld* _parent_mw;
};

//*************************************************************************
/*!	\class OwnMW Interfaces.h
 *	\ingroup CompositePattern SingletonTE DecoratorPattern
 *	\brief Member of pattern <b>Composite</b> as <b>Composite</b>. Is the one MindWorld, each Human has one.\n
 *         Member of pattern <b>Singleton</b>.\n
 *         Member of pattern <b>Decorator</b> as <b>ConcreteComponent</b>. 
 *	       Is the Container of Thinkable objects on first level
 */
class OwnMW : public MindWorld
{
    public:
      static OwnMW* get_Instance(MindWorldComponent* mwc, char* quality);
      void          ToWrite();
      char*         get_type();
      void          initialize();
      ~OwnMW();
    protected:
      OwnMW(MindWorldComponent* mwc, char* quality);
    private:
            /** @link aggregation
                @supplierCardinality 0..* */
      static OwnMW* _ownmw;
};

//*************************************************************************
/*!	\class Explainable Interfaces.h
 *	\ingroup DecoratorPattern
 *	\brief Member of pattern <b>Decorator</b> as <b>ConcreteDecorator</b>. 
 *         Decorates the "ToWrite()"-Method of Thinkable objects
 */
class Explainable : public Decorator
{
    public:
      Explainable(MindWorldComponent* mwc);
      void        ToWrite();
      char*       get_type();
      virtual int get_change_count() {return (get_mwc())->get_change_count();}
};

//*************************************************************************
/*!	\class ChangeCommand Interfaces.h
 *	\ingroup CommandPattern
 *	\brief Member of pattern <b>Command</b> as a <b>ConcreteCommand</b>. 
 *         A Command to change an Thought in a Humans MindWorld.
 *         It stores the old Thought and it sets the new.	
 */
class ChangeCommand : public Command
{
    public:
      ChangeCommand(Thought* thought, char* old_value, char* new_value);
      void Execute();
      void UnDo();
      void To_Write()
      {
          std::cout << "[ChangeCommand::ToWrite]  " << "new_value " << _new_value << "  " << std::endl;
      }
    private:
      Thought* _thought;
      char*    _old_value;
      char*    _new_value;
};

//*************************************************************************
/*!	\class BadThoughtBuilder Interfaces.h
 *	\ingroup BuilderPattern
 *	\brief Member of pattern <b>Builder</b> as <b>ConcreteBuilder</b>. 
 *         It creates an proxy of an realy bad Thought.
 */
class BadThoughtBuilder : public ThoughtBuilder
{
    public:
      CreatedThoughtProxy* create_thought();
};

//*************************************************************************
/*!	\class GoodThoughtBuilder Interfaces.h
 *	\ingroup BuilderPattern
 *	\brief Member of pattern <b>Builder</b> as <b>ConcreteBuilder</b>. 
 *         It creates an proxy of an realy good Thought.
 */
class GoodThoughtBuilder : public ThoughtBuilder
{
    public:
      CreatedThoughtProxy* create_thought();
};

//*************************************************************************
/*!	\class CreatedThought Interfaces.h
 *	\ingroup CompositePattern ProxyPattern 
 Pattern
 *	\brief Member of pattern <b>Composite</b> as <b>Leaf</b>.\n
 *         Member of pattern <b>Proxy</b> as <b>RealSubject</b>.\n
 *  	     Member of pattern <b>Decorator</b> as <b>ConcreteComponent</b>. 
 *  		   Is a Thought, which is created by the Human, himself.
 */
class CreatedThought : public MindWorldComponent
{
    public:
      CreatedThought(char* thought);
      void  ToWrite();
      void  change(char* text);
      char* get_type();
    private:
      char* _thought;
};

//*************************************************************************
/*!	\class CreatedThoughtProxy Interfaces.h
 *	\ingroup ProxyPattern BuilderPattern CompositePattern DecoratorPattern
 *	\brief Member of pattern <b>Proxy</b> as <b>Proxy</b>. Is Proxy for CreatedThought objects.\n
 *         Member of pattern <b>Builder</b> as <b>Builder</b> and as <b>Product</b>.\n
 *    		 Member of pattern <b>Composite</b> as <b>Leaf</b>.\n
 *         Member of pattern <b>Decorator</b> as <b>ConcreteComponent</b>. 
 */
class CreatedThoughtProxy : public MindWorldComponent
{
    public:
      CreatedThoughtProxy(char* thought);
      void  ToWrite();
      void  change(char* text);
      char* get_type();
    private:
      char*           _thought;
      CreatedThought* _created_thought;
};


