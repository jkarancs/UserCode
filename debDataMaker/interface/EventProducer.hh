#ifndef SusyAnalysis_debDataMaker_EventProducer_hh_
#define SusyAnalysis_debDataMaker_EventProducer_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      EventProducer
// 
/**\class EventProducer EventProducer.hh SusyAnalysis/debDataMaker/interface/EventProducer.hh

 Description: <one line class summary>

 Implementation:

   List of parameters to steer the object with (passed in iConfig):
      int storeNEvents,     : owned by Data<D>, mandatory in constructor
      InputTag objectTag,  : owned by Data<D> but decided here if set
      int selectionType,   : owned by Data<D> but decided here if set


   iConfig is passed only through the contructor. 

   !!!! See usage of inherited functions in Event.hh source code !!!!

   The following fuctions should be overloaded here:

      void set(const edm::Event&) (virtual):
         implements reading variables of D from the CMSSW framework


*/
//
// Original Author:  Attila ARANYI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: EventProducer.hh,v 1.5 2009/08/24 14:09:22 aranyi Exp $
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SusyAnalysis/debDataMaker/interface/Event.hh"
#include "SusyAnalysis/debDataMaker/interface/Producer.hh"

#include "FWCore/Framework/interface/Event.h"
//#include "DataFormats/EventReco/interface/Event.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"


namespace deb {

//----------------------------- Class Definition ------------------------------

class EventProducer : public Producer<Event>{ 
 public:
  EventProducer(const edm::ParameterSet& iConfig);
//   EventProducer() { 
//     stdErr("  EventProducer<%s> configuration missing\n",
// 	   humanTypeId().data()); 
//   }

  // Inherited functions to be overloaded
  void set(const edm::Event&);
  
};


//--------------------------------- Constructor -------------------------------
/*
   List of parameters to gear the object with (passed in iConfig):
      double eventWeight_, : owned by this class
      int procIdx_,        : owned by this class
*/
                                          
EventProducer::EventProducer(const edm::ParameterSet& iConfig) : 
 Producer<Event>(eventNumber_= iConfig.getParameter<double>("eventNumber"),
                 eventCrossSec_= iConfig.getParameter<double>("eventCrossSec"),
                 luminosity_= iConfig.getParameter<double>("luminosity"),
                 procIdx_= iConfig.getParameter<int>("procIdx")){

  stdMesg("  Event configuration:");
  stdMesg("  \teventNumber = %f", eventNumber_);
  stdMesg("  \teventCrossSec = %f", eventCrossSec_);
  stdMesg("  \tluminosity = %f", luminosity_);
  stdMesg("  \tprocIdx = %d", procIdx_);
  stdMesg("  List of variables: %s", event(0).list().data());
  stdMesg("  Object is %svalid!\n", (isValid() ? "" : "not "));

}

//----------------------------------- set() -----------------------------------

void EventProducer::set(const edm::Event& iEvent) {

  if (!isValid()) return;

  clear();
  EventData new_obj;
  push_back(new_obj);

  event(0).run   = iEvent.id().run();
  event(0).ev = iEvent.id().event();
  if(eventCrossSec_!=0&&(eventNumber_/eventCrossSec_)!=0){
    event(0).w = luminosity_/(eventNumber_/eventCrossSec_);
  }
  else{
    event(0).w = NOVAL_F;
  }
  event(0).procidx=procIdx_; // from config
  
  if ( procIdx_>=0) 
  {
    edm::Handle<int> genProcessID;
    iEvent.getByLabel("genEventProcID", genProcessID );
    if(genProcessID.isValid()) {
      event(0).genevprocid = (*genProcessID);
    }
    else
    {
      stdMesg("genEventProcID is invalid.");
      stdMesg("Generated event procid will be:%d\n",NOVAL_I);
      event(0).genevprocid = NOVAL_I;
    }
  }
  else
  {
    stdMesg("In the config file procIdx<0.");
    stdMesg("Generated event procid will be:%d\n",NOVAL_I);
    event(0).genevprocid = NOVAL_I;
  }
}

  
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
