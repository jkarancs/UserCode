#ifndef SusyAnalysis_debDataMaker_TriggerData_hh_
#define SusyAnalysis_debDataMaker_TriggerData_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      TriggerData
// 
/**\class TriggerData TriggerData.hh SusyAnalysis/debDataMaker/interface/TriggerData.hh

 Description: <one line class summary>

 Implementation:

      void clear()
         that sets all the variables to a default value 
	 (NOVAL_X where X= I,F,D)

      std::string list(std::string prefix=""):
         makes a list of the variables for a TTree::Branch() definition

*/
//
// Original Author:  Anita KAPUSI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: TriggerData.hh,v 1.1 2009/05/30 19:38:51 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include <string>
#include <sstream>
#include "CONST.hh"

namespace deb {

  class TriggerData {
  public:
    TriggerData() { clear(); }
    ~TriggerData() { }

    int hlt;

    void clear() {
      hlt=NOVAL_I;
    }
    
    std::string list(std::string prefix="") {
      std::ostringstream ss;
      ss << prefix << "hlt/I";
      return ss.str();
    }

  };

}
#endif
