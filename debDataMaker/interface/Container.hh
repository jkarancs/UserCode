#ifndef SusyAnalysis_debDataMaker_Container_hh_
#define SusyAnalysis_debDataMaker_Container_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Container
// 
/**\class Container Container.hh SusyAnalysis/debDataMaker/interface/Container.hh

 Description: <one line class summary>

 Implementation:

   'valid_'
      shows if an object is valid for use. For example, if a mandatory
      parameter is missing from the consturctor, valid_ should be set to false

   'name_'
      name of the container. This name is used in print-outs and when saving
      container on ROOT::TTree files

   Functions of Container<D> used by derived classes:

      setSelectionType(std:string selection):
         apply any data selection on this Container<D>. The actual selection
	 is applied when function select() is called (see description there)

      size_t storeNObjects(): returns the number of D elements saved on
         file (e.g. TTree is implemented).

      D* data(size_t i=0):
         returns a pointer to the i^th D element in Container<D>

      D& operator ()(size_t i):
         returns a reference to the i^th D element in Container<D>

      addBranch(TTree* tree):
         creates a branch in tree for each D element in Container<D> with a 
         name in the format: 'name_i' where 'i' is 0,1,...,size() and
	 'name' is 'name_', the name of the container

      setBranch():
         should be called before filling TTree* tree, if a branch was added 
	 to the tree with addBranch(). Since Container<D> stores every D in a 
	 vector, there is no guarantee that their location does not change 
	 during event processing. SetBranches() fixes this problem. 

      stdMesg() and stdErr():
         sends messages to the standard output, use it as printf()

      getSelectionType():
         returns selectionType_

      void setValid(bool):
         sets the validity (valid_) of an object

      bool isValid():
         returns the value of valid_
  
      void select():
         if a valid selection is set in selectionType_, uppon calling, select()
	 will drop all objects from the container that do not pass the
	 selection (i.e. this->pass(selectionType_==0) )

     void print(int verbose=0):
         prints out the variables of Container<D> and the content of each D 
	 depending on the level of verbosity. (verbose=0,1,2,3)

   NEED TO BE OVERLOADED after defining the data structure D:

      int passed(std::string selection, size_t i) (virtual):
         returns the result of selection for the i^th element of Container<D>.
	 The selection itself is implemented after Container<D> is specified.
  
      Note:      
         D& operator ()(size_t) and addBranch(TTree* tree, std::string)
         may also need to be overloaded for derived classes which mix data
         types (etc. DeltaR.hh)
 
*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Container.hh,v 1.1 2009/07/16 17:14:59 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "TTree.h"
#include "CONST.hh"
#include "Tools.hh"

namespace deb {

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template <class D> class Container : public std::vector<D> {
 public:
  Container(std::string name="") : name_(name) { init(0); }
  Container(std::string name, size_t storeNObjects) : name_(name) { 
    init(storeNObjects);
  }
  virtual ~Container() { this->clear(); }
  
 private:
  std::string      name_;
  size_t           storeNObjects_;     // storeNObjects after calling select()
  std::string      selectionType_;     // 1, 2,... variants of data selection.
  bool             valid_;             // tells if object is valid
  std::map<std::string,std::pair<char,size_t> > vars_;
  D                objVoid_;

 protected:
  TTree*           tree_;              // pointer to tree if being saved there

 private:
  void             init(size_t);

 public:
  inline D&        operator ()(size_t i) { return this->at(i); }
  inline D*        data(size_t i) { return &this->at(i); }
  inline size_t    storeNObjects() { return storeNObjects_; }
  std::string      name() { return name_; }
  void             setName(const char *name) { name_=name; }
  void             setSelectionType(std::string type) { selectionType_=type; }
  std::string      getSelectionType() { return selectionType_; }
  void             setValid(bool choice) { valid_=choice; }
  bool             isValid() { return valid_; }
  std::string      list(std::string prefix="") { return objVoid_.list(prefix);}

  void             addBranch(TTree*);
  void             setBranch();
  void             stdErr(std::string, ...);
  void             stdWarn(std::string, ...);
  void             stdMesg(std::string, ...);
  void             print(int);
  void             select();

  //
  // functions that need to be implemented in inheriting class
  // ---------------------------------------------------------

  virtual int      passed(std::string, size_t);

};

//--------------------------------- Constructor -------------------------------

template <class D> void Container<D>::init(size_t storeNObjects){
  this->clear();
  storeNObjects_=storeNObjects;
  setSelectionType(NOVAL_S);
  setValid(true);
  vars_=getVariableMap(objVoid_.list());
  tree_=NULL;
}

//--------------------------------- addBranch() -------------------------------

template <class D> void Container<D>::addBranch(TTree* tree){
  if (!isValid()) {
    stdErr("addBranch(): Object is not valid, cannot add it to tree\n");
    return;
  }
  if (tree_!=NULL) {
    stdWarn("addBranch(): Object is already added to a tree.\n");
    return;
  }
  tree_=tree;
  if (storeNObjects_==1) {
    tree_->Branch(name_.data(), &objVoid_, objVoid_.list().data());
    return;
  }
  for (size_t i=0; i<storeNObjects_; i++) {
    std::ostringstream ss;
    ss<<name_<<"_"<<i;
    tree_->Branch(ss.str().data(), &objVoid_, objVoid_.list().data());
  }
}

//--------------------------------- setBranch() -------------------------------

template <class D> void Container<D>::setBranch() {
  if (!isValid()) {
    stdErr("setBranch(): Object is not valid, can't fill its branches.\n");
    return;
  }
  if (tree_==NULL) {
    stdErr("setBranch(): Object hasn't been added to tree. "	\
	   "(Do it in the constructor!)\n");
    return;
  }
  if (storeNObjects_==1) {
    TBranch* br=tree_->GetBranch(name_.data());
    if (br!=NULL) {
      if (this->size()!=0) br->SetAddress(data(0));
      else br->SetAddress(&objVoid_);
    }
    else stdErr("setBranch(): Did not find branch %s in tree!!!\n", 
		name_.data());
    return;
  }
  for (size_t i=0; i<storeNObjects_; i++) {
    std::ostringstream ss;
    ss<<name_<<"_"<<i;
    TBranch* br=tree_->GetBranch(ss.str().data());
    if (br!=NULL) {
      if (i<this->size()) br->SetAddress(data(i));
      else br->SetAddress(&objVoid_);
    }
    else stdErr("setBranch(): Did not find branch %s in tree!!!\n", 
		ss.str().data());
  }
}

//--------------------------------- stdMesg() ---------------------------------
 
template <class D> void Container<D>::stdErr(std::string mesg, ...) {
  va_list argList;
  va_start(argList, mesg);
  char s[256];
  vsprintf(s, mesg.data(), argList);
  va_end(argList);
  mesg=s;
  std::cerr<<"*** ERROR: "<<name_<<"("<<humanTypeId(objVoid_)<<")::"
	   <<mesg<<std::endl;
}

template <class D> void Container<D>::stdWarn(std::string mesg, ...) {
  va_list argList;
  va_start(argList, mesg);
  char s[256];
  vsprintf(s, mesg.data(), argList);
  va_end(argList);
  mesg=s;
  std::cout<<"*** WARNING: "<<name_<<"("<<humanTypeId(objVoid_)<<")::"<<mesg
	   <<std::endl;
}

template <class D> void Container<D>::stdMesg(std::string mesg, ...) {
  va_list argList;
  va_start(argList, mesg);
  char s[256];
  vsprintf(s, mesg.data(), argList);
  va_end(argList);
  mesg=s;
  std::cout<<name_<<"("<<humanTypeId(objVoid_)<<")::"<<mesg<<std::endl;
}

//---------------------------------- print() ----------------------------------

template <class D> void Container<D>::print(int verbose=0) {
  stdMesg("  Number of valid objects in container (size): %d", this->size());
  stdMesg("  Number of objects to be stored (storeNObjects): %d", 
	  storeNObjects());
  stdMesg("  Selection criteria for select() function (selectionType_) : %s",
	  selectionType_.data());
  stdMesg("  List of variables: %s", objVoid_.list().data());
  stdMesg("  Object is %svalid!\n", (isValid() ? "" : "not "));
  if (verbose<1) return;

  if (tree_!=NULL) {
    stdMesg("  Added to tree '%s' as branch '%s_X'", tree_->GetName(), 
	    name_.data());
  }
  stdMesg("  Container map:");
  for (size_t i=0; i<this->size(); i++) {
    stdMesg("   (%d): 0x%x - 0x%x", i, data(i), data(i)+sizeof(D));
    if (verbose<2) continue;
    std::map<std::string,std::pair<char,size_t> >::const_iterator it;
    for (it=vars_.begin(); it!=vars_.end(); it++) {
      std::ostringstream ss;
      ss<<"   \t"<<ROOTVariableTypeMap[(*it).second.first].first;
      ss<<" "<<(*it).first<<"=\t";
      if ((*it).second.first=='F' || (*it).second.first=='D') ss<<"%f";
      else if ((*it).second.first=='I'||(*it).second.first=='L') ss<<"%d";
      else if ((*it).second.first=='i'||(*it).second.first=='l') ss<<"%u";
      void* pv=(void *)data(i);
      char *p=(char *)pv+(*it).second.second;
      if ((*it).second.first=='F') stdMesg(ss.str(), *(float*)p);
      else if((*it).second.first=='D') stdMesg(ss.str(), *(double*)p);
      else if((*it).second.first=='I') stdMesg(ss.str(), *(int*)p);
      else if((*it).second.first=='L') stdMesg(ss.str(), *(long*)p);
      else if((*it).second.first=='i') stdMesg(ss.str(), *(unsigned int*)p);
      else if((*it).second.first=='l') stdMesg(ss.str(), *(unsigned long*)p);
    }
  }
}

//--------------------------------- select() ----------------------------------

template <class D> void Container<D>::select() {
  if (!isValid()) return;
  if (selectionType_==NOVAL_S) return;
  if (objVoid_.selectionTypes_.find(selectionType_) ==
      objVoid_.selectionTypes_.end()) {
    stdErr("select(): selection type %s is not set correctly, call "	\
	   "setSelectionType(string) preferably in the constructor\n",
	   selectionType_.data());
    return;
  }
  for (int i=0; i<long(this->size()); i++) {
    if (passed(selectionType_, i)!=0) continue; 
    this->erase(this->begin()+i);
    --i;
  }
}

//--------------------------------- passed() ----------------------------------

template <class D> int Container<D>::passed(std::string selection, size_t i) {
  stdErr("passed(): virtual function passed() has not been implemented\n");
  return NOVAL_I;
}

//-----------------------------------------------------------------------------
}
#endif
