#ifndef SusyAnalysis_TopStopGenAna_TopStopGenAna_hh_
#define SusyAnalysis_TopStopGenAna_TopStopGenAna_hh_
// -*- C++ -*-
//
// Package:    TopStopGenAna
// Class:      TopStopGenAna
// 
/**\class TopStopGenAna TopStopGenAna.cc SusyAnalysis/TopStopGenAna/src/TopStopGenAna.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Attila ARANYI
//         Created:  Mon Jun 15 13:51:33 CEST 2009
// $Id$
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

#include "SusyAnalysis/debDataMaker/interface/Jet.hh"
#include "SusyAnalysis/debDataMaker/interface/Met.hh"
#include "SusyAnalysis/debDataMaker/interface/DeltaR.hh"
#include "SusyAnalysis/debDataMaker/interface/Electron.hh"
#include "SusyAnalysis/debDataMaker/interface/Muon.hh"
#include "SusyAnalysis/debDataMaker/interface/Event.hh"
#include "SusyAnalysis/debDataMaker/interface/Beamspot.hh"
#include "SusyAnalysis/debDataMaker/interface/Trigger.hh"
#include "SusyAnalysis/debDataMaker/interface/McProcess.hh"

using namespace deb;

class TopStopGenAna : public edm::EDFilter {
public:
  explicit TopStopGenAna(const edm::ParameterSet&);
  ~TopStopGenAna();

  McProcess<reco::Candidate,2> proc;
  //McProcess<reco::Candidate> proc;
  //McProcess_b proc;

  //Event event;

  TTree *tree;  

private:
  virtual void beginJob(const edm::EventSetup&);
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob();

};

#endif
