#ifndef SusyAnalysis_debDataMaker_VContainer_hh_
#define SusyAnalysis_debDataMaker_VContainer_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      VContainer
// 
/**\class VContainer VContainer.hh SusyAnalysis/debDataMaker/interface/VContainer.hh

 Description: <one line class summary>

 Implementation:

 
*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: VContainer.hh,v 1.1 2009/07/17 14:49:38 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/Container.hh"

namespace deb {

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template <class D> 
class VContainer : public Container<std::vector<D>,D,size_t> {
public:
  typedef Container<std::vector<D>,D,size_t> ContainerBase;

  VContainer(std::string name="") 
    : ContainerBase(name) { }

  VContainer(std::string name, size_t storeNObjects) 
    : ContainerBase(name, storeNObjects){ }

  VContainer(std::string name, std::vector<size_t>& storeList) 
    : ContainerBase(name, storeList) { }

  virtual ~VContainer() { }

  inline D* operator ()(size_t i) { 
    return i<this->size() ? &this->at(i) : NULL; 
  }

  inline D* data(size_t i) { return &(*this)[i]; }

  inline std::vector<size_t> getKeys();

 typename ContainerBase::KeyType key(typename std::vector<D>::iterator it) { 
    return it-this->begin();
  }

//   std::string keyToString(size_t key) {
//     std::ostringstream ss;
//     ss<<key;
//     return ss.str();
//   }

  virtual int      passed(std::string,typename std::vector<D>::const_iterator);
  virtual int      passed(std::string, size_t);

};


//---------------------------------- passed() ---------------------------------

template <class D>
int VContainer<D>::passed(std::string selection, 
			  typename std::vector<D>::const_iterator it){
  return this->passed(selection, it-this->begin());
}


template <class D> int VContainer<D>::passed(std::string selection, size_t i) {
  this->stdErr("passed(): virtual function passed() has not been "	\
	       "implemented\n");
  return NOVAL_I;
}


//---------------------------------- getKeys() --------------------------------

template <class D> std::vector<size_t> VContainer<D>::getKeys() {
  std::vector<size_t> ret;
  for (size_t i=0; i<this->size(); i++) ret.push_back(i);
  return ret;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
