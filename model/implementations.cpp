/** \file
 *  \brief Contains the implementations of the classes
 *         OwnMW, View, Thought, Feeling, MindWorld, Explainable,
 *  			 ChangeCommand, BadThoughtBuilder, GoodThoughtBuilder,
 *				 CreatedThought, CreatedThoughtProxy.
 */

#include "implementations.h"

 //******************************************************************************
 /*! Is set once, once get_Instance() is called. Only one OwnMW object are allowed for each MindWorldComponent. */
OwnMW* OwnMW::_ownmw = nullptr;

//******************************************************************************
//! Constructor of OwnMW.
/*!
 *	\param a pointer to a MindWorld object.
 *	\param a string.
 */
OwnMW::OwnMW(MindWorldComponent* mwc, char* quality): MindWorld(mwc, quality, nullptr)
{
    initialize();
}

//******************************************************************************
//! Destructor of OwnMW.
OwnMW::~OwnMW()
{
    //MindWorld::~MindWorld();
}

//******************************************************************************
//! Creates and returns a single instance of OwnMW.
/*!
 *  \param a pointer to a MindWorld object.
 *	\param a string.
 *	\return the single instance of OwnMW.
 */
OwnMW* OwnMW::get_Instance(MindWorldComponent* mwc,
                           char              * quality)
{
    if(!OwnMW::_ownmw)
        OwnMW::_ownmw = new OwnMW(mwc, quality);

    return OwnMW::_ownmw;
}

//******************************************************************************
//! Shows all MindWorlds
/*!
 *	\param none.
 *	\return none.
 */
void OwnMW::ToWrite(void)
{
    std::vector<MindWorldComponent*>::iterator pos;
    std::cout << "[OwnMW::ToWrite]  " << this << " ObserverPattern first level " << std::endl;

    for(pos = (get_mwc()).begin(); pos != (get_mwc()).end(); ++pos)
    {
        std::cout << "[OwnMW::ToWrite]  " << (*pos)->get_type() << " ";
        (*pos)->ToWrite();
    }
}

//******************************************************************************
//! Returns the type of OwnMW.
/*!
 *	\param none.
 *	\return text "OwnMW".
 */
char* OwnMW::get_type(void)
{
    return "OwnMW";
}

//******************************************************************************
//! Initializion of the OwnMW.
/*!
 *	\param none.
 *	\return none.
 */
void OwnMW::initialize(void)
{
    View               *a1 = new View("world is nice");
    View               *a2 = new View("world is nice");
    Explainable        *dec1 = new Explainable(new View("learning is important"));
    Thought            *g1 = new Thought("maybe the world is a cube");
    Feeling            *e1 = new Feeling("rain makes me blue");
    View               *a3 = new View("some humans are lovely");
    MindWorld          *dw1 = new MindWorld(a3, "middle", this);
    BadThoughtBuilder  *btb1 = new BadThoughtBuilder();
    GoodThoughtBuilder *gtb1 = new GoodThoughtBuilder();
    Feeling            *e2 = new Feeling("sun makes me cheery");

    add(a1);
    add(a2);
    add(dec1);
    a2->change("a view change is occurd");
    add(g1);
    add(e1);
    add(dw1);
    create_thought(btb1);
    create_thought(gtb1);
    add(e2);

    g1->ToWrite();
    g1->change("a thought-change is occurd, do and undo will follow");
    g1->change("again a change");
    g1->change("and again");
    g1->UnDo();
    g1->UnDo();
    g1->ReDo();
    g1->change("a new change");
    g1->ReDo();
    g1->ReDo();
    g1->UnDo();
    g1->UnDo();
    g1->UnDo();
    g1->ReDo();
    g1->ReDo();
    g1->ToWrite();

    delete btb1;
    delete gtb1;
}

//******************************************************************************
//! Constructor of View
/*!
 *	\param a string.
 */
