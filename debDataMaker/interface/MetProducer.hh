#ifndef SusyAnalysis_debDataMaker_MetProducer_hh_
#define SusyAnalysis_debDataMaker_MetProducer_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      MetProducer
// 
/**\class MetProducer MetProducer.hh SusyAnalysis/debDataMaker/interface/MetProducer.hh

 Description: <one line class summary>

 Implementation:

   List of parameters to steer the object with (passed through iConfig):
      InputTag objectTag,  : owned by Data<D> but decided here if set
      pair<string,string> correction: owned by this class
      string sortBy        : owned by this class

   iConfig must be parsed in the contructor. 

   !!!! See usage of inherited functions in Data.hh source code !!!!

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: MetProducer.hh,v 1.1 2009/07/17 13:17:10 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "SusyAnalysis/debDataMaker/interface/Met.hh"
#include "SusyAnalysis/debDataMaker/interface/Producer.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T> class MetProducer : public Producer<Met> {
 public:
  MetProducer(const edm::ParameterSet& iConfig);
  MetProducer() { 
    stdErr("  MetProducer<%s> configuration missing\n",
	   humanTypeId<T>().data());
  }

  // Inherited functions to be overloaded
  void set(const edm::Event&);

 private:
  using Producer<Met>::calculate_pass;
  // New variables and functions
  std::vector<std::string> corrections_;
 
 public: 
  const std::vector<std::string>& getCorrections() { return corrections_; }
  inline std::string correction(size_t i) { return corrections_[i]; }
  pat::MET::UncorrectionType getPatMetCorrType(std::string);

};


//--------------------------------- Constructor -------------------------------

template<class T> MetProducer<T>::MetProducer(const edm::ParameterSet& iConfig)
  : Producer<Met>(
	      iConfig.getParameter<edm::InputTag>("metTag"),
              iConfig.getParameter<std::string>("name"),
              iConfig.getParameter<std::vector<std::string> >("storeList")) {

  std::vector<std::string> corrections=
    iConfig.getParameter<std::vector<std::string> >("corrections");

  corrections_.clear();
  for (unsigned int i=0; i<corrections.size(); i++) {
    std::map<std::string,int>::const_iterator it;
    it=MetCorrTypeMap.find(corrections[i]);
    if (it==MetCorrTypeMap.end()) {
      stdErr("Correction %s not interpreted", corrections[i].data());
      continue;
    }
    corrections_.push_back(corrections[i]);
  }

  if (corrections_.size()==0) {
    stdErr("  MetProducer<%s>: no valid correction has been set. Object " \
	   "will be invalid", humanTypeId<T>().data());
    setValid(false);
  }

  stdMesg("  MetProducer<%s> configuration:", humanTypeId<T>().data());
  stdMesg("  \tcorrections(%d)=(", getCorrections().size());
  for (size_t i=0; i<getCorrections().size(); i++) {
    if (i<getCorrections().size()-1) {
      stdMesg("  \t\t%d: %s,", i, correction(i).data());
    }
    else {
      stdMesg("  \t\t%d: %s", i, correction(i).data());
    }
  }
  stdMesg("  \t)");
  stdMesg("  Options are: ");
  for (std::map<std::string,int>::const_iterator it=MetCorrTypeMap.begin(); 
       it!=MetCorrTypeMap.end(); ++it) {
    stdMesg("  \t\t%s", (*it).first.data());
  }
  stdMesg("  \tmetTag = '%s'", tag().label().data());
  stdMesg("  List of variables: %s", list().data());
  stdMesg("  Object is %svalid!\n", (isValid() ? "" : "not "));

}

//----------------------------------- set() -----------------------------------

template<class T> void MetProducer<T>::set(const edm::Event& iEvent) {

  if (!isValid()) return;

  edm::Handle<edm::View<T> > metHandle;
  iEvent.getByLabel(tag(), metHandle);

  if (!metHandle.isValid()) {
    stdErr("MetProducer<%s>::set(): Invalid tag %s\n", 
	   humanTypeId<T>().data(), tag().label().data());
    setValid(false);
    return;
  }

  if (metHandle->size()!=1) {
    stdErr("MetProducer<%s>::set(): unexpected Met collection size %d\n", 
	   humanTypeId<T>().data(), metHandle->size());
  }

  clear();
  for (unsigned int i=0; i<getCorrections().size(); i++) {
    std::string corr=correction(i);
    MetData new_obj;
    insert(corr, new_obj);
    met(corr).corr=MetCorrTypeMap[corr];
    
    if (met(corr).hasPatCorrType()) {
      pat::MET::UncorrectionType patType=getPatMetCorrType(corr);
      
      if (corr=="uncorrMAXN") {
	met(corr).et = metHandle->front().pt();
	met(corr).phi = metHandle->front().phi();
	met(corr).sumet = metHandle->front().sumEt();
      } else {
	// WHAT THE HELL, LIVE DANGEROUSLY!!!! :
	const void *p=&metHandle->front();
	const pat::MET* pmet=(const pat::MET*)p;
	met(corr).et=pmet->uncorrectedPt(patType);
	met(corr).phi=pmet->uncorrectedPhi(patType);
	met(corr).sumet=pmet->corSumEt(patType);
      }
      continue;
    }
    
    if(corr=="DEFAULT") {
      met(corr).et=metHandle->front().pt();
      met(corr).phi=metHandle->front().phi();
      met(corr).sumet=metHandle->front().sumEt();
      continue;
    }

    stdErr("Met<%s>::set(): correction type %s not recognized (implemented)\n",
	   corr.data());
  }

}

//---------------------------- getPatMetCorrType() ----------------------------

template<class T> 
pat::MET::UncorrectionType MetProducer<T>::getPatMetCorrType(std::string corr){
  if (corr=="uncorrALL") return pat::MET::uncorrALL;
  else if (corr=="uncorrJES") return pat::MET::uncorrJES;
  else if (corr=="uncorrMUON") return pat::MET::uncorrMUON;
  else if (corr=="uncorrMAXN") return pat::MET::uncorrMAXN;
  stdErr("Met<%s>::getPatMetCorrType(): correction named %s is not recognized"\
	 " as pat::MET type\n", corr.data());
  return pat::MET::uncorrMAXN;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
