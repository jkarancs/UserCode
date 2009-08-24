#ifndef SusyAnalysis_RA4MuonStudy_RA4MuonStudy_hh_
#define SusyAnalysis_RA4MuonStudy_RA4MuonStudy_hh_
// -*- C++ -*-
//
// Package:    RA4MuonStudy
// Class:      RA4MuonStudy
// 
/**\class RA4MuonStudy RA4MuonStudy.cc SusyAnalysis/RA4MuonStudy/src/RA4MuonStudy.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Attila ARANYI
//         Created:  Mon Jun 01 17:54:26 CET 2009
// $Id: RA4MuonStudy.hh,v 1.1 2009/08/24 09:40:31 aranyi Exp $
//
//
//-----------------------------------------------------------------------------

// system include files 

//user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"


#include "TTree.h"
#include "TH1.h"
#include "TMath.h"
#include "TLorentzVector.h"

// #include "SusyAnalysis/debDataMaker/interface/Beamspot.hh"
#include "SusyAnalysis/debDataMaker/interface/McProcessProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/McParticleProducer.hh"
#include "SusyAnalysis/debDataMaker/interface/MuonProducer.hh"

//#include <iostream>    
//#include <fstream> 

using namespace deb;

class RA4MuonStudy : public edm::EDFilter {
public:
  explicit RA4MuonStudy(const edm::ParameterSet&);
  ~RA4MuonStudy();

  MuonProducer<pat::Muon> pmuon;
  McProcessProducer<reco::Candidate,2> promptmuon;
  McParticleProducer<reco::Candidate,1> mcmuon;

  

public:
  std::vector<std::string> selection;

private:
  virtual void beginJob(const edm::EventSetup&);
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob();

};

#endif
