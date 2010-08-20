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
// $Id: Muon.hh,v 1.27 2010/08/16 13:41:19 veszpv Exp $
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
  void calculate (Beamspot *beamspot=NULL);

  int passed(std::string, size_t, Selection*);

};


//-------------------------------- calculate() --------------------------------

void Muon::calculate (Beamspot *beamspot) { 

  if (!isValid()) return;
  
  for (size_t i=0; i<size(); i++) {

    // Correct d0 for beam-spot
    //
    muon(i).d0_bc=NOVAL_F;
    muon(i).reliso=NOVAL_F;
    
    if (beamspot != NULL) {

      if ( muon(i).d0!=NOVAL_F&&
	   beamspot->beamspot(0).x!=NOVAL_F&&
	   beamspot->beamspot(0).y!=NOVAL_F&&
	   muon(i).phi_trk!=NOVAL_F) {

	muon(i).d0_bc = muon(i).d0 
	  - beamspot->beamspot(0).x*TMath::Sin(muon(i).phi_trk)
	  + beamspot->beamspot(0).y*TMath::Cos(muon(i).phi_trk);
      } 
    }

    // Calculate relative isolation based on calorimeter and track isolations 
    //
    if ( muon(i).isoR03_ecal!=NOVAL_F&&
	 muon(i).isoR03_hcal!=NOVAL_F&&
	 muon(i).isoR03_trk!=NOVAL_F&&
	 muon(i).pt!=NOVAL_F && muon(i).pt!=0) {

      muon(i).reliso = ( muon(i).isoR03_ecal 
			 +muon(i).isoR03_hcal
			 +muon(i).isoR03_trk ) / muon(i).pt;
    }

  }
}


//--------------------------------- passed() ----------------------------------

