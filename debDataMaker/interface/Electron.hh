#ifndef SusyAnalysis_debDataMaker_Electron_hh_
#define SusyAnalysis_debDataMaker_Electron_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Electron
// 
/**\class Electron Electron.hh SusyAnalysis/debDataMaker/interface/Electron.hh

 Description: <one line class summary>

 Implementation:

   !!!! See usage of inherited functions in Container.hh source code !!!!

   The following fuctions should be overloaded here according to the exact 
   definition of D in Container<D> :

      void calculate(Beamspot<reco::BeamSpot>  *beamspot) (virtual):
         that calculates values that depend on other data models

      int passed(std::string selection,size_t i) (virtual):
         returns the result of selection. The selections are implemented in 
	 this function.

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $$
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/VContainer.hh"
#include "SusyAnalysis/debDataMaker/interface/ElectronData.hh"
#include "SusyAnalysis/debDataMaker/interface/Beamspot.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

class Electron : public VContainer<ElectronData> {
public:
  Electron(std::string name="") : VContainer<ElectronData>(name) { }
  Electron(std::string name, size_t storeNObjects) 
    : VContainer<ElectronData>(name, storeNObjects) { }
  ~Electron() { }

  inline ElectronData& electron(size_t i) { return *(*this)(i); }

  // Inherited functions to be overloaded
  void calculate (Beamspot<reco::BeamSpot>  *beamspot=NULL);
  int passed(std::string selection, size_t i) {
    return passed(selection, i, NULL);
  };
  int passed(std::string, size_t, std::vector<std::pair<std::string,int> >*);
  
};
  
  
//-------------------------------- calculate() --------------------------------

void Electron::calculate(Beamspot<reco::BeamSpot> *beamspot) { 

  if (!isValid()) return;

  if(beamspot==NULL){
    for (unsigned int i=0; i<size(); i++) {
      electron(i).bc_d0=NOVAL_F;
      electron(i).reliso=NOVAL_F;
    }
    return;
  }
  
  for (unsigned int i=0; i<size(); i++) {

    electron(i).bc_d0=NOVAL_F;
    electron(i).reliso=NOVAL_F;

    if(electron(i).d0!=NOVAL_F&&
       (*beamspot).beamspot(0).beamspotx!=NOVAL_F&&
       (*beamspot).beamspot(0).beamspoty!=NOVAL_F&&
       electron(i).phi_trk!=NOVAL_F){
    electron(i).bc_d0=electron(i).d0
            -(*beamspot).beamspot(0).beamspotx*TMath::Sin(electron(i).phi_trk)
            +(*beamspot).beamspot(0).beamspoty*TMath::Cos(electron(i).phi_trk);
    }
    
    if(electron(i).isoR03_ecal!=NOVAL_F&&
       electron(i).isoR03_hcal!=NOVAL_F&&
       electron(i).pt!=NOVAL_F&&electron(i).pt!=0){
       electron(i).reliso=(electron(i).isoR03_ecal+electron(i).isoR03_hcal)
	                  /electron(i).pt;
    }
    
    if(electron(i).isoR03_ecal!=NOVAL_F&&
       electron(i).isoR03_hcal!=NOVAL_F&&
       electron(i).isoR03_trk!=NOVAL_F&&
       electron(i).et!=NOVAL_F&&electron(i).et!=0){
       electron(i).combined_reliso=(electron(i).isoR03_ecal+
                                    electron(i).isoR03_hcal+
                                    electron(i).isoR03_trk)/electron(i).et;
    }
  }
  
}


//--------------------------------- passed() ----------------------------------  

int Electron::passed(std::string selection, size_t i, 
                     std::vector<std::pair<std::string,int> > *cutflow) { 
                       
  if (!isValid()) return NOVAL_I;
  
  if (cutflow!=NULL) (*cutflow).clear();

  if(selection=="RefAna4JetMetMuon"){
    
    
    std::pair<std::string,int> all("Number of Candidates               ",NOVAL_I);
    all.second=1;
    if (cutflow!=NULL) (*cutflow).push_back(all);    
    
    
    std::pair<std::string,int> has_trk("has innerTrack                     ",NOVAL_I);
    if(electron(i).has_trk!=NOVAL_I) {
      electron(i).has_trk==1 ? has_trk.second=1 : has_trk.second=0;
    }
    if (cutflow!=NULL) (*cutflow).push_back(has_trk);
    
    
    std::pair<std::string,int> eta("|eta|                     <= 2.5   ",NOVAL_I);
    if(electron(i).eta!=NOVAL_F) { 
      TMath::Abs(electron(i).eta)<=2.5 ? eta.second=1 : eta.second=0;
    }
    if (cutflow!=NULL) (*cutflow).push_back(eta);


    std::pair<std::string,int> pt("pt                        >= 20 GeV",NOVAL_I);
    if(electron(i).pt!=NOVAL_F) {
      electron(i).pt>=20.0 ? pt.second=1 : pt.second=0;
    }
    if (cutflow!=NULL) (*cutflow).push_back(pt);     
    
    
    std::pair<std::string,int> bc_d0("d0 (from primary vertex)  <  0.2 cm",NOVAL_I);
    if(electron(i).bc_d0!=NOVAL_F) {
      TMath::Abs(electron(i).bc_d0)<=0.2 ? bc_d0.second=1 : bc_d0.second=0;
    }
    if (cutflow!=NULL) (*cutflow).push_back(bc_d0);
    

    std::pair<std::string,int> combined_reliso("Combined Relative isol.   <= 0.1   ",NOVAL_I);
    if(electron(i).combined_reliso!=NOVAL_F) {
      electron(i).combined_reliso<=0.1 ? 
          combined_reliso.second=1 : combined_reliso.second=0;
    }
    if (cutflow!=NULL) (*cutflow).push_back(combined_reliso);
            
    
    std::pair<std::string,int> tight("Electron Id e.g.:'eidRobustTight'  ",NOVAL_I);
    if(electron(i).tight!=NOVAL_F) {
      electron(i).tight==1.0 ? tight.second=1 : tight.second=0;
    }
    if (cutflow!=NULL) (*cutflow).push_back(tight);  
       
    
    if(electron(i).has_trk==NOVAL_I ||
       electron(i).has_trk==1 && electron(i).bc_d0==NOVAL_F ||
       electron(i).eta==NOVAL_F ||
       electron(i).pt==NOVAL_F ||
       electron(i).tight==NOVAL_F ||
       electron(i).combined_reliso==NOVAL_F) {
      stdErr("Electron::passed() : NOVAL value in the cut criteria");     
      return NOVAL_I;
    }
    
    if( has_trk.second==1 &&
        eta.second==1 &&
        pt.second==1 &&
        tight.second==1 &&
        bc_d0.second==1 &&
        combined_reliso.second==1) {
      return 1;
    }

    return 0;
  }

  
    
  if(selection=="RefAna4JetMetElectron"){
    
    
    std::pair<std::string,int> all("Number of Candidates               ",NOVAL_I);
    all.second=1;
    if (cutflow!=NULL) (*cutflow).push_back(all);
          
      
    std::pair<std::string,int> has_trk("has innerTrack                     ",NOVAL_I);
    if(electron(i).has_trk!=NOVAL_I) {
      electron(i).has_trk==1 ? has_trk.second=1 : has_trk.second=0;
    }
    if (cutflow!=NULL) (*cutflow).push_back(has_trk);
    
                
    std::pair<std::string,int> loose("Electron Id e.g.:'eidRobustLoose'  ",NOVAL_I);
    if(electron(i).loose!=NOVAL_F) {
      electron(i).loose==1.0 ? loose.second=1 : loose.second=0;
    }
    if (cutflow!=NULL) (*cutflow).push_back(loose);
      
                                   
    std::pair<std::string,int> eta("|eta|                     <= 2.5   ",NOVAL_I);
    if(electron(i).eta!=NOVAL_F) { 
      TMath::Abs(electron(i).eta)<=2.5 && 
      (TMath::Abs(electron(i).eta)<1.47 || TMath::Abs(electron(i).eta)>1.567) ? 
          eta.second=1 : eta.second=0;
    }
    if (cutflow!=NULL) (*cutflow).push_back(eta);
  
  
    std::pair<std::string,int> pt("pt                        >= 20 GeV",NOVAL_I);
    if(electron(i).pt!=NOVAL_F) {
      electron(i).pt>=20.0 ? pt.second=1 : pt.second=0;
    }
    if (cutflow!=NULL) (*cutflow).push_back(pt);
    
    
    std::pair<std::string,int> bc_d0("d0 (from primary vertex)  <  0.2 cm",NOVAL_I);
    if(electron(i).bc_d0!=NOVAL_F) {
      TMath::Abs(electron(i).bc_d0)<=0.2 ? bc_d0.second=1 : bc_d0.second=0;
    }
    if (cutflow!=NULL) (*cutflow).push_back(bc_d0);
      
    
    std::pair<std::string,int> reliso("Relative isolation        <= 0.1   ",NOVAL_I);
    if(electron(i).reliso!=NOVAL_F) {
      electron(i).reliso<=0.1 ? reliso.second=1 : reliso.second=0;
    }
    if (cutflow!=NULL) (*cutflow).push_back(reliso);
         
      
    if(electron(i).has_trk==NOVAL_I ||
       electron(i).has_trk==1 && electron(i).bc_d0==NOVAL_F ||
       electron(i).eta==NOVAL_F ||
       electron(i).pt==NOVAL_F ||
       electron(i).loose==NOVAL_F ||
       electron(i).reliso==NOVAL_F) {
      stdErr("Electron::passed() : NOVAL value in the cut criteria");     
      return NOVAL_I;
    }
      
    if( has_trk.second==1 &&
        eta.second==1 &&
        pt.second==1 &&
        loose.second==1 &&
        bc_d0.second==1 &&
        reliso.second==1) {
      return 1;
    }
  
    return 0;
  }  
  
  
  return NOVAL_I;
} 
  
  
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
