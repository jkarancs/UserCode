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

   !!!! See usage of inherited functions in Data.hh source code !!!!

   unsigned int ij(unsigned int i, unsigned int j):
       provides mapping between the (i,j) parameters of the two input classes 
       and the single 'i' parameter used in data(i). PRIVATE, used in the
       operator () and in inline DeltaRData& dr(unsigned int u, unsigned int v)

   The following fuctions should be overloaded here according to the exact 
   definition of D in Data<D> :

      void set(const edm::Event&) (virtual): NOT IMPLEMENTED, 
         we do not read any information from the CMSSW data files

      void calculate(?) (virtual): 
         calculates values that depend on other data models. WARNING, since the
	 MetData object does not have 'eta' parameter at the moment, in the
         implementation of calculate, the class template parameters must be
	 fully specified if U or V inherits from MetData

      DeltaRData& operator () (unsigned int i, unsigned int j):
         provides the (i,j) element of the Data, overloads the single parameter
	 version in Data<D>

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Sun Mar 24 12:15:11 CET 2009
// $Id: DeltaR.hh,v 1.3 2009/06/10 14:25:29 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SusyAnalysis/debDataMaker/interface/PairData.hh"
#include "SusyAnalysis/debDataMaker/interface/DeltaRData.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class U,class V> class DeltaR : public PairData<DeltaRData>{
 public:
  DeltaR(U&, std::vector<unsigned int>, V&, std::vector<unsigned int>);
  DeltaR(U&, std::vector<unsigned int>);

  inline DeltaRData& dr(unsigned int u, unsigned int v) { 
    return *PairData<DeltaRData>::at(u,v);
  }
  inline DeltaRData& dr(std::pair<unsigned int,unsigned int>& p) { 
    return *PairData<DeltaRData>::at(p);
  }
  inline DeltaRData& dr(int i) { 
    return *data(i);
  }

  // Inherited functions to be overloaded
  void calculate();

 private:
  U& U_;
  V& V_;
  void init();
  void calculate_dphi(unsigned int i);
  void calculate_deta(unsigned int i);
  void calculate_dr(unsigned int i);

};


//------------------------------- Constructors --------------------------------

template<class U,class V> 
DeltaR<U,V>::DeltaR(U& u, std::vector<unsigned int> ind_u, 
		    V& v, std::vector<unsigned int> ind_v):
  PairData<DeltaRData>(ind_u, u.max_size(), ind_v, v.max_size(), ""),
  U_(u), V_(v) {
  init();
}

template<class U,class V> 
DeltaR<U,V>::DeltaR(U& u, std::vector<unsigned int> ind_u) :
  PairData<DeltaRData>(ind_u, u.max_size(), ind_u, u.max_size(), "triangle"),
  U_(u), V_(u) {
  init();
}

// --------------------------------- init() ---------------------------------- 

template<class U,class V> void DeltaR<U,V>::init(){
  stdMesg("  DeltaR<%s,%s> configuration:", 
	  typeid(U_).name(),typeid(V_).name());
  stdMesg("  Calculate dphi between %s(%s) and %s(%s)", 
	  typeid(U_).name(), U_.tag().label().data(),
	  typeid(V_).name(), V_.tag().label().data());
  stdMesg("  for index pairs:");
  for (unsigned int i=0; i<ind().size(); i++) {
    stdMesg("\t\t(%d, %d)", ind(i).first, ind(i).second);
  }
  
  stdMesg("  List of variables: %s", data(0)->list().data());
  stdMesg("  Object is %svalid!\n", (isValid() ? "" : "not "));
}


// ------------------------------- calculate() --------------------------------
// --------------------------- and specializations ----------------------------

template<class U,class V> void DeltaR<U,V>::calculate() {
  if (!isValid()) return;
  clear();
  for (unsigned int i=0; i<storeNObjects(); i++) {
    DeltaRData new_obj;
    push_back(new_obj);
    calculate_dphi(i);
    calculate_deta(i);
    calculate_dr(i);
  }
}

// !!!! WARNING !!!!
// Your Met<pat::MET> or Met<reco::MET> object probably does not have an "eta"
// parameter; if so, you need to add a specialized calculate() function, such 
// as below:

// I will always put the Met as the second template parameter, let's don't
// duplicate the number of calculate functions just to avoid this constraint

template<> void DeltaR<Jet<pat::Jet>,Met<pat::MET> >::calculate() {
  if (!isValid()) return;
  clear();
  for (unsigned int i=0; i<storeNObjects(); i++) {
    DeltaRData new_obj;
    push_back(new_obj);
    calculate_dphi(i);
    dr(i).eta=NOVAL_F;
    dr(i).r=NOVAL_F;
  }
}

//-----------------------------------------------------------------------------

template<class U,class V> 
inline void DeltaR<U,V>::calculate_dphi(unsigned int i) { 
  if (U_[ind(i).first].phi!=NOVAL_F && V_[ind(i).second].phi!=NOVAL_F) {
    float temp_dphi=fabs(U_[ind(i).first].phi-V_[ind(i).second].phi);
    if (temp_dphi<TMath::Pi()) {
      dr(i).phi=temp_dphi;
    }
    else {
      dr(i).phi=2*TMath::Pi()-temp_dphi;
    }      
  } else {
    dr(i).phi=NOVAL_F;
  }
}

template<class U,class V> 
inline void DeltaR<U,V>::calculate_deta(unsigned int i) { 
  if (U_[ind(i).first].eta!=NOVAL_F && V_[ind(i).second].eta!=NOVAL_F) {     
    dr(i).eta=fabs(U_[ind(i).first].eta-V_[ind(i).second].eta);
  } else {
    dr(i).eta=NOVAL_F;
  }
}

template<class U,class V> 
inline void DeltaR<U,V>::calculate_dr(unsigned int i) { 
  if (dr(i).phi!=NOVAL_F && dr(i).eta!=NOVAL_F) {
    dr(i).r=sqrt(dr(i).phi*dr(i).phi+dr(i).eta*dr(i).eta);
  } else {
    dr(i).r=NOVAL_F;
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