int Muon::passed(std::string selection, size_t i, Selection *sel=NULL) {  

  #ifdef DEB_DEBUG
  stdMesg("Muon::passed(%d) : selection '%s'.", i, selection.c_str());
  #endif

  if (!isValid()) return NOVAL_I;

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


  if (selection=="RA4_MuonID"){

    if (sel==NULL) {
      check_noval(muon(i).has_trk);
      if (muon(i).has_trk==1) check_noval(muon(i).hits);
      check_noval(muon(i).eta);
      check_noval(muon(i).pt);
      check_noval(muon(i).is_combined);
      if (muon(i).is_combined==1) {
	check_noval(muon(i).ndof);
	check_noval(muon(i).chi2);
      }
      check_noval(muon(i).tight);
      if (muon(i).has_trk==1) check_noval(muon(i).d0_bc);
      check_noval(muon(i).isoR03_trk);
      check_noval(muon(i).isoR03_hcal);
      check_noval(muon(i).isoR03_ecal);

      if ( muon(i).has_trk == 1 &&
	   muon(i).hits >= 11 &&
	   fabs(muon(i).eta) < 2.1 &&
	   muon(i).pt >=10 &&
	   muon(i).is_combined == 1 &&
	   muon(i).ndof !=0 &&
	   muon(i).chi2/muon(i).ndof < 10 &&
	   muon(i).tight == 1 &&
	   fabs(muon(i).d0_bc) < 0.2 &&
	   muon(i).isoR03_trk < 6. &&
	   muon(i).isoR03_hcal < 6. &&
	   muon(i).isoR03_ecal < 6.
	   ) return 1;

      return 0;
    }

    Cut has_trk("has innerTrack", muon(i).has_trk, muon(i).has_trk==1);
        sel->add(has_trk);

    Cut trk_hits("innerTrack hits >= 11", 
		 (muon(i).has_trk==1) ? muon(i).hits : 0, muon(i).hits >= 11);
        sel->add(trk_hits);

    Cut eta("|eta| < 2.1", muon(i).eta, fabs(muon(i).eta)<2.1);
        sel->add(eta);

    Cut pt("pt >= 10", muon(i).pt, muon(i).pt>=10.);
        sel->add(pt);

    Cut combined("combined muon", muon(i).is_combined, muon(i).is_combined==1);
        sel->add(combined);

    if (muon(i).is_combined==1) check_noval(muon(i).ndof);
    Cut chi2_ndof_preq("globalTrack fit, ndof != 0", 
		       (muon(i).is_combined==1) ? muon(i).ndof : 0,
		       muon(i).is_combined==1 && muon(i).ndof!=0);
    sel->add(chi2_ndof_preq);

    if (muon(i).is_combined==1) check_noval(muon(i).chi2);
    Cut chi2_ndof("globalTrack chi2/ndof < 10",
		  (chi2_ndof_preq.passed()) ? muon(i).chi2/muon(i).ndof : 0, 
		  chi2_ndof_preq.passed() && muon(i).chi2/muon(i).ndof<10.);
    sel->add(chi2_ndof);

    
    Cut tight("GlobalMuonPromptTight", muon(i).tight, muon(i).tight == 1 );
        sel->add(tight);
  
    if (muon(i).has_trk==1) check_noval(muon(i).d0_bc);
    Cut d0_bc("|d0_bc| < 0.2 cm", (muon(i).has_trk==1) ? muon(i).d0_bc : 0, 
	      fabs(muon(i).d0_bc) < 0.2);
        sel->add(d0_bc);
                            
    Cut iso_trk("Track Iso < 6 GeV", muon(i).isoR03_trk, 
		muon(i).isoR03_trk < 6. );
        sel->add(iso_trk);
                        
    Cut iso_hcal("HCal Iso < 6 GeV", muon(i).isoR03_hcal,
		 muon(i).isoR03_hcal < 6. );
        sel->add(iso_hcal);

    Cut iso_ecal("ECal Iso < 6 GeV", muon(i).isoR03_ecal, 
		 muon(i).isoR03_ecal < 6. );
        sel->add(iso_ecal);

    if (sel->passed()) return 1;
    return 0;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


  if (selection=="RA4_MuonVeto") {

    if (sel==NULL) {
      check_noval(muon(i).has_trk);
      if (muon(i).has_trk==1) check_noval(muon(i).hits);
      check_noval(muon(i).eta);
      check_noval(muon(i).pt);
      check_noval(muon(i).is_combined);
      if (muon(i).is_combined==1) {
	check_noval(muon(i).ndof);
	check_noval(muon(i).chi2);
      }
      check_noval(muon(i).tight);
      if (muon(i).has_trk==1) check_noval(muon(i).d0_bc);
      check_noval(muon(i).reliso);
      check_noval(muon(i).hcalisodep);
      check_noval(muon(i).ecalisodep);


      if ( muon(i).has_trk == 1 &&
	   muon(i).hits >=11 &&
	   fabs(muon(i).eta) <= 2.1 &&
	   muon(i).pt >= 20. &&
	   muon(i).is_combined == 1 &&
	   muon(i).ndof != 0 &&
	   muon(i).chi2/muon(i).ndof < 10. &&
	   muon(i).tight == 1 &&
	   fabs(muon(i).d0_bc) < 0.2 &&
	   muon(i).reliso < 0.1  &&
	   muon(i).hcalisodep < 6.  &&
	   muon(i).ecalisodep < 4.
	   ) return 1;

      return 0;
    }

    Cut has_trk("has innerTrack", muon(i).has_trk, muon(i).has_trk == 1);
    sel->add(has_trk);

    Cut hits("innerTrack hits >= 11",
	     (muon(i).has_trk==1) ? muon(i).hits : 0, muon(i).hits>=11);
    sel->add(hits);
    
    Cut eta("|eta| < 2.1", muon(i).eta, fabs(muon(i).eta) <= 2.1);
    sel->add(eta);

    Cut pt("pt >= 20 GeV", muon(i).pt, muon(i).pt >= 20.);
    sel->add(pt);

    Cut combined("combined muon", muon(i).is_combined, muon(i).is_combined==1);
    sel->add(combined);

    if (muon(i).is_combined==1) check_noval(muon(i).ndof);
    Cut chi2_ndof_preq("globalTrack fit, ndof != 0", 
		       (muon(i).is_combined==1) ? muon(i).ndof : 0,
		       muon(i).is_combined==1 && muon(i).ndof!=0);
    sel->add(chi2_ndof_preq);

    if (muon(i).is_combined==1) check_noval(muon(i).chi2);
    Cut chi2_ndof("globalTrack chi2/ndof < 10",
		  (chi2_ndof_preq.passed()) ? muon(i).chi2/muon(i).ndof : 0, 
		  chi2_ndof_preq.passed() && muon(i).chi2/muon(i).ndof<10.);
    sel->add(chi2_ndof);


    Cut tight("GlobalMuonPromptTight", muon(i).tight, muon(i).tight == 1);
    sel->add(tight);

    if (muon(i).has_trk==1) check_noval(muon(i).d0_bc);
    Cut d0_bc("|d0_bc| < 0.2 cm", (muon(i).has_trk==1) ? muon(i).d0_bc : 0, 
	      fabs(muon(i).d0_bc) < 0.2);
        sel->add(d0_bc);
          
    Cut reliso("Relative Iso < 0.1", muon(i).reliso, muon(i).reliso < 0.1 );
        sel->add(reliso);

    Cut hcal_isodep("HCal Iso Deposit < 6 GeV", muon(i).hcalisodep,
		 muon(i).hcalisodep < 6. );
        sel->add(hcal_isodep);

    Cut ecal_isodep("ECal Iso Deposit < 4 GeV", muon(i).ecalisodep, 
		    muon(i).ecalisodep < 4. );
        sel->add(ecal_isodep);

    if (sel->passed()) return 1;
    return 0;
  }
  
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

  //--------------------------- OLD selection!!! -----------------------------
  
  
//   if(selection=="RefAna4JetMetMuon_Old"){
    
    
//     std::pair<std::string,int> 
//         all("Number of Candidates               ",NOVAL_I);
//     all.second=1;
//     if (cutflow!=NULL) (*cutflow).push_back(all);
    

//     std::pair<std::string,int> 
//         has_trk("has innerTrack                     ",NOVAL_I);
//     if (muon(i).has_trk!=NOVAL_I) {
//       muon(i).has_trk==1 ? has_trk.second=1 : has_trk.second=0;
//     }
//     if (cutflow!=NULL) (*cutflow).push_back(has_trk);

    
//     std::pair<std::string,int> 
//         hits("Number of innerTrack hits >= 11    ",NOVAL_I);
//     if (muon(i).hits!=NOVAL_I) muon(i).hits>=11 ? 
//           hits.second=1 : hits.second=0;
//     if (cutflow!=NULL) (*cutflow).push_back(hits);
    
    
//     std::pair<std::string,int> 
//         eta("|eta|                     <= 2.1   ",NOVAL_I);
//     if (muon(i).eta!=NOVAL_F) TMath::Abs(muon(i).eta)<=2.1 ? 
//           eta.second=1 : eta.second=0;
//     if (cutflow!=NULL) (*cutflow).push_back(eta);


// //     std::pair<std::string,int> is_combined("Combined muon                      ",NOVAL_I);
// //     if (muon(i).is_combined!=NOVAL_I) {
// //       muon(i).is_combined==1 ? is_combined.second=1 : is_combined.second=0;
// //     }
// //     if (cutflow!=NULL) (*cutflow).push_back(is_combined);


//     std::pair<std::string,int> 
//         pt("pt                        >= 20 GeV",NOVAL_I);
//     if (muon(i).pt!=NOVAL_F) muon(i).pt>=20.0 ? 
//           pt.second=1 : pt.second=0;
//     if (cutflow!=NULL) (*cutflow).push_back(pt);

	  	  	  	 
//     std::pair<std::string,int> 
//         tight("GlobalMuonPromptTight              ",NOVAL_I);
//     if (muon(i).tight!=NOVAL_I) muon(i).tight==1 ? 
//           tight.second=1 : tight.second=0;    
//     if (cutflow!=NULL) (*cutflow).push_back(tight);
  

//     std::pair<std::string,int> 
//         chi2_ndof("globalTrack fit chi2/ndof <  10    ",NOVAL_I);            
//     if (muon(i).is_combined==1 && 
//         muon(i).chi2!=NOVAL_F && muon(i).ndof!=NOVAL_F && 
//         muon(i).ndof!=0) {
//       muon(i).chi2/muon(i).ndof<10.0 ? chi2_ndof.second=1 : chi2_ndof.second=0;
//     }
//     if (muon(i).is_combined==0) chi2_ndof.second=0;
//     if (cutflow!=NULL) (*cutflow).push_back(chi2_ndof);	  
  
       
//     std::pair<std::string,int> 
//         d0_bc("d0 (from primary vertex)  <  0.2 cm",NOVAL_I);
//     if (muon(i).d0_bc!=NOVAL_F) TMath::Abs(muon(i).d0_bc)<0.2 ? 
//           d0_bc.second=1 : d0_bc.second=0;
//     if (cutflow!=NULL) (*cutflow).push_back(d0_bc);
    
    
//     std::pair<std::string,int> reliso("Relative isolation        <  0.1   ",NOVAL_I);
//     if (muon(i).reliso!=NOVAL_F) muon(i).reliso<0.1 ? 
//           reliso.second=1 : reliso.second=0;
//     if (cutflow!=NULL) (*cutflow).push_back(reliso); 
    
    
//     std::pair<std::string,int> 
//         hcalisodep("HCAL Isolation Deposit    <  6 GeV ",NOVAL_I);
//     if (muon(i).hcalisodep!=NOVAL_F) muon(i).hcalisodep<6.0 ? 
//           hcalisodep.second=1 : hcalisodep.second=0;
//     if (cutflow!=NULL) (*cutflow).push_back(hcalisodep);
    
    
//     std::pair<std::string,int> 
//         ecalisodep("ECAL Isolation Deposit    <  4 GeV ",NOVAL_I);
//     if (muon(i).ecalisodep!=NOVAL_F) muon(i).ecalisodep<4.0 ? 
//           ecalisodep.second=1 : ecalisodep.second=0;
//     if (cutflow!=NULL) (*cutflow).push_back(ecalisodep);          
        

//     if (muon(i).ndof==0.0){
//       stdErr("Muon::passed() : division by zero (ndof=0)");
//       return NOVAL_I;
//     }  
    
//     if( muon(i).tight==NOVAL_I ||
//         muon(i).pt==NOVAL_F ||
//         muon(i).eta==NOVAL_F ||
//         muon(i).hcalisodep==NOVAL_F ||
//         muon(i).ecalisodep==NOVAL_F ||
//         muon(i).reliso==NOVAL_F ||
//         muon(i).has_trk==NOVAL_I ||
//         //muon(i).is_combined==NOVAL_I ||
//         (muon(i).is_combined==1 && 
//         (muon(i).chi2==NOVAL_F || muon(i).ndof==NOVAL_F)) ||
//         (muon(i).has_trk==1 && 
//         (muon(i).d0_bc==NOVAL_F||muon(i).hits==NOVAL_I))) {
//       stdErr("Muon::passed() : NOVAL value in the cut criteria");
//       return NOVAL_I;
//     }

    
//     if( tight.second==1 &&
//         pt.second==1 &&
//         eta.second==1 &&
//         hcalisodep.second==1 &&
//         ecalisodep.second==1 &&
//         reliso.second==1 &&
//         chi2_ndof.second==1 &&
//         d0_bc.second==1 &&
//         hits.second==1 &&
//         has_trk.second==1 ) {
//         //is_combined.second==1) {
//       return 1;
//     }

//     return 0;
//   }
  
  
  
  return NOVAL_I;
} 
  

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
