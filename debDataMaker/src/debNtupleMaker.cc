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
// $Id: debNtupleMaker.cc,v 1.1 2009/05/30 19:52:31 veszpv Exp $
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
  pjet.set(iEvent);

  pmet.clear();
  pmet.set(iEvent);

  event.clear();
  event.set(iEvent);

  beamspot.clear();
  beamspot.set(iEvent);

  trigger.clear();
  trigger.set(iEvent);

  pelectron.clear();
  pelectron.set(iEvent);

  pmuon.clear();
  pmuon.set(iEvent);

  // Calculate
  // 

  pjet.calculate();
  pmet.calculate();
  event.calculate();
  beamspot.calculate();
  trigger.calculate();
  pelectron.calculate(beamspot);
  pmuon.calculate(beamspot);
  dr_pjet_pmet.clear();
  dr_pjet_pmet.calculate();

  dr_pjet.clear();
  dr_pjet.calculate();
  // Select
  //

  tree->Fill();
  return true;
}


void debNtupleMaker::beginJob(const edm::EventSetup&) {
}


void debNtupleMaker::endJob() {
}

DEFINE_FWK_MODULE(debNtupleMaker);
