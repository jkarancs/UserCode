// -*- C++ -*-
//
// Package:    StopAnalysis
// Class:      StopAnalysis
// 
/**\class StopAnalysis StopAnalysis.cc SusyAnalysis/StopAnalysis/src/StopAnalysis.cc

 Description:  Main analysis module of stop search at University of Debrecen

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
//
//
// -----------------------------------------------------------------------------

#include "SusyAnalysis/StopAnalysis/interface/StopAnalysis.hh"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

//#include "SusyAnalysis/EventSelector/interface/SelectorDecisions.h"

// -----------------------------------------------------------------------------
StopAnalysis::StopAnalysis(const edm::ParameterSet& iConfig):
patElectronTag_(iConfig.getUntrackedParameter<edm::InputTag>("patElectronTag")),
patJetTag_(iConfig.getUntrackedParameter<edm::InputTag>("patJetTag")),
patMetTag_(iConfig.getUntrackedParameter<edm::InputTag>("patMetTag")),
patMuonTag_(iConfig.getUntrackedParameter<edm::InputTag>("patMuonTag")),
recoMuonTag_(iConfig.getUntrackedParameter<edm::InputTag>("recoMuonTag")),
//recoTrackTag_(iConfig.getUntrackedParameter<edm::InputTag>("recoTrackTag")),
selectorSequence_(iConfig.getParameter<edm::ParameterSet>("selectorSequence")),
eventWeight_( iConfig.getParameter<double>("eventWeight") ),
//runOnAOD_( iConfig.getParameter<double>("runOnAOD") ),
weightSource_(iConfig.getParameter<edm::InputTag>("weightSource") ),
//overallLumi_(iConfig.getParameter<double>("overallLumi") )
//inputHLTTag_(iConfig.getUntrackedParameter<edm::InputTag>("inputHLTTag"))
//TriggerResultsTag_(iConfig.getParameter<edm::InputTag>("TriggerResultsTag"))
//TriggerResultsTag_(iConfig.getParameter<edm::ParameterSet>("hltHighLevel").getUntrackedParameter<edm::InputTag>("TriggerResultsTag"))
//rawJetTypeTag_( iConfig.getParameter<std::string>("rawJetTypeTag") )
rawJetTypeTag_( pat::Jet::correctionType(iConfig.getParameter<std::string>("rawJetTypeTag")) ),
jetorderby_( iConfig.getParameter<std::string>("jetorderby") )
{
  uncorrType_ = pat::uncorrectionTypeMET(iConfig.getParameter<edm::ParameterSet>("selectorSequence").getParameter<edm::ParameterSet>("selectors").getParameter<edm::ParameterSet>("METPre").getParameter<std::string>("uncorrType"));
   // uncorrType_ = pat::uncorrectionTypeMET(iConfig.getParameter<std::string>("uncorrType"));
  correction_ = pat::Jet::correctionType(iConfig.getParameter<edm::ParameterSet>("selectorSequence").getParameter<edm::ParameterSet>("selectors").getParameter<edm::ParameterSet>("JetEtPre").getParameter<std::string>("correction"));
  // rawJetTypeTag_ = pat::Jet::correctionType(iConfig.getParameter<std::string>("rawJetTypeTag"));

  patEle_.id=1;                         // PAT objects are stored here
  patJet_.id=1;                         // also PAT object
  patRawJet_.id=1;
  patMet_.id=1;                         // also PAT object
  recoMet_.id=0;
  patMuo_.id=1;                         // also PAT object
  recoMuo_.id=0; 
  //  recoTrk_.id=0;

  event_.id=-9999;                      // This is the event information (-9999)
  eventSeldec_.id=-9999;                   // Dont know if preselection was done on
                                    // PAT or RECO object at this point

  createOutputTree();
}


// -----------------------------------------------------------------------------
StopAnalysis::~StopAnalysis() {
}


// -----------------------------------------------------------------------------
void 
StopAnalysis::beginJob(const edm::EventSetup&) {

}


// -----------------------------------------------------------------------------
void
StopAnalysis::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  setEventBranch(iEvent, iSetup);
  setEventSelectionBranch(iEvent, iSetup);

  setJetBranch(iEvent, iSetup);
  setElectronBranch(iEvent, iSetup);
  setMuonBranch(iEvent, iSetup);
  //setMuonBranch(iEvent, iSetup, patMuonTag_);
  //setMuonBranch(iEvent, iSetup, recoMuonTag_);
  setMetBranch(iEvent, iSetup);

  // Here now we have local copies of the variables we are interested in, we can
  // do things with them if required. These variables can be found in:
  // patEle_, patJet_, ...


  // End of analyze, fill the tree
  //

  anaTree_->Fill();
}


// -----------------------------------------------------------------------------
void 
StopAnalysis::endJob() {
}


// -----------------------------------------------------------------------------
void
StopAnalysis::createOutputTree() {
  
  edm::Service<TFileService> fs;

  anaTree_=fs->make<TTree>("tree", "Flat root tree for Stop analysis");
  // Careful that list of variables must agree with list of variables in the
  // BRANCH structures. The first variable is always 'id'

  anaTree_->Branch("patEle", &patEle_.id, "id/I:"  // TTreeBranch id
		   "nele/I:"                       //  `-> ElectronBranch
		   "e1_pt/F:e1_eta/F:e1_phi/F:e1_isoR03_trk/F:e1_isoR03_cal/F:e1_hits/F:e1_chi2/F:e1_ndof/F:"   //       `-> ElectronBlock 1
		   "e2_pt/F:e2_eta/F:e2_phi/F:e2_isoR03_trk/F:e2_isoR03_cal/F:e2_hits/F:e2_chi2/F:e2_ndof/F:"   //       `-> ElectronBlock 2
		   "e1j1_dphi/F:e1j2_dphi/F:e1j3_dphi/F:e1j4_dphi/F:e1j5_dphi/F:e1j6_dphi/F:e2j1_dphi/F:e2j2_dphi/F:e2j3_dphi/F:e2j4_dphi/F:e2j5_dphi/F:e2j6_dphi/F");

  anaTree_->Branch("patJet", &patJet_.id, "id/I:"  // TTreeBranch id
		   "njet/I:"                       //  `-> JetBranch
		   "j1_et/F:j1_ret/F:j1_pt/F:j1_rpt/F:j1_eta/F:j1_phi/F:"    
		   //  `-> JetBlock 1
		   "j2_et/F:j2_ret/F:j2_pt/F:j2_rpt/F:j2_eta/F:j2_phi/F:"    
		   //  `-> JetBlock 2
		   "j3_et/F:j3_ret/F:j3_pt/F:j3_rpt/F:j3_eta/F:j3_phi/F:"    
		   //  `-> JetBlock 3
		   "j4_et/F:j4_ret/F:j4_pt/F:j4_rpt/F:j4_eta/F:j4_phi/F:"    
		   //  `-> JetBlock 4
		   "j5_et/F:j5_ret/F:j5_pt/F:j5_rpt/F:j5_eta/F:j5_phi/F:"    
		   //  `-> JetBlock 5
		   "j6_et/F:j6_ret/F:j6_pt/F:j6_rpt/F:j6_eta/F:j6_phi/F:"    
		   //  `-> JetBlock 6
		   "j1j2_dphi/F:j1j3_dphi/F:j1j4_dphi/F:j1j5_dphi/F:j1j6_dphi/F:j2j3_dphi/F:j2j4_dphi/F:j2j5_dphi/F:j2j6_dphi/F:j3j4_dphi/F:j3j5_dphi/F:j3j6_dphi/F:j4j5_dphi/F:j4j6_dphi/F:j5j6_dphi/F");

  anaTree_->Branch("patRawJet", &patRawJet_.id, "id/I:"  // TTreeBranch id
		   "njet/I:"                          //  `-> RawJetBranch
		   "rj1_et/F:rj1_ret/F:rj1_pt/F:rj1_rpt/F:rj1_eta/F:rj1_phi/F:"
		   //  `-> RawJetBlock 1
		   "rj2_et/F:rj2_ret/F:rj2_pt/F:rj2_rpt/F:rj2_eta/F:rj2_phi/F:"
		   //  `-> RawJetBlock 2
		   "rj3_et/F:rj3_ret/F:rj3_pt/F:rj3_rpt/F:rj3_eta/F:rj3_phi/F:"
		   //  `-> RawJetBlock 3
		   "rj4_et/F:rj4_ret/F:rj4_pt/F:rj4_rpt/F:rj4_eta/F:rj4_phi/F:"
		   //  `-> RawJetBlock 4
		   "rj5_et/F:rj5_ret/F:rj5_pt/F:rj5_rpt/F:rj5_eta/F:rj5_phi/F:"
		   //  `-> RawJetBlock 5
		   "rj6_et/F:rj6_ret/F:rj6_pt/F:rj6_rpt/F:rj6_eta/F:rj6_phi/F:"
		   //  `-> RawJetBlock 6
		   "rj1rj2_dphi/F:rj1rj3_dphi/F:rj1rj4_dphi/F:rj1rj5_dphi/F:rj1rj6_dphi/F:rj2rj3_dphi/F:rj2rj4_dphi/F:rj2rj5_dphi/F:rj2rj6_dphi/F:rj3rj4_dphi/F:rj3rj5_dphi/F:rj3rj6_dphi/F:rj4rj5_dphi/F:rj4rj6_dphi/F:rj5rj6_dphi/F");

  anaTree_->Branch("patMet", &patMet_.id, "id/I:"  // TTreeBranch id
                                                   //  `-> MetBranch
		   "met1_level/I:met1_et/F:met1_phi/F:"
		   "met1j1_dphi/F:met1j2_dphi/F:met1j3_dphi/F:met1j4_dphi/F:met1j5_dphi/F:met1j6_dphi/F:"
		   "met1m1_dphi/F:met1m2_dphi/F"); //  `-> MetBlock 1

  anaTree_->Branch("recoMet", &recoMet_.id, "id/I:"// TTreeBranch id
                                                   //  `-> MetBranch
		   "met1_level/I:met1_et/F:met1_phi/F:"
		   "met1j1_dphi/F:met1j2_dphi/F:met1j3_dphi/F:met1j4_dphi/F:met1j5_dphi/F:met1j6_dphi/F:"
		   "met1m1_dphi/F:met1m2_dphi/F"); //  `-> MetBlock 1
		
  anaTree_->Branch("patMuo", &patMuo_.id, "id/I:"  // TTreeBranch id
		   "nmuo/I:"                       //  `-> MuonBranch
		   "m1_pt/F:m1_eta/F:m1_phi/F:m1_isoR03_trk/F:m1_isoR03_cal/F:m1_hits/F:m1_chi2/F:m1_ndof/F:"                      //  `-> MuonBlock 1
		   "m2_pt/F:m2_eta/F:m2_phi/F:m2_isoR03_trk/F:m2_isoR03_cal/F:m2_hits/F:m2_chi2/F:m2_ndof/F");                    //       `-> MuonBlock 2

 anaTree_->Branch("recoMuo", &recoMuo_.id, "id/I:" // TTreeBranch id
		   "nmuo/I:"                       //  `-> MuonBranch
		   "m1_pt/F:m1_eta/F:m1_phi/F:m1_isoR03_trk/F:m1_isoR03_cal/F:m1_hits/F:m1_chi2/F:m1_ndof/F:"                      //  `-> MuonBlock 1
		   "m2_pt/F:m2_eta/F:m2_phi/F:m2_isoR03_trk/F:m2_isoR03_cal/F:m2_hits/F:m2_chi2/F:m2_ndof/F");                     //  `-> MuonBlock 2

  anaTree_->Branch("event", &event_.id, "id/I:"    // TTreeBranch id
		   "run/I:event/I:genevprocid/I:csa07procid/I:alpgenprocid/I:w/D:hlt/I");                                               //  `-> EventBranch

  anaTree_->Branch("eventSeldec", &eventSeldec_.id, "id/I:"
		   "preall_pass/I:"
		   "anaall_pass/I");
		   
}

// -----------------------------------------------------------------------------
void
StopAnalysis::setElectronBranch(const edm::Event& iEvent, 
				const edm::EventSetup& iSetup) {

  // Read valid PAT electrons, and sort them by pt in case they are not sorted
  //
  // get the event and define cache
  edm::Handle<edm::View<pat::Electron > > patElectronHandle;
  iEvent.getByLabel(patElectronTag_, patElectronHandle);
  if (patElectronHandle.isValid()){
    std::vector<std::pair<float, const pat::Electron* > > patElectrons;
    
    // fill cache
    for (edm::View<pat::Electron>::const_iterator iElectron=
	   (*patElectronHandle).begin(); 
	 iElectron!=(*patElectronHandle).end(); 
	 iElectron++) {
      patElectrons.push_back(std::make_pair(iElectron->pt(), &(*iElectron)));
    }
    
    // sort cache
    std::sort(patElectrons.begin(), patElectrons.end(), 
	      std::greater<std::pair<float, const pat::Electron* > >());
    
    // patElectrons now contains pointers to all good electrons sorted by pt
    // Fill electron branch
    
    patEle_.nele=0;
    for (unsigned int i=0; i<SIZE_OF_ELEBRANCH; i++) {
      patEle_.e[i].isoR03_trk=-9999.0;
      patEle_.e[i].isoR03_cal=-9999.0;
      patEle_.e[i].hits=-9999.0;
      patEle_.e[i].chi2=-9999.0;
      patEle_.e[i].ndof=-9999.0;
      if (patElectrons.size()>i) {
	patEle_.nele=i+1;
	patEle_.e[i].pt=patElectrons[i].second->pt();
	patEle_.e[i].eta=patElectrons[i].second->eta();
	patEle_.e[i].phi=patElectrons[i].second->phi();
      }
      else {
	patEle_.e[i].pt=-9999.0;
	patEle_.e[i].eta=-9999.0;
	patEle_.e[i].phi=-9999.0;
      }
    }

    int i=0;
    for (unsigned int j=0; j<SIZE_OF_JETBRANCH; j++){
      for (unsigned int k=0; k<SIZE_OF_ELEBRANCH; k++){
	if(patEle_.e[k].phi==-9999.0 || patJet_.j[j].phi==-9999.0){
	  patEle_.ej[i].dphi=-9999.0;}
	else{
	  float temp_dphi=fabs(patEle_.e[k].phi-patJet_.j[j].phi);
	  if (temp_dphi<TMath::Pi()){
	    patEle_.ej[i].dphi=temp_dphi;
	  }
	  else{
	    patEle_.ej[i].dphi=2*TMath::Pi()-temp_dphi;
	  }
	}
	i++;
      }
    }
  }


/*    for (unsigned int i=0; i<SIZE_OF_ELE_DIFFBLOCK; i++){
      for (unsigned int j=0; j<SIZE_OF_ELEBRANCH; j++){
	for (unsigned int k=0; k<SIZE_OF_JETBRANCH; k++){
	  if(patJet_.njet>=2){
	    if (j<k){
	      if (fabs(patElectrons[j].second->phi()-patJet_.j[k].phi)<TMath::Pi()){
		patEle_.ej[i].dphi=fabs(patElectrons[j].second->phi()-patJet_.j[k].phi);
	      }
	      if (fabs(patElectrons[j].second->phi()-patJet_.j[k].phi)>TMath::Pi()){
		patEle_.ej[i].dphi=2*TMath::Pi()-fabs(patElectrons[j].second->phi()-patJet_.j[k].phi);
	      }
	    }
	  }
	}
      }
    }
  }
*/

  else {std::cout << "PAT Electron doesn't exist!" << std::endl;}
}


