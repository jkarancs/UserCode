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
      classes (should not be needed though), no setter should be defined!!!

   private 'valid_'
      shows if an object is valid for use. For example, if a mandatory
      parameter is missing from the consturctor, valid_ should be set to false

   Functions of Data<D> used by inheriting classes:

    - Protected, should be used in the context of the set() function in the
      constructor of the daughter class:

      setTag(edm::InputTag tag):
         sets the InputTag for accessing data in CMSSW

      setSelectionType(std:string selection):
         apply any data selection on this Data<D> or not. The actual selection
	 is applied when function select() is called (see description there)

    - Public:

      unsigned int storeNObjects(): returns the number of D elements saved on
         file (e.g. TTree is implemented). This means that the size of the
         container should never be less than this number.

      unsigned int max_size():
         returns the size of the Data<D> container. This is should be
	 at least storeNObjects_ at any moment, but can be more depending on
	 how many D there is in the input data

      unsigned int size():
         returns the number of valid (used) D elements in Data<D> between 0 and
	 max_size(). The value size() is smaller than max_size() exactly when
	 max_size()==storeNObjects. In this case the elements between size()
	 and max_size() should be padded with void objects (in order to have
	 something to write in the correcponding TTree branches)

      tag():
         returns edm::InputTag tag

      D* data(unsigned int i=0):
         returns a pointer to the i^th D element in Data<D> (NO BOUNDARY 
	 CHECK)

      D& operator [](unsigned int i):
         returns a reference to the i^th D element in Data<D> (UNCHECKED)

      D& operator ()(unsigned int i):
         returns a reference to the i^th D element in Data<D> (UNCHECKED)

      addBranches(TTree* tree, std::string name):
         creates a branch in tree for each D element in Data<D> with a 
         name in the format: 'name[i]' where 'i' is 0,1,...,max_size()

      setBranches():
         should be called before filling TTree* tree, if a branch was added 
	 to the tree with addBranches(). Since Data<D> stores every D in a 
	 vector, there is no guarantee that their location does not change 
	 during event processing. SetBranches() fixes this problem. 

      stdMesg() and stdErr():
         sends messages to the standard output, use it as printf()

      getSelectionType():
         returns result of last calling getSelectionType()

      clear():
         zeroes size(), and allocates storeNObjects_ number of D in the
	 container vector. Each element is initialized to 'deb::NOVAL_X' 
	 by calling the clear() function implemented in the declaration of 
	 each class D.
      
      std::string list(std::string prefix="") (virtual):
         used inside addBranches(). Returns the variable string that defines 
	 the variable names in the branches of the tree. This must be 
         implemented in class D after actually declaring the variables in D 
	 following the EXACT SAME ORDER.

      void setValid(bool):
         sets the validity (valid_) of an object

      bool isValid():
         returns the value of valid_
  
      void calculate_pass():
         sets the value of the variable 'pass' in data structure D. If the bit
         at PASS_VALIDITY in pass is not set (1), the other bits are to be 
	 ignored. Otherwise, the other 31-PASS_VALIDITY bits store the results
	 of the selections listed in selectionTypes_ and implemented in 
	 int passed(string,int)

      void select():
         if a valid selection is set in selectionType_, uppon calling, select()
	 will drop all objects from the container that do not pass the
	 selection (i.e. this->pass(selectionType_==0) ). If size() falls under
	 storeNObjects_, the difference will be padded by void objects.


   NEED TO BE OVERLOADED after defining the data structure D:

      set(const edm::Event& iEvent):
         loading variables into Data<D> from iEvent, must be implemented 
         in daughter class after specifying T

      calculate():
         calculates values in D that depend on other data models

      int passed(std::string selection, unsigned int i) (virtual):
         returns the result of selection for the i^th element of Data<D>. The 
	 selection itself is implemented after Data<D> is specified.

  
      Note:      
         D& operator ()(unsigned int) and addBranch(TTree* tree, std::string)
         may also need to be overloaded for derived classes which mix data
         types (etc. DeltaR.hh)
 
