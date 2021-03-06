#ifndef SusyAnalysis_debDataMaker_Electron_hh_
#define SusyAnalysis_debDataMaker_Electron_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Electron
// 
/**\class Electron Electron.hh SusyAnalysis/debDataMaker/interface/Electron.hh

 Description: <one line class summary>

 Implementation:

   List of parameters to steer the object with (passed in iConfig):
      int storeNElectronects,   : owned by Data<D>, mandatory in constructor
      InputTag objectTag,  : owned by Data<D> but decided here if set
      int selectionType,   : owned by Data<D> but decided here if set
      int correctionType   : owned by this class

   iConfig is passed only through the contructor. 

   !!!! See usage of inherited functions in Data.hh source code !!!!

   The following fuctions should be overloaded here according to the exact 
   definition of D in Data<D> :

      void clear()
         that sets all the variables in the i^th D element returned by *data(i)
	 (or electron(i) if implemented) to a default value 
         (NOVAL_X where X= I,F,D)

      void set(const edm::Event&) (virtual):
         that implements reading variables of D from the CMSSW framework

      void calculate(Beamspot<reco::BeamSpot> & beamspot) (virtual):
         that calculates values that depend on other data models

      std::string list(std::string prefix="") (virtual): 
         that makes a list of the variables in a single D for a TTree::Branch()

      int passed(std::string,int i) (virtual):
         if selectionType is set, returns the result of the selections. The
         selections are implemented in this function.

*/
//
// Original Author:  Anita KAPUSI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Electron.hh,v 1.24.2.2 2010/09/16 09:03:24 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SusyAnalysis/debDataMaker/interface/Data.hh"
#include "SusyAnalysis/debDataMaker/interface/ElectronData.hh"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "SusyAnalysis/debDataMaker/interface/Beamspot.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T> class Electron : public Data<ElectronData>{ 
                                                          // D:=ElectronData
public:
  Electron(const edm::ParameterSet& iConfig);
  Electron() { stdErr("  Electron<%s> configuration missing\n",
		      typeid(T).name()); }
  inline ElectronData& electron(unsigned int i) { return *data(i); } 
  // just a short-hand
  
  // Inherited functions to be overloaded
  void set(const edm::Event&);
  void calculate (Beamspot<reco::BeamSpot> & beamspot);
  int passed(std::string selection,int i);
  
  // Introduce new variables and functions
  
};
  

//--------------------------------- Constructor -------------------------------
/*
   List of parameters to gear the object with (passed in iConfig):
      int storeNElectrons,      : owned by Data<D>, mandatory in constructor
      InputTag electronTag,     : owned by Data<D>
      int selectionType,        : owned by Data<D>      
*/

template<class T> Electron<T>::Electron(const edm::ParameterSet& iConfig) : 
  Data<ElectronData>(iConfig.getParameter<int>("storeNElectrons")) {
  
  setTag(iConfig.getParameter<edm::InputTag>("electronTag"));
  setSelectionType(iConfig.getParameter<std::string>("selectionType"));

  stdMesg("  Electron<%s> configuration:", typeid(T).name());
  stdMesg("\tstoreNElectrons = %d", max_size());
  stdMesg("\telectronTag = \"%s\"", tag().label().data());
  stdMesg("\tselectionType = %s", getSelectionType().data());
  stdMesg("  List of variables: %s\n", electron(0).list().data());

}

//----------------------------------- set() -----------------------------------

