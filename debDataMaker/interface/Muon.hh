#ifndef SusyAnalysis_debDataMaker_Muon_hh_
#define SusyAnalysis_debDataMaker_Muon_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Muon
// 
/**\class Muon Muon.hh SusyAnalysis/debDataMaker/interface/Muon.hh

 Description: <one line class summary>

 Implementation:

   !!!! See usage of inherited functions in Container.hh source code !!!!

   The following fuctions should be overloaded here according to the exact 
   definition of D in Container<D> :

      void calculate(Beamspot<reco::BeamSpot>  *beamspot) (virtual):
         calculates values that depend on other data models

      int passed(std::string selection,unsigned int i) (virtual):
         returns the result of selection. The selections are implemented in 
	 this function.

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Muon.hh,v 1.17 2009/11/02 15:00:40 aranyi Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/VContainer.hh"
#include "SusyAnalysis/debDataMaker/interface/MuonData.hh"
#include "SusyAnalysis/debDataMaker/interface/Beamspot.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

class Muon : public VContainer<MuonData> {
 public:
  Muon(std::string name="") : VContainer<MuonData>(name) { }
  Muon(std::string name, size_t storeNObjects) 
    : VContainer<MuonData>(name, storeNObjects) { }
  ~Muon() { }

  inline MuonData& muon(size_t i) { return *(*this)(i); }

  // Inherited functions to be overloaded
  void calculate (Beamspot<reco::BeamSpot> *beamspot=NULL);
  int passed(std::string, size_t);
  int passed(std::string, size_t, std::vector<std::pair<std::string,int> >&);

};
  
//-------------------------------- calculate() --------------------------------

void Muon::calculate (Beamspot<reco::BeamSpot>  *beamspot){ 

  if (!isValid()) return;
  
  for (size_t i=0; i<size(); i++) {
    
    muon(i).bc_d0=NOVAL_F;
    muon(i).reliso=NOVAL_F;

    if(muon(i).d0!=NOVAL_F&&
       (*beamspot).beamspot(0).beamspotx!=NOVAL_F&&
       (*beamspot).beamspot(0).beamspoty!=NOVAL_F&&
       muon(i).phi_trk!=NOVAL_F) {
	muon(i).bc_d0=muon(i).d0 
	  -(*beamspot).beamspot(0).beamspotx*TMath::Sin(muon(i).phi_trk)
	  +(*beamspot).beamspot(0).beamspoty*TMath::Cos(muon(i).phi_trk);
      } 
   
    if(muon(i).isoR03_ecal!=NOVAL_F&&
       muon(i).isoR03_hcal!=NOVAL_F&&
       muon(i).isoR03_trk!=NOVAL_F&&
       muon(i).pt!=NOVAL_F&&muon(i).pt!=0) {
	muon(i).reliso=(muon(i).isoR03_ecal 
			   +muon(i).isoR03_hcal
			   +muon(i).isoR03_trk)
	               /muon(i).pt;
      } 
  }

}


//--------------------------------- passed() ----------------------------------

int Muon::passed(std::string selection, size_t i) { 

  if (!isValid()) return NOVAL_I;


  if (selection=="RefAna4JetMetMuon") {

    if( muon(i).tight==NOVAL_I ||
        muon(i).pt==NOVAL_F ||
        muon(i).eta==NOVAL_F ||
        muon(i).isoR03_trk==NOVAL_F ||
        muon(i).isoR03_hcal==NOVAL_F ||
        muon(i).isoR03_ecal==NOVAL_F ||
        muon(i).has_trk==NOVAL_I ||
        muon(i).is_combined==NOVAL_I ||
        (muon(i).is_combined==1 && 
        (muon(i).chi2==NOVAL_F || muon(i).ndof==NOVAL_F)) ||
        (muon(i).has_trk==1 && 
        (muon(i).bc_d0==NOVAL_F||muon(i).hits==NOVAL_F))) {
        stdErr("Muon::passed() : NOVAL value in the cut criteria");
        return NOVAL_I;
    }

    if (muon(i).ndof==0.0){
      stdErr("Muon::passed() : division by zero (ndof=0)");
      return NOVAL_I;
    }

    if(muon(i).tight==1 &&
       muon(i).pt>=10.0 &&
       TMath::Abs(muon(i).eta)<=2.1 &&
       muon(i).chi2/muon(i).ndof<10.0 &&
       TMath::Abs(muon(i).bc_d0)<=0.2 &&
       muon(i).hits>=11.0 &&
       muon(i).isoR03_trk<6.0 &&
       muon(i).isoR03_hcal<6.0 &&
       muon(i).isoR03_ecal<6.0 &&
       muon(i).has_trk==1 &&
       muon(i).is_combined==1) {
      return 1;
    }

    return 0;
  }


  return NOVAL_I;
}

//--------------------------------- passed() ----------------------------------  

int Muon::passed(std::string selection, size_t i, 
                 std::vector<std::pair<std::string,int> > &cutflow) { 

  if (!isValid()) return NOVAL_I;


  if(selection=="RefAna4JetMetMuon"){


    std::pair<std::string,int> has_trk("has_trk",NOVAL_I);
    if (muon(i).has_trk!=NOVAL_I) {
      muon(i).has_trk==1 ? has_trk.second=1 : has_trk.second=0;
    }
    cutflow.push_back(has_trk);


    std::pair<std::string,int> is_combined("is_combined",NOVAL_I);
    if (muon(i).is_combined!=NOVAL_I) {
      muon(i).is_combined==1 ? is_combined.second=1 : is_combined.second=0;
    }
    cutflow.push_back(is_combined);


    std::pair<std::string,int> eta("eta",NOVAL_I);
    if (muon(i).eta!=NOVAL_F) TMath::Abs(muon(i).eta)<=2.1 ? 
          eta.second=1 : eta.second=0;
    cutflow.push_back(eta);


    std::pair<std::string,int> pt("pt",NOVAL_I);
    if (muon(i).pt!=NOVAL_F) muon(i).pt>=10.0 ? 
          pt.second=1 : pt.second=0;
    cutflow.push_back(pt);

	  	  	  	 
    std::pair<std::string,int> tight("tight",NOVAL_I);
    if (muon(i).tight!=NOVAL_I) muon(i).tight==1 ? 
          tight.second=1 : tight.second=0;    
    cutflow.push_back(tight);
  

    std::pair<std::string,int> chi2_ndof("chi2/ndof",NOVAL_I);            
    if (muon(i).is_combined==1 && 
        muon(i).chi2!=NOVAL_F && muon(i).ndof!=NOVAL_F && 
        muon(i).ndof!=0) {
      muon(i).chi2/muon(i).ndof<10.0 ? chi2_ndof.second=1 : chi2_ndof.second=0;
    }
    if (muon(i).is_combined==0) chi2_ndof.second=0;
    cutflow.push_back(chi2_ndof);	  
  
       
    std::pair<std::string,int> bc_d0("bc_d0",NOVAL_I);
    if (muon(i).bc_d0!=NOVAL_F) TMath::Abs(muon(i).bc_d0)<=0.2 ? 
          bc_d0.second=1 : bc_d0.second=0;
    cutflow.push_back(bc_d0);
    
    
    std::pair<std::string,int> hits("hits",NOVAL_I);
    if (muon(i).hits!=NOVAL_F) muon(i).hits>=11.0 ? 
          hits.second=1 : hits.second=0;
    cutflow.push_back(hits);
    
    
    std::pair<std::string,int> isoR03_trk("isoR03_trk",NOVAL_I);
    if (muon(i).isoR03_trk!=NOVAL_F) muon(i).isoR03_trk<6.0 ? 
			    isoR03_trk.second=1 : isoR03_trk.second=0;
    cutflow.push_back(isoR03_trk);
    
    
    std::pair<std::string,int> isoR03_hcal("isoR03_hcal",NOVAL_I);
    if (muon(i).isoR03_hcal!=NOVAL_F) muon(i).isoR03_hcal<6.0 ? 
			    isoR03_hcal.second=1 : isoR03_hcal.second=0;
    cutflow.push_back(isoR03_hcal);
    
    
    std::pair<std::string,int> isoR03_ecal("isoR03_ecal",NOVAL_I);
    if (muon(i).isoR03_ecal!=NOVAL_F) muon(i).isoR03_ecal<6.0 ? 
			    isoR03_ecal.second=1 : isoR03_ecal.second=0;
    cutflow.push_back(isoR03_ecal);           
        

    if (muon(i).ndof==0.0){
      stdErr("Muon::passed() : division by zero (ndof=0)");
      return NOVAL_I;
    }  
    
    if( muon(i).tight==NOVAL_I ||
        muon(i).pt==NOVAL_F ||
        muon(i).eta==NOVAL_F ||
        muon(i).isoR03_trk==NOVAL_F ||
        muon(i).isoR03_hcal==NOVAL_F ||
        muon(i).isoR03_ecal==NOVAL_F ||
        muon(i).has_trk==NOVAL_I ||
        muon(i).is_combined==NOVAL_I ||
        (muon(i).is_combined==1 && 
        (muon(i).chi2==NOVAL_F || muon(i).ndof==NOVAL_F)) ||
        (muon(i).has_trk==1 && 
        (muon(i).bc_d0==NOVAL_F||muon(i).hits==NOVAL_F))) {
      stdErr("Muon::passed() : NOVAL value in the cut criteria");
      return NOVAL_I;
    }

    
    if( tight.second==1 &&
        pt.second==1 &&
        eta.second==1 &&
        isoR03_trk.second==1 &&
        isoR03_hcal.second==1 &&
        isoR03_ecal.second==1 &&
        chi2_ndof.second==1 &&
        bc_d0.second==1 &&
        hits.second==1 &&
        has_trk.second==1 &&
        is_combined.second==1) {
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
