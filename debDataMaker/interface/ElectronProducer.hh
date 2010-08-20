#ifndef SusyAnalysis_debDataMaker_ElectronProducer_hh_
#define SusyAnalysis_debDataMaker_ElectronProducer_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      ElectronProducer
// 
/**\class ElectronProducer ElectronProducer.hh SusyAnalysis/debDataMaker/interface/ElectronProducer.hh

 Description: <one line class summary>

 Implementation:
   Works with: reco::GsfElectron and pat::Electron

   List of parameters to steer the object with (passed in iConfig):
      int storeNElectrons,      : owned by Data<D>, mandatory in constructor
      InputTag electronTag,     : owned by Data<D>
      int selectionType,   : owned by Data<D> but decided here if set
     
   iConfig is passed only through the contructor. 

   !!!! See usage of inherited functions in Electron.hh source code !!!!

   The following fuctions should be overloaded here

      void set(const edm::Event&) (virtual):
         that implements reading variables of D from the CMSSW framework



*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id$
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/Electron.hh"
#include "SusyAnalysis/debDataMaker/interface/Producer.hh"

#include "DataFormats/PatCandidates/interface/Electron.h"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T> class ElectronProducer : public Producer<Electron> { 
 public:
  ElectronProducer(const edm::ParameterSet& iConfig);
  ElectronProducer() { 
    stdErr("  Electron<%s> configuration missing\n",
	   humanTypeId<T>().data()); 
  }

 private:
  void set_isolation_(const T&, ElectronData&); // first: input, second: output
  void set_electron_id_(const T&, ElectronData&);

 public:  
  void set(const edm::Event&);
  
};
  

//--------------------------------- Constructor -------------------------------

template<class T> 
ElectronProducer<T>::ElectronProducer(const edm::ParameterSet& iConfig)
  : Producer<Electron>(iConfig.getParameter<edm::InputTag>("electronTag"),
		       iConfig.getParameter<std::string>("name"),
		       iConfig.getParameter<int>("storeNElectrons")) {
  
  setSelectionType(iConfig.getParameter<std::string>("selectionType")); 

  stdMesg("  ElectronProducer<%s> configuration:", humanTypeId<T>().data());
  stdMesg("  \tstoreNElectrons = %d", storeNObjects());
  stdMesg("  \telectronTag = \"%s\"", tag().label().data());
  stdMesg("  \tselectionType = %s", getSelectionType().data());  
  stdMesg("  List of variables: %s", list().data());
  stdMesg("  Object is %svalid!\n", (isValid() ? "" : "not "));

}


//----------------------------------- set() -----------------------------------

template<class T> void ElectronProducer<T>::set(const edm::Event& iEvent) {
  increment_event_counter();

  if (!isValid()) return;

  edm::Handle<edm::View<T> > electronHandle;
  iEvent.getByLabel(tag(), electronHandle);
  if (!electronHandle.isValid()) {
    stdErr("ElectronProducer<%s>::set() : Invalid tag %s\n", 
	   humanTypeId<T>().data(), tag().label().data());
    setValid(false);
    return;
  }

  std::vector<std::pair<float, const T*> > electrons;

  for (typename edm::View<T>::const_iterator iElectron=electronHandle->begin();
       iElectron!=electronHandle->end(); iElectron++) {
    float pt = iElectron->pt();
    electrons.push_back(std::make_pair(pt, &(*iElectron)));
  }

  std::sort(electrons.begin(), electrons.end(),
	    std::greater<std::pair<float, const T* > >());

  clear();

  for (unsigned int i=0; i<electrons.size(); i++) {

    ElectronData electron;
    electron.oid = i;
    electron.eid = event_counter();

    const T& cmsele = *electrons[i].second;

    // pat::Electron : reco::GsfElectron : reco::RecoCandidate
    // (in LeafCandidate)
    electron.e  = cmsele.energy();
    electron.px = cmsele.px();
    electron.py = cmsele.py();
    electron.pz = cmsele.pz();
    electron.m = cmsele.mass();
    electron.pt = cmsele.pt();
    electron.et = cmsele.et();
    electron.eta = cmsele.eta();
    electron.phi = cmsele.phi();


    // reco::GsfElectron::gsfTrack() or pat::Electron::gsfTrack()
    // =--> !!! pat::Electron::gsfTrack() may be EMBEDDED !!!
    if(cmsele.gsfTrack().isNonnull()) {
      electron.has_trk = 1;
      electron.d0 = cmsele.gsfTrack()->d0();
      electron.phi_trk = cmsele.gsfTrack()->phi();
    } else {
      electron.has_trk = 0;
      electron.d0 = NOVAL_F;
      electron.phi_trk = NOVAL_F;
    }


    // Isolation information, different for RECO and PAT
    //
    set_isolation_(cmsele, electron);


    // Electron Id classification:
    //
    set_electron_id_(cmsele, electron);


    // Values set by deb::Electron::calculate()
    electron.d0_bc = NOVAL_F;
    electron.reliso = NOVAL_F;
    electron.reliso_comb = NOVAL_F; 
   
    push_back(electron);
  }
}

  
//----------------------------- set_isolation_() ------------------------------

template<> 
void ElectronProducer<reco::GsfElectron>::
set_isolation_(const reco::GsfElectron& cmsele, ElectronData& electron) {

  electron.isoR03_ecal = cmsele.dr04EcalRecHitSumEt();
  electron.isoR03_hcal = cmsele.dr04HcalTowerSumEt();
  electron.isoR03_trk = cmsele.dr04TkSumPt();
}


template<> 
void ElectronProducer<pat::Electron>::
set_isolation_(const pat::Electron& cmsele, ElectronData& electron) {

  electron.isoR03_ecal = cmsele.ecalIso(); // dr04EcalRecHitSumEt();
  electron.isoR03_hcal = cmsele.hcalIso(); // dr04HcalTowerSumEt();
  electron.isoR03_trk = cmsele.trackIso(); // dr04TkSumPt();
}


//--------------------------- set_electron_id_() ------------------------------

template<> 
void ElectronProducer<reco::GsfElectron>::
set_electron_id_(const reco::GsfElectron& cmsele, ElectronData& electron) {

  electron.loose = NOVAL_I;
  electron.tight = NOVAL_I;
}


template<> 
void ElectronProducer<pat::Electron>::
set_electron_id_(const pat::Electron& cmsele, ElectronData& electron) {

  // Skip checking if electron ID is available
  electron.loose = cmsele.electronID("eidRobustLoose");
  electron.tight = cmsele.electronID("eidRobustTight");
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
