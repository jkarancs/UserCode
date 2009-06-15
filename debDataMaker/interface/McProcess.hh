#ifndef SusyAnalysis_debDataMaker_McProcess_hh_
#define SusyAnalysis_debDataMaker_McProcess_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      McProcess
// 
/**\class McProcess McProcess.hh 
		SusyAnalysis/debDataMaker/interface/McProcess.hh

 Description:     

      
 Usage:


    example:               Mo
                         /   \
                       Da1  Da2
                       / \    \
                     Da3 Da4  Da5

    transforms to:   Mo->Da1,Da2
                     Da1->Da3,Da4
                     Da2->Da5


    in ".py" file:
      mcProcessConfig = cms.PSet(
      genParticles = cms.InputTag("genParticles","","HLT"),
      storeNParticles = cms.int32(numberOfParticlesInTheTree),
      processTree  = cms.vstring(
        'Mo(pdgId),Da1(pdgId),Da2(pdgId)',
        'Da1(pdgId),Da3(pdgId),Da4(pdgId)',
        'Da2(pdgId),Da5(pdgId)')
      )
   _________________________________________________________________________
  |                                                                         |
  | Particles with the same pdgId have to be written one after the other!!! |
  |        'pi0(111),e1(11),gamma(22),e2(11)'    INCORRECT                  |
  |        'pi0(111),gamma(22),e1(11),e2(11)'    CORRECT                    |
  |        'pi0(111),e1(11),e2(11),gamma(22)'    CORRECT (cause the same)   |
  |_________________________________________________________________________|

    in ".cc" file:

      proc.clear();
      int v;
      v=proc.findProcess(iEvent);
      if (v!=0){
        proc.set(iEvent,0);
        proc.print(3);
      }


 Implementation:

   List of parameters to steer the object with (passed in iConfig):
      edm::InputTag triggerResults_,       : owned by this class
      std::vector<std::string> pathNames_, : owned by this class    

   iConfig is passed only through the contructor. 

   !!!! See usage of inherited functions in Data.hh source code !!!!

   The following fuctions should be overloaded here according to the exact 
   definition of D in Data<D> :

      void set(const edm::Trigger&) (virtual):
         that implements reading variables of D from the CMSSW framework

      void calculate() (virtual):
         that calculates values that depend on other data models

      int passed(std::string selection) (virtual):
         if selectionType is set, returns the result of the selections. The
         selections are implemented in this function.

*/
//
// Original Author:  Attila ARANYI
//         Created:  Wed Jun 03 10:28:26 CET 2009
// $Id: McProcess.hh,v 1.2 2009/06/14 05:49:35 aranyi Exp $
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SusyAnalysis/debDataMaker/interface/Data.hh"
#include "SusyAnalysis/debDataMaker/interface/McParticleData.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T> class McProcess : 
public Data<McParticleData<> >{
						// D:=ParticleData

 public:
	 
  McProcess(const edm::ParameterSet& iConfig);
  McProcess() { stdErr("  Process<%s> configuration missing\n", 
		     typeid(T).name()); }
  inline McParticleData<>& McParticle(unsigned int i) { return *data(i); }
  // Inherited functions to be overloaded
  void set(const edm::Event&,unsigned int);
  void calculate ();
  int passed(std::string selection);

  // Introduce new variables and functions
  int findProcess(const edm::Event&);

 private:

   std::vector<std::string> processTreePara_;
   edm::InputTag genParticles_;

   struct processBranch_ {

     std::string Mo_name;
     int Mo_pdgId;
     int Mo_idx;
     int sort_Mo_idx;
     int Mo_level;

     std::string name;
     int pdgId;
     int idx;
     int sort_idx;
     int level;
     std::vector<int> matched_idx;

     unsigned int nDa;
     int Da_level;
     std::vector<std::string> Da_name;
     std::vector<int> Da_pdgId;
     std::vector<int> Da_idx;
     std::vector<int> sort_Da_idx;

     processBranch_();
     processBranch_(std::string&);
     void printBranch_(int) const;
     void clearBranch_();

   };

   struct processTree_ {
	   
     std::vector<processBranch_> Branch;

     processTree_();
     processTree_(std::vector<std::string> &);
     void print_(int) const;
     void clearTree_();
     
   };

   //bool compareTrees_(const edm::Event&,unsigned int&,int &,
   //  std::vector<int> &, bool & ,std::vector<processTree_> &,bool &);

   processTree_ tree;
   std::vector<processTree_> trees;
   //void importGlobalIdx(const edm::Event&,processTree_ &,int &);

    std::vector<int> findParticle(const edm::Event&,int,int);
    bool accepted(const edm::Event&,int,int);
    void findtrees(const edm::Event&,int,int,int);
    unsigned int getIncNum(processBranch_&,int);
};

