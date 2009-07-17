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

      void calculate(Beamspot<reco::BeamSpot>  *beamspot) (virtual):
         calculates values that depend on other data models


*/
//
// Original Author:  Anita KAPUSI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: MuonProducer.hh,v 1.13 2009/07/14 12:56:05 aranyi Exp $
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SusyAnalysis/debDataMaker/interface/Muon.hh"
#include "SusyAnalysis/debDataMaker/interface/Producer.hh"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "SusyAnalysis/debDataMaker/interface/Beamspot.hh"

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
  void calculate (Beamspot<reco::BeamSpot> *beamspot=NULL);
  
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

  }
}
  
//-------------------------------- calculate() --------------------------------

template<class T> 
void MuonProducer<T>::calculate (Beamspot<reco::BeamSpot>  *beamspot){ 

  if (!isValid()) return;
  
  for (size_t i=0; i<size(); i++) {
    
    muon(i).bc_d0=NOVAL_F;
    muon(i).reliso=NOVAL_F;

    if(muon(i).d0!=NOVAL_F&&
       (*beamspot).beamspot(0).beamspotx!=NOVAL_F&&
       (*beamspot).beamspot(0).beamspoty!=NOVAL_F&&
       muon(i).phi_trk!=NOVAL_F) {
	muon(i).bc_d0=muon(i).d0 
	  -(*beamspot).beamspot(0).beamspotx*TMath::Sin(muon(i).phi_trk)
	  +(*beamspot).beamspot(0).beamspoty*TMath::Cos(muon(i).phi_trk);
      } 
   
    if(muon(i).isoR03_ecal!=NOVAL_F&&
       muon(i).isoR03_hcal!=NOVAL_F&&
       muon(i).isoR03_trk!=NOVAL_F&&
       muon(i).pt!=NOVAL_F&&muon(i).pt!=0) {
	muon(i).reliso=(muon(i).isoR03_ecal 
			   +muon(i).isoR03_hcal
			   +muon(i).isoR03_trk)
	               /muon(i).pt;
      } 
  }

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