View::View(char* view)
{
    _view = view;
    this->set_change_count(0);
}

//******************************************************************************
//! Shows the View object.
/*!
 *	\param none.
 *	\return none.
 */
void View::ToWrite(void)
{
    std::cout << "[View::ToWrite] " << this << " " << _view << std::endl;
}

//******************************************************************************
//! 
/*!
 *	\param a string.
 *	\return none.
 */
void View::change(char* text)
{
    _view = text;
    set_change_count(get_change_count() + 1);
}

//******************************************************************************
//! Gets the type of the view object
/*!
 *	\param none.
 *	\return "leave of type View".
 */
char* View::get_type(void)
{
    return "leave of type View";
}

//******************************************************************************
//! Constructor of Thought
/*!
 *	\param a string.
 */
Thought::Thought(char* thought)
{
    _thought = thought;
    this->set_change_count(0);
    _command_pos = _commands.begin();
}

//******************************************************************************
//! Shows the Thought object.
/*!
 *	\param none.
 *	\return none.
 */
void Thought::ToWrite(void)
{
    std::cout << "[Thought::ToWrite] " << this << " " << _thought << std::endl;
}

//******************************************************************************
//! Changes the Thought.
/*!
 *	\param a string.
 *	\return none.
 */
void Thought::change(char* text)
{
    ChangeCommand* command = new ChangeCommand(this, _thought, text);
    if((_command_pos + 1) < _commands.end())
    {
        ++_command_pos;
        _commands.erase(_command_pos, _commands.end());
    }
    _commands.push_back(command);
    _command_pos = _commands.end();
    --_command_pos;
    set_change_count(get_change_count() + 1);
}

//******************************************************************************
//! Returns the type of the thought.
/*!
 *	\param none.
 *	\return "leave of type Thought".
 */
char* Thought::get_type(void)
{
    return "leave of type Thought";
}

//******************************************************************************
//! Sets a new thought.
/*!
 *	\param a string.
 *	\return none.
 */
void Thought::set_thought(char* new_value)
{
    _thought = new_value;
}

//******************************************************************************
//! Undos an executed command.
/*!
 *	\param none.
 *	\return none.
 */
void Thought::UnDo(void)
{
    (*_command_pos)->UnDo();
    set_change_count(get_change_count() - 1);
    if(_command_pos > _commands.begin())
        --_command_pos;
}

//******************************************************************************
//! Redos an executed command.
/*!
 *	\param none.
 *	\return none.
 */
void Thought::ReDo(void)
{
    if((_command_pos + 1) < _commands.end())
        ++_command_pos;

    (*_command_pos)->Execute();
    set_change_count(get_change_count() + 1);
}

//******************************************************************************
//! Constructor of Feeling.
/*!
 *	\param a string.
 */
Feeling::Feeling(char* feeling)
{
    _feeling = feeling;
    this->set_change_count(0);
}

//******************************************************************************
//! Shows the Feeling object.
/*!
 *	\param none.
 *	\return none.
 */
void Feeling::ToWrite(void)
{
    std::cout << "[Feeling::ToWrite] " << this << " " << _feeling << std::endl;
}

//******************************************************************************
//! Changes the feeling.
/*!
 *	\param a string.
 *	\return none.
 */
void Feeling::change(char* text)
{
    _feeling = text;
    set_change_count(get_change_count() + 1);
}

//******************************************************************************
//! Returns the type of the feeling.
/*!
 *	\param none.
 *	\return "leave of type  Feeling".
 */
char* Feeling::get_type(void)
{
    return "leave of type  Feeling";
}

//******************************************************************************
//! Constructor of MindWorld.
/*!
 *	\param a pointer of a MindWorldComonent object.
 *	\param a string.
 *	\param a pointer of a MindWorld object.
 */
MindWorld::MindWorld(MindWorldComponent* mwc,
                     char              * quality,
                     MindWorld         * mw)
{
    _quality = quality;
    this->set_change_count(0);
    _parent_mw = mw;
    _mwc.push_back(mwc);
}

