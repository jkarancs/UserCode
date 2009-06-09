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

      selectionTypes_:
         is a map that translates the string of SelectionType to an integer

*/
//
// Original Author:  Anita KAPUSI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: EventData.hh,v 1.3 2009/06/05 19:36:38 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include <string>
#include <sstream>
#include "CONST.hh"

namespace deb {

  class EventData {
  public:
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
    int pass; // each bit tells if event passes a selection (1) or not (0)
    int mask; // each pass-bit is masked valid (1) or not (0)

    EventData() {
      clear();
      selectionTypes_["None"]=None; // Did not pass any of the selections:
      selectionTypes_["RefAna4JetMetMuon"]=RefAna4JetMetMuon;
      selectionTypes_["RefAna4JetMetElectron"]=RefAna4JetMetElectron;
    }
    ~EventData() { }

    enum EventSelectionType {
      None=PASS_VALIDITY,
      RefAna4JetMetMuon,
      RefAna4JetMetElectron
    };

    std::map<std::string, int> selectionTypes_;

    void clear() {
      run=NOVAL_I;
      ev=NOVAL_I;
      genevprocid=NOVAL_I;
      procidx=NOVAL_I;
      w=NOVAL_F;
      pass=0; // bit VALID is not used, set to 0
      mask=0; // mask out everything
    }
    
    std::string list(std::string prefix="") {
      std::ostringstream ss;
      ss << prefix << "run/I:";
      ss << prefix << "ev/I:";
      ss << prefix << "genevprocid/I:";
      ss << prefix << "procidx/I:";
      ss << prefix << "w/F:";
      ss << prefix << "pass/I:";
      ss << prefix << "mask/I";
      return ss.str();
    }

  };

}
#endif
