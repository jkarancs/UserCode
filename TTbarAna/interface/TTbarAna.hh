#ifndef SusyAnalysis_debDataMaker_TTbarAna_hh_
#define SusyAnalysis_debDataMaker_TTbarAna_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      TTbarAna
// 
/**\class TTbarAna TTbarAna.cc SusyAnalysis/debDataMaker/src/TTbarAna.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Sat Jun 20 10:28:26 CET 2009
// $$
//
//
//-----------------------------------------------------------------------------

// system include files 
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ParameterSet/interface/InputTag.h"

#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/View.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETFwd.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Framework/interface/TriggerNames.h"

#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TLorentzVector.h"

#include "SusyAnalysis/debDataMaker/interface/JetProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/MetProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/ElectronProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/MuonProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/TTbarHH.hh"


using namespace deb;

class TTbarAna : public edm::EDFilter {
public:
  explicit TTbarAna(const edm::ParameterSet&);
  ~TTbarAna();

  // Input data objects
  JetProducer<pat::Jet> pjet;
  JetProducer<reco::GenJet> gjet;
  //MetProducer<pat::MET> pmet;
  //ElectronProducer<pat::Electron> pelectron;
  //MuonProducer<pat::Muon> pmuon;

  // Derived objects
  TTbarHH<Jet> ttbar;

  edm::Service<TFileService> fs;
  TTree *tree;

private:
  virtual void beginJob(const edm::EventSetup&);
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob();

};

#endif