template<class T> void Electron<T>::set(const edm::Event& iEvent) {

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

  size_=0;
  for (unsigned int i=0; i<max_size(); i++) {
    if (electrons.size()>i) {
      size_=i+1;
      //functions from CMSSW/ DataFormats/ Candidate/ interface/ Particle.h
      electron(i).e = electrons[i].second->energy();
      electron(i).px= electrons[i].second->px();
      electron(i).py= electrons[i].second->py();
      electron(i).pz= electrons[i].second->pz();
      electron(i).m= electrons[i].second->mass();
      electron(i).pt=electrons[i].second->pt();
      electron(i).et=electrons[i].second->et();
      electron(i).eta=electrons[i].second->eta();
      electron(i).phi=electrons[i].second->phi();
      electron(i).isoR03_trk=electrons[i].second->trackIso();
      electron(i).isoR03_hcal=electrons[i].second->hcalIso();
      electron(i).isoR03_ecal=electrons[i].second->ecalIso();
      if(electrons[i].second->gsfTrack().isNonnull())
	{
	  electron(i).d0=electrons[i].second->gsfTrack()->d0();
	  electron(i).phitrack=electrons[i].second->gsfTrack()->phi();
	}
      else
	{
	  electron(i).d0=NOVAL_F;
	  electron(i).phitrack=NOVAL_F;
	}
      electron(i).idtight=electrons[i].second->electronID("eidRobustTight");
      electron(i).idloose=electrons[i].second->electronID("eidRobustLoose");
    } 
    else {
      electron(i).e=NOVAL_F;
      electron(i).px=NOVAL_F;
      electron(i).py=NOVAL_F;
      electron(i).pz=NOVAL_F;
      electron(i).m=NOVAL_F;
      electron(i).pt=NOVAL_F;
      electron(i).et=NOVAL_F;
      electron(i).eta=NOVAL_F;
      electron(i).phi=NOVAL_F;
      electron(i).isoR03_trk=NOVAL_F;
      electron(i).isoR03_hcal=NOVAL_F;
      electron(i).isoR03_ecal=NOVAL_F;
      electron(i).d0=NOVAL_F;
      electron(i).phitrack=NOVAL_F;
      electron(i).idtight=NOVAL_F;
      electron(i).idloose=NOVAL_F;
    }      
  }
}
  
//-------------------------------- calculate() --------------------------------

template<class T> 
void Electron<T>::calculate (Beamspot<reco::BeamSpot> & beamspot) { 

  if (!isValid()) return;

  for (unsigned int i=0; i<max_size(); i++) {
    if(electron(i).d0!=NOVAL_F&&
       beamspot.beamspot(0).beamspotx!=NOVAL_F&&
       beamspot.beamspot(0).beamspoty!=NOVAL_F&&
       electron(i).phitrack!=NOVAL_F){
    electron(i).bcd0=electron(i).d0
              -beamspot.beamspot(0).beamspotx*TMath::Sin(electron(i).phitrack)
              +beamspot.beamspot(0).beamspoty*TMath::Cos(electron(i).phitrack);
    }
    else{
      electron(i).bcd0=NOVAL_F;
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
    else{
      electron(i).reliso=NOVAL_F;
    }
    //for (i=0;i<max_size;i++){
    //  electron.pass=passed("RA4mu",i); //bitkodolt ize
    //}
  }
  
}
 
//--------------------------------- passed() ----------------------------------

template<class T> int Electron<T>::passed(std::string selection, int i) {

  if (!isValid()) return NOVAL_I;

  
  if(selection.compare("RA4mu")==0){
    if(electron(i).pt>=20.0&&electron(i).pt!=NOVAL_F&&
       TMath::Abs(electron(i).eta)<=2.5&&electron(i).eta!=NOVAL_F&&
       electron(i).idtight==1.0&&electron(i).idtight!=NOVAL_F&&
       electron(i).reliso<0.1&&electron(i).reliso!=NOVAL_F&&
       TMath::Abs(electron(i).bcd0)<=0.2&&electron(i).bcd0!=NOVAL_F){
      return 1;
    }      
    return 0;
  }


  if(getSelectionType().compare("RA4el")==0){
    if(electron(i).pt>=20.0&&electron(i).pt!=NOVAL_F&&
       TMath::Abs(electron(i).eta)<=2.5&&electron(i).eta!=NOVAL_F&&
       (TMath::Abs(electron(i).eta)<1.47||
	TMath::Abs(electron(i).eta)>1.567)&&
       electron(i).idloose==1.0&&electron(i).idloose!=NOVAL_F&&
       electron(i).reliso<0.1&&electron(i).reliso!=NOVAL_F&&
       TMath::Abs(electron(i).bcd0)<=0.2&&electron(i).bcd0!=NOVAL_F){
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
