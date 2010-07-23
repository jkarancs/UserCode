#ifndef SusyAnalysis_debDataMaker_debNtupleMaker_hh_
#define SusyAnalysis_debDataMaker_debNtupleMaker_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      debNtupleMaker
// 
/**\class debNtupleMaker debNtupleMaker.cc SusyAnalysis/debDataMaker/src/debNtupleMaker.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: debNtupleMaker.hh,v 1.9 2010/07/18 12:26:23 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

// system include files 
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
//#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"

//#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
//#include "FWCore/Utilities/interface/InputTag.h"

//#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
//#include "DataFormats/Candidate/interface/Candidate.h"
//#include "DataFormats/Candidate/interface/CandidateFwd.h"
//#include "DataFormats/Common/interface/Ref.h"
//#include "DataFormats/Common/interface/View.h"
//#include "FWCore/Framework/interface/ESHandle.h"

//#include "DataFormats/JetReco/interface/GenJet.h"
//#include "DataFormats/JetReco/interface/CaloJet.h"
//#include "DataFormats/METReco/interface/GenMET.h"
//#include "DataFormats/METReco/interface/GenMETFwd.h"
//#include "DataFormats/METReco/interface/CaloMET.h"
//#include "DataFormats/PatCandidates/interface/Electron.h"
//#include "DataFormats/PatCandidates/interface/Muon.h"
//#include "DataFormats/BeamSpot/interface/BeamSpot.h"

//#include "DataFormats/Common/interface/TriggerResults.h"
//#include "FWCore/Framework/interface/TriggerNames.h"

#include "TTree.h"
#include "TH1.h"
#include "TMath.h"
#include "TLorentzVector.h"

#define DEB_DEBUG
// <include modules for debug>
//#include "Cut.hh"
#undef DEB_DEBUG

#include "SusyAnalysis/debDataMaker/interface/JetProducer.hh"
// #include "SusyAnalysis/debDataMaker/interface/MetProducer.hh"
// #include "SusyAnalysis/debDataMaker/interface/DeltaR.hh"
// #include "SusyAnalysis/debDataMaker/interface/ElectronProducer.hh"
// #include "SusyAnalysis/debDataMaker/interface/MuonProducer.hh"
// #include "SusyAnalysis/debDataMaker/interface/McProcessProducer.hh"
// #include "SusyAnalysis/debDataMaker/interface/McParticleProducer.hh"
// #include "SusyAnalysis/debDataMaker/interface/EventProducer.hh"
// #include "SusyAnalysis/debDataMaker/interface/Beamspot.hh"
// #include "SusyAnalysis/debDataMaker/interface/TriggerProducer.hh"


using namespace deb;

class debNtupleMaker : public edm::EDFilter {
public:
  explicit debNtupleMaker(const edm::ParameterSet&);
  ~debNtupleMaker();

  JetProducer<pat::Jet> pjet;
  TTree *tree;
  MultiSelection* pjet_total;

private:
  virtual void beginJob();
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob();

};

#endif
