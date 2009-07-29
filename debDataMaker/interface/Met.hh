#ifndef SusyAnalysis_debDataMaker_Met_hh_
#define SusyAnalysis_debDataMaker_Met_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Met
// 
/**\class Met Met.hh SusyAnalysis/debDataMaker/interface/Met.hh

 Description: <one line class summary>

 Implementation:

   !!!! See usage of inherited functions in Data.hh source code !!!!

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Met.hh,v 1.8 2009/07/17 13:18:10 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/MContainer.hh"
#include "SusyAnalysis/debDataMaker/interface/MetData.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

class Met : public MContainer<std::string,MetData> {
 public:
  Met(std::string name="") : MContainer<std::string,MetData>(name) { }
  Met(std::string name, std::vector<std::string> storeList)
    : MContainer<std::string, MetData>(name, storeList) { }
  ~Met() { }

  inline MetData& met(std::string corr) { return *(*this)(corr); }

  inline std::vector<std::string> getCorrections() { return getKeys(); }

  // Inherited functions to be overloaded
  void calculate () { };

 private:
  using MContainer<std::string,MetData>::passed;
  using MContainer<std::string,MetData>::select;

};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
