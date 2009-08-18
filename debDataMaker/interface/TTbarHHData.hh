#ifndef SusyAnalysis_debDataMaker_TTbarHHData_hh_
#define SusyAnalysis_debDataMaker_TTbarHHData_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      TTbarHHData
// 
/**\class TTbarHHData TTbarHHData.hh SusyAnalysis/debDataMaker/interface/TTbarHHData.hh

 Description: <one line class summary>

 Implementation:

      void clear()
         that sets all the variables to a default value 
	 (NOVAL_X where X= I,F,D)

      std::string list(std::string prefix=""):
         makes a list of the variables for a TTree::Branch() definition

      selectionTypes_:
         is a map that translates the string of SelectionType to an integer

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
#include "SusyAnalysis/debDataMaker/interface/Vertex4DData.hh"
#include "TString.h"

namespace deb {

  class TTbarHHData {
  public:

    float chi2;
    int W1q1;
    int W1q2;
    int T1b;
    int W2q1;
    int W2q2;
    int T2b;

    TTbarHHData() { clear(); }
    ~TTbarHHData() { }

    void clear() { 
      chi2=NOVAL_F; 
      W1q1=NOVAL_I;
      W1q2=NOVAL_I;
      T1b=NOVAL_I;
      W2q1=NOVAL_I;
      W2q2=NOVAL_I;
      T2b=NOVAL_I;
    }

    std::string list(std::string prefix="") {
      std::ostringstream ss;
      ss << prefix << "chi2/F:";
      ss << prefix << "W1q1/I:";
      ss << prefix << "W1q2/I:";
      ss << prefix << "T1b/I:";
      ss << prefix << "W2q1/I:";
      ss << prefix << "W2q2/I:";
      ss << prefix << "T2b/I";
      return ss.str();
    }

  };

}
#endif
