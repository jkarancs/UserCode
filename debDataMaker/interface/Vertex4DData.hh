#ifndef SusyAnalysis_debDataMaker_Vertex4DData_hh_
#define SusyAnalysis_debDataMaker_Vertex4DData_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Vertex4DData
// 
/**\class Vertex4DData Vertex4DData.hh SusyAnalysis/debDataMaker/interface/Vertex4DData.hh

 Description: <one line class summary>

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
// $$
//
//
//-----------------------------------------------------------------------------

#include <string>
#include <sstream>
#include "SusyAnalysis/debDataMaker/interface/Momentum4D.hh"

namespace deb {

  class Vertex4DData : public Momentum4D {
  public:

    float mass;
    float sigma;
    float chi2;

    Vertex4DData() { clear(); }
    ~Vertex4DData() { }

    void clear() {
      Momentum4D::clear();
      mass=NOVAL_F;
      sigma=NOVAL_F;
      chi2=NOVAL_F;
    }

    std::string list(std::string prefix="") {
      std::ostringstream ss;
      ss << Momentum4D::list(prefix) << ":";
      ss << prefix << "mass/F:";
      ss << prefix << "sigma/F:";
      ss << prefix << "chi2/F";
      return ss.str();
    }

  };

}
#endif