//--------------------------------- Constructor -------------------------------
/*
   List of parameters to gear the object with (passed in iConfig):
      edm::InputTag triggerResults_,       : owned by this class
      std::vector<std::string> pathNames_, : owned by this class      
*/

template<class T> McProcess<T>::McProcess(const edm::ParameterSet& iConfig) : 
  Data<McParticleData<> >(iConfig.getParameter<int>("storeNParticles")){
  
  genParticles_= iConfig.getParameter<edm::InputTag>("genParticles");
  processTreePara_=
    iConfig.getParameter< std::vector<std::string> >("processTree");

  processTree_ t(processTreePara_);
   tree=t;
}

//----------------------------------- set() -----------------------------------
template<class T> void McProcess<T>::set(const edm::Event& iEvent,
  unsigned int numProc) {

  if (!isValid()) return;

  edm::Handle<edm::View<T> > particleHandle;
  iEvent.getByLabel(genParticles_, particleHandle );
  if (!particleHandle.isValid()){
    stdErr("set() : Invalid tag %s", tag().label().data());
    return;
  }

  std::vector<const T *> Particles;

      for(typename edm::View<T>::const_iterator p = particleHandle->begin();
	p != particleHandle->end(); ++ p ) {
	Particles.push_back( & * p );
      }

  int idx;
  int ind;
  processBranch_ lastBranch(processTreePara_[0]);

  clear();

  for(unsigned int i=0;i<trees[numProc].Branch.size();i++){
      push_back(*(new McParticleData<>));
  }

  for(unsigned int i=0;i<trees[numProc].Branch.size();i++){
  
      for(typename edm::View<T>::const_iterator p = particleHandle->begin();
	p != particleHandle->end(); ++ p ) {
	
	idx =  p - particleHandle->begin();

        if (idx==trees[numProc].Branch[i].matched_idx[0]){

          //if (i!=0) k++;

          ind=trees[numProc].Branch[i].sort_idx;

          McParticle(ind).e = p->energy();
	  McParticle(ind).px = p->px();
	  McParticle(ind).py = p->py();
	  McParticle(ind).pz = p->pz();
	  McParticle(ind).m = p->mass();
	  McParticle(ind).p = p->p();
	  McParticle(ind).et = p->et();
	  McParticle(ind).pt = p->pt();
	  McParticle(ind).phi = p->phi();
	  McParticle(ind).eta = p->eta();

	  McParticle(ind).mo1 =trees[numProc].Branch[i].sort_Mo_idx;
	  //McParticle(i).mo2 =trees[numProc].Branch[i].sort_Mo_idx;

          for (unsigned int l=0;l<trees[numProc].Branch[i].Da_idx.size();l++){

            McParticle(ind).da[l]=trees[numProc].Branch[i].sort_Da_idx[l];

          }
          
          McParticle(ind).pdg=p->pdgId();

        } 

      }
  }
}
  
//-------------------------------- calculate() --------------------------------

template<class T> void McProcess<T>::calculate () { 
}
  
//--------------------------------- passed() ----------------------------------

template<class T> int McProcess<T>::passed(std::string selection) { 
  return 1; 
}

