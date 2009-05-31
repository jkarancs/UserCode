#ifndef SusyAnalysis_debDataMaker_MuonData_hh_
#define SusyAnalysis_debDataMaker_MuonData_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      MuonData
// 
/**\class MuonData MuonData.hh SusyAnalysis/debDataMaker/interface/MuonData.hh

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
// $Id: MuonData.hh,v 1.1 2009/05/30 19:38:48 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include <string>
#include <sstream>
#include "CONST.hh"

namespace deb {

  class MuonData {
  public:
    MuonData() { }
    ~MuonData() { }

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
    float isoR03_trk;  //Tracker Isolation in DeltaR<0.3 cone
    float isoR03_hcal; //Hadron Calorimeter Isolation in DeltaR<0.3 cone
    float isoR03_ecal; //Electromagn. Calorimeter Isolation in DeltaR<0.3 cone
    float hits;        //Number of track hits
    float chi2;
    float ndof;        //Number of degrees of freedom
    float d0;          //Displacement of the track
    float phi_trk;     //Phi in the tracker
    float tight;       //Muon Id e.g.:"GlobalMuonPromptTight"
    float hcalisodep;  //Hadron Calorimeter Isolation Deposit
    float ecalisodep;  //Electromagnetic Calorimeter Isolation Deposit
    float bc_d0;       //d0 with respect to the primary vertex
    float reliso;      //Relative isolation 
                       //(isoR03_ecal+isoR03_hcal+isoR03_trk/pt)

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
      hits=NOVAL_F;
      chi2=NOVAL_F;
      ndof=NOVAL_F;
      d0=NOVAL_F;
      phi_trk=NOVAL_F;
      tight=NOVAL_F;
      hcalisodep=NOVAL_F;
      ecalisodep=NOVAL_F;
      bc_d0=NOVAL_F;
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
      ss << prefix << "hits/F:";
      ss << prefix << "chi2/F:";
      ss << prefix << "ndof/F:";
      ss << prefix << "d0/F:";
      ss << prefix << "phi_trk/F:";
      ss << prefix << "tight/F:";
      ss << prefix << "hcalisodep/F:";
      ss << prefix << "ecalisodep/F:";
      ss << prefix << "bc_d0/F:";
      ss << prefix << "reliso/F";
      return ss.str();
    }

  };

}
#endif
