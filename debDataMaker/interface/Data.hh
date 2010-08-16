#ifndef SusyAnalysis_debDataMaker_Data_hh_
#define SusyAnalysis_debDataMaker_Data_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Data
// 
/**\class Data Data.hh SusyAnalysis/debDataMaker/interface/Data.hh

 Description: base class for object data

 Implementation:

      int oid : unique object id, the serial number of the object in the 
                original input data (e.g. CMSSW file) after sorting the 
		collection, must be filled in the object collection's set()
		function

      int eid : unique event id, which is filled (if filled) from the
                Container's event counter (has to be incremented in the object
		collection's set() function)

      void clear()
         sets all the variables to a default value 
	 (NOVAL_X where X= I,F,D)

      std::string list(std::string prefix=""):
         makes a list of the variables for a TTree::Branch() definition

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id$
//
//
//-----------------------------------------------------------------------------

#include <string>
#include <sstream>
#include "CONST.hh"

namespace deb {

  class Data {
  public:
    int oid; 
    int eid;

    Data() { clear(); }
    ~Data() { }

    void clear() {
      oid=NOVAL_I;
      eid=NOVAL_I;
    }

    std::string list(std::string prefix="") {
      std::ostringstream ss;
      ss << prefix << "oid/I";
      ss << prefix << ":eid/I";
      return ss.str();
    }

  };

}

//-----------------------------------------------------------------------------
#endif
