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

#include "SusyAnalysis/TopStopGenAna/interface/TopStopGenAna.hh"

using namespace deb;

TopStopGenAna::TopStopGenAna(const edm::ParameterSet& iConfig) : 
  proc(iConfig.getParameter<edm::ParameterSet>("mcProcessConfig")){

  // Create an output tree for a manual cross-check of the produced data
  edm::Service<TFileService> fs;
  tree=fs->make<TTree>("tree", "Flat root tree for debNtupleMaker");

  proc.addBranch(tree,"process");
}


TopStopGenAna::~TopStopGenAna() {
}


bool TopStopGenAna::filter(edm::Event& iEvent, const edm::EventSetup& iSetup){

  // Clear and Set (in principle clear is not needed here, set does it)
  //
  proc.clear();

  // Set
  //
  unsigned int v;                 ///Number of processes found in the event
  v=proc.findProcess(iEvent);
  if (v!=0){
    //for(unsigned int i=0;i<v;i++){            
      proc.set(iEvent,0);
      //if (i==0)
      proc.print(3);
      proc.setBranch();
      tree->Fill();
    //}
  }


  // Calculate
  // 
  //proc.calculate();

  // Calculate pass
  //
  //proc.calculate_pass();

  // Select
  //
  //proc.select();

  // Calculate angles between selected objects
  //

  // Set branches for filling the tree
  //
  
//   proc.setBranch();
//   tree->Fill();
  
  return true;
}


void TopStopGenAna::beginJob(const edm::EventSetup&) {
}


void TopStopGenAna::endJob() {
}

DEFINE_FWK_MODULE(TopStopGenAna);
