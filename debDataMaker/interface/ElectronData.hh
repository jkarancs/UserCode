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

      selectionTypes_:
         is a map that translates the string of SelectionType to an integer

*/
//
// Original Author:  Anita KAPUSI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: ElectronData.hh,v 1.3 2009/06/03 07:56:51 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include <string>
#include <sstream>
#include "CONST.hh"

namespace deb {

  class ElectronData {
  public:
    float e;
    float px;
    float py;
    float pz;
    float m;
    float p;
    float pt;
    float et;
    float eta;
    float phi;
    float isoR03_trk;   //Tracker Isolation in DeltaR<0.3 cone
    float isoR03_hcal;  //Hadron Calorimeter Isolation in DeltaR<0.3 cone
    float isoR03_ecal;  //Electromagn. Calorimeter Isolation in DeltaR<0.3 cone
    float d0;           //Displacement of the track
    float phi_trk;      //Phi in the tracker
    float tight;        //Electron Id e.g.:"eidRobustTight"
    float loose;        //Electron Id e.g.:"eidRobustLoose"
    float bc_d0;        //d0 with respect to the primary vertex
    float reliso;       //Relative isolation 
                        //(isoR03_ecal+isoR03_hcal+isoR03_trk/et)
    int pass;

    ElectronData() {
      selectionTypes_["VALID"]=VALID;
      selectionTypes_["RefAna4JetMetMuon"]=RefAna4JetMetMuon;
      selectionTypes_["RefAna4JetMetElectron"]=RefAna4JetMetElectron;
    }
    ~ElectronData() { }

    enum ElectronSelectionType {
      VALID=PASS_VALIDITY,
      RefAna4JetMetMuon,
      RefAna4JetMetElectron
    };

    std::map<std::string, int> selectionTypes_;

    void clear() {
      e=NOVAL_F;
      px=NOVAL_F;
      py=NOVAL_F;
      pz=NOVAL_F;
      m=NOVAL_F;
      p=NOVAL_F;
      pt=NOVAL_F;
      et=NOVAL_F;
      eta=NOVAL_F;
      phi=NOVAL_F;
      isoR03_trk=NOVAL_F;
      isoR03_hcal=NOVAL_F;
      isoR03_ecal=NOVAL_F;
      d0=NOVAL_F;
      phi_trk=NOVAL_F;
      tight=NOVAL_F;
      loose=NOVAL_F;
      bc_d0=NOVAL_F;
      reliso=NOVAL_F;     
      pass=0;
    }

    std::string list(std::string prefix="") {
      std::ostringstream ss;
      ss << prefix << "e/F:";
      ss << prefix << "px/F:";
      ss << prefix << "py/F:";
      ss << prefix << "pz/F:";
      ss << prefix << "m/F:";
      ss << prefix << "p/F:";
      ss << prefix << "pt/F:";
      ss << prefix << "et/F:";
      ss << prefix << "eta/F:";
      ss << prefix << "phi/F:";
      ss << prefix << "isoR03_trk/F:";
      ss << prefix << "isoR03_hcal/F:";
      ss << prefix << "isoR03_ecal/F:";
      ss << prefix << "d0/F:";
      ss << prefix << "phi_trk/F:";
      ss << prefix << "tight/F:";
      ss << prefix << "loose/F:";
      ss << prefix << "bc_d0/F:";
      ss << prefix << "reliso/F:";
      ss << prefix << "pass/I";
      return ss.str();
    }

  };

}
#endif