//-----------------------------------findProcess()-----------------------------
template<class T> int McProcess<T>::findProcess(
  const edm::Event& iEvent) {
  

  stdMesg("%s \n", "  findprocess");
  int level_size=tree.Branch[tree.Branch.size()-1].level+1;

  unsigned int axusize;

  findtrees(iEvent,0,0,0);

  if (trees.size()==0){
    //std::cout<<"trees size= "<<trees.size()<<std::endl;
    stdMesg("  Number of processes found: %d", trees.size());
    return 0;
  }

  for(int j=1;j<level_size;j++){
    for(unsigned int k=0;k<tree.Branch.size();k++){
      axusize=trees.size();
      for(unsigned int i=0;i<axusize;i++){
        if (tree.Branch[k].level==j)
          findtrees(iEvent,i,j,k);
      }
    }
  }

  //trees[0].print_(0);
  //trees[trees.size()-1].print_(0); 

  //std::cout<<std::endl<<"trees size= "<<trees.size()<<std::endl;
  stdMesg("  Number of processes found: %d", trees.size());
//   std::cout<<std::endl<<"matched idx= ";
//   for(unsigned int i=0;i<trees.size();i++){
//     std::cout<<trees[i].Branch[0].matched_idx[0]<<" ";
//   } 
//   std::cout<<std::endl<<std::endl;

  return trees.size();

}

//-----------------------------------findtrees()-------------------------------
template<class T> void McProcess<T>::findtrees(
  const edm::Event& iEvent,int tree_idx,int level,int Branch_idx) {

  std::vector<int> pidx;
  std::vector<int> matched_pidx;

  unsigned int IncNum=0;
  
  if (Branch_idx==0){
    pidx=findParticle(iEvent,NOVAL_I,tree.Branch[Branch_idx].pdgId);
    if(pidx.size()==0)
      return;

    for (unsigned int j=0;j<pidx.size();j++){
      if(accepted(iEvent,pidx[j],Branch_idx)){
	matched_pidx.resize(matched_pidx.size()+1);
	matched_pidx[matched_pidx.size()-1]=pidx[j];
      }
    }

    trees.resize(matched_pidx.size());
    for (unsigned int i=0;i<trees.size();i++){
      trees[i]=tree;
      trees[i].Branch[0].matched_idx.resize(1);
      trees[i].Branch[0].matched_idx[0]=matched_pidx[i];
    }

  }else{
      int Mo_idx;
      Mo_idx=tree.Branch[Branch_idx].Mo_idx;
      pidx=findParticle(iEvent,trees[tree_idx].Branch[Mo_idx].matched_idx[0],
	tree.Branch[Branch_idx].pdgId);

      for (unsigned int j=0;j<pidx.size();j++){
	if(accepted(iEvent,pidx[j],Branch_idx)){
	  matched_pidx.resize(matched_pidx.size()+1);
	  matched_pidx[matched_pidx.size()-1]=pidx[j];
	}
      }

      IncNum=getIncNum(tree.Branch[Mo_idx],tree.Branch[Branch_idx].pdgId);

      
      if(IncNum>1 && IncNum!=matched_pidx.size()){
        stdErr("incorrect process declaration\n");
      }
      

      if(IncNum>1 && IncNum==matched_pidx.size()){
        unsigned int indd=0;
        unsigned int first=0;

        for(unsigned int i=0;i<tree.Branch[Mo_idx].nDa;i++){
          if(abs(tree.Branch[Mo_idx].Da_pdgId[i])==
            abs(tree.Branch[Branch_idx].pdgId)){
            first=i;
            break;
          }
        }

        for(unsigned int i=0;i<tree.Branch[Mo_idx].nDa;i++){
          if(tree.Branch[Mo_idx].sort_Da_idx[i]==
            tree.Branch[Branch_idx].sort_idx)
            indd=i-first;
        }

        trees[tree_idx].Branch[Branch_idx].matched_idx.resize(1);
        trees[tree_idx].Branch[Branch_idx].matched_idx[0]=
          matched_pidx[indd];
      }
      
      if(IncNum==1){
        trees[tree_idx].Branch[Branch_idx].matched_idx.resize(1);
        trees[tree_idx].Branch[Branch_idx].matched_idx[0]=matched_pidx[0];

	if (matched_pidx.size()>1){
	  unsigned int diff=matched_pidx.size()-1;
  
	  int ind=1;
	  trees.resize(trees.size()+diff);
	  for (unsigned int i=trees.size()-diff;i<trees.size();i++){
	    trees[i]=trees[tree_idx];	
	    trees[i].Branch[Branch_idx].matched_idx.resize(1);
	    trees[i].Branch[Branch_idx].matched_idx[0]=matched_pidx[ind];
	    ind++;
	  }
  
	}
      }
  }

}
//----------------------------------getIncNum()--------------------------------

