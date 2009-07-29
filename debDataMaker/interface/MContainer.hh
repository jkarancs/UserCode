#ifndef SusyAnalysis_debDataMaker_MContainer_hh_
#define SusyAnalysis_debDataMaker_MContainer_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      MContainer
// 
/**\class MContainer MContainer.hh SusyAnalysis/debDataMaker/interface/MContainer.hh

 Description: <one line class summary>

 Implementation:

 
*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: MContainer.hh,v 1.1 2009/07/17 14:49:38 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/Container.hh"

namespace deb {

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template <class K, class D> 
class MContainer : public Container<std::map<K,D>,D,K> {
 public:
  typedef Container<std::map<K,D>,D,K> ContainerBase;

  MContainer(std::string name="") 
    : ContainerBase(name) { }

  MContainer(std::string name, size_t storeNObjects) 
    : ContainerBase(name, storeNObjects){ }

  MContainer(std::string name, std::vector<K> storeList) 
    : ContainerBase(name, storeList) { }

  virtual          ~MContainer() { }


  virtual inline D* operator ()(K u) {
    typename std::map<K,D>::iterator it=this->find(u);
    return it==this->end() ? NULL : &(it->second);
  }

  virtual inline D* data(size_t i) { // No check on i
    typename std::map<K,D>::iterator it=this->begin();
    advance(it, i);
    return &(it->second);
  }

  std::vector<K>    getKeys();
  
  std::pair<typename std::map<K,D>::iterator,bool> insert(K u, D d) {
    return std::map<K,D>::insert(typename std::pair<K,D>(u,d));
  }

  inline K          key(typename MContainer<K,D>::iterator it) { 
    return it->first; 
  }

//   virtual std::string keyToString(K key) {
//     std::ostringstream ss;
//     ss<<key;
//     return ss.str();
//   }

  virtual int       passed(std::string,typename std::map<K,D>::const_iterator);
  virtual int       passed(std::string, K);

};


//---------------------------------- passed() ---------------------------------

template <class K, class D>
int MContainer<K,D>::passed(std::string selection, 
			  typename std::map<K,D>::const_iterator it){
  this->stdErr("passed(): virtual function passed() has not been "	\
	       "implemented\n");
  return NOVAL_I;
}


template <class K, class D> 
int MContainer<K,D>::passed(std::string selection, K u) {
  typename std::map<K,D>::iterator it=this->find(u);
  return it==this->end() ? NOVAL_I : this->passed(selection, it);
}


//---------------------------------- getKeys() --------------------------------

template <class K, class D> std::vector<K> MContainer<K,D>::getKeys() {
  std::vector<K> keys;
  typename std::map<K, D>::const_iterator it;
  for (it=this->begin(); it!=this->end(); it++) keys.push_back(it->first);
  return keys;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
