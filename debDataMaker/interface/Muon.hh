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

      int passed(std::string selection,unsigned int i) (virtual):
         returns the result of selection. The selections are implemented in 
	 this function.

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Muon.hh,v 1.13 2009/07/14 12:56:05 aranyi Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/Container.hh"
#include "SusyAnalysis/debDataMaker/interface/MuonData.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

class Muon : public Container<MuonData> {
 public:
  Muon(std::string name="") : Container<MuonData>(name) { }
  Muon(std::string name, size_t storeNObjects) 
    : Container<MuonData>(name, storeNObjects) { }
  ~Muon() { }

  inline MuonData& muon(size_t i) { return at(i); }

  // Inherited functions to be overloaded
  int passed(std::string, size_t);
  
};
  
//--------------------------------- passed() ----------------------------------

int Muon::passed(std::string selection, size_t i) { 

  if (!isValid()) return NOVAL_I;


  if(selection.compare("RefAna4JetMetMuon")==0){
    if(muon(i).tight==NOVAL_I||
       muon(i).pt==NOVAL_F||
       muon(i).eta==NOVAL_F||
       //muon(i).reliso==NOVAL_F||
       //muon(i).hcalisodep==NOVAL_F||
       //muon(i).ecalisodep==NOVAL_F||
       muon(i).isoR03_trk==NOVAL_F||
       muon(i).isoR03_hcal==NOVAL_F||
       muon(i).isoR03_ecal==NOVAL_F||
       muon(i).has_trk==NOVAL_I||
       muon(i).is_combined==NOVAL_I){
      stdErr("Muon::passed() : NOVAL value in the cut criteria");
      return NOVAL_I;
    }
    if((muon(i).bc_d0==NOVAL_F||muon(i).hits==NOVAL_F)&&
       muon(i).has_trk==0){
      return 0;
    }
    if((muon(i).chi2==NOVAL_F||muon(i).ndof==NOVAL_F)&&
       muon(i).is_combined==0){
      return 0;
    }
    if((muon(i).bc_d0==NOVAL_F||muon(i).hits==NOVAL_F)&&
       muon(i).has_trk==1){
      stdErr("Muon::passed() : NOVAL value in the cut criteria(has_trk=1)");  
      return NOVAL_I;
    }
    if((muon(i).chi2==NOVAL_F||muon(i).ndof==NOVAL_F)&&
       muon(i).is_combined==1){
      stdErr(
	    "Muon::passed() : NOVAL value in the cut criteria(is_combined=1)");
      return NOVAL_I;
    }

    if(muon(i).tight==1&&
       muon(i).pt>=10.0&&
       TMath::Abs(muon(i).eta)<=2.1&&
       //muon(i).reliso<0.1&&
       muon(i).ndof!=0.0&&
       muon(i).chi2/muon(i).ndof<10.0&&
       TMath::Abs(muon(i).bc_d0)<=0.2&&
       muon(i).hits>=11.0&&
       //muon(i).hcalisodep<6.0&&
       //muon(i).ecalisodep<4.0
       muon(i).isoR03_trk<6.0&&
       muon(i).isoR03_hcal<6.0&&
       muon(i).isoR03_ecal<6.0
      ){
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
