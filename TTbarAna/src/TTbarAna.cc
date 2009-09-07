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
  pjet(iConfig.getParameter<edm::ParameterSet>("patJetConfig")),
  gjet(iConfig.getParameter<edm::ParameterSet>("genJetConfig")),
  mcttbar1(iConfig.getParameter<edm::ParameterSet>("mcTtbarHH1ProcessConfig")),
  mcttbar2(iConfig.getParameter<edm::ParameterSet>("mcTtbarHH2ProcessConfig")),
  ttbar(pjet, 
	iConfig.getParameter<edm::ParameterSet>("ttbarConfig").
	        getParameter<std::vector<size_t> >("jetIndices"),
	iConfig.getParameter<edm::ParameterSet>("ttbarConfig").
	        getParameter<std::string>("name"),
	iConfig.getParameter<edm::ParameterSet>("ttbarConfig").
	        getParameter<size_t>("storeNCandidates")
	),
  dr_t1_pjet(mcttbar1, pjet, 
       iConfig.getParameter<edm::ParameterSet>("matchTtbarQuarksJets").
	       getParameter<std::string>("nameDr1"),
       iConfig.getParameter<edm::ParameterSet>("matchTtbarQuarksJets").
	       getParameter<std::vector<std::string> >("storeDrMatchQuarks"),
       iConfig.getParameter<edm::ParameterSet>("matchTtbarQuarksJets").
	       getParameter<std::vector<size_t> >("storeDrPatJetIndices")
       ),
  dr_t2_pjet(mcttbar2, pjet, 
       iConfig.getParameter<edm::ParameterSet>("matchTtbarQuarksJets").
	       getParameter<std::string>("nameDr2"),
       iConfig.getParameter<edm::ParameterSet>("matchTtbarQuarksJets").
	       getParameter<std::vector<std::string> >("storeDrMatchQuarks"),
       iConfig.getParameter<edm::ParameterSet>("matchTtbarQuarksJets").
	       getParameter<std::vector<size_t> >("storeDrPatJetIndices")
       ),
  qjet(iConfig.getParameter<edm::ParameterSet>("matchTtbarQuarksJets").
	       getParameter<std::string>("nameJets"),
       iConfig.getParameter<edm::ParameterSet>("matchTtbarQuarksJets").
	       getParameter<std::vector<std::string> >("storeMatchedJets")
       )
		  // ,qjet_w()
{

  tree=fs->make<TTree>("tree", "Flat root tree for TTbarAna");
  pjet.addBranch(tree);
  gjet.addBranch(tree);
  mcttbar1.addBranch(tree);
  mcttbar2.addBranch(tree);

  ttbar.addBranch(tree);
  dr_t1_pjet.addBranch(tree);
  dr_t2_pjet.addBranch(tree);
  qjet.addBranch(tree);

  qjet_list= 
    iConfig.getParameter<edm::ParameterSet>("matchTtbarQuarksJets").
            getParameter<std::vector<std::string> >("matchQuarks");

  // Add a branch with some flags for each event saved in ntuples 
  // Branch is actually already set here, no need to set it again in filter()
  tree->Branch("eventFlag", &eventFlag.quarkSep, "quarkSep/I:quarkMatch");
  eventFlag.quarkSep=NOVAL_I; // set if quarks are well separated
  eventFlag.quarkMatch=NOVAL_I; // set if all quarks have jets

  NEvents=0;
  NMinSixJets=0;
  NAllHadronicEvents=0;
  NQuarksSeparated=0;
  NQuarksMatched=0;

}


TTbarAna::~TTbarAna() {
}


