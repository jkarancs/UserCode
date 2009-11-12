#ifndef SusyAnalysis_debDataMaker_Jet_hh_
#define SusyAnalysis_debDataMaker_Jet_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Jet
// 
/**\class Jet Jet.hh SusyAnalysis/debDataMaker/interface/Jet.hh

 Description: <one line class summary>

 Implementation:

   !!!! See usage of inherited functions in Container.hh source code !!!!

   The following fuctions should be overloaded here according to the exact 
   definition of D in Container<D> :

      int passed(std::string selection,unsigned int i) (virtual):
         returns the result of selection. The selections are implemented in 
	 this function.

      void calculate(?) (virtual):
         calculates values that depend on other data models

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Jet.hh,v 1.14 2009/09/05 09:18:07 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/VContainer.hh"
#include "SusyAnalysis/debDataMaker/interface/JetData.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

class Jet : public VContainer<JetData>{
 public:
  Jet(std::string name="") : VContainer<JetData>(name) { }
  Jet(std::string name, size_t storeNObjects) 
    : VContainer<JetData>(name, storeNObjects) { }
  Jet(std::string name, std::vector<size_t> storeList) 
    : VContainer<JetData>(name, storeList) { }
  ~Jet() { }

  inline JetData& jet(size_t i) { return *(*this)(i); }

  // Inherited functions to be overloaded
  void calculate ();
  int passed(std::string, size_t);
  int passed(std::string, size_t, std::vector<std::pair<std::string,int> >&);
  
};


//-------------------------------- calculate() --------------------------------

void Jet::calculate () { 
}
  

//--------------------------------- passed() ----------------------------------

int Jet::passed(std::string selection, size_t i) { 
  
  if (!isValid()) return NOVAL_I;

  if(selection.compare("RefAna4JetMetMuon")==0){
    if(jet(i).pt==NOVAL_F||jet(i).eta==NOVAL_F||jet(i).hadfrac==NOVAL_F){
      stdErr("Jet::passed() : NOVAL value in the cut criteria");    
      return NOVAL_I;
    }
    if(jet(i).pt>=30.0&&
       TMath::Abs(jet(i).eta)<=2.4&&
       jet(i).hadfrac>=0.1){
      return 1;
    }     
    return 0;
  }


  if(selection.compare("RefAna4JetMetElectron")==0){
    if(jet(i).pt==NOVAL_F||jet(i).eta==NOVAL_F||jet(i).emfrac==NOVAL_F){
      stdErr("Jet::passed() : NOVAL value in the cut criteria");
      return NOVAL_I;
    }
    if(jet(i).pt>=25.0&&
       TMath::Abs(jet(i).eta)<=3.0&&
       jet(i).emfrac<=0.9){
      return 1;
    }      
    return 0;
  }

  
  if(selection.compare("TopJetSelection")==0){
    if(jet(i).pt==NOVAL_F||jet(i).eta==NOVAL_F||jet(i).emfrac==NOVAL_F){
      stdErr("Jet::passed() : NOVAL value in the cut criteria");
      return NOVAL_I;
    }
    if(jet(i).pt>=20.0&&
       TMath::Abs(jet(i).eta)<=2.7 &&
       jet(i).emfrac<=0.9) {
      return 1;
    }      
    return 0;
  }

  
  return NOVAL_I;
}
  

//--------------------------------- passed() ----------------------------------

int Jet::passed(std::string selection, size_t i, 
                 std::vector<std::pair<std::string,int> > &cutflow) {  
  
  if (!isValid()) return NOVAL_I;
  
  cutflow.clear();

  if(selection=="RefAna4JetMetMuon"){
    
    
    std::pair<std::string,int> eta("eta",NOVAL_I);
    if (jet(i).eta!=NOVAL_F) TMath::Abs(jet(i).eta)<=2.4 ? 
          eta.second=1 : eta.second=0;
    cutflow.push_back(eta);
    
    
    std::pair<std::string,int> pt("pt",NOVAL_I);
    if (jet(i).pt!=NOVAL_F) jet(i).pt>=30.0 ? 
          pt.second=1 : pt.second=0;
    cutflow.push_back(pt);
    
    
    std::pair<std::string,int> hadfrac("hadfrac",NOVAL_I);
    if (jet(i).hadfrac!=NOVAL_F) jet(i).hadfrac>=0.1 ? 
          hadfrac.second=1 : hadfrac.second=0;
    cutflow.push_back(hadfrac);
    
        
    if(jet(i).pt==NOVAL_F||jet(i).eta==NOVAL_F||jet(i).hadfrac==NOVAL_F){
      stdErr("Jet::passed() : NOVAL value in the cut criteria");    
      return NOVAL_I;
    }

    
    if( pt.second==1 && eta.second==1 && hadfrac.second==1) {
      return 1;
    }
    
    return 0;
    
  }
  
  
  if(selection=="RefAna4JetMetElectron"){
    
    
    std::pair<std::string,int> eta("eta",NOVAL_I);
    if (jet(i).eta!=NOVAL_F) TMath::Abs(jet(i).eta)<=3.0 ? 
          eta.second=1 : eta.second=0;
    cutflow.push_back(eta);
    
    
    std::pair<std::string,int> pt("pt",NOVAL_I);
    if (jet(i).pt!=NOVAL_F) jet(i).pt>=50.0 ? 
          pt.second=1 : pt.second=0;
    cutflow.push_back(pt);
    
    
    std::pair<std::string,int> emfrac("emfrac",NOVAL_I);
    if (jet(i).emfrac!=NOVAL_F) jet(i).emfrac<=0.9 ? 
          emfrac.second=1 : emfrac.second=0;
    cutflow.push_back(emfrac);
    
        
    if(jet(i).pt==NOVAL_F||jet(i).eta==NOVAL_F||jet(i).emfrac==NOVAL_F){
      stdErr("Jet::passed() : NOVAL value in the cut criteria");    
      return NOVAL_I;
    }

    
    if( pt.second==1 && eta.second==1 && emfrac.second==1) {
      return 1;
    }
    
    return 0;
    
  }
  
  
  if(selection=="TopJetSelection"){
    
    
    std::pair<std::string,int> eta("eta",NOVAL_I);
    if (jet(i).eta!=NOVAL_F) TMath::Abs(jet(i).eta)<=2.7 ? 
          eta.second=1 : eta.second=0;
    cutflow.push_back(eta);
    
    
    std::pair<std::string,int> pt("pt",NOVAL_I);
    if (jet(i).pt!=NOVAL_F) jet(i).pt>=20.0 ? 
          pt.second=1 : pt.second=0;
    cutflow.push_back(pt);
    
    
    std::pair<std::string,int> emfrac("emfrac",NOVAL_I);
    if (jet(i).emfrac!=NOVAL_F) jet(i).emfrac<=0.9 ? 
          emfrac.second=1 : emfrac.second=0;
    cutflow.push_back(emfrac);
    
        
    if(jet(i).pt==NOVAL_F||jet(i).eta==NOVAL_F||jet(i).emfrac==NOVAL_F){
      stdErr("Jet::passed() : NOVAL value in the cut criteria");    
      return NOVAL_I;
    }

    
    if( pt.second==1 && eta.second==1 && emfrac.second==1) {
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