// -----------------------------------------------------------------------------
void
StopAnalysis::setJetBranch(const edm::Event& iEvent, 
			   const edm::EventSetup& iSetup) {
  
  // SAME: Read valid PAT jets, and sort them by et in case they are not sorted
  //
  edm::Handle<edm::View<pat::Jet> > patJetHandle;
  iEvent.getByLabel(patJetTag_, patJetHandle);
  if (patJetHandle.isValid()) {
    std::vector<std::pair<float, const pat::Jet* > > patJets;
    

    /* std::vector<float> correctedEts;
  correctedEts.reserve(patJetHandle->size());
  for ( size_t i=0; i<patJetHandle->size(); ++i ) {
    const pat::Jet& jet = (*patJetHandle)[i];
    float et = jet.et();
    if ( correction_ != pat::Jet::DefaultCorrection ) {
      et *= jet.correctionFactor(pat::Jet::NoCorrection);
      if ( correction_ != pat::Jet::NoCorrection )  
	et *= jet.correctionFactor(correction_);
    }
    correctedEts.push_back(et);
  }
  std::vector<size_t> etSorted = 
    IndexSorter< std::vector<float> >(correctedEts,true)();   
    */

    /* for(int i=0; i<(*patJetHandle).size(),i++){
       float pt = (*patJetHandle)[i].pt();}
     */

    for (edm::View<pat::Jet>::const_iterator iJet=(*patJetHandle).begin(); 
	 iJet!=(*patJetHandle).end(); iJet++) {

      float pt = iJet->pt();
      float et = iJet->et();
      if ( correction_ != pat::Jet::DefaultCorrection ) {
	pt *= iJet->correctionFactor(pat::Jet::NoCorrection);
	et *= iJet->correctionFactor(pat::Jet::NoCorrection);
	if ( correction_ != pat::Jet::NoCorrection ){
	  pt *= iJet->correctionFactor(correction_);
	  et *= iJet->correctionFactor(correction_);
	}
      }
      
      if(jetorderby_.compare("pt")) {
	patJets.push_back(std::make_pair(pt, &(*iJet)));
      }
      if(jetorderby_.compare("et")) {
	patJets.push_back(std::make_pair(et, &(*iJet)));
      }
      if(!jetorderby_.compare("pt")&& !jetorderby_.compare("et")) {
	std::cout << "Please write \"pt\" or \"et\" to the jetorderby variable into the config file!" << std::endl;
      }
    }
    
    std::sort(patJets.begin(), patJets.end(), 
	      std::greater<std::pair<float, const pat::Jet* > >());
    
    patJet_.njet=0;
    for (unsigned int i=0; i<SIZE_OF_JETBRANCH; i++) {
      if (patJets.size()>i) {
	patJet_.njet=i+1;
	
	float et = patJets[i].second->et();
	float ret = patJets[i].second->et()*
	  patJets[i].second->correctionFactor(pat::Jet::NoCorrection);
	float pt = patJets[i].second->pt();
	float rpt = patJets[i].second->pt()*
	  patJets[i].second->correctionFactor(pat::Jet::NoCorrection);
	
	if ( correction_ != pat::Jet::DefaultCorrection ) {
	  et *= patJets[i].second->correctionFactor(pat::Jet::NoCorrection);
	  pt *= patJets[i].second->correctionFactor(pat::Jet::NoCorrection);
	  if ( correction_ != pat::Jet::NoCorrection ) {
	    et *= patJets[i].second->correctionFactor(correction_);
	    pt *= patJets[i].second->correctionFactor(correction_);
	  }
	}
 
	patJet_.j[i].et=et;
	patJet_.j[i].ret=ret;
	patJet_.j[i].pt=pt;
	patJet_.j[i].rpt=rpt;
	patJet_.j[i].eta=patJets[i].second->eta();
	patJet_.j[i].phi=patJets[i].second->phi();
      }
      else {
	patJet_.j[i].et=-9999.0;
	patJet_.j[i].ret=-9999.0;
	patJet_.j[i].pt=-9999.0;
	patJet_.j[i].rpt=-9999.0;
	patJet_.j[i].eta=-9999.0;
	patJet_.j[i].phi=-9999.0;
      }
    }

    int i=0;
    for (unsigned int j=0; j<SIZE_OF_JETBRANCH-1; j++){
      for (unsigned int k=j+1; k<SIZE_OF_JETBRANCH; k++){
	if(patJet_.j[k].phi==-9999.0 || patJet_.j[j].phi==-9999.0){
	  patJet_.jj[i].dphi=-9999.0;}
	else{
	  float temp_dphi=fabs(patJet_.j[k].phi-patJet_.j[j].phi);
	  if (temp_dphi<TMath::Pi()){
	    patJet_.jj[i].dphi=temp_dphi;
	  }
	  else{
	    patJet_.jj[i].dphi=2*TMath::Pi()-temp_dphi;
	  }
	}
	i++;
      }
    }

    // patRawJets
    std::vector<std::pair<float, const pat::Jet* > > patRawJets;
    for (edm::View<pat::Jet>::const_iterator iJet=
	   (*patJetHandle).begin(); 
	 iJet!=(*patJetHandle).end(); 
	 iJet++) {
      float pt = iJet->pt();
      float et = iJet->et();
      if ( correction_ != pat::Jet::DefaultCorrection ) {
	pt *= iJet->correctionFactor(pat::Jet::NoCorrection);
	et *= iJet->correctionFactor(pat::Jet::NoCorrection);
	if ( correction_ != pat::Jet::NoCorrection ){
	  pt *= iJet->correctionFactor(correction_);
	  et *= iJet->correctionFactor(correction_);
	}
      }      
      
      if(jetorderby_.compare("pt")) {
	patRawJets.push_back(std::make_pair(pt, &(*iJet)));
      }
      if(jetorderby_.compare("et")) {
	patRawJets.push_back(std::make_pair(et, &(*iJet)));
      }
      if(!jetorderby_.compare("pt")&& !jetorderby_.compare("et")) {
	std::cout << "Please write \"pt\" or \"et\" to the jetorderby variable into the config file!" << std::endl;
      }
    }
    
    std::sort(patRawJets.begin(), patRawJets.end(), 
	      std::greater<std::pair<float, const pat::Jet* > >());
    
    patRawJet_.njet=0;
    for (unsigned int i=0; i<SIZE_OF_JETBRANCH; i++) {
      if (patRawJets.size()>i) {
	patRawJet_.njet=i+1;
	
	float et = patRawJets[i].second->et();
	float ret = patJets[i].second->et()*
	  patJets[i].second->correctionFactor(pat::Jet::NoCorrection);
	float pt = patRawJets[i].second->pt();
	float rpt = patJets[i].second->pt()*
	  patJets[i].second->correctionFactor(pat::Jet::NoCorrection);
	if ( correction_ != pat::Jet::DefaultCorrection ) {
	  et *= patRawJets[i].second->correctionFactor(pat::Jet::NoCorrection);
	  pt *= patRawJets[i].second->correctionFactor(pat::Jet::NoCorrection);
	  if ( correction_ != pat::Jet::NoCorrection ) {
	    et *= patRawJets[i].second->correctionFactor(rawJetTypeTag_);
	    pt *= patRawJets[i].second->correctionFactor(rawJetTypeTag_);
	  }	
	} 
	patRawJet_.j[i].et=et;
	patRawJet_.j[i].ret=ret;
	patRawJet_.j[i].pt=pt;
	patRawJet_.j[i].rpt=rpt;
	patRawJet_.j[i].eta=patRawJets[i].second->eta();
	patRawJet_.j[i].phi=patRawJets[i].second->phi();
      }
      else {
	patRawJet_.j[i].et=-9999.0;
	patRawJet_.j[i].ret=-9999.0;
	patRawJet_.j[i].pt=-9999.0;
	patRawJet_.j[i].rpt=-9999.0;
	patRawJet_.j[i].eta=-9999.0;
	patRawJet_.j[i].phi=-9999.0;
      }
    }

    i=0;
    for (unsigned int j=0; j<SIZE_OF_JETBRANCH-1; j++){
      for (unsigned int k=j+1; k<SIZE_OF_JETBRANCH; k++){
	if(patRawJet_.j[k].phi==-9999.0 || patRawJet_.j[j].phi==-9999.0){
	  patRawJet_.jj[i].dphi=-9999.0;}
	else{
	  float temp_dphi=fabs(patRawJet_.j[k].phi-patRawJet_.j[j].phi);
	  if (temp_dphi<TMath::Pi()){
	    patRawJet_.jj[i].dphi=temp_dphi;
	  }
	  else{
	    patRawJet_.jj[i].dphi=2*TMath::Pi()-temp_dphi;
	  }
	}
	i++;
      }
    }

  }
  else {std::cout << "PAT Jet doesn't exist!" << std::endl;}  
}

