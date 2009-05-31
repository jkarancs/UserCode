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

      int passed(std::string,int i) (virtual):
         if selectionType is set, returns the result of the selections. The
         selections are implemented in this function.

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Jet.hh,v 1.1 2009/05/30 19:38:45 veszpv Exp $
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
  int passed(std::string selection,int i);

  // Introduce new variables and functions
 private:
  std::pair<std::string, std::string> correction_;
  std::string sortBy_;

 public:
  std::pair<std::string, std::string>& getCorrection() { return correction_; }
  std::string sortedBy_() { return sortBy_; }
  double getCorrFactor(const T*);

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
  stdMesg(" \tstoreNJets = %d", max_size());
  stdMesg(" \tcorrection = (%s, %s)", 
	  getCorrection().first.data(), getCorrection().second.data());
  stdMesg(" \tjetTag = '%s'", tag().label().data());
  stdMesg(" \tselectionType = %s", getSelectionType().data());
  stdMesg(" \tsortBy = '%s' (options are: 'et', 'pt')", sortBy_.data());
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

  size_=0;
  for (unsigned int i=0; i<max_size(); i++) {
    if (jets.size()>i) {
      size_=i+1;

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
      jet(i).hadfrac = jets[i].second->energyFractionHadronic();
      jet(i).emfrac = jets[i].second->emEnergyFraction();
      jet(i).area = jets[i].second->jetArea();

    } 
    else {
      jet(i).e=NOVAL_F;
      jet(i).px=NOVAL_F;
      jet(i).py=NOVAL_F;
      jet(i).pz=NOVAL_F;
      jet(i).m=NOVAL_F;
      jet(i).et=NOVAL_F;
      jet(i).pt=NOVAL_F;
      jet(i).phi=NOVAL_F;
      jet(i).eta=NOVAL_F;
      jet(i).hadfrac=NOVAL_F;
      jet(i).emfrac=NOVAL_F;
      jet(i).area=NOVAL_F;
    }
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


//-------------------------------- calculate() --------------------------------

template<class T> void Jet<T>::calculate () { 

  if (!isValid()) return;

  for (unsigned int i=0; i<max_size(); i++) {
    //for (i=0;i<max_size;i++){
    //  jet.pass=passed("RA4mu",i); //bitkodolt ize
    //}
  }
}


//--------------------------------- passed() ----------------------------------

template<class T> int Jet<T>::passed(std::string selection,int i) { 
  
  if (!isValid()) return NOVAL_I;


  if(selection.compare("RA4mu")==0){
    if(jet(i).pt>=30.0&&jet(i).pt!=NOVAL_F&&
       TMath::Abs(jet(i).eta)<=2.4&&jet(i).eta!=NOVAL_F&&
       jet(i).hadfrac>=0.1&&jet(i).hadfrac!=NOVAL_F){
      return 1;
    }     
    return 0;
  }


  if(getSelectionType().compare("RA4el")==0){
    if(jet(i).pt>=25.0&&jet(i).pt!=NOVAL_F&&
       TMath::Abs(jet(i).eta)<=3.0&&jet(i).eta!=NOVAL_F&&
       jet(i).emfrac<=0.9&&jet(i).emfrac!=NOVAL_F){
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
