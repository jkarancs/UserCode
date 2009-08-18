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

#include "SusyAnalysis/TTbarAna/interface/TTbarAna.hh"

using namespace deb;

TTbarAna::TTbarAna(const edm::ParameterSet& iConfig) : 
  // Input data
  pjet(iConfig.getParameter<edm::ParameterSet>("patJetConfig")),
  gjet(iConfig.getParameter<edm::ParameterSet>("genJetConfig")),
  //pmet(iConfig.getParameter<edm::ParameterSet>("patMetConfig")),
  //pelectron(iConfig.getParameter<edm::ParameterSet>("patElectronConfig")),
  //pmuon(iConfig.getParameter<edm::ParameterSet>("patMuonConfig")),
  // Derived objects
  ttbar(pjet, 
	iConfig.getParameter<edm::ParameterSet>("ttbarConfig").
	        getParameter<std::vector<size_t> >("jetIndices"),
	iConfig.getParameter<edm::ParameterSet>("ttbarConfig").
	        getParameter<std::string>("name"),
	iConfig.getParameter<edm::ParameterSet>("ttbarConfig").
	        getParameter<size_t>("storeNCandidates")
	)
{

  tree=fs->make<TTree>("tree", "Flat root tree for TTbarAna");
  pjet.addBranch(tree);
  gjet.addBranch(tree);
  //pmet.addBranch(tree);
  //pelectron.addBranch(tree);
  //pmuon.addBranch(tree);
  ttbar.addBranch(tree);

}


TTbarAna::~TTbarAna() {
}


bool TTbarAna::filter(edm::Event& iEvent, const edm::EventSetup& iSetup) {


  // Set objects from input data
  pjet.set(iEvent);
  gjet.set(iEvent);
  //pmet.set(iEvent);
  //pelectron.set(iEvent);
  //pmuon.set(iEvent);


  // Select events with at least 6 jets
  pjet.select();
  pjet.print(3);

  // Calculate derived objects:

  if (pjet.size()>=6) {
    ttbar.calculate();
    //ttbar.print(3);
  } else {
    ttbar.clear();
  }

  // Set branches for filling the tree
  //
  pjet.setBranch();
  gjet.setBranch();
  //pmet.setBranch();
  //pelectron.setBranch();
  //pmuon.setBranch();
  ttbar.setBranch();
  ttbar.print(3);

  tree->Fill();
  return true;
}


void TTbarAna::beginJob(const edm::EventSetup&) {
}


void TTbarAna::endJob() {
}

DEFINE_FWK_MODULE(TTbarAna);
