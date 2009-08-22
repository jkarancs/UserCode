#ifndef SusyAnalysis_debDataMaker_McParticleProducer_hh_
#define SusyAnalysis_debDataMaker_McParticleProducer_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      McParticleProducer
// 
/**\class McParticleProducer McParticleProducer.hh SusyAnalysis/debDataMaker/interface/McParticleProducer.hh

 Description: <one line class summary>

 Implementation:

   List of parameters to steer the object with (passed in iConfig):
      int storeNMcParticles,     : owned by Data<D>, mandatory in constructor
      InputTag objectTag,  : owned by Data<D> but decided here if set
      int selectionType,   : owned by Data<D> but decided here if set
  

   iConfig is passed only through the contructor. 

   !!!! See usage of inherited functions in McParticle.hh source code !!!!

   The following fuctions should be overloaded here:

      void set(const edm::Event&) (virtual):
         implements reading variables of D from the CMSSW framework


*/
//
// Original Author:  Anita KAPUSI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: McParticleProducer.hh,v 1.2 2009/07/29 10:06:08 veszpv Exp $
//
//
//-----------------------------------------------------------------------------
  
#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SusyAnalysis/debDataMaker/interface/McParticle.hh"
#include "SusyAnalysis/debDataMaker/interface/Producer.hh"
#include "SusyAnalysis/debDataMaker/interface/CMSSWTools.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T,int N> class McParticleProducer : 
public Producer<McParticle<N> >{

 public:
	 
  McParticleProducer(const edm::ParameterSet& iConfig);
  McParticleProducer() { stdErr("  Process<%s> configuration missing\n", 
		     typeid(T).name()); }

  // Inherited functions to be overloaded
  void set(const edm::Event&);  
  void calculate (int);

 private:
  std::vector<int> mcParticlePdgId_;
  int mcParticleStatus_;
  std::string sortBy_;

  std::vector<const T *> genParticles;

  bool isEqualPdg(int,std::vector<int>);

};

//--------------------------------- Constructor -------------------------------

template<class T,int N> McParticleProducer<T,N>::
  McParticleProducer(const edm::ParameterSet& iConfig) : 
  Producer<McParticle<N> >(
    iConfig.getParameter<edm::InputTag>("mcParticleTag"), 
    iConfig.getParameter<std::string>("name"),
    iConfig.getParameter<int>("storeNParticles")){

  // Read tag, set defaults:
  //

  VContainer<McParticleData<N> >::setSelectionType(
    iConfig.getParameter<std::string>("selectionType"));

  mcParticlePdgId_=
    (iConfig.getParameter<std::vector<int> >("mcParticlePdgId"));
  mcParticleStatus_=
    (iConfig.getParameter<int>("mcParticleStatus"));

  sortBy_=iConfig.getParameter<std::string>("sortBy");


}

//-------------------------------- calculate() --------------------------------

template<class T,int N> void McParticleProducer<T,N>::
  calculate(int origIdx) { 


   
  int particleIdx=0;  
 
  for (size_t i=0; i<Producer<McParticle<N> >::size(); i++){

    particleIdx=Producer<McParticle<N> >::mcParticle(i).idx;

    if(origIdx==NOVAL_I){
      Producer<McParticle<N> >::mcParticle(i).orig=NOVAL_I;
    }else{
      if(findDecayLink(genParticles,particleIdx,origIdx)){
        Producer<McParticle<N> >::mcParticle(i).orig=origIdx;
      }else{
        Producer<McParticle<N> >::mcParticle(i).orig=-1;
      }
    }
  }

}

//----------------------------------- set() -----------------------------------
template<class T,int N> void McParticleProducer<T,N>::set(const edm::Event& iEvent) {
if (!VContainer<McParticleData<N> >::isValid()) return;

  edm::Handle<edm::View<T> > particleHandle;
  iEvent.getByLabel(Producer<McParticle<N> >::tag(), particleHandle );
  if (!particleHandle.isValid()){
    stdErr("set() : Invalid tag %s", Producer<McParticle<N> >::
      tag().label().data());
    return;
  }


  typename std::vector<const T *>::const_iterator found; 

  genParticles.clear();
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

  VContainer<McParticleData<N> >::clear(); // clear the previous event from container
  for (unsigned int i=0; i<particles.size(); i++) {
    McParticleData<N> new_obj; // size_=i+1;
    push_back(new_obj); // size_=i+1;
    
    Producer<McParticle<N> >::mcParticle(i).e = particles[i].second->energy();
    Producer<McParticle<N> >::mcParticle(i).px = particles[i].second->px();
    Producer<McParticle<N> >::mcParticle(i).py = particles[i].second->py();
    Producer<McParticle<N> >::mcParticle(i).pz = particles[i].second->pz();
    Producer<McParticle<N> >::mcParticle(i).m = particles[i].second->mass();
    Producer<McParticle<N> >::mcParticle(i).p = particles[i].second->p();
    Producer<McParticle<N> >::mcParticle(i).et = particles[i].second->et();
    Producer<McParticle<N> >::mcParticle(i).pt = particles[i].second->pt();
    Producer<McParticle<N> >::mcParticle(i).phi = particles[i].second->phi();
    Producer<McParticle<N> >::mcParticle(i).eta = particles[i].second->eta();
    
    // get particle idx
    //

    const T * mo = particles[i].second;

    found = find(genParticles.begin(), genParticles.end(), mo);
      if(found != genParticles.end()) 
	idx = found - genParticles.begin();

    Producer<McParticle<N> >::mcParticle(i).idx=idx;

    // get particle's first daughter idx
    //

    if (particles[i].second->numberOfDaughters()!=0){
      const T * da = particles[i].second->daughter(0);
  
      found = std::find(genParticles.begin(), genParticles.end(), da);
        if(found != genParticles.end()) 
          idx = found - genParticles.begin();
  
      Producer<McParticle<N> >::mcParticle(i).da[0]=idx;
    }



    mo = particles[i].second->mother(0);

    found = find(genParticles.begin(), genParticles.end(), mo);
      if(found != genParticles.end()) 
	idx = found - genParticles.begin();                  
      
    Producer<McParticle<N> >::mcParticle(i).mo1 = idx;
    
    Producer<McParticle<N> >::mcParticle(i).pdg=particles[i].second->pdgId();
    Producer<McParticle<N> >::mcParticle(i).stat = particles[i].second->status();
    
  }

}
  
//-----------------------------------isEqualPdg()------------------------------
template<class T,int N> bool McParticleProducer<T,N>::isEqualPdg(
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
