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
// $Id: RA4Synchronization.cc,v 1.6 2009/11/12 16:17:24 aranyi Exp $
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
  
  eventCutFlowMu.clear();
  eventCutFlowEle.clear();
  
}


RA4Synchronization::~RA4Synchronization() {
}


bool RA4Synchronization::filter(edm::Event& iEvent, 
			      const edm::EventSetup& iSetup){

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
  
  // Selections

  std::string selection="RefAna4JetMetMuon";
    
    
  unsigned int numele=0;
  unsigned int nummuo=0;
  
  // Muon Selection   
  
  if (pmuon.size()>0) {
    
    bool first=false;
    bool second=false;
    bool third=false;
    
    std::vector<std::pair<std::string,int> > cutflow;
    std::vector< int > prev;
    prev.resize(pmuon.size());
    for (unsigned int i=0;i<prev.size();i++){
      prev[i]=1;
    }
    pmuon.passed(selection,0,&cutflow);
    
    if (muonCutFlowMu.size()==0) { 
      muonCutFlowMu.resize(cutflow.size());
      std::vector<int> axu;
      axu.push_back(0);
      axu.push_back(0);
      axu.push_back(0);
      for (unsigned int j=0;j<cutflow.size();j++){          
        muonCutFlowMu[j].first=cutflow[j].first;
        muonCutFlowMu[j].second=axu;
      }
    }

    for (unsigned int j=0;j<cutflow.size();j++){
      first=false;
      second=false;
      third=false;    
      
//      std::cout<<std::endl;
//      std::cout<<cutflow[j].first<<" ";
      
      for (unsigned int i=0;i<pmuon.size();i++){        
        pmuon.passed(selection,i,&cutflow);
        
//        std::cout<<cutflow[j].second<<" ";
        
        if (j>0 && prev[i]!=0) 
          prev[i]=cutflow[j-1].second;      
          
        if (prev[i]==1 && cutflow[j].second==1){
          if (first==true && second==true && third==false) {
            muonCutFlowMu[j].second[2]++;
            third=true;            
          }
          if (first==true && second==false) {
            muonCutFlowMu[j].second[1]++;
            second=true;
          }
          if ( i==0 || (i>0 && first==false) ) {
            muonCutFlowMu[j].second[0]++;
            first=true;
          }
                  
          if (j==cutflow.size()-1) {
            nummuo++;          
          }
        }
      }
      
    }
//    std::cout<<std::endl;
    
    
  }
  
  
  // Electron Selection

  if (nummuo==1) {        
    
    if (pelectron.size()>0) {
    
      bool first=false;
    
      std::vector<std::pair<std::string,int> > cutflow;
      std::vector< int > prev;
      prev.resize(pelectron.size());
      for (unsigned int i=0;i<prev.size();i++){
        prev[i]=1;
      }
      pelectron.passed(selection,0,&cutflow);
    
      if (electronCutFlowMu.size()==0) { 
        electronCutFlowMu.resize(cutflow.size());
        std::vector<int> axu;
        axu.push_back(0);
        for (unsigned int j=0;j<cutflow.size();j++){          
          electronCutFlowMu[j].first=cutflow[j].first;
          electronCutFlowMu[j].second=axu;
        }
      }

      for (unsigned int j=0;j<cutflow.size();j++){
        first=false;     
              
        for (unsigned int i=0;i<pelectron.size();i++){        
          pelectron.passed(selection,i,&cutflow);
        
          if (j>0 && prev[i]!=0) 
            prev[i]=cutflow[j-1].second;      
          
          if (prev[i]==1 && cutflow[j].second==1){
            if ( i==0 || (i>0 && first==false) ) {
              electronCutFlowMu[j].second[0]++;
              first=true;
            }                
            if (j==cutflow.size()-1)
              numele++;          
          }
        }   
      }  
    }
  }
  

  // Jet Selection
  

  if (nummuo==1 && numele==0) {
    
    if (pjet.size()>0) {
    
      bool first=false;
      bool second=false;
      bool third=false;
      bool fourth=false;
    
      std::vector<std::pair<std::string,int> > cutflow;
      std::vector< int > prev;
      prev.resize(pjet.size());
      for (unsigned int i=0;i<prev.size();i++){
        prev[i]=1;
      }
      pjet.passed(selection,0,&cutflow);
    
      if (jetCutFlowMu.size()==0) { 
        jetCutFlowMu.resize(cutflow.size());
        std::vector<int> axu;
        axu.push_back(0);
        axu.push_back(0);
        axu.push_back(0);
        axu.push_back(0);
        for (unsigned int j=0;j<cutflow.size();j++){          
          jetCutFlowMu[j].first=cutflow[j].first;
          jetCutFlowMu[j].second=axu;
        }
      }

      for (unsigned int j=0;j<cutflow.size();j++){
        first=false;
        second=false;
        third=false;
        fourth=false;     
              
        for (unsigned int i=0;i<pjet.size();i++){        
          pjet.passed(selection,i,&cutflow);
        
          if (j>0 && prev[i]!=0) 
            prev[i]=cutflow[j-1].second;      
          
          if (prev[i]==1 && cutflow[j].second==1){
            if (first==true && second==true && third==true && fourth==false) {
              jetCutFlowMu[j].second[3]++;
              fourth=true;            
            }
            if (first==true && second==true && third==false) {
              jetCutFlowMu[j].second[2]++;
              third=true;            
            }
            if (first==true && second==false) {
              jetCutFlowMu[j].second[1]++;
              second=true;
            }
            if ( i==0 || (i>0 && first==false) ) {
              jetCutFlowMu[j].second[0]++;
              first=true;
            }                        
          }
        }       
      }  
    }
  } 

  // Event selection
  
event.passed(selection,&pjet,&pmet,&pelectron,&pmuon,&trigger,&eventCutFlowMu);
      
    
//-----------------------------------------------------------------------------


  selection="RefAna4JetMetElectron";
  
  numele=0;
  nummuo=0;
  
  
  // Muon selection 
  
  
  if(trigger.trigger("HLT_Ele15_LW_L1R").hlt==1){ 
    
    if (pmuon.size()>0) {
    
      bool first=false;
    
      std::vector<std::pair<std::string,int> > cutflow;
      std::vector< int > prev;
      prev.resize(pmuon.size());
      for (unsigned int i=0;i<prev.size();i++){
        prev[i]=1;
      }
      pmuon.passed(selection,0,&cutflow);
    
      if (muonCutFlowEle.size()==0) { 
        muonCutFlowEle.resize(cutflow.size());
        std::vector<int> axu;
        axu.push_back(0);
        for (unsigned int j=0;j<cutflow.size();j++){          
          muonCutFlowEle[j].first=cutflow[j].first;
          muonCutFlowEle[j].second=axu;
        }
      }

      for (unsigned int j=0;j<cutflow.size();j++){
        first=false;
      
        for (unsigned int i=0;i<pmuon.size();i++){        
          pmuon.passed(selection,i,&cutflow);
          
          if (j>0 && prev[i]!=0) 
            prev[i]=cutflow[j-1].second;      
          
          if (prev[i]==1 && cutflow[j].second==1){
            if ( i==0 || (i>0 && first==false) ) {
              muonCutFlowEle[j].second[0]++;
              first=true;
            }
                  
            if (j==cutflow.size()-1)
              nummuo++;          
          }
        }
      
      }
    }
  }
  
  
  // Electron selection
  
  
  if (trigger.trigger("HLT_Ele15_LW_L1R").hlt==1 && nummuo==0) {
    
    if (pelectron.size()>0) {
    
      bool first=false;
      bool second=false;
      bool third=false;
    
      std::vector<std::pair<std::string,int> > cutflow;
      std::vector< int > prev;
      prev.resize(pelectron.size());
      for (unsigned int i=0;i<prev.size();i++){
        prev[i]=1;
      }
      pelectron.passed(selection,0,&cutflow);
    
      if (electronCutFlowEle.size()==0) { 
        electronCutFlowEle.resize(cutflow.size());
        std::vector<int> axu;
        axu.push_back(0);
        axu.push_back(0);
        axu.push_back(0);
        for (unsigned int j=0;j<cutflow.size();j++){          
          electronCutFlowEle[j].first=cutflow[j].first;
          electronCutFlowEle[j].second=axu;
        }
      }

      for (unsigned int j=0;j<cutflow.size();j++){
        first=false;
        second=false;
        third=false;    
      
        for (unsigned int i=0;i<pelectron.size();i++){        
          pelectron.passed(selection,i,&cutflow);
        
          if (j>0 && prev[i]!=0) 
            prev[i]=cutflow[j-1].second;      
          
          if (prev[i]==1 && cutflow[j].second==1){
            if (first==true && second==true && third==false) {
              electronCutFlowEle[j].second[2]++;
              third=true;            
            }
            if (first==true && second==false) {
              electronCutFlowEle[j].second[1]++;
              second=true;
            }
            if ( i==0 || (i>0 && first==false) ) {
              electronCutFlowEle[j].second[0]++;
              first=true;
            }
                  
            if (j==cutflow.size()-1)
              numele++;          
          }
        }
      
      }
    }
  }
  

  // Jet selection

  
  if (trigger.trigger("HLT_Ele15_LW_L1R").hlt==1 && nummuo==0 && numele==1) {
  
    if (pjet.size()>0) {
    
      bool first=false;
      bool second=false;
      bool third=false;
      bool fourth=false;
    
      std::vector<std::pair<std::string,int> > cutflow;
      std::vector< int > prev;
      prev.resize(pjet.size());
      for (unsigned int i=0;i<prev.size();i++){
        prev[i]=1;
      }
      pjet.passed(selection,0,&cutflow);
    
      if (jetCutFlowEle.size()==0) { 
        jetCutFlowEle.resize(cutflow.size());
        std::vector<int> axu;
        axu.push_back(0);
        axu.push_back(0);
        axu.push_back(0);
        axu.push_back(0);
        for (unsigned int j=0;j<cutflow.size();j++){          
          jetCutFlowEle[j].first=cutflow[j].first;
          jetCutFlowEle[j].second=axu;
        }
      }

      for (unsigned int j=0;j<cutflow.size();j++){
        first=false;
        second=false;
        third=false;
        fourth=false;     
              
        for (unsigned int i=0;i<pjet.size();i++){        
          pjet.passed(selection,i,&cutflow);
        
          if (j>0 && prev[i]!=0) 
            prev[i]=cutflow[j-1].second;      
          
          if (prev[i]==1 && cutflow[j].second==1){
            if (first==true && second==true && third==true && fourth==false) {
              jetCutFlowEle[j].second[3]++;
              fourth=true;            
            }
            if (first==true && second==true && third==false) {
              jetCutFlowEle[j].second[2]++;
              third=true;            
            }
            if (first==true && second==false) {
              jetCutFlowEle[j].second[1]++;
              second=true;
            }
            if ( i==0 || (i>0 && first==false) ) {
              jetCutFlowEle[j].second[0]++;
              first=true;
            }                        
          }
        }       
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
  std::cout << "                   Reference Analysis 4 Jet+Met+Muon" 
      << std::endl;
  std::cout<<std::endl;
  
  std::cout<<std::endl;
  std::cout<<"  "<<eventCutFlowMu[0].first<<
      "   "<<eventCutFlowMu[0].second<<std::endl;
  std::cout<<std::endl;
  
  for (unsigned int i=1;i<eventCutFlowMu.size();i++){

    
    if (i==1){      
      std::cout<<std::endl;
      std::cout<<"      Muon selection                         " \
          "1st Muon  2nd Muon  3rd Muon"<<std::endl;
      for (unsigned int j=0;j<muonCutFlowMu.size();j++){
        std::cout<<"        "<<muonCutFlowMu[j].first<<
            "   "<<muonCutFlowMu[j].second[0]<<
            "      "<<muonCutFlowMu[j].second[1]<<
            "      "<<muonCutFlowMu[j].second[2]<<std::endl;          
      }
      std::cout<<std::endl;    
    }   
    
    if (i==2){      
      std::cout<<std::endl;

      std::cout<<"      Electron selection                   " \
          "1st Electron"<<std::endl;
      for (unsigned int j=0;j<electronCutFlowMu.size();j++){
        std::cout<<"        "<<electronCutFlowMu[j].first<<
            "   "<<electronCutFlowMu[j].second[0]<<std::endl;           
      }
      std::cout<<std::endl;    
    }
    
    if (i==3){      
      std::cout<<std::endl;  
      std::cout<<"      Jet selection                          " \
          "1st Jet   2nd Jet   3rd Jet   4th Jet"<<std::endl;
      for (unsigned int j=0;j<jetCutFlowMu.size();j++){
        std::cout<<"        "<<jetCutFlowMu[j].first<<
            "   "<<jetCutFlowMu[j].second[0]<<
            "      "<<jetCutFlowMu[j].second[1]<<           
            "      "<<jetCutFlowMu[j].second[2]<<
            "      "<<jetCutFlowMu[j].second[3]<<std::endl;
      }
      std::cout<<std::endl;   
    }
    
    std::cout<<std::endl;
    if (i>0) std::cout<<"  "<<eventCutFlowMu[i].first<<
          "   "<<eventCutFlowMu[i].second<<std::endl;
    std::cout<<std::endl;
            
  }
  

  
  std::cout<<std::endl;
  std::cout << "              Reference Analysis 4 " \
      "Jet+Met+Electron" << std::endl;
  std::cout<<std::endl;
  
  
  std::cout<<std::endl;
  std::cout<<"  "<<eventCutFlowEle[0].first<<
      "   "<<eventCutFlowEle[0].second<<std::endl;
  std::cout<<std::endl;
  
  
  for (unsigned int i=1;i<eventCutFlowEle.size();i++){

    
    if (i==2){      
      std::cout<<std::endl;

      std::cout<<"      Muon selection                       " \
          "1st Muon"<<std::endl;
      for (unsigned int j=0;j<muonCutFlowEle.size();j++){
        std::cout<<"        "<<muonCutFlowEle[j].first<<
            "   "<<muonCutFlowEle[j].second[0]<<std::endl;           
      }
      std::cout<<std::endl;    
    }
    
    if (i==3){      
      std::cout<<std::endl;
      std::cout<<"      Electron selection                     " \
          "1st Ele   2nd Ele   3rd Ele"<<std::endl;
      for (unsigned int j=0;j<electronCutFlowEle.size();j++){
        std::cout<<"        "<<electronCutFlowEle[j].first<<
            "   "<<electronCutFlowEle[j].second[0]<<
            "      "<<electronCutFlowEle[j].second[1]<<
            "      "<<electronCutFlowEle[j].second[2]<<std::endl;          
      }
      std::cout<<std::endl;    
    }       
    
    if (i==4){      
      std::cout<<std::endl;  
      std::cout<<"      Jet selection                          " \
          "1st Jet   2nd Jet   3rd Jet   4th Jet"<<std::endl;
      for (unsigned int j=0;j<jetCutFlowEle.size();j++){
        std::cout<<"        "<<jetCutFlowEle[j].first<<
            "   "<<jetCutFlowEle[j].second[0]<<
            "      "<<jetCutFlowEle[j].second[1]<<           
            "      "<<jetCutFlowEle[j].second[2]<<
            "      "<<jetCutFlowEle[j].second[3]<<std::endl;
      }
      std::cout<<std::endl;   
    }
        
    std::cout<<std::endl;
    if (i>0) std::cout<<"  "<<eventCutFlowEle[i].first<<
        "   "<<eventCutFlowEle[i].second<<std::endl;
    std::cout<<std::endl;
            
  }  



}

DEFINE_FWK_MODULE(RA4Synchronization);
