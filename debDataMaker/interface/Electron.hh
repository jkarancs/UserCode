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

#include "SusyAnalysis/debDataMaker/interface/Container.hh"
#include "SusyAnalysis/debDataMaker/interface/ElectronData.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

class Electron : public Container<ElectronData> {
public:
  Electron(std::string name="") : Container<ElectronData>(name) { }
  Electron(std::string name, size_t storeNObjects) 
    : Container<ElectronData>(name, storeNObjects) { }
  ~Electron() { }

  inline ElectronData& electron(size_t i) { return at(i); }

  // Inherited functions to be overloaded
  int passed(std::string selection, size_t i);

};
  
//--------------------------------- passed() ----------------------------------

int Electron::passed(std::string selection, size_t i) {

  if (!isValid()) return NOVAL_I;

  
  if(selection.compare("RefAna4JetMetMuon")==0){
    if(electron(i).pt==NOVAL_F||
       electron(i).eta==NOVAL_F||
       electron(i).tight==NOVAL_F||
       electron(i).reliso==NOVAL_F||
       electron(i).has_trk==NOVAL_I){
      stdErr("Electron::passed() : NOVAL value in the cut criteria");     
      return NOVAL_I;
    }
    if(electron(i).bc_d0==NOVAL_F&& electron(i).has_trk==0){
      return 0;
    }
    if(electron(i).bc_d0==NOVAL_F&& electron(i).has_trk==1){
      stdErr("Electron::passed() : NOVAL value in the cut criteria");     
      return NOVAL_I;
    }
    if(electron(i).pt>=20.0&&
       TMath::Abs(electron(i).eta)<=2.5&&
       electron(i).tight==1.0&&
       electron(i).reliso<0.1&&
       TMath::Abs(electron(i).bc_d0)<0.2){
      return 1;
    }      
    return 0;
  }


  if(selection.compare("RefAna4JetMetElectron")==0){
    if(electron(i).pt==NOVAL_F||
       electron(i).eta==NOVAL_F||
       electron(i).loose==NOVAL_F||
       electron(i).reliso==NOVAL_F||
       electron(i).has_trk==NOVAL_I){
      stdErr("Electron::passed() : NOVAL value in the cut criteria");
      return NOVAL_I;
    }
    if(electron(i).bc_d0==NOVAL_F&& electron(i).has_trk==0){
      return 0;
    }
    if(electron(i).bc_d0==NOVAL_F&& electron(i).has_trk==1){
      stdErr(
	    "Electron::passed() : NOVAL value in the cut criteria(has_trk=1)");
      return NOVAL_I;
    }
    if(electron(i).pt>=20.0&&
       TMath::Abs(electron(i).eta)<=2.5&&
       (TMath::Abs(electron(i).eta)<1.47||
	TMath::Abs(electron(i).eta)>1.567)&&
       electron(i).loose==1.0&&
       electron(i).reliso<0.1&&
       TMath::Abs(electron(i).bc_d0)<=0.2){
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
