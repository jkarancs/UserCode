#ifndef SusyAnalysis_debDataMaker_Met_hh_
#define SusyAnalysis_debDataMaker_Met_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Met
// 
/**\class Met Met.hh SusyAnalysis/debDataMaker/interface/Met.hh

 Description: <one line class summary>

 Implementation:

   List of parameters to steer the object with (passed through iConfig):
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

      int passed(int i) (virtual,unsigned int i):
         if selection is set, returns the result of the selections. The
         selections are implemented in this function.

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Met.hh,v 1.2 2009/06/02 11:25:46 akapusi Exp $
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "SusyAnalysis/debDataMaker/interface/Data.hh"
#include "SusyAnalysis/debDataMaker/interface/MetData.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T> class Met : public Data<MetData>{ // D:=MetData
 public:
  Met(const edm::ParameterSet& iConfig);
  Met() { stdErr("  Met<%s> configuration missing\n", typeid(T).name()); }
  inline MetData& met(unsigned int i) { return *data(i); } // just a short-hand

  // Inherited functions to be overloaded
  void set(const edm::Event&);
  void calculate ();
  int passed(std::string,unsigned int i);

  // Introduce new variables and functions
 private:
  std::vector<std::string> corrections_; // list of requested corrections
  std::map<std::string,int> corrIndex_; // maps corrections to met(i) index 'i'

 public:
  std::vector<std::string>& getCorrection() { return corrections_; }
  pat::MET::UncorrectionType getPatMetCorrType(std::string corr);

  // Some fuctions that make configuring this object easier:
  std::map<std::string,int>& getCorrIndex() { return corrIndex_; }

  inline int ind(std::string corr) {
    std::map<std::string,int>::const_iterator it=corrIndex_.find(corr);
    if (it==corrIndex_.end()) {
      stdErr("Met<%s>::ind(%s) correction %s was not requested.\n", 
	     typeid(T).name(), corr.data(), corr.data()); 
      return NOVAL_I;
    }
    stdMesg("Met<%s>::ind(%s)=%d", typeid(T).name(), 
	    corr.data(), corrIndex_[corr]);
    return it->second;
  }

  inline std::vector<unsigned int> ind(std::vector<std::string> corrs) {
    std::vector<unsigned int> ret;
    for (unsigned int i=0; i<corrs.size(); i++) {
      int j=ind(corrs[i]);
      if (j<0) {
	ret.clear();
	break;
      }
      ret.push_back((unsigned int)(j));
    }
    return ret;
  }

};


//--------------------------------- Constructor -------------------------------
/*
   List of parameters to gear the object with (passed in iConfig):
      InputTag metTag,     : owned by Data<D>
      int selectionType,   : owned by Data<D>
      vector<string> corrections: owned by this class, contains the list of
                             the MET records of various corrections. The MET
			     records are numbered from 0 to 1,2,... accordingly
*/

template<class T> 
Met<T>::Met(const edm::ParameterSet& iConfig) : Data<MetData>(
      iConfig.getParameter<std::vector<std::string> >("corrections").size()) {

  // Read tag, set defaults:
  //
  setTag(iConfig.getParameter<edm::InputTag>("metTag"));
  setSelectionType(iConfig.getParameter<std::string>("selectionType"));
  corrections_=iConfig.getParameter<std::vector<std::string> >("corrections");

  // Print config settings
  //
  stdMesg("  Met<%s> configuration:", typeid(T).name());
  stdMesg("  \tcorrections(%d)=(", corrections_.size());
  for (unsigned int i=0; i<corrections_.size(); i++) {
    if (i<corrections_.size()-1) {
      stdMesg("  \t\t%d: %s,", i, corrections_[i].data());
    }
    else {
      stdMesg("  \t\t%d: %s", i, corrections_[i].data());
    }
  }
  stdMesg("  \t)");
  stdMesg("  Options are: ");
  for (std::map<std::string,int>::const_iterator it=MetCorrTypeMap.begin(); 
       it!=MetCorrTypeMap.end(); ++it) {
    stdMesg("  \t\t%s", (*it).first.data());
  }
  stdMesg("  \tmetTag = '%s'", tag().label().data());
  stdMesg("  \tselectionType = %s", getSelectionType().data());
  stdMesg("  List of variables: %s", met(0).list().data());
  stdMesg("  Object is %svalid!\n", (isValid() ? "" : "not "));

  // Check if requested corrections have been implemented
  // and build a map between the correction type and the met(i) index 'i'
  for (unsigned int i=0; i<corrections_.size(); i++) {
    std::map<std::string,int>::const_iterator it;
    it=MetCorrTypeMap.find(corrections_[i]);
    if (it==MetCorrTypeMap.end()) {
      stdErr("Correction %s not interpreted. Object will be invalid\n", 
	     corrections_[i].data());
      setValid(false);
      continue;
    }
    corrIndex_[corrections_[i]]=i;
  }
 
}

