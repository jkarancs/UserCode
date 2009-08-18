#ifndef SusyAnalysis_debDataMaker_Momentum4D_hh_
#define SusyAnalysis_debDataMaker_Momentum4D_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Momentum4D
// 
/**\class Momentum4D Momentum4D.hh SusyAnalysis/debDataMaker/interface/Momentum4D.hh

 Description: a 4-vector and some derived quantities

 Implementation:

      void clear()
         that sets all the variables to a default value 
	 (NOVAL_X where X= I,F,D)

      std::string list(std::string prefix=""):
         makes a list of the variables for a TTree::Branch() definition

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id$
//
//
//-----------------------------------------------------------------------------

#include <string>
#include <sstream>
#include "CONST.hh"

namespace deb {

  class Momentum4D {
  public:
    float e;
    float px;
    float py;
    float pz;
    float m;
    float p;
    float et;
    float pt;
    float phi;
    float eta;

    Momentum4D() { clear(); }
    ~Momentum4D() { }

    void clear() {
      e=NOVAL_F;
      px=NOVAL_F;
      py=NOVAL_F;
      pz=NOVAL_F;
      m=NOVAL_F;
      p=NOVAL_F;
      et=NOVAL_F;
      pt=NOVAL_F;
      phi=NOVAL_F;
      eta=NOVAL_F;
    }

    std::string list(std::string prefix="") {
      std::ostringstream ss;
      ss << prefix << "e/F:";
      ss << prefix << "px/F:";
      ss << prefix << "py/F:";
      ss << prefix << "pz/F:";
      ss << prefix << "m/F:";
      ss << prefix << "p/F:";
      ss << prefix << "et/F:";
      ss << prefix << "pt/F:";
      ss << prefix << "phi/F:";
      ss << prefix << "eta/F";
      return ss.str();
    }

  };

}
#endif