// -----------------------------------------------------------------------------
void
StopAnalysis::setMetBranch(const edm::Event& iEvent, 
			   const edm::EventSetup& iSetup) {
  
  edm::Handle<edm::View<pat::MET> > patMetHandle;
  iEvent.getByLabel(patMetTag_, patMetHandle);
  if (patMetHandle.isValid()){
    //  std::vector<std::pair<float, const pat::MET* > > patMets;
    double patMet_pt;
    float patMet_phi;
    
    patMet_pt = uncorrType_==pat::MET::uncorrMAXN ?
      patMetHandle->front().et() : patMetHandle->front().uncorrectedPt(uncorrType_);
    patMet_phi = uncorrType_==pat::MET::uncorrMAXN ?
      patMetHandle->front().phi() : patMetHandle->front().uncorrectedPhi(uncorrType_);

    //for (unsigned int i=0; i<SIZE_OF_METBRANCH; i++) {
    //  if (patMets.size()>i) {
    int i=0;
    if (uncorrType_==pat::MET::uncorrALL){
      patMet_.met[i].level=0;           //! uncorrect to bare bones
    }
    if (uncorrType_==pat::MET::uncorrJES){
      patMet_.met[i].level=1;           //! uncorrect for JES only
    }
    if (uncorrType_==pat::MET::uncorrMUON){
      patMet_.met[i].level=2;           //! uncorrect for MUON only
    } 
    if (uncorrType_==pat::MET::uncorrMAXN){
      patMet_.met[i].level=3;
    }
    patMet_.met[i].et=patMet_pt;
    patMet_.met[i].phi=patMet_phi;
    //    }
    //else {
    //  patMet_.met[i].level=-9999;
    //  patMet_.met[i].et=-9999.0;
    //  patMet_.met[i].phi=-9999.0;
    //}
    // }
  }
  else {
    std::cout << "PAT Met doesn't exist!" << std::endl;
    int i=0;
    patMet_.met[i].level=-9999;
    patMet_.met[i].et=-9999.0;
    patMet_.met[i].phi=-9999.0;
  }

  int i=0;
  int k=0;
  for (unsigned int j=0; j<SIZE_OF_JETBRANCH; j++){
    if(patMet_.met[k].phi==-9999.0 || patJet_.j[j].phi==-9999.0){
      patMet_.metj[i].dphi=-9999.0;}
    else{
      float temp_dphi=fabs(patMet_.met[k].phi-patJet_.j[j].phi);
      if (temp_dphi<TMath::Pi()){
	patMet_.metj[i].dphi=temp_dphi;
      }
      else{
	patMet_.metj[i].dphi=2*TMath::Pi()-temp_dphi;
      }
    }
    i++;
  }

  i=0;
  k=0;
  for (unsigned j=0; j<SIZE_OF_MUOBRANCH; j++){
    if(patMet_.met[k].phi==-9999.0 || patMuo_.m[j].phi==-9999.0){
      patMet_.metm[i].dphi=-9999.0;}
    else{
      float temp_dphi=fabs(patMet_.met[k].phi-patMuo_.m[j].phi);
      if (temp_dphi<TMath::Pi()){
	patMet_.metm[i].dphi=temp_dphi;
      }
      else{
	patMet_.metm[i].dphi=2*TMath::Pi()-temp_dphi;
      }
    }
    i++;
  }

 i=0;
 recoMet_.met[i].level=-9999.0;
 recoMet_.met[i].et=-9999.0;
 recoMet_.met[i].phi=-9999.0;
 for (unsigned j=0; j<SIZE_OF_JETBRANCH; j++){
   recoMet_.metj[i].dphi=-9999.0;
 }
 for (unsigned j=0; j<SIZE_OF_MUOBRANCH; j++){
   recoMet_.metm[i].dphi=-9999.0;
 }

  /*for (edm::View<pat::MET>::const_iterator iMet=
    (*patMetHandle).begin(); 
    iMet!=(*patMetHandle).end(); 
    iMet++) {
    patMets.push_back(std::make_pair(iMet->pt(), &(*iMet)));
  }
  
  std::sort(patMets.begin(), patMets.end(), 
	    std::greater<std::pair<float, const pat::MET* > >());

  for (unsigned int i=0; i<SIZE_OF_METBRANCH; i++) {
    if (patMets.size()>i) {
      patMet_.met[i].level=0;
      //patMet_.met[i].level=patMets[i].second->level();
      patMet_.met[i].et=patMets[i].second->et();
      patMet_.met[i].phi=patMets[i].second->phi();
    }
    else {
      patMet_.met[i].level=-9999;
      patMet_.met[i].et=-9999.0;
      patMet_.met[i].phi=-9999.0;
    }
  } 
  */
  /*
    edm::Handle<edm::View<reco::MET> > recoMetHandle;
    iEvent.getByLabel(recoMetTag_, recoMetHandle);
    std::vector<std::pair<float, const reco::MET* > > recoMets;
    if (recoMetHandle.isValid()){
    for (unsigned int i=0; i<SIZE_OF_METBRANCH; i++) {
    if (recoMets.size()>i) {
    recoMet_.met[i].level=-9999;
    recoMet_.met[i].et=recoMets[i].second->et();
    recoMet_.met[i].phi=recoMets[i].second->phi();
    }
    else {
    recoMet_.met[i].level=-9999;
    recoMet_.met[i].et=-9999.0;
    recoMet_.met[i].phi=-9999.0;
    }
    }
    }    
    else{cout << "RECO Met doesn't exist!" << endl;}
  */
}