template<class T> unsigned int McProcess<T>::getIncNum(processBranch_& Branch,
  int pdg){

  unsigned int IncNum=0;

  for(unsigned int i=0;i<Branch.nDa;i++){
    if(abs(Branch.Da_pdgId[i])==abs(pdg))
      IncNum++;
  }

  return IncNum;
}
//-----------------------------------accepted()--------------------------------

template<class T> bool McProcess<T>::accepted(
  const edm::Event& iEvent,int idx,int Branch_idx) {
  
  bool b=true;
  bool axub;
  std::vector<int> pidx;


  for (unsigned int i=0;i<tree.Branch[Branch_idx].nDa;i++){


    pidx=findParticle(iEvent,idx,tree.Branch[Branch_idx].Da_pdgId[i]);

      if (tree.Branch[Branch_idx].Da_idx[i]==NOVAL_I){
	if (pidx.size()==0){
	  return false;
	}
      }else{
	axub=false;
	for(unsigned int j=0;j<pidx.size();j++){
	  if(accepted(iEvent,pidx[j],tree.Branch[Branch_idx].Da_idx[i]))
	    axub=true;
	}
	if (!axub)
	  return false;
      }
    }

  return b;
}

//-----------------------------------findParticle()----------------------------
template<class T> std::vector<int> McProcess<T>::findParticle(
  const edm::Event& iEvent,int idx,int pdg){

  std::vector<int> pidx;

  if (!isValid()) return pidx;

  edm::Handle<edm::View<T> > particleHandle;
  iEvent.getByLabel(genParticles_, particleHandle );
  if (!particleHandle.isValid()){
    stdErr("set() : Invalid tag %s", tag().label().data());
    return pidx;
  }
  std::vector<const T *> Particles;
  for(typename edm::View<T>::const_iterator p = particleHandle->begin();
    p != particleHandle->end(); ++ p ) {
    Particles.push_back( & * p );
  }


  int axuidx  = -1;

  typename std::vector<const T *>::const_iterator found;

  if (idx==NOVAL_I){
    for(typename edm::View<T>::const_iterator p = particleHandle->begin();
      p != particleHandle->end(); ++ p ) {
      
      axuidx =  p - particleHandle->begin();

      if (abs(p->pdgId())==abs(pdg)){
        pidx.resize(pidx.size()+1);
        pidx[pidx.size()-1]=axuidx;
      }
    }
  }else{
    for(typename edm::View<T>::const_iterator p = particleHandle->begin();
      p != particleHandle->end(); ++ p ) {
      
      axuidx =  p - particleHandle->begin();

      if (idx==axuidx){
        for(unsigned int i = 0; i < p->numberOfDaughters(); ++i ) {
	  const T * da = p->daughter(i);

          if (abs(da->pdgId())==abs(pdg)){
            found = find(Particles.begin(), Particles.end(), da);
	    if(found != Particles.end()) 
	      idx = found - Particles.begin();          
            pidx.resize(pidx.size()+1);
            pidx[pidx.size()-1]=idx;
          } 
        }
      }
    }
  }

  return pidx;
}

//----------------------- processTree_ constructor ----------------------------
template<class T> McProcess<T>::processTree_::processTree_(){

}

