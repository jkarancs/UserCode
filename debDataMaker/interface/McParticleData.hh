#ifndef SusyAnalysis_debDataMaker_McParticleData_hh_
#define SusyAnalysis_debDataMaker_McParticleData_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      ParticleData
// 
/**\class McParticleData McParticleData.hh SusyAnalysis/debDataMaker/interface/McParticleData.hh

 Description: <one line class summary>

 Implementation:

      void clear()
         that sets all the variables to a default value 
	 (NOVAL_X where X= I,F,D)

      std::string list(std::string prefix=""):
         makes a list of the variables for a TTree::Branch() definition

*/
//
// Original Author:  Attila ARANYI
//         Created:  Wed Jun 03 10:28:26 CET 2009
// $Id: McParticleData.hh,v 1.1 2009/06/14 05:10:15 aranyi Exp $
//
//
//-----------------------------------------------------------------------------

#include <string>
#include <sstream>
#include "CONST.hh"

namespace deb {

template <int N>
  class McParticleData {
  public: 
          
    McParticleData() {clear();}
    ~McParticleData() { }

    float e;
    float px;
    float py;
    float pz;
    float m;
    float p;
    float et;
    float pt;
    float phi;
    float eta;
    
    int mo1;
    int mo2;
    int da[N];
    int pdg;

    void clear() {
      e=NOVAL_F;
      px=NOVAL_F;
      py=NOVAL_F;
      pz=NOVAL_F;
      m=NOVAL_F;
      p=NOVAL_F;
      et=NOVAL_F;
      pt=NOVAL_F;
      phi=NOVAL_F;
      eta=NOVAL_F;

      
      mo1=NOVAL_I;
      mo2=NOVAL_I;
      for(unsigned int i=0;i<N;++i){
        da[i]=NOVAL_I;
      }
      pdg=NOVAL_I;
    }
    
    std::string list(std::string prefix="") {
      std::ostringstream ss;
      ss << prefix << "e/F:";
      ss << prefix << "px/F:";
      ss << prefix << "py/F:";
      ss << prefix << "pz/F:";
      ss << prefix << "m/F:";
      ss << prefix << "p/F:";
      ss << prefix << "et/F:";
      ss << prefix << "pt/F:";
      ss << prefix << "phi/F:";
      ss << prefix << "eta/F:";

      ss << prefix << "mo1/I:";
      ss << prefix << "mo2/I:";
      ss << prefix << "da["<<N<<"]/I:";
      ss << prefix << "pdg/I";
      return ss.str();
    }

  };

}
#endif
