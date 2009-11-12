// -*- C++ -*-
//
// Package:    RA4Synchronization
// Class:      RA4Synchronization
// 
/**\class RA4Synchronization RA4Synchronization.cc SusyAnalysis/RA4Synchronization/src/RA4Synchronization.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Anita KAPUSI
//         Created:  Mon Jun 01 17:54:26 CET 2009
// $Id: RA4Synchronization.cc,v 1.3 2009/11/02 15:08:10 aranyi Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/RA4Synchronization/interface/RA4Synchronization.hh"

using namespace deb;

RA4Synchronization::RA4Synchronization(const edm::ParameterSet& iConfig) : 
  trigger(iConfig.getParameter<edm::ParameterSet>("TriggerConfig")),
  pjet(iConfig.getParameter<edm::ParameterSet>("patJetConfig")),
  pmet(iConfig.getParameter<edm::ParameterSet>("patMetConfig")),
  pelectron(iConfig.getParameter<edm::ParameterSet>("patElectronConfig")),
  pmuon(iConfig.getParameter<edm::ParameterSet>("patMuonConfig")),
  event(iConfig.getParameter<edm::ParameterSet>("EventConfig")),
  selection(iConfig.getParameter<edm::ParameterSet>("EventConfig").
    getParameter<std::vector<std::string> >("selectionType"))
{
  
  totaleventnum=0;

  cutmuonum_RA4mu=0;
  cutelenum_RA4mu=0;
  cutjet_RA4mu=0;
  cutmet_RA4mu=0;

  cuthlt_RA4el=0;
  cutelenum_RA4el=0;
  cutjet_RA4el=0;
  cutmet_RA4el=0;
  
  eventCutFlowMu.clear();
  eventCutFlowEle.clear();
}


RA4Synchronization::~RA4Synchronization() {
}


bool RA4Synchronization::filter(edm::Event& iEvent, 
			      const edm::EventSetup& iSetup){

  totaleventnum++;
  // Clear and Set (in principle clear is not needed here, set does it)
  // 

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
  beamspot.calculate();
  trigger.calculate();
  pelectron.calculate(&beamspot);
  pmuon.calculate(&beamspot);
  
  // Select

  std::string selection="RefAna4JetMetMuon";

  // Muon selection

  unsigned int nummuo=0;
  unsigned int numele=0;
  unsigned int numjetpt_mu=0;  

  std::vector<int> muonpass(pmuon.size());    

  for (unsigned int i=0;i<pmuon.size();i++){
    std::vector<std::pair<std::string,int> > cutflow;
    
    pmuon.passed(selection,i,&cutflow);     
    
    if (muonCutFlow.size()==0) { 
      muonCutFlow.resize(cutflow.size());
      std::vector<int> axu;
      axu.push_back(0);
      axu.push_back(0);
      for (unsigned int j=0;j<cutflow.size();j++){          
        muonCutFlow[j].first=cutflow[j].first;
        muonCutFlow[j].second=axu;
      }
    }
    

    int prev=1;
    for (unsigned int j=0;j<cutflow.size();j++){        
      if (j>0 && prev!=0){ 
        prev=cutflow[j-1].second;
      }          
      if (prev==1){
        if (i==0)  
          muonCutFlow[j].second[0]=
            muonCutFlow[j].second[0]+cutflow[j].second;
        if (i==1)  
          muonCutFlow[j].second[1]=
            muonCutFlow[j].second[1]+cutflow[j].second;
        if (j==cutflow.size()-1 && cutflow[j].second==1){
          nummuo++;       
        }
      }
    }   
    
  }

  // Electron selection

  for (unsigned int i=0;i<pelectron.size();i++){
    std::vector<std::pair<std::string,int> > cutflow;
    
    pelectron.passed(selection,i,cutflow);     
    
    if (electronCutFlowMu.size()==0) { 
      electronCutFlowMu.resize(cutflow.size());
      std::vector<int> axu;
      axu.push_back(0);
      axu.push_back(0);
      for (unsigned int j=0;j<cutflow.size();j++){          
        electronCutFlowMu[j].first=cutflow[j].first;
        electronCutFlowMu[j].second=axu;
      }
    }
    

    int prev=1;
    for (unsigned int j=0;j<cutflow.size();j++){        
      if (j>0 && prev!=0){ 
        prev=cutflow[j-1].second;
      }          
      if (prev==1){
        if (i==0)  
          electronCutFlowMu[j].second[0]=
              electronCutFlowMu[j].second[0]+cutflow[j].second;
        if (i==1)  
          electronCutFlowMu[j].second[1]=
              electronCutFlowMu[j].second[1]+cutflow[j].second;
        if (j==cutflow.size()-1 && cutflow[j].second==1){
          numele++;       
        }
      }
    }   
    
  }

  // Jet selection


  for (unsigned int i=0;i<pjet.size();i++){
    std::vector<std::pair<std::string,int> > cutflow;
    
    pjet.passed(selection,i,cutflow);     
    
    if (jetCutFlowMu.size()==0) { 
      jetCutFlowMu.resize(cutflow.size());
      std::vector<int> axu;
      axu.push_back(0);
      axu.push_back(0);
      for (unsigned int j=0;j<cutflow.size();j++){          
        jetCutFlowMu[j].first=cutflow[j].first;
        jetCutFlowMu[j].second=axu;
      }
    }
    

    int prev=1;
    for (unsigned int j=0;j<cutflow.size();j++){        
      if (j>0 && prev!=0){ 
        prev=cutflow[j-1].second;
      }          
      if (prev==1){
        if (i==0)  
          jetCutFlowMu[j].second[0]=
              jetCutFlowMu[j].second[0]+cutflow[j].second;
        if (i==1)  
          jetCutFlowMu[j].second[1]=
              jetCutFlowMu[j].second[1]+cutflow[j].second;
        if (j==cutflow.size()-1 && 
            cutflow[j].second==1 && 
            pjet.jet(i).pt>=50.0) {
          numjetpt_mu++;       
        }
      }
    }   
    
  } 

  // Event selection

  std::vector<std::string> corr=pmet.getCorrections();

  if(nummuo==1){
    cutmuonum_RA4mu++;
    if(numele==0){
      cutelenum_RA4mu++;
      if(numjetpt_mu>=3){
        cutjet_RA4mu++;
        if(pmet.met(corr[0]).et>100.0){
          cutmet_RA4mu++;
        }
      }
    }
  }
  
event.passed(selection,&pjet,&pmet,&pelectron,&pmuon,&trigger,&eventCutFlowMu);
      
    
//-----------------------------------------------------------------------------


  selection="RefAna4JetMetElectron";

  numele=0;
  unsigned int numjetpt_el=0;  


  // Electron selection
  
  
  for (unsigned int i=0;i<pelectron.size();i++){
    std::vector<std::pair<std::string,int> > cutflow;
    
    pelectron.passed(selection,i,cutflow);     
    
    if (electronCutFlowEle.size()==0) { 
      electronCutFlowEle.resize(cutflow.size());
      std::vector<int> axu;
      axu.push_back(0);
      axu.push_back(0);
      for (unsigned int j=0;j<cutflow.size();j++){          
        electronCutFlowEle[j].first=cutflow[j].first;
        electronCutFlowEle[j].second=axu;
      }
    }
    

    int prev=1;
    for (unsigned int j=0;j<cutflow.size();j++){        
      if (j>0 && prev!=0){ 
        prev=cutflow[j-1].second;
      }          
      if (prev==1){
        if (i==0)  
          electronCutFlowEle[j].second[0]=
              electronCutFlowEle[j].second[0]+cutflow[j].second;
        if (i==1)  
          electronCutFlowEle[j].second[1]=
              electronCutFlowEle[j].second[1]+cutflow[j].second;
        if (j==cutflow.size()-1 && cutflow[j].second==1){
          numele++;       
        }
      }
    }   
    
  }

  // Jet selection

  
  for (unsigned int i=0;i<pjet.size();i++){
    std::vector<std::pair<std::string,int> > cutflow;
    
    pjet.passed(selection,i,cutflow);     
    
    if (jetCutFlowEle.size()==0) { 
      jetCutFlowEle.resize(cutflow.size());
      std::vector<int> axu;
      axu.push_back(0);
      axu.push_back(0);
      for (unsigned int j=0;j<cutflow.size();j++){          
        jetCutFlowEle[j].first=cutflow[j].first;
        jetCutFlowEle[j].second=axu;
      }
    }
    

    int prev=1;
    for (unsigned int j=0;j<cutflow.size();j++){        
      if (j>0 && prev!=0){ 
        prev=cutflow[j-1].second;
      }          
      if (prev==1){
        if (i==0)  
          jetCutFlowEle[j].second[0]=
              jetCutFlowEle[j].second[0]+cutflow[j].second;
        if (i==1)  
          jetCutFlowEle[j].second[1]=
              jetCutFlowEle[j].second[1]+cutflow[j].second;
        if (j==cutflow.size()-1 && 
            cutflow[j].second==1) {
          numjetpt_el++;
        }
      }
    }   
    
  } 


  // Event selection
    
  corr=pmet.getCorrections();    
        
  if(trigger.trigger("HLT_Ele15_LW_L1R").hlt==1){
    cuthlt_RA4el++;
    if(numele==1){
      cutelenum_RA4el++;
      if(numjetpt_el>=3){
        cutjet_RA4el++;
        if(pmet.met(corr[0]).et>100.0){
          cutmet_RA4el++;
        }
      }
    }
  }
 
  
  
  event.passed(selection,&pjet,&pmet,&pelectron,&pmuon,&trigger,&eventCutFlowEle);
  
  
  
  

  return true;
}


void RA4Synchronization::beginJob(const edm::EventSetup&) {
}


void RA4Synchronization::endJob() {
  
  std::cout<<std::endl;
  std::cout << "              Reference Analysis 4 Jet+Met+Muon:" << std::endl;
  std::cout<<std::endl;
  for (unsigned int i=0;i<eventCutFlowMu.size();i++){
    std::cout<<"  "<<eventCutFlowMu[i].first<<
        "   "<<eventCutFlowMu[i].second<<std::endl;
    if (i==0){      
      std::cout<<std::endl;
      std::cout<<"    Muon cut       1.pt      2.pt"<<std::endl;
      for (unsigned int j=0;j<muonCutFlow.size();j++){
        std::cout<<"    "<<muonCutFlow[j].first<<
            "   "<<muonCutFlow[j].second[0]<<
            "        "<<muonCutFlow[j].second[1]<<std::endl;           
      }    
    }           
  }
  
/*  std::cout<<std::endl;
  std::cout<<"muonCutFlow:"<<std::endl;
  for (unsigned int i=0;i<muonCutFlow.size();i++){
    std::cout<<" "<<muonCutFlow[i].first<<
        " "<<muonCutFlow[i].second[0]<<
        " "<<muonCutFlow[i].second[1]<<std::endl;           
  } */    
