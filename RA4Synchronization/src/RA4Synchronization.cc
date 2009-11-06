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

  cutmuonum_RA4mu_cutflow=0;
  cutelenum_RA4mu_cutflow=0;
  cutjet_RA4mu_cutflow=0;
  cutmet_RA4mu_cutflow=0;

  cuthlt_RA4el=0;
  cutelenum_RA4el=0;
  cutjet_RA4el=0;
  cutmet_RA4el=0;

  numberofmuons=0;
  numberofmuons_cutflow=0;
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

  // Examination of the selection validation

  unsigned int string_mu=0;
  unsigned int string_ele=0;
  for(unsigned int j=0;j<selection.size();j++){
    if(selection[j].compare("RefAna4JetMetMuon")==0){
      string_mu++;
    }     
    if(selection[j].compare("RefAna4JetMetElectron")==0){
      string_ele++;  
    }
    if(selection[j].compare("RefAna4JetMetMuon")!=0 &&
       selection[j].compare("RefAna4JetMetElectron")!=0){  
      std::cout << "This cut doesn't exist:" << selection[j] << std::endl;
    }
  }
  if (string_mu==0){
    cutmuonum_RA4mu=NOVAL_I;
    cutelenum_RA4mu=NOVAL_I;
    cutjet_RA4mu=NOVAL_I;
    cutmet_RA4mu=NOVAL_I;

    cutmuonum_RA4mu_cutflow=NOVAL_I;
    cutelenum_RA4mu_cutflow=NOVAL_I;
    cutjet_RA4mu_cutflow=NOVAL_I;
    cutmet_RA4mu_cutflow=NOVAL_I;

  }
  if (string_ele==0){
    cuthlt_RA4el=NOVAL_I;
    cutelenum_RA4el=NOVAL_I;
    cutjet_RA4el=NOVAL_I;
    cutmet_RA4el=NOVAL_I;
  }

  //Selection values

  for(unsigned int j=0;j<selection.size();j++){
    unsigned int nummuo=0;
    unsigned int numele=0;
    unsigned int numjetpt_mu=0;
    unsigned int numjetpt_el=0;  

    std::vector<int> muonpass(pmuon.size());    
    
    for (unsigned int i=0;i<pmuon.size();i++){
	    muonpass[i]=pmuon.passed(selection[j],i);     

	    if(muonpass[i]==1){
              nummuo++;
              numberofmuons++;
	    }   
    } 

    unsigned int nummuo_cutflow=0;    
    std::vector<int> muonpass_cutflow(pmuon.size());






    for (unsigned int i=0;i<pmuon.size();i++){
      std::vector<std::pair<std::string,int> > cutflow;
      
      muonpass_cutflow[i]=pmuon.passed(selection[j],i,cutflow);     
     
      if (muonCutFlow.size()==0) { 
        muonCutFlow.resize(cutflow.size());
        std::vector<int> axu;
        axu.push_back(0);
        axu.push_back(0);
        for (unsigned int ii=0;ii<cutflow.size();ii++){          
          muonCutFlow[ii].first=cutflow[ii].first;
          muonCutFlow[ii].second=axu;
        }
      }
      
      if (muonpass_cutflow[i]!=NOVAL_I){

        int prev=1;
        for (unsigned int ii=0;ii<cutflow.size();ii++){        
          if (ii>0 && prev!=0){ 
            prev=cutflow[ii-1].second;
          }          
          if (prev==1){
            if (i==0)  
              muonCutFlow[ii].second[0]=
                muonCutFlow[ii].second[0]+cutflow[ii].second;
            if (i==1)  
              muonCutFlow[ii].second[1]=
                muonCutFlow[ii].second[1]+cutflow[ii].second;
            if (ii==cutflow.size()-1 && cutflow[ii].second==1){
              nummuo_cutflow++;
              numberofmuons_cutflow++;          
            }
          }
        }
      }
   
//       std::cout<<"muon["<<i<<"], cutflow:"<<muonpass_cutflow[i]<<std::endl;
//       for (unsigned int ii=0;ii<cutflow.size();ii++){
//               std::cout<<" "<<cutflow[ii].first<<
//                               " "<<cutflow[ii].second<<std::endl;           
//       }
    
    }

    





    
    std::vector<int> electronpass(pelectron.size());
    for (unsigned int i=0;i<pelectron.size();i++){
      electronpass[i]=pelectron.passed(selection[j],i);
      if(electronpass[i]==1){
      numele++;
      }
    } 
    std::vector<int> pjetpass(pjet.size());
    for (unsigned int i=0;i<pjet.size();i++){
      pjetpass[i]=pjet.passed(selection[j],i);
      if(pjet.jet(i).pt==NOVAL_F){
	std::cout << "NOVAL value in the cut criteria"<< std::endl;
      }
      else {
	if(pjetpass[i]==1&&pjet.jet(i).pt>=50.0){
	  numjetpt_mu++;
	}
      }
      if(pjet.jet(i).pt==NOVAL_F||
	 pjet.jet(i).eta==NOVAL_F||
	 pjet.jet(i).hadfrac==NOVAL_F){
	std::cout << "NOVAL value in the cut criteria"<< std::endl;
      }
      else {
	if(pjetpass[i]==1&&
	   pjet.jet(i).pt>=50.0&&
	   TMath::Abs(pjet.jet(i).eta)<3.0&&
	   pjet.jet(i).hadfrac<0.9){
	  numjetpt_el++;
	}
      }
    }  
    
    //Selection

      
     std::vector<std::string> corr=pmet.getCorrections();

    if(selection[j].compare("RefAna4JetMetMuon")==0){  
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

      if(nummuo_cutflow==1){
	cutmuonum_RA4mu_cutflow++;
	if(numele==0){
	  cutelenum_RA4mu_cutflow++;
	  if(numjetpt_mu>=3){
	    cutjet_RA4mu_cutflow++;
	    if(pmet.met(corr[0]).et>100.0){
	      cutmet_RA4mu_cutflow++;
	    }
	  }
	}
      }

    }      
       
    if(selection[j].compare("RefAna4JetMetElectron")==0){  
      if(trigger.trigger(0).hlt==1){
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
    }
      
  }

  return true;
}


