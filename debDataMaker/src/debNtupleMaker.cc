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
// $Id: debNtupleMaker.cc,v 1.5 2009/06/05 19:38:27 veszpv Exp $
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
  event(iConfig.getParameter<edm::ParameterSet>("EventConfig")),
  dr_pjet_pmet(
       pjet, iConfig.getParameter<edm::ParameterSet>("drPatJetPatMetConfig").
             getParameter<std::vector<unsigned int> >("patJetIndices"),
       pmet, pmet.ind(
             iConfig.getParameter<edm::ParameterSet>("drPatJetPatMetConfig").
	     getParameter<std::vector<std::string> >("caloMetCorrections"))),
  dr_pjet(
       pjet, iConfig.getParameter<edm::ParameterSet>("drPatJetConfig").
             getParameter<std::vector<unsigned int> >("patJetIndices"))
{

  // Create an output tree for a manual cross-check of the produced data
  edm::Service<TFileService> fs;
  tree=fs->make<TTree>("tree", "Flat root tree for debNtupleMaker");
  //gjet.addBranch(tree, "gjet");
  pjet.addBranch(tree, "pjet");
  pmet.addBranch(tree, "pmet");
  pelectron.addBranch(tree, "pelectron");
  pmuon.addBranch(tree, "pmuon");
  event.addBranch(tree,"event");
  beamspot.addBranch(tree,"beamspot");
  trigger.addBranch(tree,"trigger");
  dr_pjet_pmet.addBranch(tree, "dr_pj_pmet");
  dr_pjet.addBranch(tree, "dr_pjet");
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


  // Calculate
  // 

  pjet.calculate();
  pmet.calculate();
  event.calculate();
  beamspot.calculate();
  trigger.calculate();
  pelectron.calculate(&beamspot);
  pmuon.calculate(&beamspot);

  event.setInput(pjet,pmet,pelectron,pmuon,trigger);
  // Calculate pass
  //

  pelectron.calculate_pass();
  pmuon.calculate_pass();
  pjet.calculate_pass();
  event.calculate_pass();

  // Select
  //
  pjet.select();
  pmuon.select();
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
