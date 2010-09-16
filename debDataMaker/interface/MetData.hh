#ifndef SusyAnalysis_debDataMaker_MetData_hh_
#define SusyAnalysis_debDataMaker_MetData_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      MetData
// 
/**\class MetData MetData.hh SusyAnalysis/debDataMaker/interface/MetData.hh

 Description: <one line class summary>

 Implementation:

      void clear()
         that sets all the variables to a default value 
	 (NOVAL_X where X= I,F,D)

      std::string list(std::string prefix=""):
         makes a list of the variables for a TTree::Branch() definition

      int MetCorrTypeMap[std::string corr]; // 0,1,2,...
         returns a uniqe id of the correction type. This id is defined here

      bool isPatCorrType(int type);
         tells if a certain id pertains to one of the PAT correction types

  
   !!! WARNING !!!
      if by any chance an 'eta' parameter is defined in the future, the
      template specifications in DeltaR.hh (and similar classes) are going to
      be unecessary, don't forget to delete them. Otherwise, it would be really
      stupid to define an eta parameter for a transverse measurable, if one
      wants to model a neutrino, a separate class should be created for it.

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: MetData.hh,v 1.3.2.2 2010/09/16 09:03:24 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include <string>
#include <sstream>
#include "CONST.hh"
#include <map>

namespace deb {

  std::pair<std::string, int> _MetCorrTypes_[] = {
    std::pair<std::string, int>(NOVAL_S, NOVAL_I),
    std::pair<std::string, int>("uncorrALL", FROM_PAT*1000+0),
    std::pair<std::string, int>("uncorrJES", FROM_PAT*1000+1),
    std::pair<std::string, int>("uncorrMUON", FROM_PAT*1000+2),
    std::pair<std::string, int>("uncorrMAXN", FROM_PAT*1000+3),
    std::pair<std::string, int>("DEFAULT", 9999)
  };

  std::map<std::string, int> MetCorrTypeMap(_MetCorrTypes_, 
	   _MetCorrTypes_+sizeof(_MetCorrTypes_)/sizeof(_MetCorrTypes_[0]));


  class MetData {
  public:
    MetData() { }
    ~MetData() { }

    float et;
    float phi;
    float sumet;
    int corr;   // correction type

    void clear() {
      et=NOVAL_F;
      phi=NOVAL_F;
      sumet=NOVAL_F;
      corr=NOVAL_I;
    }

    std::string list(std::string prefix="") {
      std::ostringstream ss;
      ss << prefix << "et/F:";
      ss << prefix << "phi/F:";
      ss << prefix << "sumet/F:";
      ss << prefix << "corr/I";
      return ss.str();
    }

    inline bool hasPatCorrType() { 
      if (corr/1000%10==FROM_PAT) return true; else return false; 
    }

  };

}
#endif