void RA4Synchronization::beginJob(const edm::EventSetup&) {
}


void RA4Synchronization::endJob() {
  std::cout << "Total event number:" << totaleventnum << std::endl;
  std::cout << "Reference Analysis 4 Jet+Met+Muon:" << std::endl;
  std::cout << "After number of muon cut:" << cutmuonum_RA4mu << std::endl;
  std::cout << "After number of electron cut:" << cutelenum_RA4mu << std::endl;
  std::cout << "After jet cut:" << cutjet_RA4mu << std::endl;
  std::cout << "After met cut:" << cutmet_RA4mu << std::endl;

  std::cout << "After number of muon cut (cutflow):" << cutmuonum_RA4mu_cutflow << std::endl;
  std::cout << "After number of electron cut (cutflow):" << cutelenum_RA4mu_cutflow << std::endl;
  std::cout << "After jet cut (cutflow):" << cutjet_RA4mu_cutflow << std::endl;
  std::cout << "After met cut (cutflow):" << cutmet_RA4mu_cutflow << std::endl;

  std::cout << "Reference Analysis 4 Jet+Met+Electron:" << std::endl;
  std::cout << "After hlt cut:" << cuthlt_RA4el << std::endl;
  std::cout << "After number of electron cut:" << cutelenum_RA4el << std::endl;
  std::cout << "After jet cut:" << cutjet_RA4el << std::endl;
  std::cout << "After met cut:" << cutmet_RA4el << std::endl;


//   for (unsigned int i=0;i<muonCuts.size();i++){
//     std::cout<<"muon["<<i<<"]:"<<std::endl;
//     for (unsigned int ii=0;ii<muonCuts[i].size();ii++){
//       std::cout<<" "<<muonCuts[i][ii].first<<
//           " "<<muonCuts[i][ii].second<<std::endl;           
//     }
//   }

  std::cout<<std::endl;
  std::cout<<"numberofmuons: "<<numberofmuons<<std::endl;

  std::cout<<std::endl;
  std::cout<<"numberofmuons_cutflow: "<<numberofmuons_cutflow<<std::endl;

  std::cout<<std::endl;
  std::cout<<"muonCutFlow:"<<std::endl;
  for (unsigned int i=0;i<muonCutFlow.size();i++){
      std::cout<<" "<<muonCutFlow[i].first<<
          " "<<muonCutFlow[i].second[0]<<" "<<muonCutFlow[i].second[1]<<std::endl;           
  }     
}

DEFINE_FWK_MODULE(RA4Synchronization);
