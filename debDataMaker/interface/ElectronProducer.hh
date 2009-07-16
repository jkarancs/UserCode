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

   List of parameters to steer the object with (passed in iConfig):
      int storeNElectrons,      : owned by Data<D>, mandatory in constructor
      InputTag electronTag,     : owned by Data<D>
      int selectionType,   : owned by Data<D> but decided here if set
     
   iConfig is passed only through the contructor. 

   !!!! See usage of inherited functions in Electron.hh source code !!!!

   The following fuctions should be overloaded here

      void set(const edm::Event&) (virtual):
         that implements reading variables of D from the CMSSW framework

      void calculate(Beamspot<reco::BeamSpot>  *beamspot) (virtual):
         that calculates values that depend on other data models

*/
//
// Original Author:  Anita KAPUSI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $$
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SusyAnalysis/debDataMaker/interface/Electron.hh"
#include "SusyAnalysis/debDataMaker/interface/Producer.hh"
#include "SusyAnalysis/debDataMaker/interface/Beamspot.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T> class ElectronProducer : public Producer<Electron> { 
 public:
  ElectronProducer(const edm::ParameterSet& iConfig);
  ElectronProducer() { 
    stdErr("  Electron<%s> configuration missing\n",
	   humanTypeId<T>().data()); 
  }
  
  // Inherited functions to be overloaded
  void set(const edm::Event&);
  void calculate (Beamspot<reco::BeamSpot>  *beamspot=NULL);
  
};
  

//--------------------------------- Constructor -------------------------------

template<class T> 
ElectronProducer<T>::ElectronProducer(const edm::ParameterSet& iConfig)
  : Producer<Electron>(iConfig.getParameter<edm::InputTag>("electronTag"),
		       iConfig.getParameter<std::string>("name"),
		       iConfig.getParameter<int>("storeNElectrons")) {
  
  setSelectionType(iConfig.getParameter<std::string>("selectionType")); 

  stdMesg("  Electron<%s> configuration:", humanTypeId<T>().data());
  stdMesg("  \tstoreNElectrons = %d", storeNObjects());
  stdMesg("  \telectronTag = \"%s\"", tag().label().data());
  stdMesg("  \tselectionType = %s", getSelectionType().data());  
  stdMesg("  List of variables: %s", list().data());
  stdMesg("  Object is %svalid!\n", (isValid() ? "" : "not "));

}

//----------------------------------- set() -----------------------------------

template<class T> void ElectronProducer<T>::set(const edm::Event& iEvent) {

  if (!isValid()) return;

  edm::Handle<edm::View<T> > electronHandle;
  iEvent.getByLabel(tag(), electronHandle);
  if (!electronHandle.isValid()){
    stdErr("set() : Invalid tag %s", tag().label().data());
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
    ElectronData new_obj;
    push_back(new_obj);

    //functions from CMSSW/ DataFormats/ Candidate/ interface/ Particle.h
    electron(i).e = electrons[i].second->energy();
    electron(i).px= electrons[i].second->px();
    electron(i).py= electrons[i].second->py();
    electron(i).pz= electrons[i].second->pz();
    electron(i).m= electrons[i].second->mass();
    electron(i).p=electrons[i].second->p();
    electron(i).pt=electrons[i].second->pt();
    electron(i).et=electrons[i].second->et();
    electron(i).eta=electrons[i].second->eta();
    electron(i).phi=electrons[i].second->phi();
    electron(i).isoR03_trk=electrons[i].second->trackIso();
    electron(i).isoR03_hcal=electrons[i].second->hcalIso();
    electron(i).isoR03_ecal=electrons[i].second->ecalIso();
    if(electrons[i].second->gsfTrack().isNonnull()) {
      electron(i).has_trk=1;
      electron(i).d0=electrons[i].second->gsfTrack()->d0();
      electron(i).phi_trk=electrons[i].second->gsfTrack()->phi();
    }
    else {
      electron(i).has_trk=0;
      electron(i).d0=NOVAL_F;
      electron(i).phi_trk=NOVAL_F;
    }
    electron(i).tight=electrons[i].second->electronID("eidRobustTight");
    electron(i).loose=electrons[i].second->electronID("eidRobustLoose");
    electron(i).bc_d0=NOVAL_F;
    electron(i).reliso=NOVAL_F; 
    
  }
}
  
//-------------------------------- calculate() --------------------------------

template<class T> 
void ElectronProducer<T>::calculate(Beamspot<reco::BeamSpot> *beamspot) { 

  if (!isValid()) return;

  if(beamspot==NULL){
    for (unsigned int i=0; i<max_size(); i++) {
      electron(i).bc_d0=NOVAL_F;
      electron(i).reliso=NOVAL_F;
    }
    return;
  }
  
  for (unsigned int i=0; i<size(); i++) {

    electron(i).bc_d0=NOVAL_F;
    electron(i).reliso=NOVAL_F;

    if(electron(i).d0!=NOVAL_F&&
       (*beamspot).beamspot(0).beamspotx!=NOVAL_F&&
       (*beamspot).beamspot(0).beamspoty!=NOVAL_F&&
       electron(i).phi_trk!=NOVAL_F){
    electron(i).bc_d0=electron(i).d0
            -(*beamspot).beamspot(0).beamspotx*TMath::Sin(electron(i).phi_trk)
            +(*beamspot).beamspot(0).beamspoty*TMath::Cos(electron(i).phi_trk);
    }
    
    if(electron(i).isoR03_ecal!=NOVAL_F&&
       electron(i).isoR03_hcal!=NOVAL_F&&
       electron(i).isoR03_trk!=NOVAL_F&&
       electron(i).et!=NOVAL_F&&electron(i).et!=0){
      electron(i).reliso=(electron(i).isoR03_ecal
			  +electron(i).isoR03_hcal
			  +electron(i).isoR03_trk)
	                  /electron(i).et;
    }
  }
  
}
 
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