// -----------------------------------------------------------------------------
void
StopAnalysis::setMuonBranch(const edm::Event& iEvent, 
			    const edm::EventSetup& iSetup) {
			    //,const edm::InputTag& input) {
  
  // Read valid PAT muons, and sort them by pt in case they are not sorted
  //
  // get the event and define cache
  //if (input==patMuonTag_){
  edm::Handle<edm::View<pat::Muon > > patMuonHandle;
  iEvent.getByLabel(patMuonTag_, patMuonHandle);
  if (patMuonHandle.isValid()){ 
    std::vector<std::pair<float, const pat::Muon* > > patMuons;
    
    // fill cache
    for (edm::View<pat::Muon>::const_iterator iMuon=
	   (*patMuonHandle).begin(); 
	 iMuon!=(*patMuonHandle).end(); 
	 iMuon++) {
      patMuons.push_back(std::make_pair(iMuon->pt(), &(*iMuon)));
    }
    
    // sort cache
    std::sort(patMuons.begin(), patMuons.end(), 
	      std::greater<std::pair<float, const pat::Muon* > >());
    
    // patMuons now contains pointers to all good muons sorted by pt
    // Fill muon branch
    
    patMuo_.nmuo=0;
    for (unsigned int i=0; i<SIZE_OF_MUOBRANCH; i++) {
      if (patMuons.size()>i) {
	patMuo_.nmuo=i+1;
	patMuo_.m[i].pt=patMuons[i].second->pt();
	patMuo_.m[i].eta=patMuons[i].second->eta();
	patMuo_.m[i].phi=patMuons[i].second->phi();
	patMuo_.m[i].isoR03_trk=patMuons[i].second->trackIso();
	patMuo_.m[i].isoR03_cal=patMuons[i].second->caloIso();
	patMuo_.m[i].hits=patMuons[i].second->combinedMuon()->numberOfValidHits();
	patMuo_.m[i].chi2=patMuons[i].second->track()->chi2();
	patMuo_.m[i].ndof=patMuons[i].second->track()->ndof();
      }
      else {
	patMuo_.m[i].pt=-9999.0;
	patMuo_.m[i].eta=-9999.0;
	patMuo_.m[i].phi=-9999.0;
	patMuo_.m[i].isoR03_trk=-9999.0;
	patMuo_.m[i].isoR03_cal=-9999.0;
	patMuo_.m[i].hits=-9999.0;
	patMuo_.m[i].chi2=-9999.0;
	patMuo_.m[i].ndof=-9999.0;
      }
    }
  }
  else {
    std::cout << "PAT Muon doesn't exist!" << std::endl;
  }
  
   if ( eventWeight_<0.0 ) {  
  //if (runOnAOD_<1.0){
    // && input==recoMuonTag_){
    edm::Handle<edm::View<reco::Muon > > recoMuonHandle;
    iEvent.getByLabel(recoMuonTag_, recoMuonHandle);
    if (recoMuonHandle.isValid()){ 
      std::vector<std::pair<float, const reco::Muon* > > recoMuons;
      
      // fill cache
      for (edm::View<reco::Muon>::const_iterator jMuon=
	     (*recoMuonHandle).begin(); 
	   jMuon!=(*recoMuonHandle).end(); 
	   jMuon++) {
	recoMuons.push_back(std::make_pair(jMuon->pt(), &(*jMuon)));
      }
      
      // sort cache
      std::sort(recoMuons.begin(), recoMuons.end(), 
		std::greater<std::pair<float, const reco::Muon* > >());
      
      // patMuons now contains pointers to all good muons sorted by pt
      // Fill muon branch
      
      
      recoMuo_.nmuo=0;
      for (unsigned int i=0; i<SIZE_OF_MUOBRANCH; i++) {
	if (recoMuons.size()>i) {
	  recoMuo_.nmuo=i+1;
	  recoMuo_.m[i].pt=recoMuons[i].second->pt();
	  recoMuo_.m[i].eta=recoMuons[i].second->eta();
	  recoMuo_.m[i].phi=recoMuons[i].second->phi();
	  recoMuo_.m[i].isoR03_trk=-9999.0;
	  recoMuo_.m[i].isoR03_cal=-9999.0;
	  recoMuo_.m[i].hits=-9999.0;
	  recoMuo_.m[i].chi2=-9999.0;
	  recoMuo_.m[i].ndof=-9999.0;
	  //  recoMuo_.m[i].isoR03_trk=recoMuons[i].second->trackIso();
	  //  recoMuo_.m[i].isoR03_cal=recoMuons[i].second->caloIso();
	}
	else {
	  recoMuo_.m[i].pt=-9999.0;
	  recoMuo_.m[i].eta=-9999.0;
	  recoMuo_.m[i].phi=-9999.0;
	  recoMuo_.m[i].isoR03_trk=-9999.0;
	  recoMuo_.m[i].isoR03_cal=-9999.0;
	  recoMuo_.m[i].hits=-9999.0;
	  recoMuo_.m[i].chi2=-9999.0;
	  recoMuo_.m[i].ndof=-9999.0;
	}
      }
    }
    else {
      std::cout << "RECO Muon doesn't exist!" << std::endl;
    }
   }
   else {
     recoMuo_.nmuo=0;
     for (unsigned int i=0; i<SIZE_OF_MUOBRANCH; i++) {
       recoMuo_.m[i].pt=-9999.0;
       recoMuo_.m[i].eta=-9999.0;
       recoMuo_.m[i].phi=-9999.0;
       recoMuo_.m[i].isoR03_trk=-9999.0;
       recoMuo_.m[i].isoR03_cal=-9999.0;
       recoMuo_.m[i].hits=-9999.0;
       recoMuo_.m[i].chi2=-9999.0;
       recoMuo_.m[i].ndof=-9999.0;
     }
   }
    //}
}

