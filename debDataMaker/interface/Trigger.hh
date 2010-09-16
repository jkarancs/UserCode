#ifndef SusyAnalysis_debDataMaker_Trigger_hh_
#define SusyAnalysis_debDataMaker_Trigger_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Trigger
// 
/**\class Trigger Trigger.hh SusyAnalysis/debDataMaker/interface/Trigger.hh

 Description: <one line class summary>

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
// Original Author:  Anita KAPUSI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Trigger.hh,v 1.1 2009/05/30 19:38:52 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SusyAnalysis/debDataMaker/interface/Data.hh"
#include "SusyAnalysis/debDataMaker/interface/TriggerData.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T> class Trigger : public Data<TriggerData>{ 
                                                          // D:=TriggerData
 public:
  Trigger(const edm::ParameterSet& iConfig);
  Trigger() { stdErr("  Trigger<%s> configuration missing\n", 
		     typeid(T).name()); }
  inline TriggerData& trigger(unsigned int i) { return *data(i); } 
                                                          // just a short-hand

  // Inherited functions to be overloaded
  void set(const edm::Event&);
  void calculate ();
  int passed(std::string selection);

  // Introduce new variables and functions
 private:
  edm::InputTag triggerResults_;        // tag for input collection
  std::vector<std::string> pathNames_;  // trigger path names (ORed)  
  
};


//--------------------------------- Constructor -------------------------------
/*
   List of parameters to gear the object with (passed in iConfig):
      edm::InputTag triggerResults_,       : owned by this class
      std::vector<std::string> pathNames_, : owned by this class      
*/

template<class T> Trigger<T>::Trigger(const edm::ParameterSet& iConfig) : 
  Data<TriggerData>(int(1)) {
  
  triggerResults_= iConfig.getParameter<edm::InputTag>("triggerResults");
  pathNames_= iConfig.getParameter< std::vector<std::string> >("pathNames");

  stdMesg("  Trigger<%s> configuration:", typeid(T).name());
  stdMesg("\ttriggerResults = %s", triggerResults_.label().data());
  for (unsigned int i=0; i<pathNames_.size(); i++){
    stdMesg("\tpathNames_[%d] = %s", i, pathNames_[i].c_str());  
  }
  stdMesg("  List of variables: %s\n", trigger(0).list().data());

}

//----------------------------------- set() -----------------------------------

template<class T> void Trigger<T>::set(const edm::Event& iEvent) {

  if (!isValid()) return;

  edm::Handle<T> hltHandle;
  iEvent.getByLabel(triggerResults_, hltHandle);
  if ( hltHandle.isValid() ) {
    edm::TriggerNames trgNames;
    trgNames.init(*hltHandle);
    for ( unsigned int i=0; i<pathNames_.size(); ++i ) {
      unsigned int index = trgNames.triggerIndex(pathNames_[i]);
      if ( index==trgNames.size() ) {
	stdErr("set(): Unknown trigger name: %s\n", pathNames_[i].c_str());
	continue;
      }
    } 
    trigger(0).hlt = hltHandle->accept();
  }
  else {  
    stdErr("set(): No trigger results for InputTag\n");
    trigger(0).hlt = NOVAL_I;
  }
}
  
//-------------------------------- calculate() --------------------------------

template<class T> void Trigger<T>::calculate () { 
}
  
//--------------------------------- passed() ----------------------------------

template<class T> int Trigger<T>::passed(std::string selection) { 
  return 1; 
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
