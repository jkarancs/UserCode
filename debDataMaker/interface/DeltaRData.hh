#ifndef SusyAnalysis_debDataMaker_DeltaRData_hh_
#define SusyAnalysis_debDataMaker_DeltaRData_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      DeltaRData
// 
/**\class DeltaRData DeltaRData.hh SusyAnalysis/debDataMaker/interface/DeltaRData.hh

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
//         Created:  Sun Mar 24 12:15:11 CET 2009
// $Id$
//
//
//-----------------------------------------------------------------------------

#include <string>
#include <sstream>
#include "CONST.hh"

namespace deb {

  class DeltaRData {
  public:
    DeltaRData() { }
    ~DeltaRData() { }

    float phi;
    float eta;
    float r;

    void clear() {
      phi=NOVAL_F; 
      eta=NOVAL_F; 
      r=NOVAL_F; 
    }

    std::string list(std::string prefix="") {
      std::ostringstream ss;
      ss << prefix << "phi/F:";
      ss << prefix << "eta/F:";
      ss << prefix << "r/F";
      return ss.str();
    }

  };

}
#endif