//******************************************************************************
//! Destructor of MindWorld
MindWorld::~MindWorld()
{
    std::vector<MindWorldComponent*>::iterator pos;
    for(pos = _mwc.begin(); pos != _mwc.end(); ++pos)
        delete *pos;
}

//******************************************************************************
//! Shows the MindWorld object.
/*!
 *	\param none.
 *	\return none.
 */
void MindWorld::ToWrite(void)
{
    std::cout << "[MindWorld::ToWrite]  " << this << " " << _quality << " quality" << std::endl << std::endl;
    std::cout << "[MindWorld::ToWrite]  " << "in MindWorld " << this << " " << _quality << " quality" << std::endl;
    std::vector<MindWorldComponent*>::iterator pos;

    for(pos = _mwc.begin(); pos != _mwc.end(); ++pos)
    {
        std::cout << (*pos)->get_type() << " ";
        (*pos)->ToWrite();
    }
}

//******************************************************************************
//! Changes the quality of the mindworld.
/*!
 *	\param a string.
 *	\return none.
 */
void MindWorld::change(char* text)
{
    _quality = text;
    set_change_count(get_change_count() + 1);
}

//******************************************************************************
//! Returns the type of the mindworld.
/*!
 *	\param none.
 *	\return a string.
 */
char* MindWorld::get_type(void)
{
    return "leave and new root of type MindWorld";
}

//******************************************************************************
//! Adds a MindWorldComponent to the MindWorld
/*!
 *	\param a pointer to a MindWorldComponent object.
 *	\return none.
 */
void MindWorld::add(MindWorldComponent* mwc)
{
    _mwc.push_back(mwc);
}

//******************************************************************************
//!	like "HandleHelp()" in "Design Patterns" - Chain of Responsibility
//!	searches for an "Thinkable"-Object with the same type defined in parameter "type" 
//!	and with _change_count >= parameter min_count, calls write_target() of its successor, if not found
/*!
  \param a string.
	\param minimum count (a integer).
	\return none.
*/
void MindWorld::write_target(std::string type,
                             int         min_count)
{
    if((can_write(type, min_count) == 0) && (_parent_mw != nullptr))
    {
        _parent_mw->write_target(type, min_count);
    }
}

//******************************************************************************
//! like "HasHelp()" in "Design Patterns" - Chain of Responsibility
/*!
 *  \param a string.
 *	\param minimum count (a integer).
 *	\return true, if the write_target request can be handled from an object in this "MindWorld".
 */
bool MindWorld::can_write(std::string type,
                          int         min_count)
{
    std::vector<MindWorldComponent*>::iterator pos;
    for(pos = _mwc.begin(); pos != _mwc.end(); ++pos)
    {
        if((*pos)->get_type() == type)
        {
            if((*pos)->get_change_count() >= min_count)
            {
                std::cout << "[MindWorld::can_write]  " << "write target hit in mw " << this << " ";
                (*pos)->ToWrite();
                return 1;
            }
        }
    }

    return 0;
}

//******************************************************************************
//! Creates a thought.
/*!
 *	\param a ThoughtBuilder.
 *	\return none.
 */
void MindWorld::create_thought(ThoughtBuilder* builder)
{
    this->add(builder->create_thought());
}

//******************************************************************************
//! Constructor of Explainable.
/*!
 *  \param pointer to a MindWorldComponent object.
 */
Explainable::Explainable(MindWorldComponent* mwc): Decorator(mwc) {}

//******************************************************************************
//!	decorates the method Thinkable::ToWrite(), the decorated Object also
//!	prints his member attribute _change_count
/*!
 *	\param none.
 *	\return none.
 */
