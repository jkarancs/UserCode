#ifndef SusyAnalysis_debDataMaker_TriggerProducer_hh_
#define SusyAnalysis_debDataMaker_TriggerProducer_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Trigger
// 
/**\class Trigger Trigger.hh SusyAnalysis/debDataMaker/interface/TriggerProducer.hh

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
// Original Author:  Attila ARANYI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Trigger.hh,v 1.3 2009/06/15 17:19:42 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SusyAnalysis/debDataMaker/interface/Trigger.hh"
#include "SusyAnalysis/debDataMaker/interface/Producer.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T> class TriggerProducer : public Producer<Trigger>{ 
                                                          // D:=TriggerData
 public:
   TriggerProducer(const edm::ParameterSet& iConfig);
   TriggerProducer() { 
     stdErr("  Trigger<%s> configuration missing\n", 
            humanTypeId<T>().data());
     
   }

  // Inherited functions to be overloaded
  void set(const edm::Event&);
  
  private:

    std::vector<std::string> storeList_;
 
//   public: 
//     inline std::string correction(size_t i) { return storeList_[i]; }
  
};


//--------------------------------- Constructor -------------------------------


template<class T> TriggerProducer<T>::TriggerProducer(const edm::ParameterSet& iConfig) : Producer<Trigger>(
      iConfig.getParameter<edm::InputTag>("triggerTag"),
      iConfig.getParameter<std::string>("name"),
      iConfig.getParameter<std::vector<std::string> >("storeList")) {
  

  storeList_=iConfig.getParameter<std::vector<std::string> >("storeList");
        
  stdMesg("  TriggerProducer<%s> configuration:", humanTypeId<T>().data());
  stdMesg("  \ttriggerTag = '%s'", tag().label().data());
  stdMesg("  \tselectionType = %s", getSelectionType().data());
  stdMesg("  List of variables: %s", list().data());
  stdMesg("  Object is %svalid!\n", (isValid() ? "" : "not "));

}

//----------------------------------- set() -----------------------------------

template<class T> void TriggerProducer<T>::set(const edm::Event& iEvent) {

  if (!isValid()) return;

  edm::Handle<T> hltHandle;
  iEvent.getByLabel(tag(), hltHandle);
  
  if (!hltHandle.isValid()) {
    stdErr("TriggerProducer<%s>::set(): Invalid tag %s\n", 
           humanTypeId<T>().data(), tag().label().data());
    setValid(false);
    return;
  }

  clear();
  TriggerData new_obj;
  insert(storeList_[0], new_obj);
  trigger(storeList_[0]).hlt=1;
  
  insert(storeList_[1], new_obj);
  trigger(storeList_[1]).hlt=0;
  
//   if ( hltHandle.isValid() ) {
//     edm::TriggerNames trgNames;
//     trgNames.init(*hltHandle);
//     for ( unsigned int i=0; i<storeList_.size(); ++i ) {
//       unsigned int index = trgNames.triggerIndex(storeList_[i]);
//       if ( index==trgNames.size() ) {
//         stdErr("set(): Unknown trigger name: %s\n", storeList_[i].c_str());
// 	continue;
//       }
//     } 
//     trigger(storeList_[0]).hlt = 1;//hltHandle->accept();
//   }else{  
//     stdErr("set(): No trigger results for InputTag\n");
//   }

}  

}


#endif
