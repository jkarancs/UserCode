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

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: JetProducer.hh,v 1.4 2010/07/18 12:26:12 veszpv Exp $
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
  JetProducer(const edm::ParameterSet&);
  JetProducer() { 
    stdErr("  JetProducer<%s> configuration missing\n", 
	   humanTypeId<T>().data());
  }

  // Inherited functions to be overloaded
  void set(const edm::Event&);

  struct Correction {
    std::string level; // raw, off, rel, abs, emf, had, ue, part
    std::string flavor; // had, ue, part have different flavors: glu, uds, c, b
  };

  // New variables and functions
 private:
  Correction correction_;

  inline float getCorrFactor_(const T&);
  inline float getCorrFactorWrtRaw_(const T&);
  inline float getCorrFactorUncertainty_(const T& jet, int sigma);
  void getCorrectedJet_(const T&, T&); // first: input, second: output
  int getCorrLevel_(const T&);
  inline float getHadronicFraction_(const T&);
  inline float getEmFraction_(const T&);
  

 public:
  inline Correction& correction() { return correction_; }
  
};


//--------------------------------- Constructor ------------------------------

template<class T> JetProducer<T>::JetProducer(const edm::ParameterSet& iConfig)
  : Producer<Jet>(iConfig.getParameter<edm::InputTag>("jetTag"),
		  iConfig.getParameter<std::string>("name"),
		  iConfig.getParameter<size_t>("storeNJets")) {

  // Read tag, set defaults:
  //
  setSelectionType(iConfig.getParameter<std::string>("selectionType"));

  std::vector<std::string> jetcor = 
    iConfig.getParameter<std::vector<std::string> >("correction");
  for (int i=0; i<2; i++) {
    transform(jetcor[i].begin(), jetcor[i].end(), jetcor[i].begin(),::tolower);
  }
  correction().level  = (jetcor.size()>0) ? jetcor[0] : NOVAL_S;
  correction().flavor = (jetcor.size()>1) ? jetcor[1] : NOVAL_S;

  setSortBy(iConfig.getParameter<std::string>("sortBy"));

  // Print config settings
  //
  stdMesg("  JetProducer<%s> configuration:", humanTypeId<T>().data());
  stdMesg("  \tstoreNJets = %d", storeNObjects());
  stdMesg("  \tcorrection = (%s, %s)", 
	  correction().level.c_str(), correction().flavor.c_str());
  stdMesg("  \tjetTag = '%s'", tag().label().data());
  stdMesg("  \tselectionType = %s", getSelectionType().data());
  stdMesg("  \tsortBy = '%s' (options are: 'et', 'pt')", sortedBy());
  stdMesg("  List of variables: %s", list().data());
  stdMesg("  Object is %svalid!\n", (isValid() ? "" : "not "));
 
  // Print config errors:
  //
  if (sortBy()!=et && sortBy()!=pt) {
    stdErr("Parameter sortBy = %s cannot be interpreted, "	\
	   "object will be invalid\n", sortedBy());
    setValid(false);
    throw cms::Exception("JetsSortedByInvalidParameter");
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

  // Buffer the pointers of jets, sort them by "par". Correct jets as needed
  std::vector<std::pair<float, const T*> > jets;

  bool doCorrection = (correction().level == NOVAL_S) ? false : true;

  for (typename edm::View<T>::const_iterator iJet=jetHandle->begin();
       iJet!=jetHandle->end(); iJet++) {
    float par=iJet->et();
    if (sortBy()==pt) par=iJet->pt();
    if (doCorrection) par*=getCorrFactor_(*iJet);
    jets.push_back(std::make_pair(par, &(*iJet)));
  }


  std::sort(jets.begin(), jets.end(), 
	    std::greater<std::pair<float, const T* > >());

  
  clear(); // clear the previous event from container

  int corr_level=NOVAL_I;
  for (unsigned int i=0; i<jets.size(); i++) {

    JetData jet; // producing this
    T cmsjet; // from this

    getCorrectedJet_(*jets[i].second, cmsjet); // make a corrected copy

    #ifdef DEB_DEBUG
    if (i==0) {
      corr_level = getCorrLevel_(cmsjet);

      if ( (sortBy()==pt && 
	    fabs(cmsjet.pt()-jets[i].first)>cmsjet.pt()*0.001) ||
	   (sortBy()==et && 
	    fabs(cmsjet.et()-jets[i].first)>cmsjet.et()*0.001) ) {
	throw cms::Exception("JetsSortedByInvalidParameter")
	  << "JetProducer<" << humanTypeId<T>().data() << ">: corrected jet "
	  << "parameter is not equal to the one used to sort the jets."
	  << "sorted by " << this->sortedBy() <<"=" << jets[i].first
	  << " where et=" << cmsjet.et() << ", pt=" << cmsjet.pt() <<"\n";
      }
    }
    #endif

    jet.e = cmsjet.energy();
    jet.px = cmsjet.px();
    jet.py = cmsjet.py();
    jet.pz = cmsjet.pz();
    jet.m = cmsjet.mass();
    jet.et = cmsjet.et();
    jet.pt = cmsjet.pt();
    jet.phi = cmsjet.phi();
    jet.eta = cmsjet.eta();
    jet.hadfrac = getHadronicFraction_(cmsjet);
    jet.emfrac = getEmFraction_(cmsjet);
    jet.area = cmsjet.jetArea();
    jet.corr_level = corr_level;
    jet.corr = getCorrFactorWrtRaw_(cmsjet);
    jet.jesp = getCorrFactorUncertainty_(cmsjet, +1);
    jet.jesm = getCorrFactorUncertainty_(cmsjet, -1);

    push_back(jet);
  }

}


//------------------------------- getCorrFactor() -----------------------------
//
// Corr factor applicable on the top of the input jet (not necessarily raw)
// Used only for sorting jets by Et / pt
//

template<> float JetProducer<pat::Jet>::getCorrFactor_(const pat::Jet& jet) {
  if (jet.hasCorrFactors()) {
    return jet.corrFactor(correction().level, correction().flavor);
  }
  return 1.0;
}

template<> float JetProducer<reco::Jet>::getCorrFactor_(const reco::Jet& jet) {
  return 1.0;
}

template<> 
float JetProducer<reco::CaloJet>::getCorrFactor_(const reco::CaloJet& jet) {
  return 1.0;
}

template<> 
float JetProducer<reco::GenJet>::getCorrFactor_(const reco::GenJet& jet) {
  return 1.0;
}



//--------------------------- getCorrFactorWrtRaw() ---------------------------

template<> 
float JetProducer<pat::Jet>::getCorrFactorWrtRaw_(const pat::Jet& jet) {
  if (jet.hasCorrFactors()) return jet.corrFactor("RAW", "");
  return 1.0;
}

template<> 
float JetProducer<reco::Jet>::getCorrFactorWrtRaw_(const reco::Jet& jet) {
  return 1.0; // ASSUMED THAT DATA IS ALWAYS RAW
}

template<> float 
JetProducer<reco::CaloJet>::getCorrFactorWrtRaw_(const reco::CaloJet& jet) {
  return 1.0; // ASSUMED THAT DATA IS ALWAYS RAW
}

template<> float 
JetProducer<reco::GenJet>::getCorrFactorWrtRaw_(const reco::GenJet& jet) {
  return 1.0; // ASSUMED THAT DATA IS ALWAYS RAW
}



//------------------------ getCorrFactorUncertainty() -------------------------
//
// Corr factor applicable on the top of the input jet (not necessarily raw)
// Used only for sorting jets by Et / pt
//

template<> 
float JetProducer<pat::Jet>::getCorrFactorUncertainty_(const pat::Jet& jet,
						       int sigma) {
  return jet.relCorrUncert( (sigma>0) ? "UP" : "DOWN");
}

template<> 
float JetProducer<reco::Jet>::getCorrFactorUncertainty_(const reco::Jet& jet,
							int sigma) {
  return 0.0;
}

template<> float 
JetProducer<reco::CaloJet>::getCorrFactorUncertainty_(const reco::CaloJet& jet,
						      int sigma) {
  return 0.0;
}

template<> float 
JetProducer<reco::GenJet>::getCorrFactorUncertainty_(const reco::GenJet& jet,
						     int sigma) {
  return 0.0;
}



//----------------------------- getCorrectedJet() -----------------------------

template<> 
void JetProducer<pat::Jet>::getCorrectedJet_(const pat::Jet& jraw, 
					     pat::Jet& jcorr) {
  jcorr = jraw.correctedJet(correction().level, correction().flavor);
}


template<> 
void JetProducer<reco::Jet>::getCorrectedJet_(const reco::Jet& jraw,
					      reco::Jet& jcorr) {
  jcorr = jraw;
}

 
template<> 
void JetProducer<reco::CaloJet>::getCorrectedJet_(const reco::CaloJet& jraw,
						  reco::CaloJet& jcorr) {
  jcorr = jraw;
}
 

template<> 
void JetProducer<reco::GenJet>::getCorrectedJet_(const reco::GenJet& jraw,
						 reco::GenJet& jcorr) {
  jcorr = jraw;
}



//------------------------------- getCorrLevel() -----------------------------

template<> int JetProducer<pat::Jet>::getCorrLevel_(const pat::Jet& jet) {

  std::string step = jet.corrStep();
  std::string flavor = jet.corrFlavour();

  #ifdef DEB_DEBUG
  transform(step.begin(), step.end(), step.begin(), ::tolower);
  transform(flavor.begin(), flavor.end(), flavor.begin(), ::tolower);

  if ( step!=correction().level || flavor!=correction().flavor) {
    throw cms::Exception("JetsNotCorrected")
      << "JetProducer<pat::Jet>: corrected jet "
      << "returns a correction type different from the requested correction:"
      << step << ", " << flavor;
  }
  #endif

  pat::JetCorrFactors cf;
  pat::JetCorrFactors::CorrStep cstep = cf.corrStep(step, flavor);
  return int(cstep);
}

template<> int JetProducer<reco::Jet>::getCorrLevel_(const reco::Jet& jet) { 
  return NOVAL_I; 
}

template<> 
int JetProducer<reco::CaloJet>::getCorrLevel_(const reco::CaloJet& jet) { 
  return NOVAL_I; 
}

template<> 
int JetProducer<reco::GenJet>::getCorrLevel_(const reco::GenJet& jet) { 
  return NOVAL_I; 
}


//------------------------------- getHadronicFraction() -----------------------

template<> 
float JetProducer<pat::Jet>::getHadronicFraction_(const pat::Jet& jet) {
  return (jet.isCaloJet()) ? jet.energyFractionHadronic() : NOVAL_F;
}

template<> 
float JetProducer<reco::Jet>::getHadronicFraction_(const reco::Jet& jet) {
  return NOVAL_F;
}

template<> float 
JetProducer<reco::CaloJet>::getHadronicFraction_(const reco::CaloJet& jet) {
  return NOVAL_F;
}

template<> float 
JetProducer<reco::GenJet>::getHadronicFraction_(const reco::GenJet& jet) {
  return NOVAL_F;
}



//------------------------------- getEmFraction() -----------------------------

template<> float JetProducer<pat::Jet>::getEmFraction_(const pat::Jet& jet) {
  return (jet.isCaloJet()) ? jet.emEnergyFraction() : NOVAL_F;
}

template<> float JetProducer<reco::Jet>::getEmFraction_(const reco::Jet& jet) {
  return NOVAL_F;
}

template<> 
float JetProducer<reco::CaloJet>::getEmFraction_(const reco::CaloJet& jet) {
  return NOVAL_F;
}

template<> 
float JetProducer<reco::GenJet>::getEmFraction_(const reco::GenJet& jet) {
  return NOVAL_F;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
