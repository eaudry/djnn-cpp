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

#pragma once

#include "component.h"
#include <list>
#include <iostream>
#include "ref_property.h"
#include "int_property.h"

namespace djnn {
  using namespace std;

  class Set : public Process
  {
  public:
    Set ();
    Set (Process *parent, const string& name);
    void add_child (Process* c, const string& name) override;
    void remove_child (Process* c) override;
    void remove_child (const string &name) override;
    Process* find_component (const string &path) override;
    void activate () override;
    void deactivate () override;
    virtual ~Set ();
  private:
    shared_ptr<RefProperty> _added, _removed;
    shared_ptr <IntProperty> _size;
  };
}