// -----------------------------------------------------------------------------
void
StopAnalysis::setEventBranch(const edm::Event& iEvent, 
				const edm::EventSetup& iSetup) {
 // Get some event information (process ID, weight)
  event_.run   = iEvent.id().run();
  event_.event = iEvent.id().event();
  // event_.procid   = -1;                 // Need to implement it later

  event_.w = -9999.0;
  event_.genevprocid   = -9999.0;
  event_.csa07procid   = -9999.0;
  event_.alpgenprocid   = -9999.0;
  event_.hlt=-9999.0;
  if ( eventWeight_<0.0 ) {     // <0 => get weight from event
    edm::Handle<double> weightHandle;
    iEvent.getByLabel(weightSource_.label(),"weight", weightHandle);
    if (weightHandle.isValid()){ 
      event_.w = (*weightHandle);
    }
    else{
      std::cout << "weigthHandle doesn't exist!" << std::endl;
    }    
    edm::Handle<int> genProcessID;
    iEvent.getByLabel("genEventProcID", genProcessID );
    //(weightSource_.label(),"ProcessID", processHandle);
    if (genProcessID.isValid()){ 
      event_.genevprocid = (*genProcessID);
    }
    else{
      std::cout << "genProcessID doesn't exist!" << std::endl;
    }      
   
    //  event_.csa07procid = csa07::csa07ProcessId(iEvent,1000,"csa07EventWeightProducer");

    //bool runOnChowder = false; // check if this is a chowder sample
    //    csa07ProcessId temp;
    
    //    char * csa07ProcessName(int csa07ProcessId);
    //    int *csa07ProcessId(iEvent,overallLumi_,weightSource_.label());
    //csa07ProcessId temp;
    // event_.csa07procid=csa07ProcessId(iEvent,overallLumi_,weightSource_.label());

    //event_.csa07procid=static_cast<int>(csa07ProcessId(iEvent,overallLumi_,weightSource_.label()));


    //event_.csa07procid=static_cast<int>(csa07ProcessId(iEvent,overallLumi_,weightSource_.label()));

    edm::Handle<int> processHandle; 
    iEvent.getByLabel(weightSource_.label(),"AlpgenProcessID", processHandle);
    if (processHandle.isValid()){ 
      event_.alpgenprocid = (*processHandle);
    }
    else{
      std::cout << "AlpgenProcessID doesn't exist!" << std::endl;
    }
  } 
  else {
    event_.w = eventWeight_; // default: from config
  }
  /*
  edm::Handle<edm::TriggerResults> hltresults;
  iEvent.getByLabel(TriggerResultsTag_, hltresults);
  int ntrigs=hltresults.size();
  edm::TriggerNames triggerNames_;
  triggerNames_.init(hltresults);
  bool accept = false;
  for (int itrig = 0; itrig < ntrigs; ++itrig) {
    if (triggerNames_.triggerName(itrig) == "HLT_Jet110") {
      accept = hltresults.accept(itrig);
    }
  }
  */

  /*
    edm::Handle<edm::TriggerResults> triggerResults;
    iEvent.getByLabel(inputHLTTag_,triggerResults);
    edm::TriggerNames triggerNames(*triggerResults);
    event_.hlt=-9999.0;
    if (triggerResults.isValid()){

  //    if (triggerNames=="HLT1MuonIso"){
	event_.hlt=1; 
      } 
      if (*triggerNames="HLT2MuonIso"){
	event_.hlt=2; 
      } 
      if (*triggerNames="HLT1MuonNonIso"){
	event_.hlt=3; 
      }
      if (*triggerNames!="HLT1MuonIso"&&*triggerNames!="HLT2MuonIso"&&*triggerNames!="HLT1MuonNonIso"){
	event_.hlt=4;
	//}
      event_.hlt = triggerNames.triggerIndex("HLT1MuonIso");
    }
    else{
      std::cout << "TriggerResults doesn't exist!" << std::endl;
    }

*/
}

