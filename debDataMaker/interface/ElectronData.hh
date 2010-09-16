#ifndef SusyAnalysis_debDataMaker_ElectronData_hh_
#define SusyAnalysis_debDataMaker_ElectronData_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      ElectronData
// 
/**\class ElectronData ElectronData.hh SusyAnalysis/debDataMaker/interface/ElectronData.hh

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
// $Id: ElectronData.hh,v 1.9.2.2 2010/09/16 09:03:24 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include <string>
#include <sstream>
#include "CONST.hh"

namespace deb {

  class ElectronData {
  public:
    ElectronData() { }
    ~ElectronData() { }

    float e;
    float p;
    float px;
    float py;
    float pz;
    float m;
    float pt;
    float et;
    float eta;
    float phi;
    float isoR03_trk;
    float isoR03_hcal;
    float isoR03_ecal;
    float d0;
    float phitrack;
    float idtight;
    float idloose;
    float bcd0;
    float reliso;

    void clear() {
      e=NOVAL_F;
      px=NOVAL_F;
      py=NOVAL_F;
      pz=NOVAL_F;
      m=NOVAL_F;
      pt=NOVAL_F;
      et=NOVAL_F;
      eta=NOVAL_F;
      phi=NOVAL_F;
      isoR03_trk=NOVAL_F;
      isoR03_hcal=NOVAL_F;
      isoR03_ecal=NOVAL_F;
      d0=NOVAL_F;
      phitrack=NOVAL_F;
      idtight=NOVAL_F;
      idloose=NOVAL_F;
      bcd0=NOVAL_F;
      reliso=NOVAL_F;     
    }

    std::string list(std::string prefix="") {
      std::ostringstream ss;
      ss << prefix << "e/F:";
      ss << prefix << "px/F:";
      ss << prefix << "py/F:";
      ss << prefix << "pz/F:";
      ss << prefix << "m/F:";
      ss << prefix << "pt/F:";
      ss << prefix << "et/F:";
      ss << prefix << "eta/F:";
      ss << prefix << "phi/F:";
      ss << prefix << "isoR03_trk/F:";
      ss << prefix << "isoR03_hcal/F:";
      ss << prefix << "isoR03_ecal/F:";
      ss << prefix << "d0/F:";
      ss << prefix << "phitrack/F:";
      ss << prefix << "idtight/F:";
      ss << prefix << "idloose/F:";
      ss << prefix << "bcd0/F:";
      ss << prefix << "reliso/F";
      return ss.str();
    }

  };

}
#endif
