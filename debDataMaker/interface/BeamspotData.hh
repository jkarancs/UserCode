#ifndef SusyAnalysis_debDataMaker_BeamspotData_hh_
#define SusyAnalysis_debDataMaker_BeamspotData_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      BeamspotData
// 
/**\class BeamspotData BeamspotData.hh SusyAnalysis/debDataMaker/interface/BeamspotData.hh

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
// $Id: BeamspotData.hh,v 1.1 2009/05/30 19:38:33 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include <string>
#include <sstream>
#include "CONST.hh"

namespace deb {

  class BeamspotData {
  public:
    BeamspotData() { }
    ~BeamspotData() { }

    float beamspotx;
    float beamspoty;
    float beamspotz;

    void clear() {
      beamspotx=NOVAL_F;
      beamspoty=NOVAL_F;
      beamspotz=NOVAL_F;     
    }
    
    std::string list(std::string prefix="") {
      std::ostringstream ss;
      ss << prefix << "beamspotx/F:";
      ss << prefix << "beamspoty/F:";
      ss << prefix << "beamspotz/F";
      return ss.str();
    }

  };

}
#endif
