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

// #include "DataFormats/JetReco/interface/GenJet.h"
// #include "DataFormats/JetReco/interface/CaloJet.h"
// #include "DataFormats/METReco/interface/GenMET.h"
// #include "DataFormats/METReco/interface/GenMETFwd.h"
// #include "DataFormats/METReco/interface/CaloMET.h"
// #include "DataFormats/PatCandidates/interface/Electron.h"
// #include "DataFormats/PatCandidates/interface/Muon.h"
// #include "DataFormats/BeamSpot/interface/BeamSpot.h"

// #include "DataFormats/Common/interface/TriggerResults.h"
// #include "FWCore/Framework/interface/TriggerNames.h"

#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TLorentzVector.h"

#include "SusyAnalysis/debDataMaker/interface/JetProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/TTbarHH.hh"
#include "SusyAnalysis/debDataMaker/interface/McProcessProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/DeltaR.hh"

using namespace deb;

class TTbarAna : public edm::EDFilter {
public:
  explicit TTbarAna(const edm::ParameterSet&);
  ~TTbarAna();

  // *** Data obtained from the input files:

  JetProducer<pat::Jet> pjet;
  JetProducer<reco::GenJet> gjet;
  McProcessProducer<reco::Candidate,2> mcttbar1;
  McProcessProducer<reco::Candidate,2> mcttbar2;



  // *** Results obtained by processing input in this code:

  // Reconstruct ttbar from Pat Jets
  TTbarHH<Jet> ttbar;

  // declare DR(top, pjet) here just to be able to save it on ntuples for a
  // cross-check; otherwise we could just declare them in TTbarAna::filter
  deb::DeltaR<McProcess<2>,Jet> dr_t1_pjet;
  deb::DeltaR<McProcess<2>,Jet> dr_t2_pjet;

  // This is what we really want to compute and save: the pat jet closest to
  // the quarks in all-hadronic ttbar decays, so it must be declared here
  std::vector<std::string> qjet_list; // contains quark names to find jet for
  typedef MContainer<std::string,JetData> QJet;
  QJet qjet;

  // Reconstruct W/top from qjets (how simulation predicts mass resolution)
//   Vertex4D<QJet,QJet> qjet_w;
//   Vertex4D<Vertex4D<QJet,QJet>,QJet> qjet_t;


  // Some flags for each event
  struct{
    int quarkSep;
    int quarkMatch;
  } eventFlag;

  edm::Service<TFileService> fs;
  TTree *tree;


  // Counters:
  unsigned int NEvents;
  unsigned int NMinSixJets;
  unsigned int NAllHadronicEvents;
  unsigned int NQuarksSeparated;
  unsigned int NQuarksMatched;

private:
  virtual void beginJob(const edm::EventSetup&);
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob();

};

#endif
