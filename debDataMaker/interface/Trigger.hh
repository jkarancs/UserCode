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
// $Id: Trigger.hh,v 1.3 2009/06/15 17:19:42 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/MContainer.hh"
#include "SusyAnalysis/debDataMaker/interface/TriggerData.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

class Trigger : public MContainer<std::string,TriggerData> {
  public:
    Trigger(std::string name="") : MContainer<std::string,TriggerData>(name) { }
    Trigger(std::string name, std::vector<std::string> storeList)
  : MContainer<std::string, TriggerData>(name, storeList) { }
    ~Trigger() { }

    inline TriggerData& trigger(std::string triggerName) { return *(*this)(triggerName); }

  // Inherited functions to be overloaded
    void calculate () { };
    int passed(std::string selection);

};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