//----------------------- processTree_ constructor ----------------------------
template<class T> McProcess<T>::processTree_::
  processTree_(std::vector<std::string> & processTreePara_){

  Branch.resize(Branch.size()+processTreePara_.size());

  for(unsigned int i=0;i<processTreePara_.size();i++){
    processBranch_ brr(processTreePara_[i]);
    Branch[i]=brr;
    Branch[i].idx=i;
  }
   
  for(unsigned int i=0;i<processTreePara_.size();i++){
    for(unsigned int j=0;j<Branch[i].nDa;j++){
      Branch[i].Da_idx[j]=NOVAL_I;
      for(unsigned int k=i;k<processTreePara_.size();k++){
      if (Branch[i].Da_name[j]==Branch[k].name) Branch[i].Da_idx[j]=k;
      }
    }
  }

  Branch[0].Mo_name="";
  Branch[0].Mo_pdgId=NOVAL_I;
  Branch[0].Mo_idx=NOVAL_I;
  Branch[0].sort_Mo_idx=NOVAL_I;
  Branch[0].Mo_level=NOVAL_I;

  Branch[0].level=0;
  Branch[0].Da_level=1;



  for(unsigned int i=1;i<processTreePara_.size();i++){
    for(unsigned int j=0;j<i;j++){
      for(unsigned int k=0;k<Branch[j].nDa;k++){
        if (Branch[i].name==Branch[j].Da_name[k]){
          Branch[i].Mo_name=Branch[j].name;
          Branch[i].Mo_pdgId=Branch[j].pdgId;
          Branch[i].Mo_idx=Branch[j].idx;
        }
      }
    }
  }  

  for(unsigned int i=1;i<processTreePara_.size();i++){
    Branch[i].Mo_level=Branch[Branch[i].Mo_idx].level;
    Branch[i].level=Branch[Branch[i].Mo_idx].Da_level;
    Branch[i].Da_level=Branch[i].level+1;
  }

  unsigned int k=0;
  Branch[0].sort_idx=0;
  for(unsigned int j=0;j<Branch[0].nDa;j++){
    k++;
    Branch[0].sort_Da_idx[j]=k;
  }

  for(unsigned int i=1;i<processTreePara_.size();i++){

    Branch[i].sort_Mo_idx=Branch[Branch[i].Mo_idx].sort_idx;

    for(unsigned int ii=0;ii<Branch[Branch[i].Mo_idx].nDa;ii++){
      if (Branch[Branch[i].Mo_idx].Da_idx[ii]==Branch[i].idx)
        Branch[i].sort_idx=Branch[Branch[i].Mo_idx].sort_Da_idx[ii];
    }

    for(unsigned int j=0;j<Branch[i].nDa;j++){
      k++;Branch[i].sort_Da_idx[j]=k;
    }
    
  }

  std::string str;

  for(unsigned int i=0;i<processTreePara_.size();i++){
    for(unsigned int j=0;j<Branch[i].nDa;j++){
      if(Branch[i].Da_idx[j]==NOVAL_I){
        Branch.resize(Branch.size()+1);
        str=Branch[i].Da_name[j]+"(0)";
        processBranch_ branch_(str);
        Branch[Branch.size()-1]=branch_;
        Branch[Branch.size()-1].clearBranch_();

          Branch[Branch.size()-1].Mo_name=Branch[i].name;
          Branch[Branch.size()-1].Mo_pdgId=Branch[i].pdgId;
          Branch[Branch.size()-1].Mo_idx=Branch[i].idx;
          Branch[Branch.size()-1].sort_Mo_idx=Branch[i].sort_idx;
          Branch[Branch.size()-1].Mo_level=Branch[i].level; 

          Branch[Branch.size()-1].name=Branch[i].Da_name[j];
          Branch[Branch.size()-1].pdgId=Branch[i].Da_pdgId[j];
          Branch[Branch.size()-1].idx=Branch[i].Da_idx[j];
          Branch[Branch.size()-1].sort_idx=Branch[i].sort_Da_idx[j];
          Branch[Branch.size()-1].level=Branch[i].level+1;
      }
    }
  }

}

//-------------------------- processTree_ print() -----------------------------

template<class T> void McProcess<T>::processTree_::print_(int x) const{

   for(unsigned int i=0;i<Branch.size();i++){
      std::cout<<std::endl;
      Branch[i].printBranch_(x);
      std::cout<<std::endl;
   }
   std::cout<<std::endl;
   std::cout<<"____________________________________________"<<std::endl;

}

//-------------------------- processTree_ clearTree_() ------------------------

template<class T> void McProcess<T>::processTree_::clearTree_() {

   for(unsigned int i=0;i<Branch.size();i++){
      Branch[i].clearBranch_();
   }

}

//----------------------- processBranch_ constructor --------------------------
template<class T> McProcess<T>::processBranch_::processBranch_(){
}

