#ifndef SusyAnalysis_debDataMaker_PairData_hh_
#define SusyAnalysis_debDataMaker_PairData_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      PairData
// 
/**\class PairData PairData.hh SusyAnalysis/debDataMaker/interface/PairData.hh

 Description: <one line class summary>

 Implementation:

   !!!! See usage of inherited functions in Data.hh source code !!!!

   unsigned int ij(unsigned int i, unsigned int j):
       provides mapping between the (i,j) parameters of the two input classes 
       and the single 'i' parameter used in data(i). PRIVATE, used in the
       operator () and in 
       inline PairDataData& dr(unsigned int u, unsigned int v)

   The following fuctions should be overloaded here according to the exact 
   definition of D in Data<D> :

       void set(const edm::Event&) (virtual): NOT IMPLEMENTED, 
         we do not read any information from the CMSSW data files

       void calculate(?) (virtual): 
         calculates values that depend on other data models. WARNING, since the
	 MetData object does not have 'eta' parameter at the moment, in the
         implementation of calculate, the class template parameters must be
	 fully specified if U or V inherits from MetData

       PairDataData& operator () (unsigned int i, unsigned int j):
         provides the (i,j) element of the Data, overloads the single parameter
	 version in Data<D>

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Sun Mar 24 12:15:11 CET 2009
// $Id: PairData.hh,v 1.5.2.2 2010/09/16 09:03:25 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SusyAnalysis/debDataMaker/interface/Data.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class D> class PairData : public Data<D>{ 
 public:
  PairData(std::vector<unsigned int>, unsigned int, 
	   std::vector<unsigned int>, unsigned int, std::string);
  PairData(std::vector<std::pair<unsigned int, unsigned int> >&, 
	   std::pair<unsigned int, unsigned int>&);

  inline D* at(unsigned int u, unsigned int v){
    return map_[std::pair<unsigned int, unsigned int>(u,v)];
  }

  inline D& operator ()(unsigned int u, unsigned int v){
    return *map_[std::pair<unsigned int, unsigned int>(u,v)];
  }

  inline D* at(std::pair<unsigned int,unsigned int>& uv){
    return map_[uv];
  }

  inline D& operator ()(std::pair<unsigned int,unsigned int>& uv){
    return *map_[uv];
  }

  std::map<std::pair<unsigned int,unsigned int>, D*>& map() { return map_; }
  std::vector<std::pair<unsigned int, unsigned int> >& ind() { return ind_; }

  std::pair<unsigned int,unsigned int>& ind(unsigned int i) { return ind_[i]; }
  
  void addBranch(TTree*, std::string);


 private:
  std::map<std::pair<unsigned int,unsigned int>, D*> map_;
  std::vector<std::pair<unsigned int, unsigned int> > ind_;
  std::pair<unsigned int,unsigned int> bound_;
  std::string type_; // "diagonal", "triangle", "full". Antisymm is not ready.

  unsigned int get_size_uv(unsigned int size_u,
			   unsigned int size_v, 
			   std::string type="") {
    if (size_u!=size_v) return size_u*size_v;
    if (type=="" || type.find("full")!=std::string::npos) return size_u*size_v;
    unsigned int ret=0;
    if (type.find("diag")!=std::string::npos) ret+=size_u;
    if (type.find("triang")!=std::string::npos) ret+=((size_u-1)*size_u)/2;
    return ret;
  }

};


//--------------------------------- Constructor 1 -----------------------------

template<class D> 
PairData<D>::PairData(std::vector<std::pair<unsigned int, unsigned int> >& ind,
		      std::pair<unsigned int,unsigned int>& bound) : 
  Data<D>(ind.size()), bound_(bound) {
  
  type_=NOVAL_S;

  ind_.clear();
  std::vector<std::pair<unsigned int, unsigned int> >::const_iterator it;
  for (it=ind.begin(); it!=ind.end(); it++) {
    if (it->first>=bound_.first || it->second>=bound_.second) {
      Data<D>::stdErr("Invalid index pair (%d, %d) making object invalid:", 
		      it->first, it->second);
      Data<D>::setValid(false);
    }
    map_[*it]=Data<D>::data(ind_.size());
    ind_.push_back(*it);
  }

}

//--------------------------------- Constructor 2 -----------------------------

template<class D>
PairData<D>::PairData(std::vector<unsigned int> ind_u, unsigned int bound_u,
                      std::vector<unsigned int> ind_v, unsigned int bound_v,
		      std::string type="") :
  Data<D>(get_size_uv(ind_u.size(), ind_v.size(), type)) {

  bound_.first=bound_u;
  bound_.second=bound_v;
  type_=type;

  ind_.clear();
  for (unsigned int i=0; i<ind_u.size(); i++) {
    for (unsigned int j=0; j<ind_v.size(); j++) {

      if ((ind_u[i]>=bound_.first) || (ind_v[j]>=bound_.second)) {
        Data<D>::stdErr("Invalid index pair (%d, %d). Making object invalid :",
			ind_u[i], ind_v[j]);
	Data<D>::setValid(false);
      }

      if (type_=="" || type_.find("full")!=std::string::npos) {
	map_[std::pair<unsigned int, unsigned int>(ind_u[i], ind_v[j])]=
	  Data<D>::data(ind_.size());
	ind_.push_back(
	          std::pair<unsigned int, unsigned int>(ind_u[i], ind_v[j]));
	continue;
      }

      if (ind_u[i]==ind_v[j]) {
	if (type_.find("diag")!=std::string::npos) {
	  map_[std::pair<unsigned int, unsigned int>(ind_u[i], ind_u[i])]=
	    Data<D>::data(ind_.size());
	  ind_.push_back(
               std::pair<unsigned int, unsigned int>(ind_u[i], ind_v[j]));
	}
	continue;
      }

      if (ind_u[i]<ind_v[j]) {
	if (type_.find("triang")!=std::string::npos) {
	  map_[std::pair<unsigned int, unsigned int>(ind_u[i], ind_v[j])]=
	    Data<D>::data(ind_.size());
	  ind_.push_back(
	       std::pair<unsigned int, unsigned int>(ind_u[i], ind_v[j]));
	}
      }
    } // for j
  } // for i

}


//--------------------------------- addBranch() -------------------------------

template<class D>
void PairData<D>::addBranch(TTree* tree, std::string name) {

  if (!Data<D>::isValid()) {
    Data<D>::stdErr("Object is not valid, cannot add it to tree\n");
    return;
  }

  for (unsigned int i=0; i<Data<D>::max_size(); i++) {
    std::ostringstream ss;
    ss<<name<<"_"<<ind_[i].first<<"_"<<ind_[i].second;
    tree->Branch(ss.str().data(), Data<D>::data(i), 
		 Data<D>::data(i)->list().data());
  }

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
 
}
#endif
