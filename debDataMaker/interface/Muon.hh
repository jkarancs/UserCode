#ifndef SusyAnalysis_debDataMaker_Muon_hh_
#define SusyAnalysis_debDataMaker_Muon_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Muon
// 
/**\class Muon Muon.hh SusyAnalysis/debDataMaker/interface/Muon.hh

 Description: <one line class summary>

 Implementation:

   List of parameters to steer the object with (passed in iConfig):
      int storeNMuons,     : owned by Data<D>, mandatory in constructor
      InputTag objectTag,  : owned by Data<D> but decided here if set
      int selectionType,   : owned by Data<D> but decided here if set
  
   iConfig is passed only through the contructor. 

   !!!! See usage of inherited functions in Data.hh source code !!!!

   The following fuctions should be overloaded here according to the exact 
   definition of D in Data<D> :

      void set(const edm::Event&) (virtual):
         that implements reading variables of D from the CMSSW framework

      void calculate(Beamspot<reco::BeamSpot>  *beamspot) (virtual):
         that calculates values that depend on other data models

      int passed(std::string selection,unsigned int i) (virtual):
         returns the result of selection. The selections are implemented in
	 this function.

*/
//
// Original Author:  Anita KAPUSI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Muon.hh,v 1.12 2009/06/29 17:40:28 akapusi Exp $
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SusyAnalysis/debDataMaker/interface/Data.hh"
#include "SusyAnalysis/debDataMaker/interface/MuonData.hh"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "SusyAnalysis/debDataMaker/interface/Beamspot.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T> class Muon : public Data<MuonData>{ 
                                                          // D:=MuonData
 public:
  Muon(const edm::ParameterSet& iConfig);
  Muon() { stdErr("  Muon<%s> configuration missing\n",typeid(T).name()); }
  inline MuonData& muon(unsigned int i) { return *data(i); } 
                                                          // just a short-hand

  // Inherited functions to be overloaded
  void set(const edm::Event&);
  void calculate (Beamspot<reco::BeamSpot> *beamspot=NULL);
  int passed(std::string,unsigned int i);

  // Introduce new variables and functions
  
};


//--------------------------------- Constructor -------------------------------
/*
   List of parameters to gear the object with (passed in iConfig):
      int storeNMuons,     : owned by Data<D>, mandatory in constructor
      InputTag muonTag,    : owned by Data<D>
      int selectionType,   : owned by Data<D>
*/

template<class T> Muon<T>::Muon(const edm::ParameterSet& iConfig) : 
  Data<MuonData>(iConfig.getParameter<int>("storeNMuons")) {
  
  setTag(iConfig.getParameter<edm::InputTag>("muonTag"));
  setSelectionType(iConfig.getParameter<std::string>("selectionType")); 

  stdMesg("  Muon<%s> configuration:", typeid(T).name());
  stdMesg("  \tstoreNMuons = %d", max_size());
  stdMesg("  \tmuonTag = \"%s\"", tag().label().data());
  stdMesg("  \tselectionType = %s", getSelectionType().data());
  stdMesg("  List of variables: %s\n", muon(0).list().data());
  stdMesg("  Object is %svalid!\n", (isValid() ? "" : "not "));

}

//----------------------------------- set() -----------------------------------

template<class T> void Muon<T>::set(const edm::Event& iEvent) {

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
void Muon<T>::calculate (Beamspot<reco::BeamSpot>  *beamspot){ 

  if (!isValid()) return;
  
  for (unsigned int i=0; i<size_; i++) {
    
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

  
//--------------------------------- passed() ----------------------------------

template<class T> int Muon<T>::passed(std::string selection,unsigned int i) { 

  if (!isValid()) return NOVAL_I;


  if(selection.compare("RefAna4JetMetMuon")==0){
    if(muon(i).tight==NOVAL_I||
       muon(i).pt==NOVAL_F||
       muon(i).eta==NOVAL_F||
       //muon(i).reliso==NOVAL_F||
       //muon(i).hcalisodep==NOVAL_F||
       //muon(i).ecalisodep==NOVAL_F||
       muon(i).isoR03_trk==NOVAL_F||
       muon(i).isoR03_hcal==NOVAL_F||
       muon(i).isoR03_ecal==NOVAL_F||
       muon(i).has_trk==NOVAL_I||
       muon(i).is_combined==NOVAL_I){
      stdErr("Muon::passed() : NOVAL value in the cut criteria");
      return NOVAL_I;
    }
    if((muon(i).bc_d0==NOVAL_F||muon(i).hits==NOVAL_F)&&
       muon(i).has_trk==0){
      return 0;
    }
    if((muon(i).chi2==NOVAL_F||muon(i).ndof==NOVAL_F)&&
       muon(i).is_combined==0){
      return 0;
    }
    if((muon(i).bc_d0==NOVAL_F||muon(i).hits==NOVAL_F)&&
       muon(i).has_trk==1){
      stdErr("Muon::passed() : NOVAL value in the cut criteria(has_trk=1)");  
      return NOVAL_I;
    }
    if((muon(i).chi2==NOVAL_F||muon(i).ndof==NOVAL_F)&&
       muon(i).is_combined==1){
      stdErr(
	    "Muon::passed() : NOVAL value in the cut criteria(is_combined=1)");
      return NOVAL_I;
    }

    if(muon(i).tight==1&&
       muon(i).pt>=10.0&&
       TMath::Abs(muon(i).eta)<=2.1&&
       //muon(i).reliso<0.1&&
       muon(i).ndof!=0.0&&
       muon(i).chi2/muon(i).ndof<10.0&&
       TMath::Abs(muon(i).bc_d0)<=0.2&&
       muon(i).hits>=11.0&&
       //muon(i).hcalisodep<6.0&&
       //muon(i).ecalisodep<4.0
       muon(i).isoR03_trk<6.0&&
       muon(i).isoR03_hcal<6.0&&
       muon(i).isoR03_ecal<6.0

      ){
      return 1;
    }
    return 0;
  }
  
  
  return NOVAL_I;
} 
  

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
