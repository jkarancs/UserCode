#ifndef SusyAnalysis_debDataMaker_CMSSWTools_hh_
#define SusyAnalysis_debDataMaker_CMSSWTools_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Data
// 
/**\class Data Data.hh SusyAnalysis/debDataMaker/interface/CMSSWTools.hh

 Description:  Helper functions used in derived classes of Data

 Implementation:
 
*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Tools.hh,v 1.1 2009/06/19 08:40:24 aranyi Exp $
//
//
//-----------------------------------------------------------------------------

namespace deb {

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

  bool findDecayLink(
    std::vector<const reco::Candidate*> genParticles,
    unsigned int firstIdx,
    unsigned int secondIdx){
  
    unsigned int idx=0;
    std::vector<const reco::Candidate *>::const_iterator found;
  
      idx = firstIdx;
  
      while (genParticles[idx]->numberOfMothers()!=0){
  
	found = find(genParticles.begin(), genParticles.end(), 
	    genParticles[idx]->mother(0));
	    if(found != genParticles.end()) 
	      idx = found - genParticles.begin(); 
  
	if (idx==secondIdx)
	  return true;
      }
      return false;
  }

}
//-----------------------------------------------------------------------------
#endif