bool TTbarAna::filter(edm::Event& iEvent, const edm::EventSetup& iSetup) {

  NEvents++;

  // Clear info of previous event (for McProcess it is a must)
  mcttbar1.clear();
  mcttbar2.clear();


  // Read Pat Jets and see if there is enough to reconstruct an all-hadronic 
  // ttbar event
  pjet.set(iEvent);
  pjet.select();
  pjet.print(3);
  if (pjet.size()<6) return false;
  NMinSixJets++;


  // See if the event is an all-hadronic ttbar decay
  if (mcttbar1.findProcess(iEvent)!=2) return false;
  NAllHadronicEvents++;
  mcttbar1.set(iEvent, 0);
  mcttbar1.print(3);
  mcttbar2.findProcess(iEvent);
  mcttbar2.set(iEvent, 1);
  mcttbar2.print(3);


  // Flag events where all quarks are well separated
  // We can use McProcess (particles mapped by name), McParticle (vector of 
  // particles), or VContainer<McParticleData<2> > to collect the particles
  McProcess<2> quarks("quarks"); 
  quarks["q1"]=mcttbar1["q"];
  quarks["qbar1"]=mcttbar1["qbar"];
  quarks["b1"]=mcttbar1["b"];
  quarks["q2"]=mcttbar2["q"];
  quarks["qbar2"]=mcttbar2["qbar"];
  quarks["b2"]=mcttbar2["b"];
  quarks.print(4);

  // calculate all mutual angular separations:
  deb::DeltaR<McProcess<2>,McProcess<2> > dr_quarks(quarks, "dr_quarks");
  dr_quarks.calculate();
  dr_quarks.print(4);

  // and find the smallest of them
  deb::DeltaR<McProcess<2>,McProcess<2> >::iterator minQuarkDr;
  minQuarkDr=dr_quarks.findMinDr();

  eventFlag.quarkSep=NOVAL_I;
  if (minQuarkDr!=dr_quarks.end()) {
    std::cout<<"Min quark separation: "<<minQuarkDr->second.r<<std::endl;
    // this should be twice the jet-cone size
    if (minQuarkDr->second.r<1.0) {
      eventFlag.quarkSep=0;
    } else {
      eventFlag.quarkSep=1;
      NQuarksSeparated++;
    }
  }


  // Compute DR angles between jets and quarks in ttbar decay in order to find
  // the best matching jet for each quarks
  dr_t1_pjet.calculate();
  dr_t1_pjet.print(3);
  dr_t2_pjet.calculate();
  dr_t2_pjet.print(3);

  // and collect those jets into the MContainer already declared in the header
  deb::DeltaR<McProcess<2>,Jet>::iterator bestMatch;

  // Loop along the quark names for which we want to find the best jet
  // check both top-decays (already read into qjet_list in constructor)
  //
  // Also, find the worst of the best matches
  float worstMatch=NOVAL_F;

  for (size_t i=0; i<qjet_list.size(); i++) {

    // check firt top-decay
    std::string qname = qjet_list[i];
    bestMatch = dr_t1_pjet.findMinDrForFirst(qname);
    if (bestMatch==dr_t1_pjet.end()) {
      std::cout<<"Pat jet matching "<<qname<<" not found in ";
      std::cout<<dr_t1_pjet.name()<<std::endl;
    } else {
      qname+="1";
      JetData* jet=pjet(bestMatch->first.second);
      if (jet==NULL) {
	std::cout<<"Pat jet with index "<<bestMatch->first.second;
	std::cout<<" not found"<<std::endl;
      } else {
	qjet[qname]=*jet;
      }
      
      if (worstMatch<bestMatch->second.r) worstMatch=bestMatch->second.r;
    }

    // second top-decay
    qname = qjet_list[i];
    bestMatch = dr_t2_pjet.findMinDrForFirst(qname);
    if (bestMatch==dr_t2_pjet.end()) {
      std::cout<<"Pat jet matching "<<qname<<" not found in ";
      std::cout<<dr_t2_pjet.name()<<std::endl;
    } else {
      qname+="2";
      JetData* jet=pjet(bestMatch->first.second);
      if (jet==NULL) {
	std::cout<<"Pat jet with index "<<bestMatch->first.second;
	std::cout<<" not found"<<std::endl;
      } else {
	qjet[qname]=*jet;
      }
      
      if (worstMatch<bestMatch->second.r) worstMatch=bestMatch->second.r;
    }
  }

  qjet.print(4);


  // Flag events where all quarks have matching jets. It follows from the above
  // that if this is true, all match are unambiguous...
  eventFlag.quarkMatch=NOVAL_I;

  if (worstMatch!=NOVAL_F) {
    if (worstMatch<=0.5) {
      eventFlag.quarkMatch=1;
      NQuarksMatched++;
    } else {
      eventFlag.quarkMatch=0;
    }
  }


  // Compute 

  // Reconstruct the ttbar process based on the Pat Jets
  ttbar.calculate();
  ttbar.print(3);

  // 
  

  gjet.set(iEvent);

  // Set branches for filling the tree
  //
  pjet.setBranch();
  gjet.setBranch();
  mcttbar1.setBranch();
  mcttbar2.setBranch();
  ttbar.setBranch();
  dr_t1_pjet.setBranch();
  dr_t2_pjet.setBranch();
  qjet.setBranch();

  tree->Fill();
  return true;
}


void TTbarAna::beginJob(const edm::EventSetup&) {
}


void TTbarAna::endJob() {
}

DEFINE_FWK_MODULE(TTbarAna);
