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
// $Id: Event.hh,v 1.6 2009/06/08 18:41:42 akapusi Exp $
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
  inline EventData& event(unsigned int i=0) { return *data(i); } 
                                                          // just a short-hand

  // Inherited functions to be overloaded
  void set(const edm::Event&);
  int passed(std::string selection,
	     Jet<pat::Jet>* pjet,
	     Met<pat::MET>* pmet,
	     Electron<pat::Electron>* pele,
	     Muon<pat::Muon>* pmuon,
	     Trigger<edm::TriggerResults>* trigger);

  void calculate_pass() {
    stdWarn("calculate_pass(): function can't be called without parameters\n");
  }

  // calculate_pass() with all the possible parameters for all selections
  // if a parameter does not exist we set NULL when calling this function
  void calculate_pass(Jet<pat::Jet>* pjet,
		      Met<pat::MET>* pmet,
		      Electron<pat::Electron>* pele,
		      Muon<pat::Muon>* pmuon,
		      Trigger<edm::TriggerResults>* trigger);

  void select() {
    stdWarn("select(): How do you want to select event information for an " \
	    "event???\n");
  }

  // Introduce new variables and functions
 private:
  double eventWeight_;
  int procIdx_;
  void process_result(std::string, int);
  
};


//--------------------------------- Constructor -------------------------------
/*
   List of parameters to gear the object with (passed in iConfig):
      double eventWeight_, : owned by this class
      int procIdx_,        : owned by this class
*/

Event::Event(const edm::ParameterSet& iConfig) : Data<EventData>(int(1)) {  
  eventWeight_= iConfig.getParameter<double>("eventWeight") ;
  procIdx_= iConfig.getParameter<int>("procIdx") ;

  stdMesg("  Event configuration:");
  stdMesg("  \teventWeight = %f", eventWeight_);
  stdMesg("  \tprocIdx = %d", procIdx_);
  stdMesg("  List of variables: %s", event(0).list().data());
  stdMesg("  Object is %svalid!\n", (isValid() ? "" : "not "));

}

//----------------------------------- set() -----------------------------------

  void Event::set(const edm::Event& iEvent) {

  if (!isValid()) return;

  clear();
  push_back(*(new EventData));

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


//--------------------------------- passed() ----------------------------------

int Event::passed(std::string selection,
		  Jet<pat::Jet>* pjet,
		  Met<pat::MET>* pmet,
		  Electron<pat::Electron>* pele,
		  Muon<pat::Muon>* pmuon,
		  Trigger<edm::TriggerResults>* trigger) {

  if (!isValid()) return NOVAL_I;

  // ---------------------- RA4 selections ----------------------------
  // ------------------------------------------------------------------
  if(selection.compare("RefAna4JetMetMuon")==0 ||
     selection.compare("RefAna4JetMetElectron")==0 ) {

    if (pjet==NULL||pmet==NULL||pele==NULL||pmuon==NULL||trigger==NULL) {
      stdErr("passed(): Insufficient information to perform selection %s",
	     selection.data());
      stdErr("Have you called the right declaration type of passed()?\n");
      return NOVAL_I;
    }
    
    unsigned int numele=0;
    unsigned int nummuo=0;
    unsigned int numjetpt50=0;
    unsigned int numjetpt50eta3emfrac09=0;
    std::vector<int> muonpass((*pmuon).size());
    for (unsigned int i=0;i<(*pmuon).size();i++){
      muonpass[i]=(*pmuon).passed(selection,i);
      if(muonpass[i]==1){
	nummuo++;
      }
    }
    std::vector<int> electronpass((*pele).size());
    for (unsigned int i=0;i<(*pele).size();i++){
      electronpass[i]=(*pele).passed(selection,i);
      if(electronpass[i]==1){
	numele++;
      }
    } 
    std::vector<int> pjetpass((*pjet).size());
    for (unsigned int i=0;i<(*pjet).size();i++){
      pjetpass[i]=(*pjet).passed(selection,i);
      if((*pjet).jet(i).pt==NOVAL_F){
	stdErr("Event::passed() : NOVAL value in the cut criteria");
      }
      else {
	if(pjetpass[i]==1&&(*pjet).jet(i).pt>=50.0){
	  numjetpt50++;
	}
      }
      if((*pjet).jet(i).pt==NOVAL_F||
	 (*pjet).jet(i).eta==NOVAL_F||
	 (*pjet).jet(i).emfrac==NOVAL_F){
	stdErr("Event::passed() : NOVAL value in the cut criteria");
      }
      else {
	if(pjetpass[i]==1&&
	   (*pjet).jet(i).pt>=50.0&&
	   TMath::Abs((*pjet).jet(i).eta)<3.0&&
	   (*pjet).jet(i).emfrac<0.9){
	  numjetpt50eta3emfrac09++;
	}
      }
    }
    
    if(selection.compare("RefAna4JetMetMuon")==0){  
      if((*pmet).met(0).et==NOVAL_F){
	stdErr("Event::passed() : NOVAL value in the cut criteria");    
	return NOVAL_I;    
      }
      if(nummuo==1&&
	 numele==0&&
	 numjetpt50>=3&&
	 (*pmet).met(0).et>100.0){
	return 1;
      }      
      else{
	return 0;
      }
    }
    
    if(selection.compare("RefAna4JetMetElectron")==0){  
      if((*pmet).met(0).et==NOVAL_F){
	stdErr("Event::passed() : NOVAL value in the cut criteria");    
	return NOVAL_I;    
      }
      
      if((*trigger).trigger(0).hlt==1&&
	 numele==1&&
	 numjetpt50eta3emfrac09>=3&&
	 (*pmet).met(0).et>100.0){
	return 1;
      }
      else{
	return 0;
      }
    }
  }  

  // ------------------- End of RA4 selections ------------------------
  // ------------------------------------------------------------------

  stdErr("passed(): Selection %s is not implemented\n", selection.data());
  return NOVAL_I;
}


//------------------------- calculate_pass() ----------------------------------
// calculate_pass() with all the possible parameters for all the implemented
// selections. If a selection is not called and one of its parameters are not
// prerequisite to other selections, call the function with NULL

void Event::calculate_pass(Jet<pat::Jet>* pjet,
			   Met<pat::MET>* pmet,
			   Electron<pat::Electron>* pele,
			   Muon<pat::Muon>* pmuon,
			   Trigger<edm::TriggerResults>* trigger) {
  
  if (!isValid()) return;

  event().mask=0;
  event().pass=0;
  
  process_result("RefAna4JetMetMuon", 
	  passed("RefAna4JetMetMuon", pjet, pmet, pele, pmuon, trigger));
  
  process_result("RefAna4JetMetElectron", 
	  passed("RefAna4JetMetElectron", pjet, pmet, pele, pmuon, trigger));

}

  void Event::process_result(std::string s, int result) {
    if (result!=0 && result!=1) {
      stdErr("calculate_pass(): selection %s returned value %d",
	     s.data(), result);
      stdErr("...is it implemented? ...are all the parameters required"	\
	     " for this selection computed by the time calculate"	\
	     "_pass is called?\n");
      return;
    }
    event().mask|=1<<event().selectionTypes_[s.data()];
    event().pass|=result<<event().selectionTypes_[s.data()];
  }
  
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