void Explainable::ToWrite(void)
{
    std::cout << "[Explainable::ToWrite] " << this << " " << (get_mwc())->get_type()
              << " part of the decorator pattern; change_count: "
              << (get_mwc())->get_change_count() << " "
              << (get_mwc())->get_type() << " ";

    (get_mwc())->ToWrite();
}

//******************************************************************************
//! Returns the type of a mindworldcomponent.
/*!
 *	\param none.
 *	\return a string.
 */
char* Explainable::get_type(void)
{
    return (get_mwc())->get_type();
}

//******************************************************************************
//! Constructor of ChangeCommand
/*!
 *	\param a pointer to a Thought object.
 *	\param a string.
 *	\param a string.
 */
ChangeCommand::ChangeCommand(Thought* thought,
                             char   * old_value,
                             char   * new_value): _thought(thought), _old_value(old_value), _new_value(new_value)
{
    this->Execute();
}

//******************************************************************************
//! Execute the command ChangeCommand.
/*!
 *	\param none.
 *	\return none.
 */
void ChangeCommand::Execute(void)
{
    _thought->set_thought(_new_value);
}

//******************************************************************************
//! Undos the command ChangeCommand.
/*!
 *	\param none.
 *	\return none.
 */
void ChangeCommand::UnDo(void)
{
    _thought->set_thought(_old_value);
}

//******************************************************************************
//! Creates a new bad thought.
/*!
 *	\param none.
 *	\return a pointer to a CreatedThoughtProxy object.
 */
CreatedThoughtProxy* BadThoughtBuilder::create_thought(void)
{
    return new CreatedThoughtProxy("a realy, realy bad thought");
}

//******************************************************************************
//! Creates a new good thought.
/*!
 *	\param none
 *	\return a pointer to a CreatedThoughtProxy object.
 */
CreatedThoughtProxy* GoodThoughtBuilder::create_thought(void)
{
    return new CreatedThoughtProxy("a realy, realy good thought");
}

//******************************************************************************
//! Constructor of CreatedThought.
/*!
 *  \param a string.
 */
CreatedThought::CreatedThought(char* thought)
{
    _thought = thought;
    this->set_change_count(0);
}

//******************************************************************************
//! Shows the CreatedThought object
/*!
 *	\param none.
 *	\return none.
 */
void CreatedThought::ToWrite(void)
{
    std::cout << "[CreatedThought::ToWrite] " << this << " " << _thought << std::endl;
}

//******************************************************************************
//! Changes the thought.
/*!
 *	\param a text.
 *	\return none.
 */
void CreatedThought::change(char* text)
{
    _thought = text;
    set_change_count(get_change_count() + 1);
}

//******************************************************************************
//! Gets the type of CreatedThought object.
/*!
 *	\param none.
 *	\return "CreatedThought".
 */
char* CreatedThought::get_type(void)
{
    return "CreatedThought";
}

//******************************************************************************
//! Constructor of CreatedThoughtProxy.
/*!
 *	\param a string.
 */
CreatedThoughtProxy::CreatedThoughtProxy(char* thought)
{
    _thought = thought;
    _created_thought = nullptr;
}

//******************************************************************************
//! Shows the CreatedThought object
/*!
 *  \param none.
 *  \return none.
 */
void CreatedThoughtProxy::ToWrite(void)

{
    if(!_created_thought) _created_thought = new CreatedThought(_thought);
    _created_thought->ToWrite();
}

//******************************************************************************
//! Changes the thought.
/*!
 *	\param a string.
 *	\return none.
 */
void CreatedThoughtProxy::change(char* text)

{
    if(!_created_thought)
        _created_thought = new CreatedThought(_thought);

    _created_thought->change(text);
}

//******************************************************************************
//! Returns the type of the new thought.
/*!
 *	\param none.
 *	\return a string.
 */
char* CreatedThoughtProxy::get_type(void)
{
    if((!_created_thought) == NULL)
        _created_thought = new CreatedThought(_thought);

    return _created_thought->get_type();
}

