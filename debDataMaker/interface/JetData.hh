#ifndef SusyAnalysis_debDataMaker_JetData_hh_
#define SusyAnalysis_debDataMaker_JetData_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      JetData
// 
/**\class JetData JetData.hh SusyAnalysis/debDataMaker/interface/JetData.hh

 Description: <one line class summary>

 Implementation:

      void clear()
         that sets all the variables to a default value 
	 (NOVAL_X where X= I,F,D)

      std::string list(std::string prefix=""):
         makes a list of the variables for a TTree::Branch() definition

      selectionTypes_:
         is a map that translates the string of SelectionType to an integer

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: JetData.hh,v 1.3 2009/06/05 19:36:38 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include <string>
#include <sstream>
#include "CONST.hh"

namespace deb {

  class JetData {
  public:
    float e;
    float px;
    float py;
    float pz;
    float m;
    float et;
    float pt;
    float phi;
    float eta;
    float hadfrac;
    float emfrac;
    float area;
    int corr;   // correction type
    int pass;

    JetData() {
      clear();
      selectionTypes_["VALID"]=VALID;
      selectionTypes_["RefAna4JetMetMuon"]=RefAna4JetMetMuon;
      selectionTypes_["RefAna4JetMetElectron"]=RefAna4JetMetElectron;
      selectionTypes_["TopJetSelection"]=TopJetSelection;
    }
    ~JetData() { }

    std::map<std::string, int> selectionTypes_;

    enum JetSelectionType {
      VALID=PASS_VALIDITY,
      RefAna4JetMetMuon,
      RefAna4JetMetElectron,
      TopJetSelection
    };

    void clear() {
      e=NOVAL_F;
      px=NOVAL_F;
      py=NOVAL_F;
      pz=NOVAL_F;
      m=NOVAL_F;
      et=NOVAL_F;
      pt=NOVAL_F;
      phi=NOVAL_F;
      eta=NOVAL_F;
      hadfrac=NOVAL_F;
      emfrac=NOVAL_F;
      area=NOVAL_F;
      corr=NOVAL_I;
      pass=0; // set 0 to bit at PASS_VALIDITY (pass is invalid)
    }

    std::string list(std::string prefix="") {
      std::ostringstream ss;
      ss << prefix << "e/F:";
      ss << prefix << "px/F:";
      ss << prefix << "py/F:";
      ss << prefix << "pz/F:";
      ss << prefix << "m/F:";
      ss << prefix << "et/F:";
      ss << prefix << "pt/F:";
      ss << prefix << "phi/F:";
      ss << prefix << "eta/F:";
      ss << prefix << "hadfrac/F:";
      ss << prefix << "emfrac/F:";
      ss << prefix << "area/F:";
      ss << prefix << "corr/I:";
      ss << prefix << "pass/I";
      return ss.str();
    }

  };

}
#endif
