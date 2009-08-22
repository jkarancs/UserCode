#ifndef SusyAnalysis_debDataMaker_McParticle_hh_
#define SusyAnalysis_debDataMaker_McParticle_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      McParticle
// 
/**\class McParticle McParticle.hh 
		SusyAnalysis/debDataMaker/interface/McParticle.hh

 Description:


 Implementation:

   List of parameters to steer the object with (passed in iConfig):
      edm::InputTag triggerResults_,       : owned by this class
      std::vector<std::string> pathNames_, : owned by this class    

   iConfig is passed only through the contructor. 

   !!!! See usage of inherited functions in Data.hh source code !!!!

   The following fuctions should be overloaded here according to the exact 
   definition of D in Data<D> :

      void set(const edm::Trigger&) (virtual):
         that implements reading variables of D from the CMSSW framework

      void calculate() (virtual):
         that calculates values that depend on other data models

      int passed(std::string selection) (virtual):
         if selectionType is set, returns the result of the selections. The
         selections are implemented in this function.

*/
//
// Original Author:  Attila ARANYI
//         Created:  Wed Jun 03 10:28:26 CET 2009
// $Id: McParticle.hh,v 1.2 2009/07/28 01:16:58 aranyi Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/VContainer.hh"
#include "SusyAnalysis/debDataMaker/interface/McParticleData.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<int N> class McParticle : 
public VContainer<McParticleData<N> >{

 public:

  McParticle(std::string name="") : VContainer<McParticleData<N> >(name) { }
  McParticle(std::string name, size_t storeNObjects) 
    : VContainer<McParticleData<N> >(name, storeNObjects) { }
  ~McParticle() { }

  inline McParticleData<N>& mcParticle(size_t i) { return *(*this)(i); }

  // Inherited functions to be overloaded

  int passed(std::string selection,unsigned int i);

};
 
  
//--------------------------------- passed() ----------------------------------

template<int N> int McParticle<N>::passed(std::string selection,
  unsigned int i) { 

  if (!McParticle<N>::isValid()) return NOVAL_I;

  if (selection.compare("Origin")==0){
    if (mcParticle(i).orig==-1)
      return 0;
    if (mcParticle(i).orig>=0)
      return 1;  
  }

  return NOVAL_I;

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
