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
// $Id: RA4Synchronization.cc,v 1.5 2009/11/12 14:54:28 aranyi Exp $
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
  event(iConfig.getParameter<edm::ParameterSet>("EventConfig"))
{
  
  totaleventnum=0;
  
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
  
  // Select and CutFlow

  std::string selection="RefAna4JetMetMuon";
  
  // Muon CutFlow   

  for (unsigned int i=0;i<pmuon.size();i++){
    std::vector<std::pair<std::string,int> > cutflow;
    
    pmuon.passed(selection,i,&cutflow);     
    
    if (muonCutFlowMu.size()==0) { 
      muonCutFlowMu.resize(cutflow.size());
      std::vector<int> axu;
      axu.push_back(0);
      axu.push_back(0);
      for (unsigned int j=0;j<cutflow.size();j++){          
        muonCutFlowMu[j].first=cutflow[j].first;
        muonCutFlowMu[j].second=axu;
      }
    }
    

    int prev=1;
    for (unsigned int j=0;j<cutflow.size();j++){        
      if (j>0 && prev!=0){ 
        prev=cutflow[j-1].second;
      }          
      if (prev==1){
        if (i==0)  
          muonCutFlowMu[j].second[0]=
              muonCutFlowMu[j].second[0]+cutflow[j].second;
        if (i==1)  
          muonCutFlowMu[j].second[1]=
              muonCutFlowMu[j].second[1]+cutflow[j].second;
      }
    }   
    
  }

  // Electron CutFlow

  for (unsigned int i=0;i<pelectron.size();i++){
    std::vector<std::pair<std::string,int> > cutflow;
    
    pelectron.passed(selection,i,&cutflow);     
    
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
      }
    }   
    
  }

  // Jet CutFlow


  for (unsigned int i=0;i<pjet.size();i++){
    std::vector<std::pair<std::string,int> > cutflow;
    
    pjet.passed(selection,i,&cutflow);     
    
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
      }
    }   
    
  } 

  // Event selection

  
event.passed(selection,&pjet,&pmet,&pelectron,&pmuon,&trigger,&eventCutFlowMu);
      
    
//-----------------------------------------------------------------------------


  selection="RefAna4JetMetElectron";

  // Electron CutFlow
  
  
  for (unsigned int i=0;i<pelectron.size();i++){
    std::vector<std::pair<std::string,int> > cutflow;
    
    pelectron.passed(selection,i,&cutflow);     
    
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
      }
    }   
    
  }
  
  
  
  // Muon CutFlow   

  for (unsigned int i=0;i<pmuon.size();i++){
    std::vector<std::pair<std::string,int> > cutflow;
    
    pmuon.passed(selection,i,&cutflow);     
    
    if (muonCutFlowEle.size()==0) { 
      muonCutFlowEle.resize(cutflow.size());
      std::vector<int> axu;
      axu.push_back(0);
      axu.push_back(0);
      for (unsigned int j=0;j<cutflow.size();j++){          
        muonCutFlowEle[j].first=cutflow[j].first;
        muonCutFlowEle[j].second=axu;
      }
    }
    

    int prev=1;
    for (unsigned int j=0;j<cutflow.size();j++){        
      if (j>0 && prev!=0){ 
        prev=cutflow[j-1].second;
      }          
      if (prev==1){
        if (i==0)  
          muonCutFlowEle[j].second[0]=
              muonCutFlowEle[j].second[0]+cutflow[j].second;
        if (i==1)  
          muonCutFlowEle[j].second[1]=
              muonCutFlowEle[j].second[1]+cutflow[j].second;
      }
    }   
    
  }

  // Jet CutFlow

  
  for (unsigned int i=0;i<pjet.size();i++){
    std::vector<std::pair<std::string,int> > cutflow;
    
    pjet.passed(selection,i,&cutflow);     
    
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
      }
    }   
    
  } 


  // Event selection
    
  
event.passed(selection,&pjet,&pmet,&pelectron,&pmuon,&trigger,&eventCutFlowEle);
  

  return true;
}


