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
// $Id: debNtupleMaker.cc,v 1.12 2009/08/24 18:34:30 aranyi Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/debNtupleMaker.hh"

using namespace deb;

debNtupleMaker::debNtupleMaker(const edm::ParameterSet& iConfig) : 
  trigger(iConfig.getParameter<edm::ParameterSet>("TriggerConfig")),
  //gjet(iConfig.getParameter<edm::ParameterSet>("genJetConfig")),
  pjet(iConfig.getParameter<edm::ParameterSet>("patJetConfig")),
  pmet(iConfig.getParameter<edm::ParameterSet>("patMetConfig")),
  pelectron(iConfig.getParameter<edm::ParameterSet>("patElectronConfig")),
  pmuon(iConfig.getParameter<edm::ParameterSet>("patMuonConfig")),
  promptmuon(iConfig.getParameter<edm::ParameterSet>("promptMuonConfig")),
  mcmuon(iConfig.getParameter<edm::ParameterSet>("mcMuonConfig")),
  event(iConfig.getParameter<edm::ParameterSet>("EventConfig")),
  dr_pjet_pmet(pjet, pmet, 
       iConfig.getParameter<edm::ParameterSet>("drPatJetPatMetConfig").
	       getParameter<std::string >("name"),
       iConfig.getParameter<edm::ParameterSet>("drPatJetPatMetConfig").
	       getParameter<std::vector<unsigned int> >("patJetIndices"),
       iConfig.getParameter<edm::ParameterSet>("drPatJetPatMetConfig").
	       getParameter<std::vector<std::string> >("patMetIndices")),
  dr_pjet(
	  pjet,  
	  iConfig.getParameter<edm::ParameterSet>("drPatJetConfig").
	  getParameter<std::string>("name"),
	  iConfig.getParameter<edm::ParameterSet>("drPatJetConfig").
	  getParameter<std::vector<unsigned int> >("patJetIndices"))
{

  // Create an output tree for a manual cross-check of the produced data
  edm::Service<TFileService> fs;
  tree=fs->make<TTree>("tree", "Flat root tree for debNtupleMaker");
  //gjet.addBranch(tree, "gjet");
  pjet.addBranch(tree);
  pmet.addBranch(tree);
  pelectron.addBranch(tree);
  pmuon.addBranch(tree);
  promptmuon.addBranch(tree);
  mcmuon.addBranch(tree);
  event.addBranch(tree);
  beamspot.addBranch(tree,"beamspot");
  trigger.addBranch(tree);
  dr_pjet_pmet.addBranch(tree);
  dr_pjet.addBranch(tree);
  dr_pjet.setMode(1);
}


debNtupleMaker::~debNtupleMaker() {
}


bool debNtupleMaker::filter(edm::Event& iEvent, const edm::EventSetup& iSetup){

  // Clear and Set (in principle clear is not needed here, set does it)
  // 
  // gjet.clear();
  //gjet.set(iEvent);

  pjet.clear();
  pmet.clear();
  event.clear();  
  beamspot.clear();
  trigger.clear();
  pelectron.clear();
  pmuon.clear();
  promptmuon.clear();
  mcmuon.clear();
  dr_pjet_pmet.clear();
  dr_pjet.clear();

  // Set
  //

  pjet.set(iEvent);
  pmet.set(iEvent);
  event.set(iEvent);
  beamspot.set(iEvent);
  trigger.set(iEvent);
  pelectron.set(iEvent);
  pmuon.set(iEvent);
  unsigned int v;                 ///Number of processes found in the event
  v=promptmuon.findProcess(iEvent);
  if (v!=0)
    promptmuon.set(iEvent,0);
  mcmuon.set(iEvent);


  // Calculate
  // 

  pjet.calculate();
  beamspot.calculate();
  trigger.calculate();
  pelectron.calculate(&beamspot);
  pmuon.calculate(&beamspot);
  if (v!=0)
    mcmuon.calculate(promptmuon("chi1")->idx);

  // Calculate pass
  //

  pelectron.calculate_pass();
  pmuon.calculate_pass();
  pjet.calculate_pass();
  event.calculate_pass(&pjet, &pmet, &pelectron, &pmuon, &trigger);

  // Select
  //
  pjet.select();
  pmuon.select();
  mcmuon.select();
  pelectron.select();

  // Calculate angles between selected objects
  //
  dr_pjet_pmet.calculate();
  dr_pjet.calculate();

  // Set branches for filling the tree
  //
  pjet.setBranch();
  pmet.setBranch();
  pelectron.setBranch();
  pmuon.setBranch();
  promptmuon.setBranch();
  mcmuon.setBranch();
  event.setBranch();
  beamspot.setBranch();
  trigger.setBranch();
  dr_pjet_pmet.setBranch();
  dr_pjet.setBranch();


  tree->Fill();
  return true;
}


void debNtupleMaker::beginJob(const edm::EventSetup&) {
}


void debNtupleMaker::endJob() {
}

DEFINE_FWK_MODULE(debNtupleMaker);
