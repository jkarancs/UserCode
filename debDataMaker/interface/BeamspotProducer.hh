#ifndef SusyAnalysis_debDataMaker_BeamspotProducer_hh_
#define SusyAnalysis_debDataMaker_BeamspotProducer_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      BeamspotProducer
// 
/**\class BeamspotProducer BeamspotProducer.hh SusyAnalysis/debDataMaker/interface/BeamspotProducer.hh

 Description: 

 Implementation:

   List of parameters to steer the object with (passed through iConfig):
      int storeNObjects,   : owned by Beamspot
      InputTag objectTag,  : owned by Beamspot but decided here if set
      int selectionType,   : owned by Beamspot but decided here if set
      pair<string,string> correction: owned by this class
      string sortBy        : owned by this class

   iConfig must be parsed in the contructor. 

   !!!! See usage of inherited functions in Beamspot.hh source code !!!!

   The following fuctions should be overloaded here:

      void set(const edm::Event&) (virtual):
         implements reading variables of D from the CMSSW framework

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Tue Aug 3 12:21:11 CET 2010
// $Id: BeamspotProducer.hh,v 1.1 2010/08/09 15:39:51 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/Beamspot.hh"
#include "SusyAnalysis/debDataMaker/interface/Producer.hh"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T> class BeamspotProducer : public Producer<Beamspot> { 
 public:
  BeamspotProducer(const edm::ParameterSet&);
  BeamspotProducer() {
    stdErr("  BeamspotProducer<%s> configuration missing\n", 
	   humanTypeId<T>().data());
  }

  // Inherited functions to be overloaded
  void set(const edm::Event&);

};


//--------------------------------- Constructor -------------------------------

template<class T> 
BeamspotProducer<T>::BeamspotProducer(const edm::ParameterSet& iConfig)
  : Producer<Beamspot> (iConfig.getParameter<edm::InputTag>("beamspotTag"),
			iConfig.getParameter<std::string>("name") ) {
  
  stdMesg("  BeamspotProducer<%s> configuration:", humanTypeId<T>().data());
  stdMesg("  \tbeamspotTag = '%s'", tag().label().data());
  stdMesg("  List of variables: %s", list().data());
  stdMesg("  Object is %svalid!\n", (isValid() ? "" : "not "));

}

//----------------------------------- set() -----------------------------------

template<class T> void BeamspotProducer<T>::set(const edm::Event& iEvent) {
  increment_event_counter();

  if (!isValid()) return;

  edm::Handle<T> beamSpotHandle;
  iEvent.getByLabel(tag(), beamSpotHandle);

  clear();

  BeamspotData beamspot;
  beamspot.oid = 0;
  beamspot.eid = event_counter();

  if ( beamSpotHandle.isValid() ) {

    beamspot.x = (*beamSpotHandle).x0();
    beamspot.y = (*beamSpotHandle).y0();
    beamspot.z = (*beamSpotHandle).z0();

  } else {

    stdErr("set(): No beamspot available.\n");
    setValid(false);
    return;

  }

  push_back(beamspot);

}
  
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
