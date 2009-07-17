#ifndef SusyAnalysis_debDataMaker_JetProducer_hh_
#define SusyAnalysis_debDataMaker_JetProducer_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      JetProducer
// 
/**\class JetProducer JetProducer.hh SusyAnalysis/debDataMaker/interface/JetProducer.hh

 Description: <one line class summary>

 Implementation:

   List of parameters to steer the object with (passed through iConfig):
      int storeNObjects,   : owned by Jet
      InputTag objectTag,  : owned by Jet but decided here if set
      int selectionType,   : owned by Jet but decided here if set
      pair<string,string> correction: owned by this class
      string sortBy        : owned by this class

   iConfig must be parsed in the contructor. 

   !!!! See usage of inherited functions in Jet.hh source code !!!!

   The following fuctions should be overloaded here:

      void set(const edm::Event&) (virtual):
         implements reading variables of D from the CMSSW framework

      void calculate(?) (virtual):
         calculates values that depend on other data models

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: JetProducer.hh,v 1.1 2009/07/16 17:18:26 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SusyAnalysis/debDataMaker/interface/Jet.hh"
#include "SusyAnalysis/debDataMaker/interface/Producer.hh"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T> class JetProducer : public Producer<Jet> {
 public:
  JetProducer(const edm::ParameterSet& iConfig);
  JetProducer() { 
    stdErr("  JetProducer<%s> configuration missing\n", 
	   humanTypeId<T>().data());
  }

  // Inherited functions to be overloaded
  void set(const edm::Event&);
  void calculate ();

  // New variables and functions
 private:
  std::pair<std::string, std::string> correction_;
  std::string sortBy_;

 public:
  std::pair<std::string, std::string>& getCorrection() { return correction_; }
  std::string sortedBy_() { return sortBy_; }
  double getCorrFactor(const T*);
  float getHadronicFraction(const T*);
  float getEmFraction(const T*);

};


//--------------------------------- Constructor -------------------------------

template<class T> JetProducer<T>::JetProducer(const edm::ParameterSet& iConfig)
  : Producer<Jet>(iConfig.getParameter<edm::InputTag>("jetTag"),
		  iConfig.getParameter<std::string>("name"),
		  iConfig.getParameter<int>("storeNJets")) {

  // Read tag, set defaults:
  //
  setSelectionType(iConfig.getParameter<std::string>("selectionType"));

  correction_=std::make_pair(NOVAL_S, NOVAL_S);
  std::vector<std::string> patcorr = 
    iConfig.getParameter<std::vector<std::string> >("correction");
  if (patcorr.size()>0) correction_.first=patcorr[0];
  if (patcorr.size()>1) correction_.second=patcorr[1];

  sortBy_=iConfig.getParameter<std::string>("sortBy");

  // Print config settings
  //
  stdMesg("  JetProducer<%s> configuration:", humanTypeId<T>().data());
  stdMesg("  \tstoreNJets = %d", storeNObjects());
  stdMesg("  \tcorrection = (%s, %s)", 
	  getCorrection().first.data(), getCorrection().second.data());
  stdMesg("  \tjetTag = '%s'", tag().label().data());
  stdMesg("  \tselectionType = %s", getSelectionType().data());
  stdMesg("  \tsortBy = '%s' (options are: 'et', 'pt')", sortBy_.data());
  stdMesg("  List of variables: %s", list().data());
  stdMesg("  Object is %svalid!\n", (isValid() ? "" : "not "));
 
  // Print config errors:
  //
  if (sortBy_!="et" && sortBy_!="pt") {
    stdErr("Parameter sortBy = %s cannot be interpreted, "	\
	   "object will be invalid\n", sortBy_.data());
    setValid(false);
  }

}

//----------------------------------- set() -----------------------------------

template<class T> void JetProducer<T>::set(const edm::Event& iEvent) {

  if (!isValid()) return;

  edm::Handle<edm::View<T> > jetHandle;
  iEvent.getByLabel(tag(), jetHandle);
  if (!jetHandle.isValid()){
    stdErr("JetProducer<%s>::set() : Invalid tag %s\n", 
	   humanTypeId<T>().data(), tag().label().data());
    setValid(false);
    return;
  }

  // convert jet correction type

  std::vector<std::pair<float, const T*> > jets;  
  for (typename edm::View<T>::const_iterator iJet=jetHandle->begin();
       iJet!=jetHandle->end(); iJet++) {

    // choose parameter by which jets should be sorted, default: sort by E_T
    float par=iJet->et();
    if (sortBy_=="pt") par=iJet->pt();

    // correct jets if correction is available
    par*=getCorrFactor(&(*iJet));
    jets.push_back(std::make_pair(par, &(*iJet)));

  }
  std::sort(jets.begin(), jets.end(),
	    std::greater<std::pair<float, const T* > >());
  
  clear(); // clear the previous event from container
  for (unsigned int i=0; i<jets.size(); i++) {
    JetData new_obj; // size_=i+1;
    push_back(new_obj); // size_=i+1;
    
    // correct jets if correction is available      
    double corr=getCorrFactor(jets[i].second);
    
    jet(i).e = jets[i].second->energy()*corr;
    jet(i).px = jets[i].second->px()*corr;
    jet(i).py = jets[i].second->py()*corr;
    jet(i).pz = jets[i].second->pz()*corr;
    jet(i).m = jets[i].second->mass()*corr;
    jet(i).et = jets[i].second->et()*corr;
    jet(i).pt = jets[i].second->pt()*corr;
    jet(i).phi = jets[i].second->phi();
    jet(i).eta = jets[i].second->eta();
    jet(i).hadfrac = getHadronicFraction(jets[i].second);
    jet(i).emfrac = getEmFraction(jets[i].second);
    jet(i).area = jets[i].second->jetArea();
    
  }

}

//------------------------------- getCorrFactor() -----------------------------

template<> double JetProducer<pat::Jet>::getCorrFactor(const pat::Jet* jet) {
  pat::JetCorrFactors::CorrStep cstep = 
    pat::JetCorrFactors::corrStep(correction_.first, correction_.second);
  if (jet->hasJetCorrFactors() && cstep!=jet->jetCorrStep()) {
    return jet->jetCorrFactors().correction(cstep);
  }
  return 1.0;
}

template<> double JetProducer<reco::Jet>::getCorrFactor(const reco::Jet* jet) {
  return 1.0;
}

template<> 
double JetProducer<reco::CaloJet>::getCorrFactor(const reco::CaloJet* jet) {
  return 1.0;
}

template<> 
double JetProducer<reco::GenJet>::getCorrFactor(const reco::GenJet* jet) {
  return 1.0;
}


//------------------------------- getHadronicFraction() -----------------------

template<> 
float JetProducer<pat::Jet>::getHadronicFraction(const pat::Jet* jet) {
  return jet->energyFractionHadronic();
}

template<> 
float JetProducer<reco::Jet>::getHadronicFraction(const reco::Jet* jet) {
  return NOVAL_F;
}

template<> float 
JetProducer<reco::CaloJet>::getHadronicFraction(const reco::CaloJet* jet) {
  return NOVAL_F;
}

template<> 
float JetProducer<reco::GenJet>::getHadronicFraction(const reco::GenJet* jet) {
  return NOVAL_F;
}


//------------------------------- getEmFraction() -----------------------------

template<> float JetProducer<pat::Jet>::getEmFraction(const pat::Jet* jet) {
  return jet->emEnergyFraction();
}

template<> float JetProducer<reco::Jet>::getEmFraction(const reco::Jet* jet) {
  return NOVAL_F;
}

template<> 
float JetProducer<reco::CaloJet>::getEmFraction(const reco::CaloJet* jet) {
  return NOVAL_F;
}

template<> 
float JetProducer<reco::GenJet>::getEmFraction(const reco::GenJet* jet) {
  return NOVAL_F;
}


//-------------------------------- calculate() --------------------------------

template<class T> void JetProducer<T>::calculate () { 
}
  
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
