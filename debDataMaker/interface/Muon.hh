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

      void calculate(Beamspot<reco::BeamSpot> & beamspot) (virtual):
         that calculates values that depend on other data models

      int passed(std::string,int i) (virtual):
         if selectionType is set, returns the result of the selections. The
         selections are implemented in this function.

*/
//
// Original Author:  Anita KAPUSI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Muon.hh,v 1.29.2.2 2010/09/16 09:03:24 veszpv Exp $
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
  void calculate (Beamspot<reco::BeamSpot> & beamspot);
  int passed(std::string,int i);

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
  stdMesg("\tstoreNMuons = %d", max_size());
  stdMesg("\tmuonTag = \"%s\"", tag().label().data());
  stdMesg("\tselectionType = %s", getSelectionType().data());
  stdMesg("  List of variables: %s\n", muon(0).list().data());
  stdMesg("valid vagyok vagy megsem, Object is valid vagy Object is invalid");

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

  size_=0;
  for (unsigned int i=0; i<max_size(); i++) {
    if (muons.size()>i) {
      size_=i+1;
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
      if(muons[i].second->track().isNonnull()){
	muon(i).hits=muons[i].second->track()->numberOfValidHits();
	muon(i).d0=muons[i].second->track()->d0();
	muon(i).phitrack=muons[i].second->track()->phi();
      }
      else{
	muon(i).hits=NOVAL_F;
	muon(i).d0=NOVAL_F;
	muon(i).phitrack=NOVAL_F;
      }
      if(muons[i].second->combinedMuon().isNonnull()){
	muon(i).chi2=muons[i].second->combinedMuon()->chi2();
	muon(i).ndof=muons[i].second->combinedMuon()->ndof();
      }
      else{
	muon(i).chi2=NOVAL_F;
	muon(i).ndof=NOVAL_F;
      }
      muon(i).mutype=muons[i].second->isGood(reco::Muon::GlobalMuonPromptTight);
      muon(i).hcalisodep=muons[i].second->hcalIsoDeposit()->candEnergy();
      muon(i).ecalisodep=muons[i].second->ecalIsoDeposit()->candEnergy();
    } 
    else {
      muon(i).e=NOVAL_F;
      muon(i).px=NOVAL_F;
      muon(i).py=NOVAL_F;
      muon(i).pz=NOVAL_F;
      muon(i).m=NOVAL_F;
      muon(i).pt=NOVAL_F;
      muon(i).et=NOVAL_F;
      muon(i).eta=NOVAL_F;
      muon(i).phi=NOVAL_F;
      muon(i).isoR03_trk=NOVAL_F;
      muon(i).isoR03_hcal=NOVAL_F;
      muon(i).isoR03_ecal=NOVAL_F;
      muon(i).hits=NOVAL_F;
      muon(i).chi2=NOVAL_F;
      muon(i).ndof=NOVAL_F;
      muon(i).d0=NOVAL_F;
      muon(i).phitrack=NOVAL_F;
      muon(i).mutype=NOVAL_F;
      muon(i).hcalisodep=NOVAL_F;
      muon(i).ecalisodep=NOVAL_F;
    }      
  }
}
  
//-------------------------------- calculate() --------------------------------

template<class T> 
void Muon<T>::calculate (Beamspot<reco::BeamSpot> & beamspot){ 

  if (!isValid()) return;


  for (unsigned int i=0; i<max_size(); i++) {

    if(muon(i).d0!=NOVAL_F&&
       beamspot.beamspot(0).beamspotx!=NOVAL_F&&
       beamspot.beamspot(0).beamspoty!=NOVAL_F&&
       muon(i).phitrack!=NOVAL_F) 
      {
	muon(i).bcd0=muon(i).d0
	  -beamspot.beamspot(0).beamspotx*TMath::Sin(muon(i).phitrack)
	  +beamspot.beamspot(0).beamspoty*TMath::Cos(muon(i).phitrack);
      }
    muon(i).bcd0=NOVAL_F;

    if(muon(i).isoR03_ecal!=NOVAL_F&&
       muon(i).isoR03_hcal!=NOVAL_F&&
       muon(i).isoR03_trk!=NOVAL_F&&
       muon(i).pt!=NOVAL_F&&muon(i).pt!=0)
      {
	muon(i).reliso=(muon(i).isoR03_ecal
			   +muon(i).isoR03_hcal
			   +muon(i).isoR03_trk)
	               /muon(i).pt;
      }
    muon(i).reliso=NOVAL_F;
      
    //for (i=0;i<max_size;i++){
    //  muon.pass=passed("RA4mu",i); //bitkodolt ize
    //}
  }

}

  
//--------------------------------- passed() ----------------------------------

template<class T> int Muon<T>::passed(std::string selection,int i) { 

  if (!isValid()) return NOVAL_I;


  if(selection.compare("RA4mu")==0){
    if(muon(i).mutype==1.0&&muon(i).mutype!=NOVAL_F&&
       muon(i).pt>=20.0&&muon(i).pt!=NOVAL_F&&
       TMath::Abs(muon(i).eta)<=2.1&&muon(i).eta!=NOVAL_F&&
       muon(i).reliso<0.1&&muon(i).reliso!=NOVAL_F&&
       muon(i).ndof!=0.0&&muon(i).ndof!=NOVAL_F&&
       muon(i).chi2!=NOVAL_F&&
       muon(i).chi2/muon(i).ndof<10.0&&
       TMath::Abs(muon(i).bcd0)<=0.2&&muon(i).bcd0!=NOVAL_F&&
       muon(i).hits>=11.0&&muon(i).hits!=NOVAL_F&&
       muon(i).hcalisodep<6.0&&muon(i).hcalisodep!=NOVAL_F&&
       muon(i).ecalisodep<4.0&&muon(i).ecalisodep!=NOVAL_F){
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
