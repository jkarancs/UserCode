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

   The following fuctions should be overloaded here according to the exact 
   definition of D in Container<D> :

      int passed(std::string selection,size_t i) (virtual):
         returns the result of selection. The selections are implemented in 
	 this function.

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Met.hh,v 1.7 2009/06/15 17:19:42 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/Container.hh"
#include "SusyAnalysis/debDataMaker/interface/MetData.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

class Met : private Container<MetData> {
 public:
  Met(std::string name="") : Container<MetData>(name) { init(); }
  Met(std::string name, std::vector<std::string> corrections) 
    : Container<MetData>(name, corrections.size()) { init(corrections); }
  ~Met() { }

  inline MetData& met(size_t i) { return at(i); }

  // Inherited functions to be overloaded
  int passed(std::string, size_t);

  // New variables and functions
 private:
  std::vector<std::string> corrections_; // i -> correction name
  std::map<std::string,int> corrIndex_;  // correction name -> i 

  inline size_t init();
  inline size_t init(std::vector<std::string>);

 public:
  const std::vector<std::string>& getCorrections() { return corrections_; }
  std::string correction(size_t i) { return corrections_[i]; }

  const std::map<std::string,int>& getCorrIndex()  { return corrIndex_; }
  inline int ind(std::string);
  inline std::vector<size_t> ind(std::vector<std::string>);

  // Enable some of the Container functions:
  using Container<MetData>::operator [];
  using Container<MetData>::size;
  using Container<MetData>::operator ();
  using Container<MetData>::data;
  using Container<MetData>::storeNObjects;
  using Container<MetData>::name;
  using Container<MetData>::setName;
  using Container<MetData>::setValid;
  using Container<MetData>::isValid;
  using Container<MetData>::list;

  using Container<MetData>::addBranch;
  using Container<MetData>::setBranch;
  using Container<MetData>::stdErr;
  using Container<MetData>::stdWarn;
  using Container<MetData>::stdMesg;
  using Container<MetData>::print;

  void clear() { for (size_t i=0; i<size(); i++) met(i).clear(); }
  size_t max_size() { return size(); }

};

//--------------------------------- init() ------------------------------------

size_t Met::init() {
  corrections_.clear();
  corrIndex_.clear();
  corrections_.push_back(NOVAL_S);
  corrIndex_[NOVAL_S]=0;
  MetData new_obj;
  push_back(new_obj);
  
  return size();
}

size_t Met::init(std::vector<std::string> corrections) {
  // Check if requested corrections have been implemented
  // and build a map between the correction type and the met(i) index 'i'
  corrections_.clear();
  corrIndex_.clear();
  for (unsigned int i=0; i<corrections.size(); i++) {
    std::map<std::string,int>::const_iterator it;
    it=MetCorrTypeMap.find(corrections[i]);
    if (it==MetCorrTypeMap.end()) {
      stdErr("Correction %s not interpreted. Object will be invalid\n", 
	     corrections[i].data());
      continue;
    }
    corrections_.push_back(corrections[i]);
    corrIndex_[corrections[i]]=i;
    MetData new_obj;
    push_back(new_obj);
  }
  return size();
}

//---------------------------------- ind() ------------------------------------

int Met::ind(std::string corr) {
  std::map<std::string,int>::const_iterator it=corrIndex_.find(corr);
  if (it==corrIndex_.end()) {
    stdErr("Met::ind(%s) correction %s was not requested.\n", 
	   corr.data(), corr.data()); 
    return NOVAL_I;
  }
  stdMesg("Met::ind(%s)=%d", corr.data(), corrIndex_[corr]);
  return it->second;
}


std::vector<size_t> Met::ind(std::vector<std::string> corrs) {
  std::vector<size_t> ret;
  for (size_t i=0; i<corrs.size(); i++) {
    int j=ind(corrs[i]);
    if (j<0) {
      ret.clear();
      break;
    }
    ret.push_back((size_t)(j));
  }
  return ret;
}


//--------------------------------- passed() ----------------------------------

int Met::passed(std::string selection, size_t i) {
  stdWarn("Met::passed(): Met selection is an event selection.");
  return NOVAL_I;
}

  
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
