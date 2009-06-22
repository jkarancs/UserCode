#ifndef SusyAnalysis_debDataMaker_McProcess2_hh_
#define SusyAnalysis_debDataMaker_McProcess2_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      McProcess2
// 
/**\class McProcess2 McProcess2.hh SusyAnalysis/debDataMaker/interface/McProcess2.hh

 Description: <one line class summary>

 Implementation:

   List of parameters to steer the object with (passed through iConfig):
      InputTag objectTag,  : owned by Data<D> but decided here if set

   !!!! See usage of inherited functions in Data.hh source code !!!!

   The following fuctions should be overloaded here according to the exact 
   definition of D in Data<D> :

      void set(const edm::Event&) (virtual):
         implements reading variables of D from the CMSSW framework

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Sun Jun 21 13:05:21 CET 2009
// $$
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SusyAnalysis/debDataMaker/interface/Data.hh"
#include "SusyAnalysis/debDataMaker/interface/McParticleData.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T,int N> class McProcess2 : public Data<McParticleData<N> >{
 public:
	 
  McProcess2(const edm::ParameterSet& iConfig);
  McProcess2() { 
    Data<McParticleData<N> >::stdErr("  Process<%s,%d> configuration "
				     "missing\n", typeid(T).name(), N); 
  }

  inline McParticleData<N>& particle(unsigned int i) { 
    return *Data<McParticleData<N> >::data(i); 
  }

  void set(const edm::Event&,unsigned int);
  void calculate () {} ;
  int passed(std::string selection) { return NOVAL_I; };

  void addBranch(TTree*, std::string);
  void setBranch();

  unsigned int findProcess(const edm::Event&);

 private:
  struct DecayVertex {
    std::string name;
    std::vector<int> pdg;
    std::vector<DecayVertex*> da;
    const reco::Candidate* p;
    void print() {
      printf("%s (", name.data());
      for (size_t j=0; j<pdg.size(); ++j) printf("%d ", pdg[j]); printf(")");
      if (da.size()>0) printf(" -> ");
      for (size_t j=0; j<da.size(); ++j) printf("%s ", da[j]->name.data());
      printf("\n");
    }
  };

  std::vector<const reco::Candidate *> genParticles_;
  std::vector<DecayVertex> vertices_;
  std::vector<std::vector<DecayVertex> > processes_; // IMPORTANT!!!: in
  // processes_ the da-pointers are not set correctly at this point

  bool findVertex(std::vector<const reco::Candidate *>&,
		  DecayVertex*,
		  DecayVertex*,
		  std::vector<DecayVertex>*);

};

//--------------------------------- Constructor -------------------------------

template<class T,int N> 
McProcess2<T,N>::McProcess2(const edm::ParameterSet& iConfig) : 
  Data<McParticleData<N> >(
       iConfig.getParameter<std::vector<std::string> >("processTree").size()) {
  
  Data<McParticleData<N> >::setTag(
			  iConfig.getParameter<edm::InputTag>("genParticles"));

  std::vector<std::string> vertexList=
    iConfig.getParameter<std::vector<std::string> >("processTree");

  std::vector<std::string> daughters;
  for (size_t i=0; i<vertexList.size(); i++) {
    std::string v=vertexList[i];
    v.erase(std::remove(v.begin(), v.end(), ' '), v.end());
    std::string da_list="";
    size_t decay=v.find("->");
    if (decay!=std::string::npos) {
      da_list=v.substr(decay+2);
      v.erase(decay);
    } else if (i==0) {
      Data<McParticleData<N> >::stdErr("init(): The first particle %s in" \
				"processTree does not decay!!!\n", v.data()); 
      Data<McParticleData<N> >::setValid(false);
      return;
    }
    size_t par=v.find("(");
    if (par==std::string::npos || v.find(")")==std::string::npos){
      Data<McParticleData<N> >::stdErr("init(): Particle definition %s " \
				       "is incorrect!!!\n", v.data());
      Data<McParticleData<N> >::setValid(false);
      return;
    }
    DecayVertex vertex;
    vertex.name=v.substr(0, par);
    par++;
    size_t coma=v.find_first_of(",");
    while (coma!=std::string::npos) {
      vertex.pdg.push_back(atoi(v.substr(par, coma-par).data()));
      par=coma+1;
      coma=v.find_first_of(",", par);
    }
    vertex.pdg.push_back(atoi(v.substr(par, v.find(")")-par).data()));
    vertices_.push_back(vertex);
    daughters.push_back(da_list);
  } // for i

  for (size_t i=0; i<vertices_.size(); i++) {
    size_t par=0;
    std::vector<std::string> da;
    size_t coma=daughters[i].find_first_of(",");
    while (coma!=std::string::npos) {
      da.push_back(daughters[i].substr(par, coma-par));
      par=coma+1;
      coma=daughters[i].find_first_of(",", par);
    }
    if (daughters[i]!="") da.push_back(daughters[i].substr(par));
    
    for (size_t j=0; j<da.size(); j++) {
      size_t ida=0;
      for (ida=0; ida<vertices_.size(); ida++) {
	if (vertices_[ida].name==da[j]) break;
      }
      if (ida==vertices_.size()) {
	Data<McParticleData<N> >::stdErr("init(): Cannot find %s, daughter" \
			   " of %s\n", da[j].data(), vertices_[i].name.data());
	Data<McParticleData<N> >::setValid(false);
	continue;
      }
      vertices_[i].da.push_back(&vertices_[ida]);
    } // for j

    vertices_[i].print();
  } // for i

} // end of constructor


//----------------------------- findProcess () --------------------------------

template<class T,int N> 
unsigned int McProcess2<T,N>::findProcess(const edm::Event& iEvent) {

  if (!Data<McParticleData<N> >::isValid()) return 0;

  edm::Handle<reco::CandidateView> genPartHandle;
  iEvent.getByLabel(Data<McParticleData<N> >::tag(), genPartHandle);
  if (!genPartHandle.isValid()) {
    Data<McParticleData<N> >::stdErr("set() : Invalid tag %s", 
			       Data<McParticleData<N> >::tag().label().data());
    Data<McParticleData<N> >::setValid(false);
    return 0;
  }

  for(reco::CandidateView::const_iterator iPart=genPartHandle->begin();
      iPart!=genPartHandle->end(); ++iPart) {
    genParticles_.push_back(&*iPart); 
  }

  findVertex(genParticles_);
  stdMesg("  Num of processes found: %d\n", processes_.size());

  return processes_.size();
}


//----------------------------------- set() -----------------------------------

template<class T,int N> 
void McProcess2<T,N>::set(const edm::Event& iEvent, unsigned int iProc) {

  if (!Data<McParticleData<N> >::isValid()) return;
  if (processes_.size()==0) findProcess(iEvent);
  
  if (iProc<processes_.size()) {
    for (size_t i=0; i<processes_[iProc].size(); i++) {
      const reco::Candidate* p=processes_[iProc][i].p;
      particle(i).e = p->energy();
      particle(i).px = p->px();
      particle(i).py = p->py();
      particle(i).pz = p->pz();
      particle(i).m = p->mass();
      particle(i).p = p->p();
      particle(i).et = p->et();
      particle(i).pt = p->pt();
      particle(i).phi = p->phi();
      particle(i).eta = p->eta(); 
      for (size_t j=0; j<processes_[iProc][i].da.size() && j<N; j++) {
	size_t k;
	for (k=0; k<vertices_.size(); k++) {
	  if (vertices_[i].da[j]==&vertices_[k]) break;
	}
	particle(i).da[j]=k;
	if (particle(k).mo1==-9999) {
	  particle(k).mo1=i;
	} else {
	  particle(k).mo2=i;
	}
      }
      particle(i).pdg = p->pdgId();
    }
  }
  processes_.clear();
  genParticles_.clear();

}

//---------------------------------- findVertex() -----------------------------
template<class T,int N>
bool McProcess2<T,N>::findVertex(std::vector<const reco::Candidate *>& genp,
				 DecayVertex* particle=NULL,
				 DecayVertex* mother=NULL,
				 std::vector<DecayVertex>* proc=NULL) {

  if (proc==NULL) {
    DecayVertex v=vertices_[0];
    for (size_t i=0; i<genp.size(); i++) {
      size_t j;
      for (j=0; j<v.pdg.size(); j++) if(genp[i]->pdgId()==v.pdg[j]) break;
      if (j!=v.pdg.size()) {
	v.p=genp[i];
	proc=new std::vector<DecayVertex>;
	proc->push_back(v);
	// Treat here is the whole process is just one particle
	size_t k;
	for (k=0; k<v.da.size(); k++) {
	  if (!findVertex(genp, v.da[k], &v, proc)) break;
	}
	if (k==v.da.size()) processes_.push_back(*proc);
	delete proc;
      }
    }
    if (processes_.size()!=0) return true;
    return false;
  }

  DecayVertex v=*particle;

  std::vector<const reco::Candidate *>::const_iterator mo;
  mo=find(genp.begin(), genp.end(), mother->p);
  for (size_t i=mo-genp.begin()+1; i<genp.size(); i++) {
  //for (size_t i=0; i<genp.size(); i++) {
    size_t j;
    for (j=0; j<v.pdg.size(); j++) {
      if(genp[i]->pdgId()==v.pdg[j]) {
	mo = find(genp.begin(), genp.end(), genp[i]->mother(0));
	if(mo!=genp.end()) if (genp[mo-genp.begin()]==mother->p) break;
	mo = find(genp.begin(), genp.end(), 
		  genp[i]->mother(genp[i]->numberOfMothers())-1);
	if(mo!=genp.end()) if (genp[mo-genp.begin()]==mother->p) break;
      }
    }
    if (j!=v.pdg.size()) {
      v.p=genp[i];
      proc->push_back(v);
      size_t k;
      for (k=0; k<v.da.size(); k++) {
	if (!findVertex(genp, v.da[k], &v, proc)) break;
      }
      if (k==v.da.size()) return true;
      proc->pop_back();
    }
  }

  return false;
}

//--------------------------------- addBranch() -------------------------------

template<class T,int N>
void McProcess2<T,N>::addBranch(TTree* tree, std::string name) {
  if (!Data<McParticleData<N> >::isValid()) {
    Data<McParticleData<N> >::stdErr("addBranch(): Object isn't valid, "
				     "can't add it to tree\n");
    return;
  }
  if (Data<McParticleData<N> >::tree_!=NULL) {
    Data<McParticleData<N> >::stdWarn("addBranch(): Object is already added "
				      "to a tree.\n");
    return;
  }
  Data<McParticleData<N> >::branch_=name;
  Data<McParticleData<N> >::tree_=tree;
  for (unsigned int i=0; i<vertices_.size(); i++) {
    std::ostringstream ss;
    ss<<name<<"_"<<vertices_[i].name<<"_"<<i;
    tree->Branch(ss.str().data(),&particle(i),particle(i).list().data());
  }
}


//--------------------------------- setBranch() -------------------------------

template<class T,int N> void McProcess2<T,N>::setBranch() {
  if (!Data<McParticleData<N> >::isValid()) {
    Data<McParticleData<N> >::stdErr("setBranch(): Object isn't valid, " \
				     "can't fill its branches.\n");
    return;
  }
  if (Data<McParticleData<N> >::tree_==NULL) {
    Data<McParticleData<N> >::stdErr("setBranch(): Object hasn't been added " \
				     "to tree. (Do it in the constructor!)\n");
    return;
  }
  for (unsigned int i=0; i<vertices_.size(); i++) {
    std::ostringstream ss;
    ss<<Data<McParticleData<N> >::branch_<<"_"<<vertices_[i].name<<"_"<<i;
    TBranch* br=Data<McParticleData<N> >::tree_->GetBranch(ss.str().data());
    if (br!=NULL) br->SetAddress(&particle(i));
    else Data<McParticleData<N> >::stdErr("setBranch(): Did not find branch " \
					  "%s in tree!!!\n", ss.str().data());
  }

}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
