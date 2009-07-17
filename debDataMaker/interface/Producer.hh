#ifndef SusyAnalysis_debDataMaker_Producer_hh_
#define SusyAnalysis_debDataMaker_Producer_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Producer
// 
/**\class Producer Producer.hh SusyAnalysis/debDataMaker/interface/Producer.hh

 Description: <one line class summary>

 Implementation:

   protected 'size_'
      number of valid objects stored, only accessible from the inheriting 
      classes (should not be needed though), no setter should be defined!!!

   private 'valid_'
      shows if an object is valid for use. For example, if a mandatory
      parameter is missing from the consturctor, valid_ should be set to false

   Functions of Producer<D> used by inheriting classes:

    - Protected, should be used in the context of the set() function in the
      constructor of the daughter class:

      setTag(edm::InputTag tag):
         sets the InputTag for accessing data in CMSSW

      setSelectionType(std:string selection):
         apply any data selection on this Producer<D> or not. The actual selection
	 is applied when function select() is called (see description there)

    - Public:

      unsigned int storeNObjects(): returns the number of D elements saved on
         file (e.g. TTree is implemented). This means that the size of the
         container should never be less than this number.

      unsigned int max_size():
         returns the size of the Producer<D> container. This is should be
	 at least storeNObjects_ at any moment, but can be more depending on
	 how many D there is in the input data

      unsigned int size():
         returns the number of valid (used) D elements in Producer<D> between 0 and
	 max_size(). The value size() is smaller than max_size() exactly when
	 max_size()==storeNObjects. In this case the elements between size()
	 and max_size() should be padded with void objects (in order to have
	 something to write in the correcponding TTree branches)

      tag():
         returns edm::InputTag tag

      D* data(unsigned int i=0):
         returns a pointer to the i^th D element in Producer<D> (NO BOUNDARY 
	 CHECK)

      D& operator [](unsigned int i):
         returns a reference to the i^th D element in Producer<D> (UNCHECKED)

      D& operator ()(unsigned int i):
         returns a reference to the i^th D element in Producer<D> (UNCHECKED)

      addBranch(TTree* tree, std::string name):
         creates a branch in tree for each D element in Producer<D> with a 
         name in the format: 'name[i]' where 'i' is 0,1,...,max_size()

      setBranch():
         should be called before filling TTree* tree, if a branch was added 
	 to the tree with addBranch(). Since Producer<D> stores every D in a 
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
         used inside addBranch(). Returns the variable string that defines 
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

     void print(int verbose=0):
         prints out the variables of Producer<D> and the content of each D 
	 depending on the level of verbosity. (verbose=0,1,2,3)

   NEED TO BE OVERLOADED after defining the data structure D:

      set(const edm::Event& iEvent):
         loading variables into Producer<D> from iEvent, must be implemented 
         in daughter class after specifying T

      calculate():
         calculates values in D that depend on other data models

      int passed(std::string selection, unsigned int i) (virtual):
         returns the result of selection for the i^th element of Producer<D>. 
	 The selection itself is implemented after Producer<D> is specified.

  
      Note:      
         D& operator ()(unsigned int) and addBranch(TTree* tree, std::string)
         may also need to be overloaded for derived classes which mix data
         types (etc. DeltaR.hh)
 
*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Producer.hh,v 1.1 2009/07/16 17:15:24 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/Container.hh"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/Framework/interface/Event.h"

namespace deb {

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template <class C> class Producer : public C {
public:
  Producer(edm::InputTag tag, std::string name="") : C(name), tag_(tag) { }
  Producer(edm::InputTag tag, std::string name, size_t storeNObjects) 
    : C(name, storeNObjects), tag_(tag) { }
  Producer(edm::InputTag tag, std::string name, std::vector<std::string> list) 
    : C(name, list), tag_(tag) { }
  
  virtual ~Producer() { }
  
 private:
  edm::InputTag tag_;                   // objectTag

 public:
  inline edm::InputTag tag() { return tag_; }

  //
  // functions that need to be implemented in derived classes
  // ---------------------------------------------------------
  
  virtual void     set(const edm::Event&) { 
    this->stdWarn("set(): virtual function is not implemented\n");
  }

  virtual void     calculate() { 
    this->stdWarn("calculate(): virtual function is not implemented\n");
  }

  void             calculate_pass();

};

//------------------------ calculate_pass() -----------------------------------

template<class C> void Producer<C>::calculate_pass() {
  if (!this->isValid()) return;
  for (size_t i=0; i<this->size(); i++) {
    this->at(i).pass=0;
    std::map<std::string, int>::const_iterator it;
    for (it=this->at(i).selectionTypes_.begin();
	 it!=this->at(i).selectionTypes_.end();
	 it++){
      if (it->first.find("VALID")!=std::string::npos) {
	this->at(i).pass|=1<<it->second;
	continue;
      }
      int result=this->passed(it->first, i);
      if (result!=0 && result!=1) {
	this->stdErr("calculate_pass(): selection %s on element %d returned " \
		     "value %d", it->first.data(), i, result);
	this->stdErr("...is it implemented? ...are all the parameters "	\
		     "required for this selection computed by the time " \
		     "calculate_pass is called?\n");
	this->print(3);
	this->at(i).pass=0;
	return;
      }
      this->at(i).pass|=result<<it->second;
    }
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
