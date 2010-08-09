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

      selectionTypes_:
         is a map that translates the string of SelectionType to an integer

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: MuonData.hh,v 1.11 2009/11/12 14:23:37 aranyi Exp $
//
//
//-----------------------------------------------------------------------------

#include <string>
#include <sstream>
#include "CONST.hh"

namespace deb {

  class MuonData {
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

                         // Inner Track (aka track) :
    int   has_trk;       // has innerTrack
    int   hits;          // number of innerTrack hits
    float d0;            // displacement of the innerTrack
    float phi_trk;       // phi of the innerTrack

                         // Global Track (aka Combined Muon) :
    int   is_combined;   // is muon a Combined Muon (has a Global Track)
    float chi2;          // chi2 of fitting the globalTrack
    float ndof;          // deg of freedom in fitting the globalTrack

                         // Outer Track (aka Standalone Muon) :
    // Not used for now
    //

                         // What track is this? Check an event with no Global
    float isoR03_ecal;   // pat::Muon::Iso == reco::Muon::isolationR03 ?
    float isoR03_hcal;   // pat::Muon::Iso == reco::Muon::isolationR03 ?
    float isoR03_trk;    // pat::Muon::trackIso == reco::Muon::isolationR03
    float ecalisodep;    // ECal Isolation Deposit
    float hcalisodep;    // HCal Isolation Deposit

                         // Muon identification :
    int tight;           // Muon ID "GlobalMuonPromptTight"

                         // Quantities set by deb::Muon::calculate()
    float d0_bc;         // d0 with respect to the primary vertex
    float reliso;        // (isoR03_ecal + isoR03_hcal + isoR03_trk) / pt


//     float time;
//     float timeerr;
//     int dttimevalid;
//     float dttime;
//     float dttimeerr;
//     float ecaltime;
//     float ecaltimeerr;
//     float ecalenergy;
//     float ecalphi;
//     float ecaltheta;
//     int   ecaldet;
//     float hcaltime;
//     float hcaltimeerr;
//     float hcalenergy;

    MuonData() { clear(); }
    ~MuonData() { }

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
      hits=NOVAL_I;
      d0=NOVAL_F;
      phi_trk=NOVAL_F;

      is_combined=NOVAL_I;
      chi2=NOVAL_F;
      ndof=NOVAL_F;

      isoR03_ecal=NOVAL_F;
      isoR03_hcal=NOVAL_F;
      isoR03_trk=NOVAL_F;
      ecalisodep=NOVAL_F;
      hcalisodep=NOVAL_F;

      tight=NOVAL_I;

      d0_bc=NOVAL_F;
      reliso=NOVAL_F;

//       time=NOVAL_F;
//       timeerr=NOVAL_F;
//       dttimevalid=NOVAL_I;
//       dttime=NOVAL_F;
//       dttimeerr=NOVAL_F;
//       ecaltime=NOVAL_F;
//       ecaltimeerr=NOVAL_F;
//       ecalenergy=NOVAL_F;
//       ecalphi=NOVAL_F;
//       ecaltheta=NOVAL_F;
//       ecaldet=NOVAL_I;
//       hcaltime=NOVAL_F;
//       hcaltimeerr=NOVAL_F;
//       hcalenergy=NOVAL_F;
    }

    std::string list(std::string prefix="") {
      std::ostringstream ss;
      ss << prefix << "e/F";
      ss << prefix << ":px/F";
      ss << prefix << ":py/F";
      ss << prefix << ":pz/F";
      ss << prefix << ":m/F";
      ss << prefix << ":pt/F";
      ss << prefix << ":et/F";
      ss << prefix << ":eta/F";
      ss << prefix << ":phi/F";

      ss << prefix << ":has_trk/I";
      ss << prefix << ":hits/I";
      ss << prefix << ":d0/F";
      ss << prefix << ":phi_trk/F";

      ss << prefix << ":is_combined/I";
      ss << prefix << ":chi2/F";
      ss << prefix << ":ndof/F";

      ss << prefix << ":isoR03_ecal/F";
      ss << prefix << ":isoR03_hcal/F";
      ss << prefix << ":isoR03_trk/F";
      ss << prefix << ":ecalisodep/F";
      ss << prefix << ":hcalisodep/F";

      ss << prefix << ":tight/I";

      ss << prefix << ":d0_bc/F";
      ss << prefix << ":reliso/F";

//       ss << prefix << ":time/F";
//       ss << prefix << ":timeerr/F";
//       ss << prefix << ":dttimevalid/I";
//       ss << prefix << ":dttime/F";
//       ss << prefix << ":dttimeerr/F";
//       ss << prefix << ":ecaltime/F";
//       ss << prefix << ":ecaltimeerr/F";
//       ss << prefix << ":ecalenergy/F";
//       ss << prefix << ":ecalphi/F";
//       ss << prefix << ":ecaltheta/F";
//       ss << prefix << ":ecaldet/I";
//       ss << prefix << ":hcaltime/F";
//       ss << prefix << ":hcaltimeerr/F";
//       ss << prefix << ":hcalenergy/F";

      return ss.str();
    }

  };

}
#endif
