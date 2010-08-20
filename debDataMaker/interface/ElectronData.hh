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
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id$
//
//
//-----------------------------------------------------------------------------

#include <string>
#include <sstream>
#include "CONST.hh"
#include "Data.hh"

namespace deb {

  class ElectronData : public Data {
  public:
                         // reco::Candidates :
    float e;             //
    float px;            //
    float py;            //
    float pz;            //
    float m;             //
    float pt;            //
    float et;            //
    float eta;           //
    float phi;           //

                         // reco::GsfElectron:: or pat::Electron::gsfTrack()
    int   has_trk;       // has a GsfTrack
    float d0;            // displacement of the track
    float phi_trk;       // phi of the GsfTrack

                         // DeltaR<0.3 cone isolations:
    float isoR03_ecal;   // ECal isolation with electron hit removed
    float isoR03_hcal;   // HCal isolation, total sum after electron removed
    float isoR03_trk;    // tracker isolation with electron removed

                         // For now, only for Pat electrons
    float loose;         // electron Id e.g.:"eidRobustLoose"
    float tight;         // electron Id e.g.:"eidRobustTight"

    float d0_bc;         // d0 with respect to the primary vertex
    float reliso;        // Relative isolation 
                         // (isoR03_ecal+isoR03_hcal)/pt    
    float reliso_comb;   // Combined Relative isolation 
                         // (isoR03_ecal+isoR03_hcal+isoR03_trk)/et

    ElectronData() { clear(); }
    ~ElectronData() { }

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

      has_trk=NOVAL_I;
      d0=NOVAL_F;
      phi_trk=NOVAL_F;

      isoR03_ecal=NOVAL_F;
      isoR03_hcal=NOVAL_F;
      isoR03_trk=NOVAL_F;

      loose=NOVAL_F;
      tight=NOVAL_F;

      d0_bc=NOVAL_F;
      reliso=NOVAL_F; 
      reliso_comb=NOVAL_F;    
    }

    std::string list(std::string prefix="") {
      std::ostringstream ss;
      ss << Data::list(prefix);
      ss << prefix <<":e/F";
      ss << prefix <<":px/F";
      ss << prefix <<":py/F";
      ss << prefix <<":pz/F";
      ss << prefix <<":m/F";
      ss << prefix <<":pt/F";
      ss << prefix <<":et/F";
      ss << prefix <<":eta/F";
      ss << prefix <<":phi/F";

      ss << prefix <<":has_trk/I";
      ss << prefix <<":d0/F";
      ss << prefix <<":phi_trk/F";

      ss << prefix <<":isoR03_ecal/F";
      ss << prefix <<":isoR03_hcal/F";
      ss << prefix <<":isoR03_trk/F";

      ss << prefix <<":loose/F";
      ss << prefix <<":tight/F";

      ss << prefix <<":d0_bc/F";
      ss << prefix <<":reliso/F";
      ss << prefix <<":reliso_comb/F";

      return ss.str();
    }

  };

}
#endif
