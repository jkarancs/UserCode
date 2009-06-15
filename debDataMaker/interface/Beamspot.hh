#ifndef SusyAnalysis_debDataMaker_Beamspot_hh_
#define SusyAnalysis_debDataMaker_Beamspot_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Beamspot
// 
/**\class Beamspot Beamspot.hh SusyAnalysis/debDataMaker/interface/Beamspot.hh

 Description: 

	The beam spot is the luminous region produced by the collisions of proton beams.

	The algorithm used to calculated the transverse beam position is the so called d0-phi algorithm. This 
	is a robust and fast χ2 fit which just needs 1000 good tracks to reach micron precision. Using a
	Log-Likelihood fit, the beam width can be extracted using 20000 good tracks. A more detail description
	can be found in the CMS Note 2007/021. 

	Luminosity:     L = (f*n*N1*N2) / A

		f : 	the revolution frequency
		n : 	the number of bunches in one beam in the storage ring
	   N1 & N2: 	the number of particles in each bunch
		A : 	the cross section of the beam

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
// $Id: Beamspot.hh,v 1.4 2009/06/05 19:59:25 veszpv Exp $
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
  
  clear();

  BeamspotData new_obj;
  push_back(new_obj);
  if ( beamSpotHandle.isValid() ) {
    beamspot(0).beamspotx = (*beamSpotHandle).x0();
    beamspot(0).beamspoty = (*beamSpotHandle).y0();
    beamspot(0).beamspotz = (*beamSpotHandle).z0();
  } else {
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
