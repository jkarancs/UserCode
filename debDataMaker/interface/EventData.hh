#ifndef SusyAnalysis_debDataMaker_EventData_hh_
#define SusyAnalysis_debDataMaker_EventData_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      EventData
// 
/**\class EventData EventData.hh SusyAnalysis/debDataMaker/interface/EventData.hh

 Description: <one line class summary>

 Implementation:

      void clear()
         that sets all the variables to a default value 
	 (NOVAL_X where X= I,F,D)

      std::string list(std::string prefix=""):
         makes a list of the variables for a TTree::Branch() definition

*/
//
// Original Author:  Anita KAPUSI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: EventData.hh,v 1.5.2.2 2010/09/16 09:03:24 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include <string>
#include <sstream>
#include "CONST.hh"

namespace deb {

  class EventData {
  public:
    EventData() { }
    ~EventData() { }

    int run;
    int ev;
    int genevprocid;                      //genEvent process id
    int procidx;                          // LM0: 0
                                          // LM1: 1
                                          // LM2: 2
                                          // LM3: 3
                                          // LM4: 4
                                          // LM5: 5
                                          // LM6: 6
                                          // LM7: 7
                                          // LM8: 8
                                          // LM9: 9
                                          // W+Jet: 10
                                          // TTbar+Jet: 20
                                          // Z+Jet: 30
                                          // QCD: 40
    float w;
       
    void clear() {
      run=NOVAL_I;
      ev=NOVAL_I;
      genevprocid=NOVAL_I;
      procidx=NOVAL_I;
      w=NOVAL_F;
    }
    
    std::string list(std::string prefix="") {
      std::ostringstream ss;
      ss << prefix << "run/I:";
      ss << prefix << "ev/I:";
      ss << prefix << "genevprocid/I:";
      ss << prefix << "procidx/I:";
      ss << prefix << "w/F";
      return ss.str();
    }

  };

}
#endif
