// -*- C++ -*-
//
// Package:    RA4MuonStudy
// Class:      RA4MuonStudy
// 
/**\class RA4MuonStudy RA4MuonStudy.cc SusyAnalysis/
  RA4MuonStudy/src/RA4MuonStudy.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Attila ARANYI
//         Created:  Mon Jun 01 17:54:26 CET 2009
// $Id: RA4MuonStudy.cc,v 1.1 2009/08/24 09:44:38 aranyi Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/RA4MuonStudy/interface/RA4MuonStudy.hh"

using namespace deb;

RA4MuonStudy::RA4MuonStudy(const edm::ParameterSet& iConfig) : 

  pmuon(iConfig.getParameter<edm::ParameterSet>("patMuonConfig")),
  promptmuon(iConfig.getParameter<edm::ParameterSet>("promptMuonConfig")),
  mcmuon(iConfig.getParameter<edm::ParameterSet>("mcMuonConfig"))
{


}


RA4MuonStudy::~RA4MuonStudy() {
}


bool RA4MuonStudy::filter(edm::Event& iEvent, 
			      const edm::EventSetup& iSetup){


  pmuon.clear();
  pmuon.set(iEvent);
  pmuon.print(3);

  promptmuon.clear();
  unsigned int v;                 ///Number of processes found in the event
  v=promptmuon.findProcess(iEvent);
  if (v!=0)
    promptmuon.set(iEvent,0);
  promptmuon.print(3);

  mcmuon.clear();  
  mcmuon.set(iEvent);  
  if (v!=0){
    mcmuon.calculate(promptmuon("~chi1+")->idx);
    mcmuon.select();
  }
  mcmuon.print(3);


  return true;
}


void RA4MuonStudy::beginJob(const edm::EventSetup&) {
}


void RA4MuonStudy::endJob() {
}

DEFINE_FWK_MODULE(RA4MuonStudy);
