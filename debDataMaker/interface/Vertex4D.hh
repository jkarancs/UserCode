#ifndef SusyAnalysis_debDataMaker_Vertex4D_hh_
#define SusyAnalysis_debDataMaker_Vertex4D_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Vertex4D
// 
/**\class Vertex4D Vertex4D.hh SusyAnalysis/debDataMaker/interface/Vertex4D.hh

 Description: <one line class summary>

 Implementation: adds two 4-momentum objects (one from U and one from V) 
                 together and stores the sum in a Vertex4DData. 

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Sun Mar 24 12:15:11 CET 2009
// $Id: Vertex4D.hh,v 1.1 2009/06/10 14:25:29 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/VContainer.hh"
#include "SusyAnalysis/debDataMaker/interface/Vertex4DData.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class U,class V> class Vertex4D : public VContainer<Vertex4DData>{
 public:
  typedef VContainer<Vertex4DData>                  CBase;
  typedef typename U::KeyType                       KeyTypeU;
  typedef typename V::KeyType                       KeyTypeV;
  typedef typename std::pair<KeyTypeU,KeyTypeV>     KeyTypeUV;
  typedef typename std::vector<KeyTypeUV>           KeyListUV;
  typedef typename U::iterator                      U_iterator;
  typedef typename V::iterator                      V_iterator;

  Vertex4D(U&, V&, KeyListUV, std::string name, size_t);
  ~Vertex4D() { }

  void calculate();
  inline KeyTypeUV& ind(size_t i) { return calcList_[i]; }
  void setNominalMass(float mass, float sigma) { mass_=mass; sigma_=sigma; }

 private:
  inline Vertex4DData& vtx(size_t i) { return (*this)[i]; }
  U& U_;
  V& V_;
  KeyListUV calcList_;
  void init();
  float mass_; // Nominal mass of decaying particle
  float sigma_; // expected resolution of mass

};


//------------------------- Two-parameter constructors ------------------------
template<class U,class V>
Vertex4D<U,V>::Vertex4D(U& u, V& v, KeyListUV calcList, 
			std::string name="", size_t storeNObjects=0) :
  CBase(name, storeNObjects), U_(u), V_(v), calcList_(calcList) {
  init();
  mass_=sigma_=NOVAL_F;
}

//-------------------------------------- init() -------------------------------

template<class U,class V> void Vertex4D<U,V>::init(){

  stdMesg("  Vertex4D<Vertex4DData> configuration:");
  stdMesg("  Calculate sum of %s(%s) and %s(%s)", 
	  U_.name().data(), humanTypeId(U_).data(),
	  V_.name().data(), humanTypeId(V_).data());
  stdMesg("  for %d index pairs:", calcList_.size());
  for (size_t i=0; i<calcList_.size(); i++) {
    stdMesg("\t\t(%s, %s)", keyToString(calcList_[i].first).data(), 
	                    keyToString(calcList_[i].second).data());
  }
  
  stdMesg("  List of variables: %s", list().data());
  stdMesg("  Object is %svalid!\n", (isValid() ? "" : "not "));
}

// ------------------------------- calculate() --------------------------------
// --------------------------- and specializations ----------------------------

template<class U,class V> void Vertex4D<U,V>::calculate() {
  if (!isValid()) return;
  clear();

  for (size_t i=0; i<calcList_.size(); i++) {
    Vertex4DData vtx;
    typename U::ValueType* u=U_(calcList_[i].first);
    typename V::ValueType* v=V_(calcList_[i].second);
    if (u==NULL || v==NULL) {
      stdWarn("calculate(): invalid index pair (%s, %s)!!!\n", 
	      keyToString(calcList_[i].first).data(), 
	      keyToString(calcList_[i].second).data());
      push_back(vtx);
      continue;
    }
    if (u->m==NOVAL_F || v->m==NOVAL_F) {
      push_back(vtx);
      continue;
    }
    vtx.e   = u->e  + v->e;
    vtx.px  = u->px + v->px;
    vtx.py  = u->py + v->py;
    vtx.pz  = u->pz + v->pz;
    vtx.pt  = sqrt(vtx.px*vtx.px + vtx.py*vtx.py);
    vtx.p   = sqrt(vtx.pt*vtx.pt + vtx.pz*vtx.pz);
    vtx.m   = sqrt(vtx.e*vtx.e - vtx.p*vtx.p);
    vtx.et  = sqrt(vtx.pt*vtx.pt + vtx.m*vtx.m);
    vtx.phi = atan2(vtx.py, vtx.px);
    vtx.eta = log((vtx.e + vtx.pz) / (vtx.e - vtx.pz));

    if (mass_!=NOVAL_F && sigma_!=NOVAL_F) {
      vtx.mass = mass_;
      vtx.sigma = sigma_;
      vtx.chi2 = ((vtx.m-vtx.mass)*(vtx.m-vtx.mass)) / (vtx.sigma*vtx.sigma);
    }

    push_back(vtx);
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
