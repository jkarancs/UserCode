#ifndef SusyAnalysis_debDataMaker_McParticle_hh_
#define SusyAnalysis_debDataMaker_McParticle_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      McParticle
// 
/**\class McParticle McParticle.hh 
		SusyAnalysis/debDataMaker/interface/McParticle.hh

 Description:


 Implementation:

   List of parameters to steer the object with (passed in iConfig):
      edm::InputTag triggerResults_,       : owned by this class
      std::vector<std::string> pathNames_, : owned by this class    

   iConfig is passed only through the contructor. 

   !!!! See usage of inherited functions in Data.hh source code !!!!

   The following fuctions should be overloaded here according to the exact 
   definition of D in Data<D> :

      void set(const edm::Trigger&) (virtual):
         that implements reading variables of D from the CMSSW framework

      void calculate() (virtual):
         that calculates values that depend on other data models

      int passed(std::string selection) (virtual):
         if selectionType is set, returns the result of the selections. The
         selections are implemented in this function.

*/
//
// Original Author:  Attila ARANYI
//         Created:  Wed Jun 03 10:28:26 CET 2009
// $Id: McParticle.hh,v 1.12 2009/07/14 13:20:27 aranyi Exp $
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SusyAnalysis/debDataMaker/interface/Data.hh"
#include "SusyAnalysis/debDataMaker/interface/McParticleData.hh"
#include "SusyAnalysis/debDataMaker/interface/CMSSWTools.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T,int N> class McParticle : 
public Data<McParticleData<N> >{
						// D:=ParticleData

 public:
	 
  McParticle(const edm::ParameterSet& iConfig);
  McParticle() { stdErr("  Process<%s> configuration missing\n", 
		     typeid(T).name()); }
  inline McParticleData<N>& mcParticle(unsigned int i) 
    { return *Data<McParticleData<N> >::data(i); }
  // Inherited functions to be overloaded
  void set(const edm::Event&);
  void calculate (McParticleData<2> *mcParticleData=NULL);
  int passed(std::string selection,unsigned int i);

  // Introduce new variables and functions
  

 private:
  std::vector<int> mcParticlePdgId_;
  int mcParticleStatus_;
  std::string sortBy_;

  std::vector<const T *> genParticles;

  bool isEqualPdg(int,std::vector<int>);

};

//--------------------------------- Constructor -------------------------------

template<class T,int N> McParticle<T,N>::
  McParticle(const edm::ParameterSet& iConfig) : 
  Data<McParticleData<N> >(iConfig.getParameter<int>("storeNParticles")){

  // Read tag, set defaults:
  //

  Data<McParticleData<N> >::setTag(
    iConfig.getParameter<edm::InputTag>("mcParticleTag"));
  Data<McParticleData<N> >::setSelectionType(
    iConfig.getParameter<std::string>("selectionType"));

  mcParticlePdgId_=
    (iConfig.getParameter<std::vector<int> >("mcParticlePdgId"));
  mcParticleStatus_=
    (iConfig.getParameter<int>("mcParticleStatus"));

  sortBy_=iConfig.getParameter<std::string>("sortBy");


}

//----------------------------------- set() -----------------------------------
template<class T,int N> void McParticle<T,N>::set(const edm::Event& iEvent) {
if (!Data<McParticleData<N> >::isValid()) return;

  edm::Handle<edm::View<T> > particleHandle;
  iEvent.getByLabel(Data<McParticleData<N> >::tag(), particleHandle );
  if (!particleHandle.isValid()){
    stdErr("set() : Invalid tag %s", Data<McParticleData<N> >::
      tag().label().data());
    return;
  }


  typename std::vector<const T *>::const_iterator found;

  for(typename edm::View<T>::const_iterator p = particleHandle->begin();
    p != particleHandle->end(); ++ p ) {
    genParticles.push_back( & * p );
  }


  std::vector<std::pair<float, const T*> > particles;

  int idx=-1;

  for(typename edm::View<T>::const_iterator iParticle = particleHandle->begin();
    iParticle != particleHandle->end(); ++ iParticle ) {

    if (isEqualPdg(iParticle->pdgId(),mcParticlePdgId_) && 
        mcParticleStatus_   == iParticle->status()){

      idx =  iParticle - particleHandle->begin();
  
      float par = iParticle->pt();
      if (sortBy_=="pt") par=iParticle->pt();
      particles.push_back(std::make_pair(par, &(*iParticle)));
    }

  }

  std::sort(particles.begin(), particles.end(),
    std::greater<std::pair<float, const T* > >());

  Data<McParticleData<N> >::clear(); // clear the previous event from container
  for (unsigned int i=0; i<particles.size(); i++) {
    McParticleData<N> new_obj; // size_=i+1;
    push_back(new_obj); // size_=i+1;
    
    mcParticle(i).e = particles[i].second->energy();
    mcParticle(i).px = particles[i].second->px();
    mcParticle(i).py = particles[i].second->py();
    mcParticle(i).pz = particles[i].second->pz();
    mcParticle(i).m = particles[i].second->mass();
    mcParticle(i).p = particles[i].second->p();
    mcParticle(i).et = particles[i].second->et();
    mcParticle(i).pt = particles[i].second->pt();
    mcParticle(i).phi = particles[i].second->phi();
    mcParticle(i).eta = particles[i].second->eta();

    // get particle idx
    //

    const T * mo = particles[i].second;

    found = find(genParticles.begin(), genParticles.end(), mo);
      if(found != genParticles.end()) 
	idx = found - genParticles.begin();

    mcParticle(i).idx=idx;

    // get particle's first mother idx
    //

    mo = particles[i].second->mother(0);

    found = find(genParticles.begin(), genParticles.end(), mo);
      if(found != genParticles.end()) 
	idx = found - genParticles.begin();                  
      
    mcParticle(i).mo1 = idx;
    
    mcParticle(i).pdg=particles[i].second->pdgId();
    mcParticle(i).stat = particles[i].second->status();
    
  }

}
  
//-------------------------------- calculate() --------------------------------

template<class T,int N> void McParticle<T,N>::calculate (
  McParticleData<2> *mcParticleData) { 

   
  unsigned int particleIdx=0;
  unsigned int origIdx=mcParticleData->idx;
 
  for (unsigned int i=0;i<Data<McParticleData<N> >::size_;i++){

    particleIdx=mcParticle(i).idx;

    if(findDecayLink(genParticles,particleIdx,origIdx)){
      mcParticle(i).orig=origIdx;
    }else{
      mcParticle(i).orig=-1;
    }
  }

}
  
//--------------------------------- passed() ----------------------------------

template<class T,int N> int McParticle<T,N>::passed(std::string selection,
  unsigned int i) { 

  if (!McParticle<T,N>::isValid()) return NOVAL_I;

  if (selection.compare("Origin")==0){
    if (mcParticle(i).orig==-1)
      return 0;
    if (mcParticle(i).orig>=0)
      return 1;  
  }

  return NOVAL_I;

}
//-----------------------------------isEqualPdg()------------------------------
template<class T,int N> bool McParticle<T,N>::isEqualPdg(
  int pdg,std::vector<int> pdgId){


  for (unsigned int i=0;i<pdgId.size();i++){
    if (pdg==pdgId[i] || pdg==0 || pdgId[i]==0) return true;
  }
  return false;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
