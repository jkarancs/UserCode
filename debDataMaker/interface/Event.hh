#ifndef SusyAnalysis_debDataMaker_Event_hh_
#define SusyAnalysis_debDataMaker_Event_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Event
// 
/**\class Event Event.hh SusyAnalysis/debDataMaker/interface/Event.hh

 Description: <one line class summary>

 Implementation:

   List of parameters to steer the object with (passed in iConfig):
      double eventWeight_, : owned by this class
      int procIdx_,        : owned by this class
      int selectionType,   : owned by Data<D>

   iConfig is passed only through the contructor. 

   !!!! See usage of inherited functions in Data.hh source code !!!!

   The following fuctions should be overloaded here according to the exact 
   definition of D in Data<D> :

      void set(const edm::Event&) (virtual):
         that implements reading variables of D from the CMSSW framework

      void calculate() (virtual):
         that calculates values that depend on other data models

      int passed(std::string selection,
                 Jet<pat::Jet> & pjet,
                 Met<pat::MET> & pmet,
                 Electron<pat::Electron> & electron,
	         Muon<pat::Muon> & muon,
		 Trigger<edm::TriggerResults> & trigger) (virtual):
         if selectionType is set, returns the result of the selections. The
         selections are implemented in this function.

*/
//
// Original Author:  Anita KAPUSI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Event.hh,v 1.1 2009/05/30 19:38:43 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SusyAnalysis/debDataMaker/interface/Data.hh"
#include "SusyAnalysis/debDataMaker/interface/EventData.hh"

#include "SusyAnalysis/debDataMaker/interface/Trigger.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

class Event : public Data<EventData>{ 
                                                          // D:=EventData
 public:
  Event(const edm::ParameterSet& iConfig);
  Event() { stdErr("  Event configuration missing\n"); }
  inline EventData& event(unsigned int i) { return *data(i); } 
                                                          // just a short-hand

  // Inherited functions to be overloaded
  void set(const edm::Event&);
  void calculate ();
  int passed(std::string selection,
	     Jet<pat::Jet> & pjet,
	     Met<pat::MET> & pmet,
	     Electron<pat::Electron> & electron,
	     Muon<pat::Muon> & muon,
	     Trigger<edm::TriggerResults> & trigger);

  // Introduce new variables and functions
 private:
  double eventWeight_;
  int procIdx_;
 
};


//--------------------------------- Constructor -------------------------------
/*
   List of parameters to gear the object with (passed in iConfig):
      double eventWeight_, : owned by this class
      int procIdx_,        : owned by this class
      int selectionType,   : owned by Data<D>
*/

Event::Event(const edm::ParameterSet& iConfig) : Data<EventData>(int(1)) {  
  eventWeight_= iConfig.getParameter<double>("eventWeight") ;
  procIdx_= iConfig.getParameter<int>("procIdx") ;
  setSelectionType(iConfig.getParameter<std::string>("selectionType"));  

  stdMesg("  Event configuration:");
  stdMesg("\teventWeight = %f", eventWeight_);
  stdMesg("\tprocIdx = %d", procIdx_);
  stdMesg("\tselectionType = %s", getSelectionType().data());
  stdMesg("  List of variables: %s\n", event(0).list().data());

}

//----------------------------------- set() -----------------------------------

void Event::set(const edm::Event& iEvent) {

  if (!isValid()) return;

  event(0).run   = iEvent.id().run();
  event(0).ev = iEvent.id().event();
  event(0).w = eventWeight_; // from config
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
  
//-------------------------------- calculate() --------------------------------

void Event::calculate () { 
}
  
//--------------------------------- passed() ----------------------------------

int Event::passed(std::string selection,
		  Jet<pat::Jet> & pjet,
		  Met<pat::MET> & pmet,
		  Electron<pat::Electron> & electron,
		  Muon<pat::Muon> & muon,
		  Trigger<edm::TriggerResults> & trigger) {

  if (!isValid()) return NOVAL_I;

  unsigned int numele=0;
  unsigned int nummuo=0;
  unsigned int numjetpt50=0;
  unsigned int numjetpt50eta3emfrac09=0;
  std::vector<int> muonpass(muon.max_size());
  for (unsigned int i=0;i<muon.max_size();i++){
    muonpass[i]=muon.passed(selection,i);
    if(muonpass[i]==1){
      nummuo++;
    }
  }
  std::vector<int> electronpass(electron.max_size());
  for (unsigned int i=0;i<electron.max_size();i++){
    electronpass[i]=electron.passed(selection,i);
    if(electronpass[i]==1){
      numele++;
    }
  } 
  std::vector<int> pjetpass(pjet.max_size());
  for (unsigned int i=0;i<pjet.max_size();i++){
    pjetpass[i]=pjet.passed(selection,i);
    if(pjetpass[i]==1&&pjet.jet(i).pt>=50.0){
      numjetpt50++;
    }
    if(pjetpass[i]==1&&
       pjet.jet(i).pt>=50.0&&
       TMath::Abs(pjet.jet(i).eta)<3.0&&
       pjet.jet(i).emfrac<0.9){
      numjetpt50eta3emfrac09++;
    }
  }
  std::vector<int> pmetpass(pmet.max_size());
  for (unsigned int i=0;i<pmet.max_size();i++){
    pmetpass[i]=pmet.passed(selection,i);
  }
  
  if(selection.compare("RA4mu")==0){  
    if(nummuo==1&&
       numele==0&&
       numjetpt50>=3&&
       pmet.met(0).et>100.0){
      return 1;
    }      
    else{
      return 0;
    }
  }
  if(selection.compare("RA4el")==0){  
    if(trigger.trigger(0).hlt==1&&
       numele==1&&
       numjetpt50eta3emfrac09>=3&&
       pmet.met(0).et>100.0){
      return 1;
    }
    else{
      return 0;
    }
  }
  return NOVAL_I;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
