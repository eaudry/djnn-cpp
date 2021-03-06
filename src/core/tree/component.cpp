/*
 *  djnn v2
 *
 *  The copyright holders for the contents of this file are:
 *      Ecole Nationale de l'Aviation Civile, France (2018)
 *  See file "license.terms" for the rights and conditions
 *  defined by copyright holders.
 *
 *
 *  Contributors:
 *      Mathieu Magnaudet <mathieu.magnaudet@enac.fr>
 *
 */

#include "component.h"
#include "../execution/graph.h"
#include <iostream>
#include <algorithm>
#include "../execution/component_observer.h"

#include <iostream>

#define DBG std::cerr << __FILE__ ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;

namespace djnn
{
  using namespace std;

  Container::Container ()
  {
    _cpnt_type = COMPONENT;
  }

  Container::Container (Process* parent, const string& name) :
      Process (parent, name)
  {
    _cpnt_type = COMPONENT;
  }

  Container::~Container ()
  {
    for (auto c: _children)
      delete c;
  }

  void
  Container::add_child (Process* c, const std::string& name)
  {
    if (c == nullptr)
      return;
    _children.push_back (c);
    /* WARNING should we authorize multiple parenthood? */
    if (c->get_parent () != nullptr && c->get_parent() != this) {
      c->get_parent()->remove_child (c);
    }
    c->set_parent (this);
    add_symbol (name, c);
    if (get_state () == activated) {
      c->activation ();
    } else if (c->get_state () == activated) {
      c->deactivation ();
    }
  }

  void
  Container::remove_child (Process* c)
  {
    Process::remove_child (c);
    _children.erase (std::remove (_children.begin (), _children.end (), c), _children.end ());
  }

  void
  Container::remove_child (const std::string& name)
  {
    std::map<std::string, Process*>::iterator it = _symtable.find (name);
    if (it != _symtable.end ()) {
      Process* c = it->second;
      _children.erase (std::remove (_children.begin (), _children.end (), c), _children.end ());
      _symtable.erase (it);
    } else
      std::cerr << "Warning: symbol " << name << " not found in Component " << _name << "\n";
  }

  void
  Container::activate ()
  {
    ComponentObserver::instance ().start_component ();
    for (auto c : _children) {
      if (!c->is_model ()) {
        c->activation ();
      }
    }
    ComponentObserver::instance ().end_component ();
  }

  void
  Container::draw ()
  {
    if (_activation_flag > activated)
      return;
    ComponentObserver::instance ().start_draw ();
    for (auto c: _children) {
      c->draw ();
    }
    ComponentObserver::instance ().end_draw ();
  }

  void
  Container::deactivate ()
  {
    for (auto c : _children) {
      c->deactivation ();
    }
  }

  void
  Container::print_children ()
  {
    cout << _name << "'s children:\n";
    for (auto c : _children) {
      cout << c->get_name () << endl;
    }
    cout << endl;
  }

  Process*
  Component::clone () {
    Process* clone = new Component ();
    for (auto c: _children) {
      clone->add_child (c->clone (), c->get_name ());
    }
    return clone;
  }
}