// 
//   std::cout<<std::endl;
//   std::cout<<"electronCutFlow:"<<std::endl;
//   for (unsigned int i=0;i<electronCutFlowMu.size();i++){
//     std::cout<<" "<<electronCutFlowMu[i].first<<
//         " "<<electronCutFlowMu[i].second[0]<<
//         " "<<electronCutFlowMu[i].second[1]<<std::endl;           
//   } 
// 
//   std::cout<<std::endl;
//   std::cout<<"jetCutFlow:"<<std::endl;
//   for (unsigned int i=0;i<jetCutFlowMu.size();i++){
//     std::cout<<" "<<jetCutFlowMu[i].first<<
//         " "<<jetCutFlowMu[i].second[0]<<
//         " "<<jetCutFlowMu[i].second[1]<<std::endl;           
//   } 
  
  std::cout<<std::endl;
  std::cout << "Reference Analysis 4 Jet+Met+Electron:" << std::endl;
  std::cout << "After hlt cut:" << cuthlt_RA4el << std::endl;
  std::cout << "After number of electron cut:" << cutelenum_RA4el << std::endl;
  std::cout << "After jet cut:" << cutjet_RA4el << std::endl;
  std::cout << "After met cut:" << cutmet_RA4el << std::endl;
  
  
  std::cout<<std::endl;
  std::cout<<"eventCutFlowEle:"<<std::endl;
  for (unsigned int i=0;i<eventCutFlowEle.size();i++){
    std::cout<<" "<<eventCutFlowEle[i].first<<
        "   "<<eventCutFlowEle[i].second<<std::endl;           
  }
  
  
//   std::cout<<std::endl;
//   std::cout<<"electronCutFlow:"<<std::endl;
//   for (unsigned int i=0;i<electronCutFlowEle.size();i++){
//     std::cout<<" "<<electronCutFlowEle[i].first<<
//         " "<<electronCutFlowEle[i].second[0]<<
//         " "<<electronCutFlowEle[i].second[1]<<std::endl;           
//   } 
// 
//   std::cout<<std::endl;
//   std::cout<<"jetCutFlow:"<<std::endl;
//   for (unsigned int i=0;i<jetCutFlowEle.size();i++){
//     std::cout<<" "<<jetCutFlowEle[i].first<<
//         " "<<jetCutFlowEle[i].second[0]<<
//         " "<<jetCutFlowEle[i].second[1]<<std::endl;           
//   } 


}

DEFINE_FWK_MODULE(RA4Synchronization);
