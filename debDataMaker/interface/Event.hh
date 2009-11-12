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
      double eventNumber_,   : owned by this class
      double eventCrossSec_, : owned by this class
      double luminosity_,    : owned by this class
      int procIdx_,          : owned by this class

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
         returns the result of the selection. The selections are implemented 
	 in this function. passed() has to be declared for each selection with
	 the exact list of parameters that are used in the selection. (i.e.
	 there can be more than one declaration of this function.) Returns 
	 NOVAL_I if one of the parameters (pointer) is NULL

     void calculate_pass(Jet<pat::Jet>* pjet,
                         Met<pat::MET>* pmet,
		         Electron<pat::Electron>* pele,
		         Muon<pat::Muon>* pmuon,
		         Trigger* trigger):
	 calculate_pass() with all the possible parameters for all selections
         if a parameter does not exist we set NULL when calling this function,
	 there is only one declaration of this function

*/
//
// Original Author:  Anita KAPUSI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Event.hh,v 1.16 2009/11/12 14:19:04 aranyi Exp $
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SusyAnalysis/debDataMaker/interface/Data.hh"
#include "SusyAnalysis/debDataMaker/interface/EventData.hh"

#include "SusyAnalysis/debDataMaker/interface/MuonProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/ElectronProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/JetProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/MetProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/TriggerProducer.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

class Event : public VContainer<EventData>{ 
                                                          // D:=EventData
 public:
   
   Event(std::string name="") : VContainer<EventData>(name) { }
   Event(std::string name, size_t storeNObjects) 
  : VContainer<EventData>(name, storeNObjects) { }
   ~Event() { }

   inline EventData& event(size_t i=0) { return *(*this)(i); }

  // Inherited functions to be overloaded
  void set(const edm::Event&);

  // a passed() has to be declared for each selection with the exact list of
  // parameters that are used in the selection. Returns NOVAL_I if one of the
  // parameters (pointer) is NULL
  int passed(std::string selection,
             Jet* pjet,
             Met* pmet,
             Electron* pele,
             Muon* pmuon,
             Trigger* trigger,
             std::vector<std::pair<std::string,int> >* eventCutFlow);
  
  int passed(std::string selection,
             Jet* pjet,
             Met* pmet,
             Electron* pele,
             Muon* pmuon,
             Trigger* trigger){

           return passed(selection, pjet, pmet, pele, pmuon, trigger, NULL);
             
  }

  void calculate_pass() {
    stdWarn("calculate_pass(): function can't be called without parameters\n");
  }

  //calculate_pass() with all the possible parameters for all selections
  //if a parameter does not exist we set NULL when calling this function
  void calculate_pass(Jet*, Met*, Electron*,
		      Muon*, Trigger*);

  void select() {
    stdWarn("select(): How do you want to select event information for an " \
	    "event???\n");
  }

  // Introduce new variables and functions
 //private:
  double eventNumber_;
  double eventCrossSec_;
  double luminosity_;
  int procIdx_;
  void process_result(std::string, int);
  
};

//--------------------------------- passed() ----------------------------------

