#ifndef SusyAnalysis_debDataMaker_Producer_hh_
#define SusyAnalysis_debDataMaker_Producer_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Producer
// 
/**\class Producer Producer.hh SusyAnalysis/debDataMaker/interface/Producer.hh

 Description: <one line class summary>

 Implementation:

   NEED TO BE OVERLOADED after defining the data structure C:

      set(const edm::Event& iEvent):
         loading variables into C from iEvent, must be implemented 
         in daughter class after specifying T

      calculate():
         calculates values in C that depend on other data models
 
*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Producer.hh,v 1.2 2009/07/17 13:15:41 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/Container.hh"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/Framework/interface/Event.h"

namespace deb {

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template <class C> class Producer : public C {
public:
  Producer(edm::InputTag tag, std::string name="") : C(name), tag_(tag) { }
  Producer(edm::InputTag tag, std::string name, size_t storeNObjects) 
    : C(name, storeNObjects), tag_(tag) { }
  Producer(edm::InputTag tag, std::string name, std::vector<std::string> list) 
    : C(name, list), tag_(tag) { }
  
  virtual ~Producer() { }
  
 private:
  edm::InputTag tag_;                   // objectTag

 public:
  inline edm::InputTag tag() { return tag_; }

  //
  // functions that need to be implemented in derived classes
  // ---------------------------------------------------------
  
  virtual void     set(const edm::Event&) { 
    this->stdWarn("set(): virtual function is not implemented\n");
  }

  virtual void     calculate() { 
    this->stdWarn("calculate(): virtual function is not implemented\n");
  }

  void             calculate_pass();

};

//------------------------ calculate_pass() -----------------------------------

template<class C> void Producer<C>::calculate_pass() {
  if (!this->isValid()) return;
  for (size_t i=0; i<this->size(); i++) {
    this->at(i).pass=0;
    std::map<std::string, int>::const_iterator it;
    for (it=this->at(i).selectionTypes_.begin();
	 it!=this->at(i).selectionTypes_.end();
	 it++){
      if (it->first.find("VALID")!=std::string::npos) {
	this->at(i).pass|=1<<it->second;
	continue;
      }
      int result=this->passed(it->first, i);
      if (result!=0 && result!=1) {
	this->stdErr("calculate_pass(): selection %s on element %d returned " \
		     "value %d", it->first.data(), i, result);
	this->stdErr("...is it implemented? ...are all the parameters "	\
		     "required for this selection computed by the time " \
		     "calculate_pass is called?\n");
	this->print(3);
	this->at(i).pass=0;
	return;
      }
      this->at(i).pass|=result<<it->second;
    }
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
