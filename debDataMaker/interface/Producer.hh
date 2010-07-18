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
// $Id: Producer.hh,v 1.5 2009/11/12 14:38:30 aranyi Exp $
//
//
//-----------------------------------------------------------------------------

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/Event.h"

namespace deb {

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template <class C> class Producer : public C {
public:
  Producer(edm::InputTag tag, std::string name="") : C(name), tag_(tag) { }

  Producer(edm::InputTag tag, std::string name, size_t storeNObjects) 
    : C(name, storeNObjects), tag_(tag) { }

  Producer(edm::InputTag tag, std::string name, std::vector<size_t> list) 
    : C(name, list), tag_(tag) { }

  Producer(edm::InputTag tag, std::string name, std::vector<std::string> list) 
    : C(name, list), tag_(tag) { }
  
  Producer(double eventNumber, double eventCrossSec, double luminosity, 
           int procIdx) 
  : C() { }
  
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

};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
