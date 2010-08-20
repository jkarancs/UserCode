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
// $Id$
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
  void calculate (Beamspot *beamspot=NULL);

  int passed(std::string, size_t, Selection*);
  
};


//-------------------------------- calculate() --------------------------------

void Electron::calculate(Beamspot *beamspot) { 

  if (!isValid()) return;

  for (size_t i=0; i<size(); i++) {

    // Correct d0 for beam-spot
    //
    electron(i).d0_bc = NOVAL_F;
    electron(i).reliso = NOVAL_F;
    electron(i).reliso_comb = NOVAL_F;

    if (beamspot != NULL) {

      if( electron(i).d0 != NOVAL_F&&
	  beamspot->beamspot(0).x != NOVAL_F&&
	  beamspot->beamspot(0).y != NOVAL_F&&
	  electron(i).phi_trk != NOVAL_F) {

	electron(i).d0_bc = electron(i).d0
	  - beamspot->beamspot(0).x*TMath::Sin(electron(i).phi_trk)
	  + beamspot->beamspot(0).y*TMath::Cos(electron(i).phi_trk);
      }
    }
    
    if( electron(i).isoR03_ecal!=NOVAL_F&&
	electron(i).isoR03_hcal!=NOVAL_F&&
	electron(i).pt!=NOVAL_F && electron(i).pt!=0) {

      electron(i).reliso = ( electron(i).isoR03_ecal +
			     electron(i).isoR03_hcal ) / electron(i).pt;
    }
    
    if( electron(i).isoR03_ecal!=NOVAL_F&&
	electron(i).isoR03_hcal!=NOVAL_F&&
	electron(i).isoR03_trk!=NOVAL_F&&
	electron(i).et!=NOVAL_F && electron(i).et!=0) {

      electron(i).reliso_comb = ( electron(i).isoR03_ecal+
				  electron(i).isoR03_hcal+
				  electron(i).isoR03_trk ) /electron(i).et;
    }
  } // for
  
}



//--------------------------------- passed() ----------------------------------

int Electron::passed(std::string selection, size_t i, Selection *sel=NULL) {  
                       
  #ifdef DEB_DEBUG
  stdMesg("Electron::passed(%d) : selection '%s'.", i, selection.c_str());
  #endif

  if (!isValid()) return NOVAL_I;
  
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


  if (selection=="RA4_ElectronVeto") {

    const ElectronData& ele = electron(i);

    if (sel==NULL) {

      check_noval(ele.has_trk);
      check_noval(ele.eta);
      check_noval(ele.pt);
      if (ele.has_trk==1) check_noval(ele.d0_bc);
      check_noval(ele.reliso_comb);
      check_noval(ele.tight);

      if ( ele.has_trk == 1 &&
	   fabs(ele.eta) < 2.5 &&
	   ele.pt >= 20. &&
	   fabs(ele.d0_bc) < 0.2 &&
	   ele.reliso_comb < 0.1 &&
	   ele.tight == 1.0
	   ) return 1;

      return 0;
    }

    Cut has_trk("has gsfTrack", ele.has_trk, ele.has_trk == 1);
    sel->add(has_trk);

    Cut eta("|eta| < 2.5", ele.eta, fabs(ele.eta) < 2.5);
    sel->add(eta);

    Cut pt("pt >= 20 GeV", ele.pt, ele.pt >= 20.);
    sel->add(pt);

    if (ele.has_trk==1) check_noval(ele.d0_bc);
    Cut d0_bc("|d0_bc| < 0.2 cm", (ele.has_trk==1) ? ele.d0_bc : 0, 
	      fabs(ele.d0_bc) < 0.2);
    sel->add(d0_bc);

    Cut reliso_comb("Combined Relative Iso < 0.1", 
		    ele.reliso_comb, ele.reliso_comb < 0.1 );
    sel->add(reliso_comb);

    Cut ele_id("eidRobustTight", ele.tight, ele.tight == 1.0);
    sel->add(ele_id);

    if (sel->passed()) return 1;
    return 0;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


  if (selection=="RA4_ElectronID") {
    
    const ElectronData& ele = electron(i);

    if (sel==NULL) {

      check_noval(ele.has_trk);
      check_noval(ele.eta);
      check_noval(ele.pt);
      if (ele.has_trk==1) check_noval(ele.d0_bc);
      check_noval(ele.reliso);
      check_noval(ele.loose);

      if ( ele.has_trk == 1 &&
	   ( fabs(ele.eta)<1.47 || 
	     ( fabs(ele.eta) >= 1.567 && fabs(ele.eta) < 2.5 ) ) &&
	   ele.pt >= 20. &&
	   fabs(ele.d0_bc) < 0.2 &&
	   ele.reliso < 0.1 &&
	   ele.loose == 1.0
	   ) return 1;

      return 0;
    }

    Cut has_trk("has gsfTrack", ele.has_trk, ele.has_trk == 1);
    sel->add(has_trk);
    
    Cut eta("|eta| < 1.47 or 1.567 <= |eta| < 2.5", ele.eta, 
	    fabs(ele.eta)<1.47 || (fabs(ele.eta)>=1.567 && fabs(ele.eta)<2.5));
    sel->add(eta);

    Cut pt("pt >= 20 GeV", ele.pt, ele.pt >= 20.);
    sel->add(pt);
  
    if (ele.has_trk==1) check_noval(ele.d0_bc);
    Cut d0_bc("|d0_bc| < 0.2 cm", (ele.has_trk==1) ? ele.d0_bc : 0, 
	      fabs(ele.d0_bc) < 0.2);
    sel->add(d0_bc);

    Cut reliso("Relative Iso < 0.1", ele.reliso, ele.reliso < 0.1 );
    sel->add(reliso);
    
    Cut ele_id("eidRobustLoose", ele.loose, ele.loose == 1.0);
    sel->add(ele_id);

    if (sel->passed()) return 1;
    return 0;
  }  
  
  
  return NOVAL_I;
} 
  
  
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
