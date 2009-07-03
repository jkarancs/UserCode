#ifndef SusyAnalysis_debDataMaker_Jet_hh_
#define SusyAnalysis_debDataMaker_Jet_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Jet
// 
/**\class Jet Jet.hh SusyAnalysis/debDataMaker/interface/Jet.hh

 Description: <one line class summary>

 Implementation:

   List of parameters to steer the object with (passed through iConfig):
      int storeNObjects,   : owned by Data<D>, mandatory in constructor
      InputTag objectTag,  : owned by Data<D> but decided here if set
      int selectionType,   : owned by Data<D> but decided here if set
      pair<string,string> correction: owned by this class
      string sortBy        : owned by this class

   iConfig must be parsed in the contructor. 

   !!!! See usage of inherited functions in Data.hh source code !!!!

   The following fuctions should be overloaded here according to the exact 
   definition of D in Data<D> :

      void set(const edm::Event&) (virtual):
         implements reading variables of D from the CMSSW framework

      void calculate(?) (virtual):
         calculates values that depend on other data models

      int passed(std::string selection,unsigned int i) (virtual):
         returns the result of selection. The selections are implemented in 
	 this function.

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Jet.hh,v 1.9 2009/06/15 17:19:42 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "SusyAnalysis/debDataMaker/interface/Data.hh"
#include "SusyAnalysis/debDataMaker/interface/JetData.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T> class Jet : public Data<JetData>{ // D:=JetData
 public:
  Jet(const edm::ParameterSet& iConfig);
  Jet() { stdErr("  Jet<%s> configuration missing\n", typeid(T).name()); }
  inline JetData& jet(unsigned int i) { return *data(i); } // just a short-hand

  // Inherited functions to be overloaded
  void set(const edm::Event&);
  void calculate ();
  int passed(std::string selection,unsigned int i);

  // Introduce new variables and functions
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
/*
   List of parameters to gear the object with (passed in iConfig):
      int storeNJets,      : owned by Data<D>, mandatory in constructor
      InputTag jetTag,     : owned by Data<D>
      int selectionType,   : owned by Data<D>
      pair<string,string> correction: owned by this class
      string sortBy        : owned by this class
*/

template<class T> Jet<T>::Jet(const edm::ParameterSet& iConfig) : 
  Data<JetData>(iConfig.getParameter<int>("storeNJets")) {

  // Read tag, set defaults:
  //
  setTag(iConfig.getParameter<edm::InputTag>("jetTag"));
  setSelectionType(iConfig.getParameter<std::string>("selectionType"));

  correction_=std::make_pair(NOVAL_S, NOVAL_S);
  std::vector<std::string> patcorr = 
    iConfig.getParameter<std::vector<std::string> >("correction");
  if (patcorr.size()>0) correction_.first=patcorr[0];
  if (patcorr.size()>1) correction_.second=patcorr[1];

  sortBy_=iConfig.getParameter<std::string>("sortBy");

  // Print config settings
  //
  stdMesg("  Jet<%s> configuration:", typeid(T).name());
  stdMesg("  \tstoreNJets = %d", max_size());
  stdMesg("  \tcorrection = (%s, %s)", 
	  getCorrection().first.data(), getCorrection().second.data());
  stdMesg("  \tjetTag = '%s'", tag().label().data());
  stdMesg("  \tselectionType = %s", getSelectionType().data());
  stdMesg("  \tsortBy = '%s' (options are: 'et', 'pt')", sortBy_.data());
  stdMesg("  List of variables: %s", jet(0).list().data());
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

template<class T> void Jet<T>::set(const edm::Event& iEvent) {

  if (!isValid()) return;

  edm::Handle<edm::View<T> > jetHandle;
  iEvent.getByLabel(tag(), jetHandle);
  if (!jetHandle.isValid()){
    stdErr("set() : Invalid tag %s\n", tag().label().data());
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

template<> double Jet<pat::Jet>::getCorrFactor(const pat::Jet* jet) {
  pat::JetCorrFactors::CorrStep cstep = 
    pat::JetCorrFactors::corrStep(correction_.first, correction_.second);
  if (jet->hasJetCorrFactors() && cstep!=jet->jetCorrStep()) {
    return jet->jetCorrFactors().correction(cstep);
  }
  return 1.0;
}

template<> double Jet<reco::Jet>::getCorrFactor(const reco::Jet* jet) {
  return 1.0;
}

template<> double Jet<reco::CaloJet>::getCorrFactor(const reco::CaloJet* jet) {
  return 1.0;
}

template<> double Jet<reco::GenJet>::getCorrFactor(const reco::GenJet* jet) {
  return 1.0;
}


//------------------------------- getHadronicFraction() -----------------------

template<> float Jet<pat::Jet>::getHadronicFraction(const pat::Jet* jet) {
  return jet->energyFractionHadronic();
}

template<> float Jet<reco::Jet>::getHadronicFraction(const reco::Jet* jet) {
  return NOVAL_F;
}

template<> 
float Jet<reco::CaloJet>::getHadronicFraction(const reco::CaloJet* jet) {
  return NOVAL_F;
}

template<> 
float Jet<reco::GenJet>::getHadronicFraction(const reco::GenJet* jet) {
  return NOVAL_F;
}


//------------------------------- getEmFraction() -----------------------------

template<> float Jet<pat::Jet>::getEmFraction(const pat::Jet* jet) {
  return jet->emEnergyFraction();
}

template<> float Jet<reco::Jet>::getEmFraction(const reco::Jet* jet) {
  return NOVAL_F;
}

template<> 
float Jet<reco::CaloJet>::getEmFraction(const reco::CaloJet* jet) {
  return NOVAL_F;
}

template<> 
float Jet<reco::GenJet>::getEmFraction(const reco::GenJet* jet) {
  return NOVAL_F;
}


//-------------------------------- calculate() --------------------------------

template<class T> void Jet<T>::calculate () { 
}


//--------------------------------- passed() ----------------------------------

template<class T> int Jet<T>::passed(std::string selection,unsigned int i) { 
  
  if (!isValid()) return NOVAL_I;


  if(selection.compare("RefAna4JetMetMuon")==0){
    if(jet(i).pt==NOVAL_F||jet(i).eta==NOVAL_F||jet(i).hadfrac==NOVAL_F){
      stdErr("Jet::passed() : NOVAL value in the cut criteria");    
      return NOVAL_I;
    }
    if(jet(i).pt>=30.0&&
       TMath::Abs(jet(i).eta)<=2.4&&
       jet(i).hadfrac>=0.1){
      return 1;
    }     
    return 0;
  }


  if(selection.compare("RefAna4JetMetElectron")==0){
    if(jet(i).pt==NOVAL_F||jet(i).eta==NOVAL_F||jet(i).emfrac==NOVAL_F){
      stdErr("Jet::passed() : NOVAL value in the cut criteria");
      return NOVAL_I;
    }
    if(jet(i).pt>=25.0&&
       TMath::Abs(jet(i).eta)<=3.0&&
       jet(i).emfrac<=0.9){
      return 1;
    }      
    return 0;
  }

  
  if(selection.compare("TopJetSelection")==0){
    if(jet(i).pt==NOVAL_F||jet(i).eta==NOVAL_F||jet(i).emfrac==NOVAL_F){
      stdErr("Jet::passed() : NOVAL value in the cut criteria");
      return NOVAL_I;
    }
    if(jet(i).pt>=20.0&&
       TMath::Abs(jet(i).eta)<=2.7){//&&
       //jet(i).emfrac<=0.9) {
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
