#ifndef SusyAnalysis_debDataMaker_PContainer_hh_
#define SusyAnalysis_debDataMaker_PContainer_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      PContainer
// 
/**\class PContainer PContainer.hh SusyAnalysis/debDataMaker/interface/PContainer.hh

 Description: <one line class summary>

 Implementation:

   !!!! See usage of inherited functions in Data.hh source code !!!!

   unsigned int ij(unsigned int i, unsigned int j):
       provides mapping between the (i,j) parameters of the two input classes 
       and the single 'i' parameter used in data(i). PRIVATE, used in the
       operator () and in 
       inline PContainerData& dr(unsigned int u, unsigned int v)

   The following fuctions should be overloaded here according to the exact 
   definition of D in Data<D> :

       void set(const edm::Event&) (virtual): NOT IMPLEMENTED, 
         we do not read any information from the CMSSW data files

       void calculate(?) (virtual): 
         calculates values that depend on other data models. WARNING, since the
	 MetData object does not have 'eta' parameter at the moment, in the
         implementation of calculate, the class template parameters must be
	 fully specified if U or V inherits from MetData

       PContainerData& operator () (unsigned int i, unsigned int j):
         provides the (i,j) element of the Data, overloads the single parameter
	 version in Data<D>

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Sun Mar 24 12:15:11 CET 2009
// $Id: PContainer.hh,v 1.4 2009/06/24 07:47:58 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/MContainer.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class K1, class K2, class D> 
class PContainer : public MContainer<std::pair<K1,K2>, D> { 
 public:
  typedef MContainer<std::pair<K1,K2>, D>  ContainerBase;
  typedef K1                               KeyType1;
  typedef K2                               KeyType2;
  typedef std::pair<K1,K2>                 KeyType;
  typedef std::vector<K1>                  KeyList1;
  typedef std::vector<K2>                  KeyList2;
  typedef std::vector<std::pair<K1,K2> >   KeyList;

  PContainer(std::string name="")
    : ContainerBase(name) { storeType_=""; }

  PContainer(std::string name, size_t storeNObjects)
    : ContainerBase(name, storeNObjects) { storeType_=""; }

  PContainer(std::string name, KeyList& storeList)
    : ContainerBase(name, storeList) { storeType_="set"; }

  PContainer(std::string name, KeyList1& ind1, KeyList2& ind2)
    : ContainerBase(name, generateKeys(ind1, ind2)) { storeType_="full"; }

  PContainer(std::string name,
	     KeyList1& ind1, KeyList1& ind2, std::string storeType)
    : ContainerBase(name, generateKeys(ind1, ind2, storeType)), 
      storeType_(storeType) { }

 private:
  std::string storeType_; // "diagonal", "triangle", "full", "set", ""

 public:

  //  virtual std::string keyToString(KeyType);

  bool isGoodKey(K1, K2, std::string);

  KeyList generateKeys(KeyList1&, KeyList2&);
  KeyList generateKeys(KeyList1&, KeyList1&, std::string);

  inline D* operator()(K1 u, K2 v){ return (*this)(KeyType(u,v)); }

  std::pair<typename ContainerBase::iterator,bool> insert(K1 u, K2 v, D d) {
    return ContainerBase::insert(KeyType(u,v), d);
  }

  //  void             addBranch(TTree*);
//   void             setBranch();
  //void             print(int);
  std::string      getStoreType() { return storeType_; }

};


//------------------------------- isGoodKey() ---------------------------------

template<class K1, class K2, class D>
bool PContainer<K1,K2,D>::isGoodKey(K1 u, K2 v, std::string type) {

  if (type.find("full")!=std::string::npos) return true;

  if (humanTypeId(u)!=humanTypeId(v)) return true;

  const void *p=&v;
  const K1& v2=*(const K1*)p;

  if (u==v2) {
    if (type.find("diag")!=std::string::npos) return true;
    return false;
  }
  
  if (u<v2) {
    if (type.find("triang")!=std::string::npos) return true;
  }
  
  return false;
}

//------------------------------- generateKeys() ------------------------------

template<class K1, class K2, class D>
typename PContainer<K1,K2,D>::KeyList 
PContainer<K1,K2,D>::generateKeys(KeyList1& ind1, KeyList2& ind2) {
  
  KeyList ret;
  for (size_t i=0; i<ind1.size(); i++) {
    for (size_t j=0; j<ind2.size(); j++) {
      std::pair<K1, K2> pair(ind1[i], ind2[j]);
      ret.push_back(pair);
    }
  }

  return ret;
}


template<class K1, class K2, class D>
typename PContainer<K1,K2,D>::KeyList 
PContainer<K1,K2,D>::generateKeys(KeyList1& ind1, KeyList1& ind2,
				  std::string type) {
  KeyList ret;
  
  for (size_t i=0; i<ind1.size(); i++) {
    for (size_t j=0; j<ind2.size(); j++) {
      if (isGoodKey(ind1[i], ind2[j], type)) {
	ret.push_back(KeyType(ind1[i], ind2[j]));
      }

//       if (type_=="" || type_.find("full")!=std::string::npos) {
// 	ret.push_back(std::pair<KeyType1, KeyType2>(ind1[i], ind2[j]));
// 	continue;
//       }

//       if (ind1[i]==ind2[j]) {
// 	if (type_.find("diag")!=std::string::npos) {
// 	  ret.push_back(std::pair<KeyType1, KeyType2>(ind1[i], ind2[j]));
// 	}
// 	continue;
//       }

//       if (ind1[i]<ind2[j]) {
// 	if (type_.find("triang")!=std::string::npos) {
// 	  ret.push_back(std::pair<KeyType1, KeyType2>(ind1[i], ind2[j]));
// 	}
//       }
    } // for j
  } // for i

  return ret;
}


// //------------------------------- keyToString() -------------------------------

// template <class K1, class K2, class D> 
// std::string PContainer<K1,K2,D>::keyToString(KeyType key) {
//   std::ostringstream ss;
//   ss<<key.first<<"_"<<key.second;
//   return ss.str();
// }

// //--------------------------------- addBranch() -------------------------------

// template <class K1, class K2, class D> 
// void PContainer<K1,K2,D>::addBranch(TTree* tree){
//   if (!this->isValid()) {
//     this->stdErr("addBranch(): Object is not valid, cannot add it to tree\n");
//     return;
//   }
//   if (this->storeNObjects_==0) return;
//   if (this->tree_!=NULL) {
//     this->stdWarn("addBranch(): Object is already added to a tree.\n");
//     return;
//   }
//   this->tree_=tree;

//   if (this->storeNObjects_==1 && this->storeList_.size()==0) {
//     this->tree_->Branch(this->name_.data(), &this->objVoid_, this->objVoid_.list().data());
//     return;
//   }

//   for (size_t i=0; i<this->storeNObjects_; i++) {
//     std::ostringstream ss;
//     if (this->storeList_.size()==0) {
//       ss<<this->name_<<"_"<<i;
//     } else {
//       ss<<this->name_<<"_"<<this->keyToString(this->storeList_[i]);
//     }
//     this->tree_->Branch(ss.str().data(), &this->objVoid_, this->objVoid_.list().data());
//   }
// }

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
 
}
#endif
