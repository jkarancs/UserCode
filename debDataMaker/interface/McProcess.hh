#ifndef SusyAnalysis_debDataMaker_McProcess_hh_
#define SusyAnalysis_debDataMaker_McProcess_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      McProcess
// 
/**\class McProcess McProcess.hh 
		SusyAnalysis/debDataMaker/interface/McProcess.hh

 Description:     

      
 Usage:


    example:               Mo
                         /   \
                       Da1  Da2
                       / \    \
                     Da3 Da4  Da5

    transforms to:   Mo->Da1,Da2
                     Da1->Da3,Da4
                     Da2->Da5


    in ".py" file:
      mcProcessConfig = cms.PSet(
	mcProcessTag = cms.InputTag("genParticles","","HLT"),
	processTree  = cms.vstring(
	  'Mo(pdgId,pdgId,...),Da1(pdgId,pdgId,...),Da2(pdgId,pdgId,...)',
	  'Da1(pdgId,pdgId,...),Da3(pdgId,pdgId,...),Da4(pdgId,pdgId,...)',
	  'Da2(pdgId,pdgId,...),Da5(pdgId,...,pdgId,...)'
        )
      )
   _________________________________________________________________________
  |                                                                         |
  | Particles with the same pdgId have to be written one after the other!!! |
  |        'pi0(111),e-(11),gamma(22),e+(-11)'   INCORRECT                  |
  |        'pi0(111),gamma(22),e-(11),e+(-11)'   CORRECT                    |
  |        'pi0(111),e-(11),e+(-11),gamma(22)'   CORRECT (cause the same)   |
  |_________________________________________________________________________|

    in ".cc" file:

      proc.clear();
      int a;                           //Number of processes found
      int b;
      a=proc.findProcess(iEvent);
      if (b<=a ){
        proc.set(iEvent,b);           //set the b. process
        proc.print(3);
      }


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
// $Id: McProcess.hh,v 1.12 2009/07/14 13:20:27 aranyi Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/MContainer.hh"
#include "SusyAnalysis/debDataMaker/interface/McParticleData.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<int N> class McProcess : 
public MContainer<std::string,McParticleData<N> >{

 public:
	 
  McProcess(std::string name="") : 
    MContainer<std::string,McParticleData<N> >(name) { }

  McProcess(std::string name, std::vector<std::string> storeList) 
    : MContainer<std::string, McParticleData<N> >(name, storeList) { }
  ~McProcess() { }
        
  inline McParticleData<N>& McParticle(std::string particleName) 
    { return *(*this)(particleName); }  
                                                        

  // Inherited functions to be overloaded

  void calculate ();
  int passed(std::string selection);


};
  
//-------------------------------- calculate() --------------------------------

template<int N> void McProcess<N>::calculate () { 
}
  
//--------------------------------- passed() ----------------------------------

template<int N> int McProcess<N>::passed(std::string selection) { 
return 1;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