//----------------------- processBranch_ constructor --------------------------
template<class T> McProcess<T>::processBranch_::processBranch_(
  std::string & str){

  nDa=0;
  
  char* last;
  last=&str[str.size()-1];
  std::string::iterator it;

  sort_idx=NOVAL_I;
  sort_Mo_idx=NOVAL_I;  

  level=NOVAL_I;
  Mo_level=NOVAL_I;
  Da_level=NOVAL_I;
   
  for ( it=str.begin() ; it < str.end(); it++ )
    if(*it==',') nDa++;

   Da_name.resize(Da_name.size()+nDa);
   Da_pdgId.resize(Da_pdgId.size()+nDa);
   Da_idx.resize(Da_idx.size()+nDa);
   sort_Da_idx.resize(sort_Da_idx.size()+nDa);

  std::string ds,di;


  it=str.begin();
  for (unsigned int i=0;i<nDa+1;i++){
    while (*it != '('){ 
        ds+=*it;
        it++;
    }
      it++;
    while (*it != ')'){ 
        di+=*it;
        it++;
    }
      it++;
    if (i==0){
      name=ds;
      pdgId=string2int(di);
    }else{
      Da_name[i-1]=ds;
      Da_pdgId[i-1]=string2int(di);
      sort_Da_idx[i-1]=NOVAL_I;
    }
    ds="";
    di="";
    if(i!=nDa+1) it++;
  }
}

//----------------------- processBranch_ print() ------------------------------
template<class T> void McProcess<T>::processBranch_::printBranch_(int x) const{

  if (x>=3){
    std::cout<<std::endl;
    std::cout<<"Mo_name="<<Mo_name<<std::endl;
    std::cout<<"Mo_pdgId="<<Mo_pdgId<<std::endl;
    std::cout<<"Mo_idx="<<Mo_idx<<std::endl;
    std::cout<<"sort_Mo_idx="<<sort_Mo_idx<<std::endl;
    std::cout<<"Mo_level="<<Mo_level<<std::endl;
    std::cout<<std::endl;
  }
    
    std::cout<<"name="<<name<<std::endl;
  if (x>=1){
    std::cout<<"pdgId="<<pdgId<<std::endl;
    std::cout<<"idx="<<idx<<std::endl;
    std::cout<<"sort_idx="<<sort_idx<<std::endl;
    std::cout<<"level="<<level<<std::endl;
    std::cout<<std::endl;
  }
    std::cout<<"matched_idx=";
    if (matched_idx.size()==0)
      std::cout<<NOVAL_I;
    for (unsigned int i=0;i<matched_idx.size();i++){      
      std::cout<<matched_idx[i]<<" ";
    }
  if(x>=2){
    std::cout<<std::endl;
    std::cout<<"Da_level="<<Da_level<<std::endl;
    for (unsigned int i=0;i<nDa;i++){
      std::cout<<"Da_name["<<i+1<<"]="<<Da_name[i]<<std::endl;
      std::cout<<"Da_pdgId["<<i+1<<"]="<<Da_pdgId[i]<<std::endl;
      std::cout<<"Da_idx["<<i+1<<"]="<<Da_idx[i]<<std::endl;
      std::cout<<"sort_Da_idx["<<i+1<<"]="<<sort_Da_idx[i]<<std::endl;
    }
    std::cout<<std::endl;
  }
}

//----------------------- processBranch_ clearBranch() ------------------------
template<class T> void McProcess<T>::processBranch_::clearBranch_() {

  Mo_name="";
  Mo_pdgId=NOVAL_I;
  Mo_idx=NOVAL_I;
  sort_Mo_idx=NOVAL_I;
  Mo_level=NOVAL_I;

  name="";
  pdgId=NOVAL_I;
  idx=NOVAL_I;
  sort_idx=NOVAL_I;
  level=NOVAL_I;

  matched_idx.resize(0);

  for (unsigned int i=0;i<nDa;i++){
    Da_name[i]="";
    Da_pdgId[i]=NOVAL_I;
    Da_idx[i]=NOVAL_I;
    sort_Da_idx[i]=NOVAL_I;
  }

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
