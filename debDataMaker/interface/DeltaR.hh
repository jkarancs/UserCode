#ifndef SusyAnalysis_debDataMaker_DeltaR_hh_
#define SusyAnalysis_debDataMaker_DeltaR_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      DeltaR
// 
/**\class DeltaR DeltaR.hh SusyAnalysis/debDataMaker/interface/DeltaR.hh

 Description: <one line class summary>

 Implementation:

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Sun Mar 24 12:15:11 CET 2009
// $Id: DeltaR.hh,v 1.8 2009/08/18 13:13:34 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/PContainer.hh"
#include "SusyAnalysis/debDataMaker/interface/DeltaRData.hh"
#include "SusyAnalysis/debDataMaker/interface/Met.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class U,class V> 
class DeltaR
  : public PContainer<typename U::KeyType,typename V::KeyType,DeltaRData>{
 public:
  typedef PContainer<typename U::KeyType,typename V::KeyType,DeltaRData> CBase;
  typedef typename CBase::KeyType1                  KeyType1;
  typedef typename CBase::KeyType2                  KeyType2;
  typedef typename CBase::KeyType                   KeyType;
  typedef typename CBase::KeyList1                  KeyList1;
  typedef typename CBase::KeyList2                  KeyList2;
  typedef typename CBase::KeyList                   KeyList;
  typedef typename U::iterator                      U_iterator;
  typedef typename V::iterator                      V_iterator;
  // Note: KeyType1   := U::KeyType
  //       KeyType2   := V::KeyType
  //       KeyType    := std::pair<KeyType1,KeyType2>
  //       KeyList1/2 := std::vector<KeyType1/2>
  //       KeyList    := std::vector<std::pair<KeyType1,KeyType2> >

  // One parameter -> type_="triangle"
  DeltaR(U&, std::string name);
  DeltaR(U&, std::string name, size_t storeNObjects);
  DeltaR(U&, std::string name, std::vector<std::pair<KeyType1,KeyType1> >);
  DeltaR(U&, std::string name, KeyList1);

  // Two parameters -> type_="full"
  DeltaR(U&, V&, std::string name);
  DeltaR(U&, V&, std::string name, size_t storeNObjects);
  DeltaR(U&, V&, std::string name, KeyList);
  DeltaR(U&, V&, std::string name, KeyList1, KeyList2);

  ~DeltaR() { }

  void calculate();
  
  // Mode determines if DR is calculated for all pairs that can be produced
  // from U and V containers or just for the ones that are going to be stored
  // in the ROOT::TTree-s (in principle these two cases should be the same)
  inline int getMode() { return mode_; }
  inline void setMode(int mode) { 
    this->stdMesg("Mode set to calculate DR for %s pairs\n", 
		  (mode==0 ? "ALL (mode=0)" : "ONLY STORED"));
    mode_=mode; 
  }
  
  typename CBase::iterator findMinDrForFirst(KeyType1 u);
  typename CBase::iterator findMinDr();

 private:
  // No need to check if KeyType (u,v) exists, since we create it in 
  // calculate() before calling dr() the first time. Also, dr() is private
  // in order to prevent calling it with the wrong (u,v)
  inline DeltaRData& dr(KeyType1 u, KeyType2 v) { 
    return (*this)[KeyType(u,v)]; 
  }
  U& U_;
  V& V_;
  std::string type_;
  int mode_;
  void init();
  void calculate_dr(U_iterator, V_iterator);
  void calculate_dphi(U_iterator, V_iterator);
  void calculate_deta(U_iterator, V_iterator);

};


//------------------------- One-parameter constructors ------------------------
template<class U,class V>
DeltaR<U,V>::DeltaR(U& u, std::string name="") :
  CBase(name), U_(u), V_(u) {
  type_="triangle";
  init();
}

template<class U,class V>
DeltaR<U,V>::DeltaR(U& u, std::string name, size_t storeNObjects) :
  CBase(name, storeNObjects), U_(u), V_(u) {
  type_="triangle";
  init();
}

template<class U,class V>
DeltaR<U,V>::DeltaR(U& u, std::string name, 
		    std::vector<std::pair<KeyType1,KeyType1> > storeList) :
  CBase(name, storeList), U_(u), V_(u) {
  type_="triangle";
  init();
}

template<class U,class V>
DeltaR<U,V>::DeltaR(U& u, std::string name, KeyList1 ind) :
  CBase(name, ind, ind, "triangle"), U_(u), V_(u) {
  type_="triangle";
  init();
}


//------------------------- Two-parameter constructors ------------------------
template<class U,class V>
DeltaR<U,V>::DeltaR(U& u, V& v, std::string name="") :
  CBase(name), U_(u), V_(v) {
  type_="full";
  init();
}

template<class U,class V>
DeltaR<U,V>::DeltaR(U& u, V& v, std::string name, size_t storeNObjects) :
  CBase(name, storeNObjects), U_(u), V_(v) {
  type_="full";
  init();
}

template<class U,class V>
DeltaR<U,V>::DeltaR(U& u, V& v, std::string name, KeyList storeList) :
  CBase(name, storeList), U_(u), V_(v) {
  type_="full";
  init();
}

template<class U,class V>
DeltaR<U,V>::DeltaR(U& u, V& v, std::string name, 
		    KeyList1 ind1, KeyList2 ind2)
  : CBase(name, ind1, ind2), U_(u), V_(v) {
  type_="full";
  init();
}


// --------------------------------- init() ---------------------------------- 

template<class U,class V> void DeltaR<U,V>::init(){
  mode_=0;

  stdMesg("  DeltaR<%s,%s> configuration:", 
	  humanTypeId(U_).data(), humanTypeId(V_).data());
  stdMesg("  Calculate dphi between %s(%s) and %s(%s)", 
	  U_.name().data(),  humanTypeId(U_).data(),
	  V_.name().data(), humanTypeId(V_).data());
  stdMesg("  index pairs calculated in: %s", type_.data());
  stdMesg("  for %s pairs", (this->mode_==0 ? "ALL (mode=0)" : "ONLY STORED"));
  stdMesg("  List of variables: %s", this->list().data());
  stdMesg("  Object is %svalid!\n", (this->isValid() ? "" : "not "));
}


// ------------------------------- calculate() --------------------------------
// --------------------------- and specializations ----------------------------

template<class U,class V> void DeltaR<U,V>::calculate() {
  if (!this->isValid()) return;
  this->clear();

  for (U_iterator it1=U_.begin(); it1!=U_.end(); it1++) {
    for (V_iterator it2=V_.begin(); it2!=V_.end(); it2++) {
      KeyType1 u=U_.key(it1);
      KeyType2 v=V_.key(it2);
      if (mode_) {
	size_t j=0;
	for (; j<this->storeList().size(); j++) 
	  if (this->storeList()[j]==KeyType(u,v)) break;
	if (j==this->storeList().size()) continue; 
      }
      if (type_.find("full")==std::string::npos) {
	if (!this->isGoodKey(u, v, type_)) continue;
      }
      DeltaRData dr;
      this->insert(u, v, dr);
      calculate_dr(it1, it2);
    }
  }
}

//-----------------------------------------------------------------------------

template<class U,class V> 
void DeltaR<U,V>::calculate_dr(U_iterator it1, V_iterator it2) { 
  calculate_dphi(it1, it2);
  calculate_deta(it1, it2);
  KeyType1 u=U_.key(it1);
  KeyType2 v=V_.key(it2);

  if (dr(u,v).phi!=NOVAL_F && dr(u,v).eta!=NOVAL_F) {
    dr(u,v).r=sqrt(dr(u,v).phi*dr(u,v).phi+dr(u,v).eta*dr(u,v).eta);
  } else {
    dr(u,v).r=NOVAL_F;
  }
}

template<> 
void DeltaR<Met,Jet>::calculate_dr(U_iterator it1, V_iterator it2) { 
  calculate_dphi(it1, it2);
  KeyType1 u=U_.key(it1);
  KeyType2 v=V_.key(it2);
  dr(u,v).eta=NOVAL_F;
  dr(u,v).r=NOVAL_F;
}

template<> 
void DeltaR<Jet,Met>::calculate_dr(U_iterator it1, V_iterator it2) { 
  calculate_dphi(it1, it2);
  KeyType1 u=U_.key(it1);
  KeyType2 v=V_.key(it2);
  dr(u,v).eta=NOVAL_F;
  dr(u,v).r=NOVAL_F;
}

//-----------------------------------------------------------------------------

template<class U,class V> 
inline void DeltaR<U,V>::calculate_dphi(U_iterator it1, V_iterator it2) { 
  KeyType1 u=U_.key(it1);
  KeyType2 v=V_.key(it2);

  if (U_(u)->phi!=NOVAL_F && V_(v)->phi!=NOVAL_F) {
    float temp_dphi=fabs(U_(u)->phi - V_(v)->phi);
    if (temp_dphi<TMath::Pi()) {
      dr(u,v).phi=temp_dphi;
    } else {
      dr(u,v).phi=2*TMath::Pi()-temp_dphi;
    }      
  } else {
    dr(u,v).phi=NOVAL_F;
  }
}

template<class U,class V> 
inline void DeltaR<U,V>::calculate_deta(U_iterator it1, V_iterator it2) { 
  KeyType1 u=U_.key(it1);
  KeyType2 v=V_.key(it2);

  if (U_(u)->eta!=NOVAL_F && V_(v)->eta!=NOVAL_F) {     
    dr(u,v).eta=fabs(U_(u)->eta - V_(v)->eta);
  } else {
    dr(u,v).eta=NOVAL_F;
  }
}

//-------------------------------- findMinDr() --------------------------------

template<class U,class V> 
typename DeltaR<U,V>::CBase::iterator DeltaR<U,V>::findMinDr() {
  float minDr=fabs(NOVAL_F);
  typename CBase::iterator ret=this->end();
  typename CBase::iterator it=this->begin();
  for (; it!=this->end(); it++) {
    if (it->second.r>=minDr) continue; 
    minDr=it->second.r;
    ret=it;
  }
  return ret;
}

//----------------------------- findMinDrForFirst() ---------------------------

template<class U,class V> 
typename DeltaR<U,V>::CBase::iterator 
DeltaR<U,V>::findMinDrForFirst(KeyType1 u) {
  float minDr=fabs(NOVAL_F);
  typename CBase::iterator it=this->begin();
  typename CBase::iterator ret=this->end();
  for (; it!=this->end(); it++) {
    if (it->first.first!=u) continue;
    if (it->second.r>=minDr) continue; 
    minDr=it->second.r;
    ret=it;
  }
  return ret;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
