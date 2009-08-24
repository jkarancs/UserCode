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
// Original Author:  Anita KAPUSI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: MuonProducer.hh,v 1.3 2009/08/22 17:23:52 aranyi Exp $
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SusyAnalysis/debDataMaker/interface/Muon.hh"
#include "SusyAnalysis/debDataMaker/interface/Producer.hh"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"


namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T> class MuonProducer : public Producer<Muon>{ 
 public:
  MuonProducer(const edm::ParameterSet& iConfig);
  MuonProducer() { 
    stdErr("  MuonProducer<%s> configuration missing\n",
	   humanTypeId<T>().data()); 
  }

  // Inherited functions to be overloaded
  void set(const edm::Event&);
  
};


//--------------------------------- Constructor -------------------------------
/*
   List of parameters to gear the object with (passed in iConfig):
      int storeNMuons,     : owned by Data<D>, mandatory in constructor
      InputTag muonTag,    : owned by Data<D>
      int selectionType,   : owned by Data<D>
*/

template<class T> 
MuonProducer<T>::MuonProducer(const edm::ParameterSet& iConfig) 
  : Producer<Muon>(iConfig.getParameter<edm::InputTag>("muonTag"),
		   iConfig.getParameter<std::string>("name"),
		   iConfig.getParameter<int>("storeNMuons")) {

  setSelectionType(iConfig.getParameter<std::string>("selectionType")); 

  stdMesg("  MuonProducer<%s> configuration:", humanTypeId<T>().data());
  stdMesg("  \tstoreNMuons = %d", storeNObjects());
  stdMesg("  \tmuonTag = \"%s\"", tag().label().data());
  stdMesg("  \tselectionType = %s", getSelectionType().data());
  stdMesg("  List of variables: %s", list().data());
  stdMesg("  Object is %svalid!\n", (isValid() ? "" : "not "));

}

//----------------------------------- set() -----------------------------------

template<class T> void MuonProducer<T>::set(const edm::Event& iEvent) {

  if (!isValid()) return;

  edm::InputTag mcMuonTag("genParticles","","HLT");
	
  edm::Handle<edm::View<reco::Candidate> > particleHandle;
  iEvent.getByLabel(mcMuonTag, particleHandle );

  std::vector<const reco::Candidate *> genParticles;
  genParticles.clear();
  for(edm::View<reco::Candidate>::const_iterator p = particleHandle->begin();
    p != particleHandle->end(); ++ p ) {
    genParticles.push_back( & * p );
  }

  edm::Handle<edm::View<T> > muonHandle;
  iEvent.getByLabel(tag(), muonHandle);
  if (!muonHandle.isValid()){
    stdErr("set() : Invalid tag %s", tag().label().data());
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
    MuonData new_obj;
    push_back(new_obj);

    //functions from CMSSW/ DataFormats/ Candidate/ interface/ Particle.h
    muon(i).e = muons[i].second->energy();
    muon(i).px= muons[i].second->px();
    muon(i).py= muons[i].second->py();
    muon(i).pz= muons[i].second->pz();
    muon(i).m= muons[i].second->mass();
    muon(i).pt=muons[i].second->pt();
    muon(i).et=muons[i].second->et();
    muon(i).eta=muons[i].second->eta();
    muon(i).phi=muons[i].second->phi();
    muon(i).isoR03_trk=muons[i].second->trackIso();
    muon(i).isoR03_hcal=muons[i].second->hcalIso();
    muon(i).isoR03_ecal=muons[i].second->ecalIso();
    // This is the innerTrack() - track()
    if(muons[i].second->track().isNonnull()) {
      muon(i).has_trk=1;
      muon(i).hits=muons[i].second->track()->numberOfValidHits();
      muon(i).d0=muons[i].second->track()->d0();
      muon(i).phi_trk=muons[i].second->track()->phi();
    }
    else {
      muon(i).has_trk=0;
      muon(i).hits=NOVAL_F;
      muon(i).d0=NOVAL_F;
      muon(i).phi_trk=NOVAL_F;
    }
    // This is the globalTrack() - combinedMuon()
    if(muons[i].second->combinedMuon().isNonnull()) {
      muon(i).is_combined=1;
      muon(i).chi2=muons[i].second->combinedMuon()->chi2();
      muon(i).ndof=muons[i].second->combinedMuon()->ndof();
    }
    else {
      muon(i).is_combined=0;
      muon(i).chi2=NOVAL_F;
      muon(i).ndof=NOVAL_F;
    }
    muon(i).tight=muons[i].second->isGood(reco::Muon::GlobalMuonPromptTight);
    muon(i).hcalisodep=muons[i].second->hcalIsoDeposit()->candEnergy();
    muon(i).ecalisodep=muons[i].second->ecalIsoDeposit()->candEnergy();
    muon(i).bc_d0=NOVAL_F;
    muon(i).reliso=NOVAL_F;

#if DEB_PROJECT_VERSION >= DEB_CMSSW_VERSION_31X
#line __LINE__ "Compiling for CMSSW_3_1_X"

    if (muons[i].second->isTimeValid()) {
      muon(i).dttimevalid=1;
      muon(i).dttime=muons[i].second->time().timeAtIpInOut;
      muon(i).dttimeerr=muons[i].second->time().timeAtIpInOutErr;
    }

    muons(i).ecalenergy=muons[i].second->calEnergy().emMax;
    if (muons[i].second->calEnergy().ecal_id.subdetId()==EcalEndcap) {
      EEDetId hitId(muons[i].second->calEnergy().ecal_id);
      muons(i).ecalphi=hitId.ix();
      muons(i).ecaltheta=hitId.iy();
      muons(i).ecaldet=hitId.subdet();
    } else if (muons[i].second->calEnergy().ecal_id.subdetId()==EcalBarrel) {
      EBDetId hitId(muons[i].second->calEnergy().ecal_id);
      muons(i).ecalphi=hitId.iphi();
      muons(i).ecaltheta=atan(exp((hitId.ieta()-0.5*
				   (hitId.ieta()/fabs(hitId.ieta()))
				   )*-1.479/85.
				  ))*2;
      muons(i).ecaldet=hitId.subdet();
      muons(i).ecaltime=muons[i].second->calEnergy().ecal_time-
	                4.77/sin(muons(i).ecaltheta);
      muons(i).ecaltimeerr=33./(muons[i].second->calEnergy().emMax/0.3);
    }

#endif

    const reco::Candidate * gl = muons[i].second->genLepton();
    
    std::vector<const reco::Candidate *>::const_iterator found;

    int idx=-1;

    if (gl==NULL){
      muon(i).gen=NOVAL_I;
    }else{ 


      found = find(genParticles.begin(), genParticles.end(), gl);
       if(found != genParticles.end()) 
 	idx = found - genParticles.begin(); 

        muon(i).gen = idx;
    }

  }
}
  
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
