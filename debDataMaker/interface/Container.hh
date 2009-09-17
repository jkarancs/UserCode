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
// $Id: Container.hh,v 1.6 2009/09/05 09:19:59 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "TTree.h"
#include "CONST.hh"
#include "Tools.hh"

namespace deb {

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template <class C, class D, class K=size_t> class Container : public C {
 public:
  Container(std::string name="") : name_(name) { init(0); }
  Container(std::string name, size_t storeNObjects) : name_(name) { 
    init(storeNObjects);
  }
  Container(std::string name, std::vector<K>& storeList) : name_(name) {
    init(storeList);
  }
  virtual          ~Container() { this->clear(); }

  typedef C                 StlType;
  typedef D                 ValueType;
  typedef K                 KeyType;
  typedef std::vector<K>    KeyList;

 protected:
  std::string       name_;
  size_t            storeNObjects_;     // storeNObjects after calling select()
  std::vector<K>    storeList_;
  std::string       selectionType_;     // 1, 2,... variants of data selection.
  bool              valid_;             // tells if object is valid
  std::map<std::string,std::pair<char,size_t> > vars_;
  D                 objVoid_;

 protected:
  TTree*            tree_;              // pointer to tree if being saved there

 private:
  void              init(size_t);
  void              init(std::vector<K>&);

 public:
  //virtual std::string       keyToString(K)=0;
  virtual KeyType   key(typename C::iterator)=0;
  // Commented out because it is dangerous, this operator should not be called
  // from Container, but from one of the derived classes, lets see what happens
  //  virtual D*        operator ()(K i) { return &(*this)[i]; }//Needtocheck i
  virtual D*        operator ()(K i) { return NULL; } // Need to check i
  virtual D*        data(size_t i) { return NULL; }
  inline size_t     storeNObjects() { return storeNObjects_; }
  const std::vector<K>& storeList() { return storeList_; }
  std::string       name() { return name_; }
  void              setName(const char *name) { name_=name; }
  void              setSelectionType(std::string type) { selectionType_=type; }
  std::string       getSelectionType() { return selectionType_; }
  void              setValid(bool choice) { valid_=choice; }
  bool              isValid() { return valid_; }
  std::string       list(std::string prefix="") {return objVoid_.list(prefix);}

  void              addBranch(TTree*);
  void              setBranch();
  void              stdErr(std::string, ...);
  void              stdWarn(std::string, ...);
  void              stdMesg(std::string, ...);
  void              print(int);

  //
  // functions that need to be implemented in inheriting class
  // ---------------------------------------------------------

  virtual void      calculate() { 
    this->stdWarn("calculate(): virtual function is not implemented\n");
  }
  void              calculate_pass();
  void              select();
  virtual int       passed(std::string, typename C::const_iterator);
  virtual int       passed(std::string, size_t);

};

//--------------------------------- Constructor -------------------------------

template <class C, class D, class K> 
void Container<C,D,K>::init(size_t storeNObjects) {
  this->clear();
  storeNObjects_=storeNObjects;
  setSelectionType(NOVAL_S);
  setValid(true);
  vars_=getVariableMap(objVoid_.list());
  tree_=NULL;
}

template <class C, class D, class K>
void Container<C,D,K>::init(std::vector<K>& storeList){
  storeList_.clear();
  typename std::vector<K>::const_iterator it;
  for (it=storeList.begin(); it!=storeList.end(); it++) {
    typename std::vector<K>::const_iterator it2;
    it2=std::find(storeList_.begin(), storeList_.end(), *it);
    if (it2==storeList_.end()) {
      storeList_.push_back(*it);
    }
  }
  init(storeList_.size());
}

// //------------------------------- keyToString() -------------------------------

// template <class C, class D, class K> 
// std::string Container<C,D,K>::keyToString(K key) {
//   std::ostringstream ss;
//   ss<<key;
//   return ss.str();
// }

//--------------------------------- addBranch() -------------------------------

template <class C, class D, class K> 
void Container<C,D,K>::addBranch(TTree* tree){
  if (!isValid()) {
    stdErr("addBranch(): Object is not valid, cannot add it to tree\n");
    return;
  }
  if (storeNObjects_==0) return;
  if (name_.empty()) {
    stdErr("addBranch(): Cannot add to tree without name.");
    return;
  }
  if (tree_!=NULL) {
    stdWarn("addBranch(): Object is already added to a tree.\n");
    return;
  }
  tree_=tree;

  if (storeNObjects_==1 && storeList_.size()==0) {
    tree_->Branch(name_.data(), &objVoid_, objVoid_.list().data());
    return;
  }

  for (size_t i=0; i<storeNObjects_; i++) {
    std::ostringstream ss;
    if (storeList_.size()==0) {
      ss<<name_<<"_"<<i;
    } else {
      ss<<name_<<"_"<<keyToString(storeList_[i]);
    }
    tree_->Branch(ss.str().data(), &objVoid_, objVoid_.list().data());
  }
}


//--------------------------------- setBranch() -------------------------------

template <class C, class D, class K> 
void Container<C,D,K>::setBranch() {
  if (!isValid()) {
    stdErr("setBranch(): Object is not valid, can't fill its branches.\n");
    return;
  }
  if (storeNObjects_==0) return;
  if (tree_==NULL) {
    stdErr("setBranch(): Object hasn't been added to tree. "	\
	   "(Do it in the constructor!)\n");
    return;
  }

  objVoid_.clear();
  typename C::iterator it=this->begin(); // used only when saving sequentially
  // If only one element and no mapping then do not number the branch
  if (storeNObjects_==1 && storeList_.size()==0) {
    TBranch* br=tree_->GetBranch(name_.data());
    if (br!=NULL) {
      if (this->size()!=0) br->SetAddress(&(*it));
      else br->SetAddress(&objVoid_);
    }
    else stdErr("setBranch(): Did not find branch %s in tree!!!\n", 
		name_.data());
    return; // single element saved as required
  }
  // Save storeNObjects_ number of elements either sequentially or mapped
  for (size_t i=0; i<storeNObjects_; i++) {
    std::ostringstream ss;
    if (storeList_.size()==0) { // save sequentially, branch is numbered by i
      ss<<name_<<"_"<<i;
    } else { // save mapped elements, branch is named by the mapping key
      ss<<name_<<"_"<<keyToString(storeList_[i]);
    }
    TBranch* br=tree_->GetBranch(ss.str().data());
    if (br!=NULL) { // branch with appropriate name found
      if (storeList_.size()==0) { // SAVE SEQUENTIALLY
	if (i<this->size()) { // make sure element exists
	  br->SetAddress(&(*it));
	  it++;
	} else { // if not, just save the void element
	  br->SetAddress(&objVoid_);
	}
      } else { // SAVE MAPPED ELEMENTS
	D* data=(*this)(storeList_[i]); // try to find the element (checked)
	if (data==NULL) { // if not in the container
	  stdErr("setBranch(): data with key %s does not exist",
		 keyToString(storeList_[i]).data());
	  br->SetAddress(&objVoid_);
	} else { // if it is in the container
	  br->SetAddress(data);
	}
      }
      
//   if (i<this->size()) {
// 	if (storeList_.size()==0) {
// 	  br->SetAddress(&(*it));	  
// 	} else {
// 	  D* data=(*this)(storeList_[i]);
// 	  if (data==NULL) {
// 	    stdErr("setBranch(): data with key %s does not exist",
// 		   keyToString(storeList_[i]).data());
// 	    br->SetAddress(&objVoid_);
// 	  } else {
// 	    br->SetAddress(data);
// 	  }
// 	  //br->SetAddress(&(*this)[storeList_[i]]);
// 	}
//   } else {
// 	br->SetAddress(&objVoid_);
//   }

    }
    else stdErr("setBranch(): Did not find branch %s in tree!!!\n", 
		ss.str().data());
    //if (it!=this->end()) it++;
  }
}


//--------------------------------- stdMesg() ---------------------------------
 
template <class C, class D, class K> 
void Container<C,D,K>::stdErr(std::string mesg, ...) {
  va_list argList;
  va_start(argList, mesg);
  char s[10000];
  vsprintf(s, mesg.data(), argList);
  va_end(argList);
  mesg=s;
  std::cerr<<"*** ERROR: "<<name_<<"("<<humanTypeId(objVoid_)<<")::"
	   <<mesg<<std::endl;
}


template <class C, class D, class K> 
void Container<C,D,K>::stdWarn(std::string mesg, ...) {
  va_list argList;
  va_start(argList, mesg);
  char s[10000];
  vsprintf(s, mesg.data(), argList);
  va_end(argList);
  mesg=s;
  std::cout<<"*** WARNING: "<<name_<<"("<<humanTypeId(objVoid_)<<")::"<<mesg
	   <<std::endl;
}


template <class C, class D, class K> 
void Container<C,D,K>::stdMesg(std::string mesg, ...) {
  va_list argList;
  va_start(argList, mesg);
  char s[10000];
  vsprintf(s, mesg.data(), argList);
  va_end(argList);
  mesg=s;
  std::cout<<name_<<"("<<humanTypeId(objVoid_)<<")::"<<mesg<<std::endl;
}

//---------------------------------- print() ----------------------------------

template <class C, class D, class K> 
void Container<C,D,K>::print(int verbose=0) {
  // verbose 0: Print BASIC SETTINGS of object
  //         1: add LIST OF VARIABLES IF it will be saved in a tree,
  //            show container MAP in memory of ELEMENTS to be saved (STORED)
  //         2: show container MAP for ALL ELEMENTS (not stored up to 20)
  //         3: additionally list VALUES in the elements to be saved (STORED)
  //         4: show container MAP for ALL ELEMENTS and
  //            list VALUES of ALL elements in the container (up to 20)
  //         5: list all elements with all values
  stdMesg("  Number of valid objects in container (size): %d", this->size());
  stdMesg("  Number of objects to be stored (storeNObjects): %d", 
	  storeNObjects());
  if (storeList_.size()!=0) {
    std::ostringstream ss; 
    ss<<keyToString(storeList_[0]);
    for (size_t i=1; i<storeList_.size(); i++) 
      ss<<", "<<keyToString(storeList_[i]);
    stdMesg("   '%s'", ss.str().data());
  }
  stdMesg("  Selection criteria for select() function (selectionType_) : %s",
	  selectionType_.data());
  stdMesg("  List of variables: %s", objVoid_.list().data());
  stdMesg("  Object is %svalid!\n", (isValid() ? "" : "not "));
  if (verbose<1) {
    stdMesg("");
    return;
  }

  if (tree_!=NULL) {
    stdMesg("  Added to tree '%s' as branch '%s_X'", tree_->GetName(), 
	    name_.data());
  }
  stdMesg("  Container map:");
  //  for (size_t i=0; i<this->size(); i++) {
  typename C::iterator iObj=this->begin();
  size_t nNonStored=0;
  for (size_t i=0; iObj!=this->end(); iObj++) {
    std::string sstore="";
    std::string k=keyToString(key(iObj));
    if (k.find_first_of("_")!=std::string::npos) 
      k.replace(k.find_first_of("_"), 1, ",");
    if (storeNObjects()!=0) {
      if (storeList_.size()==0) {
	if (i<storeNObjects()) sstore=" * [STORE]";
      } else {
	size_t j=0;
	for (; j<storeList_.size(); j++) if (storeList_[j]==key(iObj)) break;
	if (j!=storeList_.size()) sstore=" * [STORE]";
      }
    }
    // conditions:
    if (sstore.empty()) nNonStored++;
    if (!sstore.empty() || (verbose>=2 && nNonStored<21) || verbose>=4) {
      stdMesg("   (%s): 0x%x - 0x%x %s", 
	      k.data(), &(*iObj), &(*iObj)+sizeof(D), sstore.data());
    }
    if (verbose<3 || (sstore.empty() && verbose==3) || 
	(sstore.empty() && verbose==4 && nNonStored>20)) {
      i++; 
      continue;
    }
    std::map<std::string,std::pair<char,size_t> >::const_iterator it;
    for (it=vars_.begin(); it!=vars_.end(); it++) {
      std::ostringstream ss;
      ss<<"   \t"<<ROOTVariableTypeMap[(*it).second.first].first;
      ss<<" "<<(*it).first<<"=\t";
      if ((*it).second.first=='F' || (*it).second.first=='D') ss<<"%f";
      else if ((*it).second.first=='I'||(*it).second.first=='L') ss<<"%d";
      else if ((*it).second.first=='i'||(*it).second.first=='l') ss<<"%u";
      //      void* pv=(void *)data(i);
      //void* pv=(void *)(&(*iObj));
      void* pv=(void *)(&(*this)[key(iObj)]);
      char *p=(char *)pv+(*it).second.second;
      if ((*it).second.first=='F') stdMesg(ss.str(), *(float*)p);
      else if((*it).second.first=='D') stdMesg(ss.str(), *(double*)p);
      else if((*it).second.first=='I') stdMesg(ss.str(), *(int*)p);
      else if((*it).second.first=='L') stdMesg(ss.str(), *(long*)p);
      else if((*it).second.first=='i') stdMesg(ss.str(), *(unsigned int*)p);
      else if((*it).second.first=='l') stdMesg(ss.str(), *(unsigned long*)p);
    }
    i++;
  }
  stdMesg("");
}

//------------------------ calculate_pass() -----------------------------------

template <class C, class D, class K> void Container<C,D,K>::calculate_pass() {
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


//--------------------------------- select() ----------------------------------

template <class C, class D, class K> void Container<C,D,K>::select() {

  if (!isValid()) return;
  if (selectionType_==NOVAL_S) return;
  if (objVoid_.selectionTypes_.find(selectionType_) ==
      objVoid_.selectionTypes_.end()) {
    stdErr("select(): selection type %s is not set correctly, call "	\
	   "setSelectionType(string) preferably in the constructor\n",
	   selectionType_.data());
    return;
  }
  for(typename C::reverse_iterator rit=this->rbegin(); rit!=this->rend();) {
    rit++;
    typename C::iterator erase_it=rit.base();
    if (passed(selectionType_, erase_it)==0) this->erase(erase_it);
  }
}


//--------------------------------- passed() ----------------------------------

template <class C, class D, class K>
int Container<C,D,K>::passed(std::string selection, 
			      typename C::const_iterator it) {
  stdErr("passed(): virtual function passed() has not been implemented\n");
  return NOVAL_I;
}


template <class C, class D, class K>
int Container<C,D,K>::passed(std::string selection, size_t i) {
  stdErr("passed(): virtual function passed() has not been implemented\n");
  return NOVAL_I;
}

//-----------------------------------------------------------------------------
}
#endif