// -----------------------------------------------------------------------------
void
StopAnalysis::setEventSelectionBranch(const edm::Event& iEvent, 
				 const edm::EventSetup& iSetup) {
//  bool*  decisions_;  
  // bool   globalDec_;
  // SelectorDecisions decisions=selectorSequence_.decisions(iEvent);
  //globalDec_ = true;
  // for ( size_t i=0; i<selectorSequence_.size(); ++i ) {
  //  globalDec_ = (globalDec_ && decisions.decision(i));
  //  decisions_[i] = decisions.decision(i);
  // }

SelectorDecisions decisions=selectorSequence_.decisions(iEvent);
 eventSeldec_.preall.pass = decisions.decision(0);
 eventSeldec_.anaall.pass = decisions.decision(1); 

 // for (unsigned int i=0; i<SIZE_OF_EVENTSELECTIONBRANCH; i++) {
 // if (decisions.size()>i){
 //   eventSelname_.pre[i].pass = i;
 //   eventSelname_.ana[i].pass = i+10;
 //  }
 // }

// eventSel_.pre.pass = true;
// for ( size_t i=0; i<selectorSequence_.size(); ++i ) {
//   eventSel_.pre.pass = (eventSel_.pre.pass && decisions.decision(i));
// }
 
}


// -----------------------------------------------------------------------------
DEFINE_FWK_MODULE(StopAnalysis);
