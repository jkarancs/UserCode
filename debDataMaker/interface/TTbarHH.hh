#ifndef SusyAnalysis_debDataMaker_TTbarHH_hh_
#define SusyAnalysis_debDataMaker_TTbarHH_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      TTbarHH
// 
/**\class TTbarHH TTbarHH.hh SusyAnalysis/debDataMaker/interface/TTbarHH.hh

 Description: <one line class summary>

 Implementation:

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $$
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/TTbarHHData.hh"
#include "SusyAnalysis/debDataMaker/interface/Vertex4D.hh"
#include "TString.h"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T> class TTbarHH : public VContainer<TTbarHHData>{
 public:
  TTbarHH(T&, std::vector<size_t>, std::string, size_t);
  TTbarHH() { 
    stdErr("  TTbarHH<%s> configuration missing\n", typeid(T).name());
  }
  ~TTbarHH() { }

  // vector of (t,tbar) index pairs
  inline std::vector<std::pair<size_t,size_t> >& ttbarI() {
    return ind_[4];
  }

  // indices of t and tbar in the ttbar pair
  inline std::pair<size_t,size_t> ttbarI(size_t i) {
    return ind_[4][i];
  }

  void set(const edm::Event&) { };
  void calculate ();
  void addBranch(TTree* tree);
  void setBranch();
  int passed(std::string selection,size_t i) { return NOVAL_I; }

  void clear() {
    VContainer<TTbarHHData>::clear();
    W1.clear(); W2.clear(); T1.clear(); T2.clear();
  }

  void print(size_t verbosity) {
    VContainer<TTbarHHData>::print(verbosity);
    W1.print(verbosity); W2.print(verbosity); 
    T1.print(verbosity); T2.print(verbosity);
  }

  VContainer<Vertex4DData> W1;
  VContainer<Vertex4DData> W2;
  VContainer<Vertex4DData> T1;
  VContainer<Vertex4DData> T2;

 private:
  // ttbar record in the container
  TTbarHHData& ttbar(size_t i) { return *(*this)(i); }

  std::vector<std::vector<std::pair<size_t, size_t> > >
                                        init(std::vector<size_t>&);

  size_t init_insert_pair(size_t p1, size_t p2, 
			  std::vector<std::pair<size_t, size_t> >& v);

  std::vector<std::vector<std::pair<size_t, size_t> > > ind_;

  Vertex4D<T,T> W1_;
  Vertex4D<Vertex4D<T,T>,T> T1_;
  Vertex4D<T,T> W2_;
  Vertex4D<Vertex4D<T,T>,T> T2_;

};


//--------------------------------- Constructor -------------------------------

template<class T> 
TTbarHH<T>::TTbarHH(T& t, std::vector<size_t> jetIndices, 
		    std::string name="", size_t storeNCandidates=0) :
  VContainer<TTbarHHData>(name, storeNCandidates),
  W1(Form("%s_W1", name.data()), storeNCandidates),
  W2(Form("%s_W2", name.data()), storeNCandidates),
  T1(Form("%s_T1", name.data()), storeNCandidates),
  T2(Form("%s_T2", name.data()), storeNCandidates),
  ind_(init(jetIndices)),
  W1_(t, t, ind_[0], "W1"),
  T1_(W1_, t, ind_[1], "T1"),
  W2_(t, t, ind_[2], "W2"),
  T2_(W2_, t, ind_[3], "T2")
{

  W1_.setNominalMass(80.2, 20.);
  T1_.setNominalMass(171.2, 21.);
  W2_.setNominalMass(80.2, 20);
  T2_.setNominalMass(171.2, 21.);

  stdMesg("  TTbarHH<%s> configuration:", humanTypeId(t).data());
  stdMesg("  for ttbar events with %d index pairs:", ind_[4].size());
  for (size_t i=0; i<ind_[4].size(); i++) {
    stdMesg("\t\t(%d, %d)", ind_[4][i].first, ind_[4][i].second);
  }
  stdMesg("  List of variables: %s,", list().data());
  stdMesg("  \t%s: %s,", W1_.name().data(), W1_.list().data());
  stdMesg("  \t%s: %s,", T1_.name().data(), T1_.list().data());
  stdMesg("  \t%s: %s,", W2_.name().data(), W2_.list().data());
  stdMesg("  \t%s: %s,", T2_.name().data(), T2_.list().data());
  stdMesg("  Object is %svalid!\n", (isValid() ? "" : "not "));

}


template<class T> 
std::vector<std::vector<std::pair<size_t, size_t> > >
TTbarHH<T>::init(std::vector<size_t>& jetIndices) {

  std::vector<std::vector<std::pair<size_t, size_t> > > ret;

  size_t n=jetIndices.size();
  if (n<6) {
    setValid(false);
    return ret;
  }

  std::vector<size_t> symm(6,6);
  symm[1]=0;
  symm[4]=3;
  std::vector<std::vector<size_t> > list;
  generateIndices(n, 6, list, &symm);
  stdMesg("init(): Generated %d indices", list.size());
  size_t listSize=list.size();
  for (size_t i=0; i<listSize; i++) {
    for (size_t j=i+1; j<listSize; j++) {
      if (list[i][0]!=list[j][3] || 
	  list[i][1]!=list[j][4] || 
	  list[i][2]!=list[j][5]) continue;
      list.erase(list.begin()+j);
      listSize=list.size();
      break;
    }
  }
  stdMesg("init(): Kept %d indices", list.size());

  std::vector<std::pair<size_t,size_t> > indW1, indT1;
  std::vector<std::pair<size_t,size_t> > indW2, indT2, indTT;

  for (size_t i=0; i<list.size(); i++) {
    init_insert_pair(
         init_insert_pair(
	      init_insert_pair(jetIndices[list[i][0]], 
			       jetIndices[list[i][1]], indW1), 
	      jetIndices[list[i][2]], indT1),
	 init_insert_pair(
	      init_insert_pair(jetIndices[list[i][3]], 
			       jetIndices[list[i][4]], indW2), 
	      jetIndices[list[i][5]], indT2),
	 indTT);
  }

  ret.push_back(indW1);
  ret.push_back(indT1);
  ret.push_back(indW2);
  ret.push_back(indT2);
  ret.push_back(indTT);
  return ret;
}


template<class T> 
size_t TTbarHH<T>::init_insert_pair(size_t p1, size_t p2, 
				    std::vector<std::pair<size_t,size_t> >& v){

  std::pair<size_t, size_t> p(p1,p2);
  size_t j;
  for (j=0; j<v.size(); j++) {
    if (v[j].first==p.first && v[j].second==p.second) break;
  }
  if (j==v.size()) {
    v.push_back(p);
    j=v.size()-1;
  }
  return j;
}


//-------------------------------- calculate() --------------------------------

template<class T> void TTbarHH<T>::calculate () {

  if (!isValid()) return;

  W1_.calculate();
  T1_.calculate();
  W2_.calculate();
  T2_.calculate();

  std::vector<std::pair<float, size_t> > chi2_list;

  for (size_t i=0; i<ttbarI().size(); i++) {
    // NOTE: it is important that in T1/T2 the first index runs over W1/W2
    Vertex4DData& t1 = T1_[ttbarI(i).first];
    Vertex4DData& t2 = T2_[ttbarI(i).second];
    Vertex4DData& w1 = W1_[T1_.ind(ttbarI(i).first).first];
    Vertex4DData& w2 = W2_[T2_.ind(ttbarI(i).second).first];

    if (w1.m==NOVAL_F || t1.m==NOVAL_F || 
	w2.m==NOVAL_F || t2.m==NOVAL_F) continue;

    float chi2=w1.chi2+t1.chi2+w2.chi2+t2.chi2;
    std::pair<float, size_t> p(chi2, i);
    chi2_list.push_back(p);
  }

  std::sort(chi2_list.begin(), chi2_list.end(),
	    std::less<std::pair<float, size_t> >());
  
  clear();
  for (size_t i=0; i<ttbarI().size(); i++) {
    TTbarHHData tt;
    size_t j=chi2_list[i].second;

    // NOTE: it is important that jn T1/T2 the first index runs over W1/W2
    Vertex4DData& t1 = T1_[ttbarI(j).first];
    Vertex4DData& t2 = T2_[ttbarI(j).second];
    Vertex4DData& w1 = W1_[T1_.ind(ttbarI(j).first).first];
    Vertex4DData& w2 = W2_[T2_.ind(ttbarI(j).second).first];

    stdMesg("  calculate(): %d: chi2=%f of %d", i, chi2_list[i].first, j);
    stdMesg("               m_w1=%f, m_t1=%f, m_w2=%f, m_t2=%f", 
	    w1.m, t1.m, w2.m, t2.m);

    tt.chi2=chi2_list[i].first;
    tt.W1q1=W1_.ind(T1_.ind(ttbarI(j).first).first).first;
    tt.W1q2=W1_.ind(T1_.ind(ttbarI(j).first).first).second;
    tt.T1b=T1_.ind(ttbarI(j).first).second;
    tt.W2q1=W2_.ind(T2_.ind(ttbarI(j).second).first).first;
    tt.W2q2=W2_.ind(T2_.ind(ttbarI(j).second).first).second;
    tt.T2b=T2_.ind(ttbarI(j).second).second;

    push_back(tt);
    W1.push_back(w1);
    T1.push_back(t1);
    W2.push_back(w2);
    T2.push_back(t2);
  }

}


//--------------------------------- addBranch() -------------------------------

template<class T> void TTbarHH<T>::addBranch(TTree* tree) {
  if (!isValid()) {
    stdErr("addBranch(): Object isn't valid, can't add it to tree\n");
    return;
  }
  
  VContainer<TTbarHHData>::addBranch(tree);
  W1.addBranch(tree);
  W2.addBranch(tree);
  T1.addBranch(tree);
  T2.addBranch(tree);
}

//--------------------------------- setBranch() -------------------------------

template<class T> void TTbarHH<T>::setBranch() {
  if (!isValid()) {
    stdErr("addBranch(): Object isn't valid, can't add it to tree\n");
    return;
  }

  VContainer<TTbarHHData>::setBranch();
  // A trick here. I want to use these containers only to set the branches
  W1.setBranch();
  W2.setBranch();
  T1.setBranch();
  T2.setBranch();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