void RA4Synchronization::beginJob(const edm::EventSetup&) {
}


void RA4Synchronization::endJob() {
  
  std::cout<<std::endl;
  std::cout << "              Reference Analysis 4 Jet+Met+Muon" << std::endl;
  std::cout<<std::endl;
  for (unsigned int i=0;i<eventCutFlowMu.size();i++){
    std::cout<<"  "<<eventCutFlowMu[i].first<<
        "   "<<eventCutFlowMu[i].second<<std::endl;
    
    if (i==0){      
      std::cout<<std::endl;
      std::cout<<"    Muon cutflow       1.pt      2.pt"<<std::endl;
      for (unsigned int j=0;j<muonCutFlowMu.size();j++){
        std::cout<<"        "<<muonCutFlowMu[j].first<<
            "   "<<muonCutFlowMu[j].second[0]<<
            "        "<<muonCutFlowMu[j].second[1]<<std::endl;           
      }
      std::cout<<std::endl;    
    }   
    
    if (i==1){      
      std::cout<<std::endl;
      std::cout<<"  Electron cutflow     1.pt      2.pt"<<std::endl;
      for (unsigned int j=0;j<electronCutFlowMu.size();j++){
        std::cout<<"        "<<electronCutFlowMu[j].first<<
            "   "<<electronCutFlowMu[j].second[0]<<
            "        "<<electronCutFlowMu[j].second[1]<<std::endl;           
      }
      std::cout<<std::endl;    
    }
    
    if (i==2){      
      std::cout<<std::endl;
      std::cout<<"     Jet cutflow       1.pt      2.pt"<<std::endl;
      for (unsigned int j=0;j<jetCutFlowMu.size();j++){
        std::cout<<"        "<<jetCutFlowMu[j].first<<
            "   "<<jetCutFlowMu[j].second[0]<<
            "        "<<jetCutFlowMu[j].second[1]<<std::endl;           
      }
      std::cout<<std::endl;   
    }
            
  }
  

  
  std::cout<<std::endl;
  std::cout << "              Reference Analysis 4 " \
      "Jet+Met+Electron" << std::endl;
  std::cout<<std::endl;
  for (unsigned int i=0;i<eventCutFlowEle.size();i++){
    std::cout<<"  "<<eventCutFlowEle[i].first<<
        "   "<<eventCutFlowEle[i].second<<std::endl;
    
    if (i==1){      
      std::cout<<std::endl;
      std::cout<<"    Muon cutflow       1.pt      2.pt"<<std::endl;
      for (unsigned int j=0;j<muonCutFlowEle.size();j++){
        std::cout<<"        "<<muonCutFlowEle[j].first<<
            "   "<<muonCutFlowEle[j].second[0]<<
            "        "<<muonCutFlowEle[j].second[1]<<std::endl;           
      }
      std::cout<<std::endl;    
    } 
    
    if (i==2){      
      std::cout<<std::endl;
      std::cout<<"  Electron cutflow     1.pt      2.pt"<<std::endl;
      for (unsigned int j=0;j<electronCutFlowEle.size();j++){
        std::cout<<"        "<<electronCutFlowEle[j].first<<
            "   "<<electronCutFlowEle[j].second[0]<<
            "        "<<electronCutFlowEle[j].second[1]<<std::endl;           
      }
      std::cout<<std::endl;    
    }          
    
    if (i==3){      
      std::cout<<std::endl;
      std::cout<<"     Jet cutflow       1.pt      2.pt"<<std::endl;
      for (unsigned int j=0;j<jetCutFlowEle.size();j++){
        std::cout<<"        "<<jetCutFlowEle[j].first<<
            "   "<<jetCutFlowEle[j].second[0]<<
            "        "<<jetCutFlowEle[j].second[1]<<std::endl;           
      }
      std::cout<<std::endl;   
    }
            
  }  



}

DEFINE_FWK_MODULE(RA4Synchronization);
