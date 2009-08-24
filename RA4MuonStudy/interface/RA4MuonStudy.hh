#ifndef SusyAnalysis_RA4MuonStudy_RA4MuonStudy_hh_
#define SusyAnalysis_RA4MuonStudy_RA4MuonStudy_hh_
// -*- C++ -*-
//
// Package:    RA4MuonStudy
// Class:      RA4MuonStudy
// 
/**\class RA4MuonStudy RA4MuonStudy.cc SusyAnalysis/RA4MuonStudy/src/RA4MuonStudy.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Attila ARANYI
//         Created:  Mon Jun 01 17:54:26 CET 2009
// $Id: RA4MuonStudy.hh,v 1.1.1.1 2009/07/03 10:11:55 aranyi Exp $
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
#include "TMath.h"
#include "TLorentzVector.h"

#include "SusyAnalysis/debDataMaker/interface/CONST.hh"
#include "SusyAnalysis/debDataMaker/interface/Jet.hh"
#include "SusyAnalysis/debDataMaker/interface/Met.hh"
#include "SusyAnalysis/debDataMaker/interface/Electron.hh"
#include "SusyAnalysis/debDataMaker/interface/Muon.hh"
#include "SusyAnalysis/debDataMaker/interface/Event.hh"
#include "SusyAnalysis/debDataMaker/interface/Beamspot.hh"
#include "SusyAnalysis/debDataMaker/interface/Trigger.hh"
#include "SusyAnalysis/debDataMaker/interface/McProcessProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/McParticleProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/JetProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/MetProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/ElectronProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/MuonProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/DeltaR.hh"

#include <iostream>    
#include <fstream> 

using namespace deb;

class RA4MuonStudy : public edm::EDFilter {
public:
  explicit RA4MuonStudy(const edm::ParameterSet&);
  ~RA4MuonStudy();

  MuonProducer<pat::Muon> patmuon;
  McProcessProducer<reco::Candidate,2> promptmuon;
  McParticleProducer<reco::Candidate,1> mcmuon;



public:
  std::vector<std::string> selection;

private:
  virtual void beginJob(const edm::EventSetup&);
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob();

};

#endif