int Event::passed(std::string selection,
                  Jet* pjet,
                  Met* pmet,
                  Electron* pele,
                  Muon* pmuon,
		  Trigger* trigger,
                  std::vector<std::pair<std::string,int> >* eventCutFlow) {

  if (!isValid()) return NOVAL_I;

  // ---------------------- RA4 selections ----------------------------
  // ------------------------------------------------------------------
  if(selection=="RefAna4JetMetMuon") {

    if (pjet==NULL||pmet==NULL||pele==NULL||pmuon==NULL||trigger==NULL) {
      stdErr("passed(std::string selection, Jet<pat::Jet>*, "		\
	     "Met<pat::MET>*, Electron<pat::Electron>*, Muon<pat::Muon>*, " \
	     "Trigger*): Insufficient information to" \
	     " perform selection %s", selection.data());
      stdErr("Have you called the right declaration type of passed()?\n");
      return NOVAL_I;
    }
    
    if (eventCutFlow!=NULL && (*eventCutFlow).size()==0){
      std::pair<std::string,int> exactlyOneMuon("exactly one good muon   ",0);
      (*eventCutFlow).push_back(exactlyOneMuon);
      std::pair<std::string,int> zeroElectrons("zero electrons          ",0);
      (*eventCutFlow).push_back(zeroElectrons);
      std::pair<std::string,int> jetCuts("≥ 3 jets                ",0);
      (*eventCutFlow).push_back(jetCuts);
      std::pair<std::string,int> met100 ("MET > 100               ",0);
      (*eventCutFlow).push_back(met100);
    }
    
    unsigned int numele=0;
    unsigned int nummuo=0;
    unsigned int numjetpt50=0;
    std::vector<std::pair<std::string,int> > cutflow;
    
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
        stdErr("passed(std::string selection, Jet<pat::Jet>*, "		\
            "Met<pat::MET>*, Electron<pat::Electron>*, Muon<pat::Muon>*, " \
            "Trigger*): NOVAL value in the cut " \
            "criteria");   
      }else{
	if(pjetpass[i]==1&&(*pjet).jet(i).pt>=50.0){
	  numjetpt50++;
	}
      }
    }
    
    if((*pmet).met("uncorrMAXN").et==NOVAL_F){
      stdErr("passed(std::string selection, Jet<pat::Jet>*, "		\
          "Met<pat::MET>*, Electron<pat::Electron>*, Muon<pat::Muon>*, " \
          "Trigger*): NOVAL value in the cut " \
          "criteria");      
      return NOVAL_I;    
    }
    
        
    
    if(nummuo==1){
      if(eventCutFlow!=NULL) (*eventCutFlow)[0].second++;
      
      if(numele==0){
        if(eventCutFlow!=NULL) (*eventCutFlow)[1].second++;
        
        if(numjetpt50>=3){
          if(eventCutFlow!=NULL) (*eventCutFlow)[2].second++;
          
          if((*pmet).met("uncorrMAXN").et>100.0){
            if(eventCutFlow!=NULL) (*eventCutFlow)[3].second++;
            return 1;
            
          }
        }
      }
    }
    
    
  return 0;
    
    
  } 
  
  
  if(selection=="RefAna4JetMetElectron") {

    if (pjet==NULL||pmet==NULL||pele==NULL||pmuon==NULL||trigger==NULL) {
      stdErr("passed(std::string selection, Jet<pat::Jet>*, "		\
          "Met<pat::MET>*, Electron<pat::Electron>*, Muon<pat::Muon>*, " \
          "Trigger*): Insufficient information to" \
          " perform selection %s", selection.data());
      stdErr("Have you called the right declaration type of passed()?\n");
      return NOVAL_I;
    }
    
    
    if (eventCutFlow!=NULL && (*eventCutFlow).size()==0){ 
         
      std::pair<std::string,int> electronTrigger("single electron " \
          "trigger   ",0);
      (*eventCutFlow).push_back(electronTrigger);
      
      std::pair<std::string,int> zeroMuons("no good muons             ",0);
      (*eventCutFlow).push_back(zeroMuons);
      
      std::pair<std::string,int> exactlyOneElectron("exactly one " \
          "good electron ",0);
      (*eventCutFlow).push_back(exactlyOneElectron);

      std::pair<std::string,int> jetCuts("≥ 3 good jets             ",0);
      (*eventCutFlow).push_back(jetCuts);
      
      std::pair<std::string,int> met100("MET > 100                 ",0);
      (*eventCutFlow).push_back(met100);
    }
    
    unsigned int numele=0;
    unsigned int nummuo=0;
    unsigned int numjetpt50eta3emfrac09=0;
    std::vector<std::pair<std::string,int> > cutflow;
    
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
      if((*pjet).jet(i).pt==NOVAL_F||
           (*pjet).jet(i).eta==NOVAL_F||
           (*pjet).jet(i).emfrac==NOVAL_F){
	stdErr("passed(std::string selection, Jet<pat::Jet>*, "		\
	       "Met<pat::MET>*, Electron<pat::Electron>*, Muon<pat::Muon>*, " \
	       "Trigger*): NOVAL value in the cut " \
	       "criteria");   
      }else{
        if(pjetpass[i]==1&&
          (*pjet).jet(i).pt>=50.0&&
          TMath::Abs((*pjet).jet(i).eta)<3.0&&
          (*pjet).jet(i).emfrac<0.9){
          numjetpt50eta3emfrac09++;
        }
      }
    }
    
    
    if((*pmet).met("uncorrMAXN").et==NOVAL_F){
      stdErr("passed(std::string selection, Jet<pat::Jet>*, "		\
          "Met<pat::MET>*, Electron<pat::Electron>*, Muon<pat::Muon>*, " \
          "Trigger*): NOVAL value in the cut " \
          "criteria");      
      return NOVAL_I;    
    }
    
    if((*trigger).trigger("HLT_Ele15_LW_L1R").hlt==1){
      if(eventCutFlow!=NULL) (*eventCutFlow)[0].second++;
      
      if(nummuo==0){
        if(eventCutFlow!=NULL) (*eventCutFlow)[1].second++;
        
        if(numele==1){
          if(eventCutFlow!=NULL) (*eventCutFlow)[2].second++;
          
          if(numjetpt50eta3emfrac09>=3){
            if(eventCutFlow!=NULL) (*eventCutFlow)[3].second++;
            
            if((*pmet).met("uncorrMAXN").et>100.0){
              if(eventCutFlow!=NULL) (*eventCutFlow)[4].second++;
              return 1;
              
            }
          }
        }
      }
    }
    
    
    return 0;
    
    
  } 

  // ------------------- End of RA4 selections ------------------------
  // ------------------------------------------------------------------

  stdErr("passed(std::string selection, Jet<pat::Jet>*, Met<pat::MET>*, "\
	 "Electron<pat::Electron>*, Muon<pat::Muon>*, "\
	 "Trigger*): Selection %s is not implemented "\
	 "in this function\n", selection.data());

  return NOVAL_I;
}

//------------------------- calculate_pass() ----------------------------------
// calculate_pass() with all the possible parameters for all the implemented
// selections. If a selection is not needed and one of its parameters are not
// prerequisite to other selections, call the function with NULL

void Event::calculate_pass(Jet* pjet,
			   Met* pmet,
			   Electron* pele,
			   Muon* pmuon,
			   Trigger* trigger) {
  
  if (!isValid()) return;

  event().mask=0;
  event().pass=0;
  
  if (pjet!=NULL&& pmet!=NULL&& pele!=NULL&& pmuon!=NULL&& trigger!=NULL) {

    process_result("RefAna4JetMetMuon", 
	    passed("RefAna4JetMetMuon", pjet, pmet, pele, pmuon, trigger));
    
    process_result("RefAna4JetMetElectron", 
	    passed("RefAna4JetMetElectron", pjet, pmet, pele, pmuon, trigger));
  }

}


  void Event::process_result(std::string s, int result) {
    if (result!=0 && result!=1) {
      stdErr("calculate_pass(Jet<pat::Jet>*, Met<pat::MET>*, "\
	     "Electron<pat::Electron>*, Muon<pat::Muon>*, "\
	     "Trigger*): selection %s returned value %d",
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
