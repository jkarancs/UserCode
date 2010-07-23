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
// $Id: Jet.hh,v 1.21 2010/07/23 09:27:43 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/VContainer.hh"
#include "SusyAnalysis/debDataMaker/interface/JetData.hh"
#include <algorithm>
#include "SusyAnalysis/debDataMaker/interface/Selection.hh"


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

  // easy to read substitute for (*this)(i)
  inline JetData& jet(size_t i) { return *(*this)(i); } 

  enum SortBy {
    et = 0,
    pt = 1,
    nan = NOVAL_I
  };

 private:

  SortBy sortBy_;

 public:

  inline SortBy& sortBy() { return sortBy_; }

  void setSortBy(std::string param) {
    sortBy_ = nan;
    std::transform(param.begin(), param.end(), param.begin(),::tolower);
    if (param == "et") sortBy_ = et;
    if (param == "pt") sortBy_ = pt;
  }

  inline const char* sortedBy() {
    if (sortBy_==et) return "et";
    if (sortBy_==pt) return "pt";
    return "nan";
  }

  // Inherited functions to be overloaded
  void calculate ();

  int passed(std::string, size_t, Selection*);

};


//-------------------------------- calculate() --------------------------------

void Jet::calculate () { 
}
  

//--------------------------------- passed() ----------------------------------

int Jet::passed(std::string selection, size_t i, Selection *sel=NULL) {  
  
  #ifdef DEB_DEBUG
  stdMesg("Jet::passed(%d) : selection '%s'.", i, selection.c_str());
  #endif

  if (!isValid()) return NOVAL_I;
  
//   if(selection=="RefAna4JetMetMuon"){
        
    
//     std::pair<std::string,int> 
//         all("Number of Candidates               ",NOVAL_I);
//     all.second=1;
//     if (cutflow!=NULL) (*cutflow).push_back(all);

    
//     std::pair<std::string,int> 
//         eta("|eta|                     <= 2.4   ",NOVAL_I);
//     if (jet(i).eta!=NOVAL_F) TMath::Abs(jet(i).eta)<=2.4 ? 
//           eta.second=1 : eta.second=0;
//     if (cutflow!=NULL) (*cutflow).push_back(eta);
    
    
//     std::pair<std::string,int> 
//         pt("pt                        >= 30 GeV",NOVAL_I);
//     if (jet(i).pt!=NOVAL_F) jet(i).pt>=30.0 ? 
//           pt.second=1 : pt.second=0;
//     if (cutflow!=NULL) (*cutflow).push_back(pt);
    
                                       
//     std::pair<std::string,int> 
//         hadfrac("Hadronic Energy Fraction  >= 0.1   ",NOVAL_I);
//     if (jet(i).hadfrac!=NOVAL_F) jet(i).hadfrac>=0.1 ? 
//           hadfrac.second=1 : hadfrac.second=0;
//     if (cutflow!=NULL) (*cutflow).push_back(hadfrac);
    

//     std::pair<std::string,int> 
//         ptOnlySync("pt (for synchronization)  >= 50 GeV",NOVAL_I);
//     if (jet(i).pt!=NOVAL_F) jet(i).pt>=50.0 ? 
//           ptOnlySync.second=1 : ptOnlySync.second=0;
//     if (cutflow!=NULL) (*cutflow).push_back(ptOnlySync);
    
        
//     if(jet(i).pt==NOVAL_F||jet(i).eta==NOVAL_F||jet(i).hadfrac==NOVAL_F){
//       stdErr("Jet::passed() : NOVAL value in the cut criteria");    
//       return NOVAL_I;
//     }

    
//     if( pt.second==1 && eta.second==1 && hadfrac.second==1) {
//       return 1;
//     }
    
//     return 0;
    
//   }
  
  
//   if(selection=="RefAna4JetMetElectron"){
        
    
//     std::pair<std::string,int> 
//         all("Number of Candidates               ",NOVAL_I);
//     all.second=1;
//     if (cutflow!=NULL) (*cutflow).push_back(all);
    
    
//     std::pair<std::string,int> 
//         eta("|eta|                     <= 3.0   ",NOVAL_I);
//     if (jet(i).eta!=NOVAL_F) TMath::Abs(jet(i).eta)<=3.0 ? 
//           eta.second=1 : eta.second=0;
//     if (cutflow!=NULL) (*cutflow).push_back(eta);
    
    
//     std::pair<std::string,int> 
//         pt("pt                        >= 50 GeV",NOVAL_I);
//     if (jet(i).pt!=NOVAL_F) jet(i).pt>=50.0 ? 
//           pt.second=1 : pt.second=0;
//     if (cutflow!=NULL) (*cutflow).push_back(pt);
    
                                      
//     std::pair<std::string,int> 
//         emfrac("EM Energy Fraction        <= 0.9   ",NOVAL_I);
//     if (jet(i).emfrac!=NOVAL_F) jet(i).emfrac<=0.9 ? 
//           emfrac.second=1 : emfrac.second=0;
//     if (cutflow!=NULL) (*cutflow).push_back(emfrac);
    
        
//     if(jet(i).pt==NOVAL_F||jet(i).eta==NOVAL_F||jet(i).emfrac==NOVAL_F){
//       stdErr("Jet::passed() : NOVAL value in the cut criteria");    
//       return NOVAL_I;
//     }

    
//     if( pt.second==1 && eta.second==1 && emfrac.second==1) {
//       return 1;
//     }
    
//     return 0;
    
//   }
  
  
  if (selection=="TopJetSelection") {
    
    // The fast route
    if (sel==NULL) {

      Cut::check(jet(i).eta);
      Cut::check(jet(i).pt);

      if ( jet(i).pt>=20 && fabs(jet(i).eta)<2.7 ) return 1;
      return 0;
    }

    // Collect information for cut-flow analysis
    Cut pt("pt >=20.0 GeV", jet(i).pt, jet(i).pt>=20.);
    sel->add(pt);

    Cut eta("|eta| <2.7", jet(i).eta, fabs(jet(i).eta)<2.7);
    sel->add(eta);

    if (sel->passed()) return 1;
    return 0;

  }
  


  stdErr("Jet::passed() : requested selection is not implemented.\n");
  assert(0);
  
  return NOVAL_I;
}
  
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
