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

#include "abstract_property.h"
#include <string>

namespace djnn {
  using namespace std;

  class TextProperty: public AbstractProperty {
  public:
    TextProperty (string v) : AbstractProperty (), value (v) { _type = String; };
    TextProperty (Process*  p, const string &name, string v) : AbstractProperty (p, name), value (v) { _type = String; Process::finalize (); };
    void activate () override {} ;
    void deactivate () override {};
    string& get_value () { return value; };
    void set_value (int newValue, bool propagate) override;
    void set_value (double v, bool propagate) override;
    void set_value (bool v, bool propagate) override;
    void set_value (Process* v, bool propagate) override;
    void set_value (const string &v, bool propagate) override;

    void dump (int level=0) override;
  private:
    string value;
  };

}
