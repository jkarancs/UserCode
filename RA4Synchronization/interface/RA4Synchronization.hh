#ifndef SusyAnalysis_RA4Synchronization_RA4Synchronization_hh_
#define SusyAnalysis_RA4Synchronization_RA4Synchronization_hh_
// -*- C++ -*-
//
// Package:    RA4Synchronization
// Class:      RA4Synchronization
// 
/**\class RA4Synchronization RA4Synchronization.cc SusyAnalysis/RA4Synchronization/src/RA4Synchronization.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Anita KAPUSI
//         Created:  Mon Jun 01 17:54:26 CET 2009
// $Id: RA4Synchronization.hh,v 1.2 2009/10/02 07:31:58 aranyi Exp $
//
//
//-----------------------------------------------------------------------------

// system include files 

//user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"


#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"


#include "TTree.h"
#include "TH1.h"
#include "TMath.h"
#include "TLorentzVector.h"   

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Framework/interface/TriggerNames.h"

#include "SusyAnalysis/debDataMaker/interface/Trigger.hh"
#include "SusyAnalysis/debDataMaker/interface/MuonProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/ElectronProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/JetProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/MetProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/Event.hh"

#include <iostream>    
#include <fstream> 

using namespace deb;

class RA4Synchronization : public edm::EDFilter {
public:
  explicit RA4Synchronization(const edm::ParameterSet&);
  ~RA4Synchronization();

  Trigger<edm::TriggerResults> trigger;
  Beamspot<reco::BeamSpot> beamspot;
  JetProducer<pat::Jet> pjet;
  MetProducer<pat::MET> pmet;
  ElectronProducer<pat::Electron> pelectron;
  MuonProducer<pat::Muon> pmuon;
  Event event;

public:
  //int stg;
  int totaleventnum;
  std::vector<std::string> selection;

  int cutmuonum_RA4mu;
  int cutelenum_RA4mu;
  int cutjet_RA4mu;
  int cutmet_RA4mu;

  int cutmuonum_RA4mu_cutflow;
  int cutelenum_RA4mu_cutflow;
  int cutjet_RA4mu_cutflow;
  int cutmet_RA4mu_cutflow;

  int cuthlt_RA4el;
  int cutelenum_RA4el;
  int cutjet_RA4el;
  int cutmet_RA4el;

  std::vector<std::pair<std::string,std::vector<int> > > muonCutFlow;
  int numberofmuons;
  int numberofmuons_cutflow;

private:
  virtual void beginJob(const edm::EventSetup&);
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob();

};

#endif
