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
         sets all the variables to a default value 
	 (NOVAL_X where X= I,F,D)

      std::string list(std::string prefix=""):
         makes a list of the variables for a TTree::Branch() definition

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Tue Aug 3 12:21:11 CET 2010
// $Id: BeamspotData.hh,v 1.3 2010/08/09 15:40:25 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include <string>
#include <sstream>
#include "CONST.hh"
#include "Data.hh"

namespace deb {

  class BeamspotData : public Data {
  public:
    float x;
    float y;
    float z;

    BeamspotData() { clear(); }
    ~BeamspotData() { }

    void clear() {
      x=NOVAL_F;
      y=NOVAL_F;
      z=NOVAL_F;
    }
    
    std::string list(std::string prefix="") {
      std::ostringstream ss;
      ss << Data::list(prefix);
      ss << prefix << ":x/F";
      ss << prefix << ":y/F";
      ss << prefix << ":z/F";
      return ss.str();
    }

  };

}
#endif