*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Data.hh,v 1.3 2009/06/04 07:14:46 veszpv Exp $
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
    storeNObjects_=max_size;
    if (storeNObjects_<1) {
      stdErr("incorrect data size, object will be invalid\n");
      init(int(1));
      setValid(false);
      return;
    }
    selectionType_=NOVAL_S;
    edm::InputTag tag; 
    tag_=tag;
    branch_="";
    tree_=NULL;
    setValid(true);
    clear();
  }

 private:
  std::vector<D> data_;                 // contained for data D-s
  //D* data_;
  std::string selectionType_;           // 1, 2,... variants of data selection.
  edm::InputTag tag_;                   // objectTag
  bool valid_;                          // tells if object is valid
  unsigned int storeNObjects_;          // storeNObjects after calling select()
  std::string branch_;                  // branch name if saved to tree
  TTree* tree_;                         // pointer to tree if being saved there

 protected:
  unsigned int size_;
  //inline std::vector<D>& data() { return data_; }
  void setTag(edm::InputTag tag) { tag_=tag; }
  void setSelectionType(std::string type) { selectionType_=type; }

 public:
  //
  // functions that need to be implemented in daughter class
  // ---------------------------------------------------------

  virtual void set(const edm::Event&) { }
  virtual void calculate() { }
  virtual int passed(std::string, unsigned int i) {
    return NOVAL_I;
  }


  //
  // ---------------------------------------------------------

  inline edm::InputTag tag() { return tag_; }
  inline unsigned int max_size() { return data_.size(); }
  inline unsigned int storeNObjects() { return storeNObjects_; }
  inline unsigned int size() { return size_; }
  inline D& operator [](unsigned int i) { return data_[i]; } // array style
  inline D& operator ()(unsigned int i) { return data_[i]; } // accessor style
  //D* data(unsigned int i=0) { return data_+i; }
  inline D* data(unsigned int i) { return &data_[i]; }

  inline void clear() {
    size_=0;
    data_.clear();
    D d;
    d.clear();
    data_.resize(storeNObjects_, d);
    if (data_.size()!=storeNObjects_) {
      stdErr("unsuccesful memory allocation for %s\n", typeid(D).name());
      setValid(false);
    }
  }

  void push_back(const D& d) {
    if (size_<data_.size()) {
      data_[size_]=d;
    } else {
      data_.push_back(d);
    }
    size_++;
  }

  void addBranches(TTree* tree, std::string name) {
    if (!isValid()) {
      stdErr("addBranches(): Object is not valid, cannot add it to tree\n");
      return;
    }
    if (tree_!=NULL) {
      stdWarn("addBranches(): Object is already added to a tree.\n");
      return;
    }
    branch_=name;
    tree_=tree;
    for (unsigned int i=0; i<storeNObjects_; i++) {
      std::ostringstream ss;
      ss<<branch_<<"_"<<i;
      tree_->Branch(ss.str().data(), data(i), data(i)->list().data());
    }
  }

  void setBranches() {
    if (!isValid()) {
      stdErr("setBranches(): Object is not valid, can't fill its branches.\n");
      return;
    }
    if (tree_==NULL) {
      stdErr("setBranches(): Object hasn't been added to tree. "	\
	     "(Do it in the constructor!)\n");
      return;
    }
    for (unsigned int i=0; i<storeNObjects_; i++) {
      std::ostringstream ss;
      ss<<branch_<<"_"<<i;
      TBranch* br=tree_->GetBranch(ss.str().data());
      if (br!=NULL) br->SetAddress(data(i));
      else stdErr("setBranches(): Did not find branch %s in tree!!!\n", 
		  ss.str().data());
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

  void calculate_pass() {
    if (!isValid()) return;
    for (unsigned int i=0; i<size(); i++) {
      data(i)->pass=0;
      std::map<std::string, int>::const_iterator it;
      for (it=data(i)->selectionTypes_.begin();
           it!=data(i)->selectionTypes_.end();
           it++){
	if (it->first.find("VALID")!=std::string::npos) {
	  data(i)->pass|=1<<it->second;
	  continue;
	}
	int result=passed(it->first, i);
	if (result!=0 && result!=1) {
	  stdErr("calculate_pass(): selection %s on element %d returned " \
		 "value %d", it->first.data(), i, result);
	  stdErr("...is it implemented? ...are all the parameters required" \
		 " for this selection computed by the time calculate"	\
		 "_pass is called?\n");
	  data(i)->pass=0;
	  return;
	}
        data(i)->pass|=result<<it->second;
      }
    }
  }

  void select() {
    if (!isValid()) return;
    if (data(0)->selectionTypes_.find(selectionType_) ==
	data(0)->selectionTypes_.end()) {
      stdErr("select(): selection type %s is not set correctly, call "\
	     "setSelectionType(string) preferably in the constructor\n",
	     selectionType_.data());
      return;
    }
    for (int i=0; i<(int)size_; i++) { // erase elements not passing selection
      if (passed(selectionType_, i)!=0) continue; 
      data_.erase(data_.begin()+i);
      --i;
      --size_;
    }
    for (unsigned int i=size_; i<storeNObjects_; i++) {
      D d; // padding space between size_ and storeNObjects_ with void data
      d.clear();
      data_.push_back(d);
    }
  }

};


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// Helper functions used in derived classes of Data

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
