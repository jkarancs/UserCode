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
         sets all the variables to a default value 
	 (NOVAL_X where X= I,F,D)

      std::string list(std::string prefix=""):
         makes a list of the variables for a TTree::Branch() definition

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: JetData.hh,v 1.6 2010/08/09 15:38:09 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include <string>
#include <sstream>
#include "CONST.hh"
#include "Data.hh"

namespace deb {

  class JetData : public Data {
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
    int corr_level;      // level of correction applied on this jet collection
    float corr;          // jet energy correction factor w.r.t raw
    float jesp;          // +1 systematics of energy corr. factor (w.r.t raw)
    float jesm;          // -1 systematics of energy corr. factor (w.r.t raw)

    JetData() { clear(); }
    ~JetData() { }

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
      corr_level=NOVAL_I;
      corr=NOVAL_F;
      jesp=NOVAL_F;
      jesm=NOVAL_F;
    }

    std::string list(std::string prefix="") {
      std::ostringstream ss;
      ss << Data::list(prefix);
      ss << prefix << ":e/F";
      ss << prefix << ":px/F";
      ss << prefix << ":py/F";
      ss << prefix << ":pz/F";
      ss << prefix << ":m/F";
      ss << prefix << ":et/F";
      ss << prefix << ":pt/F";
      ss << prefix << ":phi/F";
      ss << prefix << ":eta/F";
      ss << prefix << ":hadfrac/F";
      ss << prefix << ":emfrac/F";
      ss << prefix << ":area/F";
      ss << prefix << ":corr_level/I";
      ss << prefix << ":corr/F";
      ss << prefix << ":jesp/F";
      ss << prefix << ":jesm/F";
      return ss.str();
    }

  };

}
#endif