//----------------------------------- set() -----------------------------------

template<class T> void Met<T>::set(const edm::Event& iEvent) {

  if (!isValid()) return;

  edm::Handle<edm::View<T> > metHandle;
  iEvent.getByLabel(tag(), metHandle);

  if (!metHandle.isValid()) {
    stdErr("Met<%s>::set(): Invalid tag %s\n", 
	   typeid(T).name(), tag().label().data());
    setValid(false);
    return;
  }

  if (metHandle->size()!=1) {
    stdErr("Met<%s>::set(): unexpected Met collection size %d\n", 
	   typeid(T).name(), metHandle->size());
  }

  for (unsigned int i=0; i<max_size(); i++) {
    met(i).corr=MetCorrTypeMap[corrections_[i].data()];

    if (met(i).hasPatCorrType()) {
      pat::MET::UncorrectionType patType=getPatMetCorrType(corrections_[i]);

      if (corrections_[i]=="uncorrMAXN") {
	met(i).et = metHandle->front().pt();
	met(i).phi = metHandle->front().phi();
	met(i).sumet = metHandle->front().sumEt();
      } else {
	// WHAT THE HELL, LIVE DANGEROUSLY!!!! :
	const void *p=&metHandle->front();
	const pat::MET* pmet=(const pat::MET*)p;
	met(i).et=pmet->uncorrectedPt(patType);
	met(i).phi=pmet->uncorrectedPhi(patType);
	met(i).sumet=pmet->corSumEt(patType);
      }
      continue;
    }

    if(corrections_[i]=="DEFAULT") {
      met(i).et=metHandle->front().pt();
      met(i).phi=metHandle->front().phi();
      met(i).sumet=metHandle->front().sumEt();
      continue;
    }

    stdErr("Met<%s>::set(): correction type %s not recognized (implemented)\n",
	   corrections_[i].data());

    met(i).corr=NOVAL_I;
    met(i).et=NOVAL_F;
    met(i).phi=NOVAL_F;
    met(i).sumet=NOVAL_F;
  }

}

//---------------------------- getPatMetCorrType() ----------------------------

template<class T> 
pat::MET::UncorrectionType Met<T>::getPatMetCorrType(std::string corr){
  if (corr=="uncorrALL") return pat::MET::uncorrALL;
  else if (corr=="uncorrJES") return pat::MET::uncorrJES;
  else if (corr=="uncorrMUON") return pat::MET::uncorrMUON;
  else if (corr=="uncorrMAXN") return pat::MET::uncorrMAXN;
  stdErr("Met<%s>::getPatMetCorrType(): correction named %s is not recognized"\
	 " as pat::MET type\n", corr.data());
  return pat::MET::uncorrMAXN;
}


//-------------------------------- calculate() --------------------------------

template<class T> void Met<T>::calculate () { 

  if (!isValid()) return;

  for (unsigned int i=0; i<max_size(); i++) {
    //for (i=0;i<max_size;i++){
    //  met.pass=passed("RA4mu",i); //bitkodolt ize
    //}
  }
}


//--------------------------------- passed() ----------------------------------

template<class T> int Met<T>::passed(std::string selection,unsigned int i) { 

  if (!isValid()) return NOVAL_I;

  
  if(selection.compare("RefAna4JetMetMuon")==0){  
    if(met(i).et>100.0&&met(i).et!=NOVAL_F){
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
