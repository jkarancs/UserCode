#ifndef SusyAnalysis_StopAnalysis_StopAnalysis_hh_
#define SusyAnalysis_StopAnalysis_StopAnalysis_hh_
// -*- C++ -*-
//
// Package:    StopAnalysis
// Class:      StopAnalysis
// 
/**\class StopAnalysis StopAnalysis.cc SusyAnalysis/StopAnalysis/src/StopAnalysis.cc

 Description: Main analysis module of stop search at University of Debrecen

 Implementation:
   Oct 18, 2008 Viktor created the main files and started to implement a flat
                ROOT ntuple maker
*/
//
// Original Author:  Viktor Veszpremi
//         Created:  Sat Oct 18 16:23:31 CEST 2008
// $Id$
//
//
// -----------------------------------------------------------------------------

#include <memory>
#include <string>
#include <iostream>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ParameterSet/interface/InputTag.h"

#include "DataFormats/Common/interface/View.h"

// SUSY include files
#include "SusyAnalysis/EventSelector/interface/SusyEventSelector.h"
#include "SusyAnalysis/EventSelector/interface/SelectorSequence.h"
//#include "SusyAnalysis/EventSelector/interface/SelectorDecisions.h"
#include "SusyAnalysis/EventSelector/interface/uncorrectionTypeMET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "PhysicsTools/HepMCCandAlgos/interface/CSA07ProcessId.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Framework/interface/TriggerNames.h"

#include "TTree.h"
#include <map>

// -----------------------------------------------------------------------------
// Flat ROOT tree BLOCKS, here we define what we want to put in the tree
// EVERY VARIABLE USED IN THIS CODE MUST BE PUT IN THE TREE!!!
//

struct LeptonBlock {
  float pt;
  float eta;
  float phi;
  float isoR03_trk;
  float isoR03_cal;
  float hits;
  float chi2;
  float ndof;
};


struct ElectronBlock: LeptonBlock {
};


struct MuonBlock: LeptonBlock {
};


struct JetBlock {
  float et;
  float ret;
  float pt;
  float rpt;
  float eta;
  float phi;
};


struct MetBlock {
  int level;                            // what level MET is corrected at
                                        // level == 0 : default in PAT
  float et;
  float phi;
};


struct EventSelectionBlock {
  int pass;                             // Did the event pass? ( 0 / 1 )
};

struct PreSelectionBlock: EventSelectionBlock {
  // Preselection is determined usually by the trigger choice
};


struct AnalysisSelectionBlock: EventSelectionBlock {
  // Analysis selection can choose a region to analyze, such as control and
  // signal regions
};

struct DphiBlock {
  float dphi;
};

// -----------------------------------------------------------------------------
// Flat ROOT tree BRANCHES, here we construct the branches
//

struct TTreeBranch {
  int id;                               // Identifies the collection used
                                        // id%2 == 0 : RECO object
                                        //      == 1 : PAT object
                                        // id   == -9999 : Event information
};


struct EventBranch: TTreeBranch{
  int run;
  int event;
  int genevprocid;                      //genEvent process id
  int csa07procid;                      //csa07 process id
  int alpgenprocid;                     //Alpgen process id should be -9999 if running on data
  double w;
  int hlt;                              //1:TriggerResults::HLT is HLT1MuonIso
                                        //2:TriggerResults::HLT is HLT2MuonIso
                                        //3:TriggerResults::HLT is HLT1MuonNonIso
                                        //4:TriggerResults::HLT is other
};


#define SIZE_OF_JETBRANCH 6
#define SIZE_OF_JET_DIFFBLOCK (SIZE_OF_JETBRANCH*(SIZE_OF_JETBRANCH-1))/2
struct JetBranch: TTreeBranch{
  int njet;                             // How many valid jets we have
  JetBlock j[SIZE_OF_JETBRANCH];        // We can store this many of them
  DphiBlock jj[SIZE_OF_JET_DIFFBLOCK];
};

#define SIZE_OF_ELEBRANCH 2
#define SIZE_OF_ELE_DIFFBLOCK (SIZE_OF_ELEBRANCH*SIZE_OF_JETBRANCH)
struct ElectronBranch: TTreeBranch{
  int nele;                             // How many valid electrons we have
  ElectronBlock e[SIZE_OF_ELEBRANCH];   // We can store this many of them
  DphiBlock ej[SIZE_OF_ELE_DIFFBLOCK];
};

#define SIZE_OF_MUOBRANCH 2
struct MuonBranch: TTreeBranch{
  int nmuo;                             // How many valid muons we have
  MuonBlock m[SIZE_OF_MUOBRANCH];       // We can store this many of them
};

#define SIZE_OF_METBRANCH 1
struct MetBranch: TTreeBranch{
  MetBlock met[SIZE_OF_METBRANCH];      // We can store this many of them
  DphiBlock metj[SIZE_OF_JETBRANCH];
  DphiBlock metm[SIZE_OF_MUOBRANCH];
};

struct EventSelectionBranch: TTreeBranch{
  PreSelectionBlock preall;
  AnalysisSelectionBlock anaall;
};


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

class StopAnalysis : public edm::EDAnalyzer {
public:
  explicit StopAnalysis(const edm::ParameterSet&);
  ~StopAnalysis();


private:
  virtual void beginJob(const edm::EventSetup&);
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();


private:

  // Selections
  SelectorSequence selectorSequence_;   // Interface to selectors

  // Input tags
  edm::InputTag patElectronTag_;
  edm::InputTag patJetTag_;
  edm::InputTag patMetTag_;
  edm::InputTag recoMetTag_;
  pat::MET::UncorectionType uncorrType_;
  pat::Jet::CorrectionType correction_;
  edm::InputTag patMuonTag_;
  edm::InputTag recoMuonTag_;
  // edm::InputTag recoTrackTag_;
  double eventWeight_;
  //double runOnAOD_;
  edm::InputTag weightSource_;
  //  double overallLumi_;
  // edm::InputTag inputHLTTag_;
  edm::InputTag TriggerResultsTag_;
  pat::Jet::CorrectionType rawJetTypeTag_;
  std::string jetorderby_;

  // Output tree, its branches, and fuctions to fill them
  TTree* anaTree_;
  ElectronBranch patEle_;
  JetBranch patJet_;
  JetBranch patRawJet_;
  MetBranch patMet_;
  MetBranch recoMet_;
  MuonBranch patMuo_;
  MuonBranch recoMuo_;
  // MuonBranch recoTrk_;
  EventBranch event_;
  EventSelectionBranch eventSeldec_;

  void createOutputTree();
  void setElectronBranch(const edm::Event&, const edm::EventSetup&);
  void setJetBranch(const edm::Event&, const edm::EventSetup&);
  void setMetBranch(const edm::Event&, const edm::EventSetup&);
  void setMuonBranch(const edm::Event&, const edm::EventSetup&);
		     //, const edm::InputTag&);
  void setEventBranch(const edm::Event&, const edm::EventSetup&);
  void setEventSelectionBranch(const edm::Event&, const edm::EventSetup&);
};

#endif
