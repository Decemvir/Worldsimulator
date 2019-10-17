//*************************************************************************
/** \file 
 *  \brief Contains the declarations of the classes 
 *         Thinkable, MindWorldComponent, 
 *         Decorator, Command, ThoughtBuilder.
 */

//#pragma warning (disable:4541)
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>


//*************************************************************************
/*! \interface Thinkable
 *	\ingroup CompositePattern
 * 	\brief Member of pattern <b>Composite</b> as <b>Component</b>. 
 *         Defines basic functionality for MindWorldComponents.
 */
class Thinkable
{
    public:
      //! prints the respective member attributes of Thinkable -primitives.
      virtual void ToWrite() = 0;
};

//*************************************************************************
/*! \interface MindWorldComponent
 *	\ingroup DecoratorPattern ProxyPattern
 * 	\brief Member of pattern <b>Decorator</b> as <b>Component</b>. 
 *          Defines basic functionality for MindWorldComponents.
 */
class MindWorldComponent : public Thinkable
{
    public:
      virtual void  change(char* text) = 0;
      virtual char* get_type() = 0;
      virtual int   get_change_count() {return _change_count;}

      void  set_change_count(int new_count) {_change_count = new_count;}
    private:
      int _change_count;
};

//*************************************************************************
/*!	\interface Decorator
 *	\ingroup DecoratorPattern
 *	\brief Member of pattern <b>Decorator</b> as <b>Decorator</b>. 
 *         Adds additional functionality to MindWorldComponents, the method change() - if required.
 */
class Decorator : public MindWorldComponent
{
    public:
      Decorator(MindWorldComponent* mwc);
      void                change(char* text);
      MindWorldComponent* get_mwc() {return _mwc;}
    private:
            /** @link aggregation
                @supplierCardinality 0..* */
      MindWorldComponent* _mwc;
};

//*************************************************************************
/*!	\interface Command
 *	\ingroup CommandPattern
 *	\brief Member of pattern <b>Command</b> as <b>Command</b>. 
 *         Defines basic functionality for ChangeCommands.
 */
class Command
{
    public:
      virtual void Execute() = 0;
      virtual void UnDo() = 0;
};

//*************************************************************************

class CreatedThoughtProxy;

//*************************************************************************
/*!	\interface ThoughtBuilder
 *	\ingroup BuilderPattern
 *	\brief Member of pattern <b>Builder</b> as <b>Builder</b>. 
 *         Builds objects of type CreatedThoughtProxy.
 */
class ThoughtBuilder
{
    public:
      virtual CreatedThoughtProxy* create_thought() = 0;
};
