#ifndef SusyAnalysis_debDataMaker_Beamspot_hh_
#define SusyAnalysis_debDataMaker_Beamspot_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Beamspot
// 
/**\class Beamspot Beamspot.hh SusyAnalysis/debDataMaker/interface/Beamspot.hh

 Description: <one line class summary>

 Implementation:

   !!!! See usage of inherited functions in Data.hh source code !!!!

   The following fuctions should be overloaded here according to the exact 
   definition of D in Data<D> :

      void set(const edm::Beamspot&) (virtual):
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
// $Id: Beamspot.hh,v 1.7.2.2 2010/09/16 09:03:24 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SusyAnalysis/debDataMaker/interface/Data.hh"
#include "SusyAnalysis/debDataMaker/interface/BeamspotData.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T> class Beamspot : public Data<BeamspotData>{ 
                                                          // D:=BeamspotData
 public:
  Beamspot();
  inline BeamspotData& beamspot(unsigned int i) { return *data(i); } 
                                                          // just a short-hand

  // Inherited functions to be overloaded
  void set(const edm::Event&);
  void calculate ();
  int passed(std::string selection);

  // Introduce new variables and functions
 
};


//--------------------------------- Constructor -------------------------------

template<class T> Beamspot<T>::Beamspot():Data<BeamspotData>(int(1)) {
  
  stdMesg("  Beamspot configuration:\n", typeid(T).name());
  
}

//----------------------------------- set() -----------------------------------

template<class T> void Beamspot<T>::set(const edm::Event& iEvent) {

  if (!isValid()) return;

  edm::Handle<T> beamSpotHandle;
  iEvent.getByLabel("offlineBeamSpot", beamSpotHandle);
  
  if ( beamSpotHandle.isValid() )
    {
      beamspot(0).beamspotx = (*beamSpotHandle).x0();
      beamspot(0).beamspoty = (*beamSpotHandle).y0();
      beamspot(0).beamspotz = (*beamSpotHandle).z0();
    } else
    {
      stdErr("set(): No beamspot available.\n");
    }
}
  
//-------------------------------- calculate() --------------------------------

template<class T> void Beamspot<T>::calculate () { 
}
  
//--------------------------------- passed() ----------------------------------

template<class T> int Beamspot<T>::passed(std::string selection) { 
  return 1; 
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
