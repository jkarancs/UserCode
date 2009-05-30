#ifndef SusyAnalysis_debDataMaker_Data_hh_
#define SusyAnalysis_debDataMaker_Data_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Data
// 
/**\class Data Data.hh SusyAnalysis/debDataMaker/interface/Data.hh

 Description: <one line class summary>

 Implementation:

   protected 'size_'
      number of valid objects stored, only accessible from the inheriting 
      classes, no setter should be defined!!!

   private 'valid_'
      shows if an object is valid for use. For example, if a mandatory
      parameter is missing from the consturctor, valid_ should be set to false

   Functions of Data<D> used by inheriting classes:

    - Protected, should be used in the context of the set() function in the
      constructor of the daughter class:

      setTag(edm::InputTag tag):
         sets the InputTag for accessing data in CMSSW

      setSelectionType(int type=1):
         apply any data selection on this Data<D> or not. 0 means no 
         selection, 1,2,... are the serial numbers of possible selections.

    - Public:

      unsigned int max_size():
         returns the maximum number of D elements in Data<D>

      unsigned int size():
         returns the number of valid (used) D elements in Data<D>

      tag():
         returns edm::InputTag tag

      D* data(unsigned int i=0):
         returns a pointer to the i^th D element in Data<D> (NO BOUNDARY 
	 CHECK)

      D& operator [](unsigned int i):
         returns a reference to the i^th D element in Data<D> (UNCHECKED)

      D& operator ()(unsigned int i):
         returns a reference to the i^th D element in Data<D> (UNCHECKED)

      addBranch(TTree* tree, std::string name):
         creates a branch in tree for each D element in Data<D> with a 
         name in the format: 'name[i]' where 'i' is 0,1,...,max_size()

      stdMesg() and stdErr():
         sends messages to the standard output, use it as printf()

      getSelectionType():
         returns result of last calling getSelectionType()

      clear():
         zeroes size(), setting variables to 'deb::NOVAL_X' in Data<D> 
         needs to be implemented in the class definition of D
      
      std::string list(std::string prefix="") (virtual):
         used inside addBranch(). Returns the variable string that defines the
         variable names in the branches of the tree. This must be implemented 
         in class D after actually declaring the variables in D following
	 the EXACT SAME ORDER.

      void setValid(bool):
         sets the validity of an object

      bool isValid():
         returns the value of valid_
  
   NEED TO BE OVERLOADED after defining the data structure D:

      set(const edm::Event& iEvent):
         loading variables into Data<D> from iEvent, must be implemented 
         in daughter class after specifying T

      calculate():
         calculates values in D that depend on other data models

      int passed(int i) (virtual):
         if setSelectionType() is set, returns the result of the selections for
	 the i^th element of Data<D>. The selection itself is implemented
         after Data<D> is specified.

  
      Note:      
         D& operator ()(unsigned int) and addBranch(TTree* tree, std::string)
         may also need to be overloaded for derived classes which mix data
         types (etc. DeltaR.hh)
 
*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id$
//
//
//-----------------------------------------------------------------------------

#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/Framework/interface/Event.h"
#include "TTree.h"
#include "CONST.hh"

namespace deb {

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template <class D> class Data {
 public:
  Data() {
    stdErr("data size unspecified, object will be invalid\n");
    init(int(1));
    setValid(false);
  }

  Data(int max_size) { init(max_size); }

  virtual ~Data() { }
  
 private:
  void init(int max_size){
    max_size_=max_size;
    if (max_size_<1) {
      stdErr("incorrect data size, object will be invalid\n");
      init(int(1));
      setValid(false);
      return;
    }
    data_=new D[max_size_];
    //data_.reserve(max_size_);
    //if (data_.capacity()!=max_size_)
    if (data_==NULL) {
      stdErr("unsuccesful memory allocation for %s\n", typeid(D).name());
      setValid(false);
      return;
    }
    selectionType_=NOVAL_S;
    edm::InputTag tag; 
    tag_=tag;
    clear();
    setValid(true);
  }

 private:
  unsigned int max_size_; // storeNObjects
  //std::vector<D> data_;
  D* data_;
  std::string selectionType_; // 1, 2,... variants of data selection.
  edm::InputTag tag_; // objectTag
  bool valid_;

 protected:
  unsigned int size_;
  void setTag(edm::InputTag tag) { tag_=tag; }
  void setSelectionType(std::string type) { selectionType_=type; }

 public:
  //
  // functions that need to be implemented in daughter class
  // ---------------------------------------------------------

  virtual void set(const edm::Event&) { }

  virtual void calculate() { }

  virtual int passed(std::string) {
    return NOVAL_I;
  }


  //
  // ---------------------------------------------------------

  edm::InputTag tag() { return tag_; }
  unsigned int max_size() { return max_size_; }
  unsigned int size() { return size_; }
  D& operator [](unsigned int i) { return data_[i]; } // array style
  D& operator ()(unsigned int i) { return data_[i]; } // accessor style
  D* data(unsigned int i=0) { return data_+i; }
  //D* data(unsigned int i=0) { return &data_[i]; }

  void clear() {
    size_=0;
    for (unsigned int i=0; i<max_size_; i++) data(i)->clear();
  }

  void addBranch(TTree* tree, std::string name) {
    if (!isValid()) {
      stdErr("Object is not valid, cannot add it to tree\n");
      return;
    }
    for (unsigned int i=0; i<max_size_; i++) {
      std::ostringstream ss;
      ss<<name<<"_"<<i;
      tree->Branch(ss.str().data(), data(i), data(i)->list().data());
    }
  }

  void stdErr(std::string mesg, ...) {
    va_list argList;
    va_start(argList, mesg);
    char s[256];
    vsprintf(s, mesg.data(), argList);
    va_end(argList);
    mesg=s;
    std::string dataType=typeid(D).name();
    std::string label=tag().label();
    std::cerr<<"*** ERROR: "<<dataType<<"("<<label<<")::"<<mesg<<std::endl;
  }

  void stdWarn(std::string mesg, ...) {
    va_list argList;
    va_start(argList, mesg);
    char s[256];
    vsprintf(s, mesg.data(), argList);
    va_end(argList);
    mesg=s;
    std::string dataType=typeid(D).name();
    std::string label=tag().label();
    std::cout<<"*** WARNING: "<<dataType<<"("<<label<<")::"<<mesg<<std::endl;
  }

  void stdMesg(std::string mesg, ...) {
    va_list argList;
    va_start(argList, mesg);
    char s[256];
    vsprintf(s, mesg.data(), argList);
    va_end(argList);
    mesg=s;
    std::string dataType=typeid(D).name();
    std::string label=tag().label();
    std::cout<<dataType<<"("<<label<<")::"<<mesg<<std::endl;
  }

  std::string getSelectionType() { return selectionType_; }

  void setValid(bool choice) { valid_=choice; }
  bool isValid() { return valid_; }
};


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// Helper functions used in daughter classes of Data

template<class T> bool isContext(std::string context) {
  if (strstr(typeid(T).name(), context.data())!=NULL) return true;
  return false;
}

template<class T> std::string humanTypeId() {
  std::string id = typeid(T).name();
  return id;
}


}
#endif
