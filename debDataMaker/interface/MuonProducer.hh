#ifndef SusyAnalysis_debDataMaker_MuonProducer_hh_
#define SusyAnalysis_debDataMaker_MuonProducer_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      MuonProducer
// 
/**\class MuonProducer MuonProducer.hh SusyAnalysis/debDataMaker/interface/MuonProducer.hh

 Description: <one line class summary>

 Implementation:

   List of parameters to steer the object with (passed in iConfig):
      int storeNMuons,     : owned by Data<D>, mandatory in constructor
      InputTag objectTag,  : owned by Data<D> but decided here if set
      int selectionType,   : owned by Data<D> but decided here if set


   iConfig is passed only through the contructor. 

   !!!! See usage of inherited functions in Muon.hh source code !!!!

   The following fuctions should be overloaded here:

      void set(const edm::Event&) (virtual):
         implements reading variables of D from the CMSSW framework


*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: MuonProducer.hh,v 1.7 2010/08/09 15:36:08 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/Muon.hh"
#include "SusyAnalysis/debDataMaker/interface/Producer.hh"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T> class MuonProducer : public Producer<Muon>{ 
 public:
  MuonProducer(const edm::ParameterSet&);
  MuonProducer() { 
    stdErr("  MuonProducer<%s> configuration missing\n",
	   humanTypeId<T>().data()); 
  }

 private:
  void set_isolation_(const T&, MuonData&); // first: input, second: output

 public:
  // Inherited functions to be overloaded
  void set(const edm::Event&);

  
};


//--------------------------------- Constructor -------------------------------

template<class T> 
MuonProducer<T>::MuonProducer(const edm::ParameterSet& iConfig) 
  : Producer<Muon>(iConfig.getParameter<edm::InputTag>("muonTag"),
		   iConfig.getParameter<std::string>("name"),
		   iConfig.getParameter<int>("storeNMuons")) {

  // Read tag, set defaults:
  //
  setSelectionType(iConfig.getParameter<std::string>("selectionType")); 

  stdMesg("  MuonProducer<%s> configuration:", humanTypeId<T>().data());
  stdMesg("  \tstoreNMuons = %d", storeNObjects());
  stdMesg("  \tmuonTag = \"%s\"", tag().label().data());
  stdMesg("  \tselectionType = %s", getSelectionType().data());
  stdMesg("  List of variables: %s", list().data());
  stdMesg("  Object is %svalid!\n", (isValid() ? "" : "not "));

}

//----------------------------- set_isolation_() ------------------------------

template<> 
void MuonProducer<reco::Muon>::set_isolation_(const reco::Muon& cmsmuon, 
					      MuonData& muon) {

  // reco::Muon::isolationR03()
  if (cmsmuon.isIsolationValid()) {
    muon.isoR03_ecal = cmsmuon.isolationR03().hadEt;
    muon.isoR03_hcal = cmsmuon.isolationR03().emEt;
    muon.isoR03_trk = cmsmuon.isolationR03().sumPt;
  } else {
    muon.isoR03_ecal = NOVAL_F;
    muon.isoR03_hcal = NOVAL_F;
    muon.isoR03_trk = NOVAL_F;
  }

  // I have not figured this one out, yet:
  muon.ecalisodep = NOVAL_F;
  muon.hcalisodep = NOVAL_F;

}


template<> 
void MuonProducer<pat::Muon>::set_isolation_(const pat::Muon& cmsmuon, 
					     MuonData& muon) {

  // pat::Muon::xxxIso() using reco::Muon::isolationR03()
  if (cmsmuon.isIsolationValid()) {
    muon.isoR03_ecal = cmsmuon.ecalIso(); // reco::Muon::isolationR03().hadEt
    muon.isoR03_hcal = cmsmuon.hcalIso(); // reco::Muon::isolationR03().emEt
    muon.isoR03_trk = cmsmuon.trackIso(); // reco::Muon::isolationR03().sumPt
  } else {
    muon.isoR03_ecal = NOVAL_F;
    muon.isoR03_hcal = NOVAL_F;
    muon.isoR03_trk = NOVAL_F;
  }

  // pat::Lepton::ecalIsoDeposit returns a reco::IsoDeposit()
  // has not figured it out for RECO, look at DQM or ElectorWeek analyses
  if (cmsmuon.ecalIsoDeposit()!=NULL) {
    muon.ecalisodep = cmsmuon.ecalIsoDeposit()->candEnergy();
  } else {
    muon.ecalisodep = NOVAL_F;;
  }

  // pat::Lepton::hcalIsoDeposit returns a reco::IsoDeposit()
  // has not figured it out for RECO, look at DQM or ElectorWeek analyses
  if (cmsmuon.hcalIsoDeposit()!=NULL) {
    muon.hcalisodep = cmsmuon.hcalIsoDeposit()->candEnergy();
  } else {
    muon.hcalisodep = NOVAL_F;
  }

}


//----------------------------------- set() -----------------------------------

template<class T> void MuonProducer<T>::set(const edm::Event& iEvent) {
  increment_event_counter();

  if (!isValid()) return;

  edm::Handle<edm::View<T> > muonHandle;
  iEvent.getByLabel(tag(), muonHandle);
  if (!muonHandle.isValid()){
    stdErr("MuonProducer<%s>::set() : Invalid tag %s\n", 
	   humanTypeId<T>().data(), tag().label().data());
    setValid(false);
    return;
  }
  
  std::vector<std::pair<float, const T*> > muons;  

  for (typename edm::View<T>::const_iterator iMuon=muonHandle->begin();
       iMuon!=muonHandle->end(); iMuon++) {
    float pt = iMuon->pt();
    muons.push_back(std::make_pair(pt, &(*iMuon)));
  }

  std::sort(muons.begin(), muons.end(),
	    std::greater<std::pair<float, const T* > >());

  clear();

  for (unsigned int i=0; i<muons.size(); i++) {

    MuonData muon;
    muon.oid = i;
    muon.eid = event_counter();

    const T& cmsmuon = *muons[i].second;

    // reco::Candidates
    muon.e = cmsmuon.energy();
    muon.px = cmsmuon.px();
    muon.py = cmsmuon.py();
    muon.pz = cmsmuon.pz();
    muon.m = cmsmuon.mass();
    muon.pt = cmsmuon.pt();
    muon.et = cmsmuon.et();
    muon.eta = cmsmuon.eta();
    muon.phi = cmsmuon.phi();


    // reco::Muon::innerTrack() or pat::Muon::innerTrack() == track()
    // =---> !!! pat::Muon::innerTrack() may be EMBEDDED !!!
    if(cmsmuon.innerTrack().isNonnull()) {
      muon.has_trk = 1;
      muon.hits = cmsmuon.innerTrack()->numberOfValidHits();
      muon.d0 = cmsmuon.track()->d0();
      muon.phi_trk = cmsmuon.track()->phi();
    } else {
      muon.has_trk = 0;
      muon.hits = NOVAL_I;
      muon.d0 = NOVAL_F;
      muon.phi_trk = NOVAL_F;
    }


    // reco::Muon::globalTrack() or pat::Muon::globalTrack() == combinedMuon()
    // =---> !!! pat::Muon::globalTrack() may be EMBEDDED !!!
    if(cmsmuon.globalTrack().isNonnull()) {
      muon.is_combined = 1;
      muon.chi2 = cmsmuon.globalTrack()->chi2();
      muon.ndof = cmsmuon.globalTrack()->ndof();
    } else {
      muon.is_combined = 0;
      muon.chi2 = NOVAL_F;
      muon.ndof = NOVAL_F;
    }

    // Isolation information, very different for RECO and PAT
    //
    set_isolation_(cmsmuon, muon);

    // Careful, we are reading the result of the RECO classification!!!
    // For PAT should call: pat::Muon::muonID("GlobalMuonPromptTight"):
    muon.tight  =  
      muon::isGoodMuon(cmsmuon, muon::GlobalMuonPromptTight);

    // Values set by deb::Muon::calculate()
    muon.d0_bc = NOVAL_F;
    muon.reliso = NOVAL_F;


//     //
//     // MUON TIMING, DO WE NEED THIS?
//     //
//     if (cmsmuon.isTimeValid()) {
//       muon.dttimevalid = 1;
//       muon.dttime = cmsmuon.time().timeAtIpInOut;
//       muon.dttimeerr = cmsmuon.time().timeAtIpInOutErr;
//     }

//     muon.ecalenergy = cmsmuon.calEnergy().emMax;
//     if (cmsmuon.calEnergy().ecal_id.subdetId() == EcalEndcap) {
//       EEDetId hitId(cmsmuon.calEnergy().ecal_id);
//       muon.ecalphi = hitId.ix();
//       muon.ecaltheta = hitId.iy();
//       muon.ecaldet = hitId.subdet();
//     } else if (cmsmuon.calEnergy().ecal_id.subdetId() == EcalBarrel) {
//       EBDetId hitId(cmsmuon.calEnergy().ecal_id);
//       muon.ecalphi = hitId.iphi();
//       muon.ecaltheta = atan(exp((hitId.ieta()-0.5*
// 				   (hitId.ieta()/fabs(hitId.ieta()))
// 				   )*-1.479/85.
// 				  ))*2;
//       muon.ecaldet = hitId.subdet();
//       muon.ecaltime = cmsmuon.calEnergy().ecal_time-
// 	                4.77/sin(muon.ecaltheta);
//       muon.ecaltimeerr = 33./(cmsmuon.calEnergy().emMax/0.3);
//     }

    push_back(muon);
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
