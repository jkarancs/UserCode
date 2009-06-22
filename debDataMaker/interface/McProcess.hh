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
        'Mo(pdgId,pdgId,...),Da1(pdgId,pdgId,...),Da2(pdgId,pdgId,...)',
        'Da1(pdgId,pdgId,...),Da3(pdgId,pdgId,...),Da4(pdgId,pdgId,...)',
        'Da2(pdgId,pdgId,...),Da5(pdgId,...,pdgId,...)')
      )
   _________________________________________________________________________
  |                                                                         |
  | Particles with the same pdgId have to be written one after the other!!! |
  |        'pi0(111),e-(11),gamma(22),e+(-11)'   INCORRECT                  |
  |        'pi0(111),gamma(22),e-(11),e+(-11)'   CORRECT                    |
  |        'pi0(111),e-(11),e+(-11),gamma(22)'   CORRECT (cause the same)   |
  |_________________________________________________________________________|

    in ".cc" file:

      proc.clear();
      int a;                           //Number of processes found
      int b;
      a=proc.findProcess(iEvent);
      if (b<=a ){
        proc.set(iEvent,b);           //set the b. process
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
// $Id: McProcess.hh,v 1.7 2009/06/18 15:09:23 aranyi Exp $
//
//
//-----------------------------------------------------------------------------

#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SusyAnalysis/debDataMaker/interface/Data.hh"
#include "SusyAnalysis/debDataMaker/interface/McParticleData.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T,int N> class McProcess : 
public Data<McParticleData<N> >{
						// D:=ParticleData

 public:
	 
  McProcess(const edm::ParameterSet& iConfig);
  McProcess() { stdErr("  Process<%s> configuration missing\n", 
		     typeid(T).name()); }
  inline McParticleData<N>& McParticle(unsigned int i) 
    { return *Data<McParticleData<N> >::data(i); }
  // Inherited functions to be overloaded
  void set(const edm::Event&,unsigned int);
  void calculate ();
  int passed(std::string selection);

  // Introduce new variables and functions
  unsigned int findProcess(const edm::Event&);

 private:

   std::vector<std::string> processTreePara_;
   edm::InputTag genParticles_;

   struct processBranch_ {

     std::string Mo_name;
     std::vector<int> Mo_pdgId;
     int Mo_idx;
     int sort_Mo_idx;
     int Mo_level;

     std::string name;
     std::vector<int> pdgId;
     int idx;
     int sort_idx;
     int level;
     std::vector<int> matched_idx;

     unsigned int nDa;
     int Da_level;
     std::vector<std::string> Da_name;
     std::vector<std::vector<int> > Da_pdgId;
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

   processTree_ tree;
   std::vector<processTree_> trees;

    std::vector<int> findParticle(const edm::Event&,int,std::vector<int>);
    bool accepted(const edm::Event&,int,int);
    void findtrees(const edm::Event&,int,int,int);
    unsigned int getIncNum(processBranch_&,std::vector<int>);
    bool isEqualPdg(int,std::vector<int>);
};

//typedef McProcess<reco::Candidate,2> McProcess_b;

//template <class T,int N=2> typedef McProcess<T,2> template <class T> McProcess<T>;


//--------------------------------- Constructor -------------------------------
/*
   List of parameters to gear the object with (passed in iConfig):
      edm::InputTag triggerResults_,       : owned by this class
      std::vector<std::string> pathNames_, : owned by this class      
*/

template<class T,int N> McProcess<T,N>::
  McProcess(const edm::ParameterSet& iConfig) : 
  Data<McParticleData<N> >(iConfig.getParameter<int>("storeNParticles")){
  
  genParticles_= iConfig.getParameter<edm::InputTag>("genParticles");
  processTreePara_=
    iConfig.getParameter< std::vector<std::string> >("processTree");

    processBranch_ Branch(processTreePara_[0]);
    //Branch.printBranch_(3);
   processTree_ t(processTreePara_);
   tree=t;
}

//----------------------------------- set() -----------------------------------
template<class T,int N> void McProcess<T,N>::set(const edm::Event& iEvent,
  unsigned int numProc) {

  if (!Data<McParticleData<N> >::isValid()) return;

  edm::Handle<edm::View<T> > particleHandle;
  iEvent.getByLabel(genParticles_, particleHandle );
  if (!particleHandle.isValid()){
    stdErr("set() : Invalid tag %s", Data<McParticleData<N> >::
      tag().label().data());
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

  Data<McParticleData<N> >::clear();

  for(unsigned int i=0;i<trees[numProc].Branch.size();i++){
      McParticleData<N> new_obj;
      push_back(new_obj);
  }

  for(unsigned int i=0;i<trees[numProc].Branch.size();i++){
  
      for(typename edm::View<T>::const_iterator p = particleHandle->begin();
	p != particleHandle->end(); ++ p ) {
	
	idx =  p - particleHandle->begin();

        if (idx==trees[numProc].Branch[i].matched_idx[0]){

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

template<class T,int N> void McProcess<T,N>::calculate () { 
}
  
//--------------------------------- passed() ----------------------------------

template<class T,int N> int McProcess<T,N>::passed(std::string selection) { 
return 1;
}

//-----------------------------------findProcess()-----------------------------
template<class T,int N> unsigned int McProcess<T,N>::findProcess(
  const edm::Event& iEvent) {
  

  Data<McParticleData<N> >::stdMesg("%s", "  findprocess");
  int level_size=tree.Branch[tree.Branch.size()-1].level+1;

  //tree.print_(3);

  trees.resize(0);

  unsigned int axusize;

  findtrees(iEvent,0,0,0);



  if (trees.size()==0){
    stdMesg("  Number of processes found: %d \n", trees.size());
    return 0;
  }	    

  for(int j=1;j<level_size;j++){
    for(unsigned int k=0;k<tree.Branch.size();k++){
      if (tree.Branch[k].level==j){
	axusize=trees.size();
	for(unsigned int i=0;i<axusize;i++){        
	  findtrees(iEvent,i,j,k);  
	}
      }
    }
  }


//  trees[trees.size()-1].print_(3); 
  
  stdMesg("  Number of processes found: %d", trees.size());  

  for(unsigned int i=0;i<trees.size();i++){
    trees[i].print_(0);
  }

  //tree.print_(3);
//   std::cout<<std::endl<<"matched idx= ";
//   for(unsigned int i=0;i<trees.size();i++){
//     std::cout<<trees[i].Branch[0].matched_idx[0]<<" ";
//   } 
//   std::cout<<std::endl<<std::endl;

  return trees.size();

}

//-----------------------------------findtrees()-------------------------------
template<class T,int N> void McProcess<T,N>::findtrees(
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

//       std::cout<<std::endl;
//       std::cout<<"pidx= ";
//       for(unsigned int i=0;i<pidx.size();i++){
//         std::cout<<pidx[i]<<" ";
//       }
//       std::cout<<std::endl;

      for (unsigned int j=0;j<pidx.size();j++){
	if(accepted(iEvent,pidx[j],Branch_idx)){
	  matched_pidx.resize(matched_pidx.size()+1);
	  matched_pidx[matched_pidx.size()-1]=pidx[j];
	}
      }

//       std::cout<<"matched_pidx= ";
//       for(unsigned int i=0;i<matched_pidx.size();i++){
//         std::cout<<matched_pidx[i]<<" ";
//       }
//       std::cout<<std::endl;

      IncNum=getIncNum(tree.Branch[Mo_idx],tree.Branch[Branch_idx].pdgId);

      
      if(IncNum>1 && IncNum!=matched_pidx.size()){
        Data<McParticleData<N> >::stdErr("incorrect process declaration\n");
      }
      

      if(IncNum>1 && IncNum==matched_pidx.size()){
        unsigned int indd=0;
        unsigned int first=0;

        for(unsigned int i=0;i<tree.Branch[Mo_idx].nDa;i++){
          if(tree.Branch[Mo_idx].Da_pdgId[i]==tree.Branch[Branch_idx].pdgId){
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

template<class T,int N> unsigned int McProcess<T,N>::
  getIncNum(processBranch_& Branch,std::vector<int> pdg){

  unsigned int IncNum=0;

  for(unsigned int i=0;i<Branch.nDa;i++){
    if(Branch.Da_pdgId[i]==pdg)
      IncNum++;
  }

  return IncNum;
}
//-----------------------------------accepted()--------------------------------

template<class T,int N> bool McProcess<T,N>::accepted(
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
//-----------------------------------isEqualPdg()------------------------------
template<class T,int N> bool McProcess<T,N>::isEqualPdg(
  int pdg,std::vector<int> pdgId){


  for (unsigned int i=0;i<pdgId.size();i++){
    if (pdg==pdgId[i]) return true;
  }
  return false;
}

//-----------------------------------findParticle()----------------------------
template<class T,int N> std::vector<int> McProcess<T,N>::findParticle(
  const edm::Event& iEvent,int idx,std::vector<int> pdg){

  std::vector<int> pidx;

  if (!Data<McParticleData<N> >::isValid()) return pidx;

  edm::Handle<edm::View<T> > particleHandle;
  iEvent.getByLabel(genParticles_, particleHandle );
  if (!particleHandle.isValid()){
    stdErr("set() : Invalid tag %s", Data<McParticleData<N> >::
    tag().label().data());
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

      if (isEqualPdg(p->pdgId(),pdg)){
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

          if (isEqualPdg(da->pdgId(),pdg)){
            found = find(Particles.begin(), Particles.end(), da);
	    if(found != Particles.end()) 
	      idx = found - Particles.begin();          
            pidx.resize(pidx.size()+1);
            pidx[pidx.size()-1]=idx;
          }           
        }
        return pidx;
      }
      
    }
  }

  return pidx;
}

//----------------------- processTree_ constructor ----------------------------
template<class T,int N> McProcess<T,N>::processTree_::processTree_(){

}

//----------------------- processTree_ constructor ----------------------------
template<class T,int N> McProcess<T,N>::processTree_::
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
  Branch[0].Mo_pdgId.resize(0);
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
          Branch[i].Mo_pdgId.resize(Branch[j].pdgId.size());
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

        Branch[Branch.size()-1].pdgId.resize(Branch[i].Da_pdgId[j].size());

          Branch[Branch.size()-1].Mo_name=Branch[i].name;
          Branch[Branch.size()-1].Mo_pdgId.resize(Branch[i].pdgId.size());
          Branch[Branch.size()-1].Mo_pdgId=Branch[i].pdgId;
          Branch[Branch.size()-1].Mo_idx=Branch[i].idx;
          Branch[Branch.size()-1].sort_Mo_idx=Branch[i].sort_idx;
          Branch[Branch.size()-1].Mo_level=Branch[i].level; 

          Branch[Branch.size()-1].name=Branch[i].Da_name[j];          
          Branch[Branch.size()-1].pdgId=Branch[i].Da_pdgId[j];
          Branch[Branch.size()-1].idx=Branch[i].Da_idx[j];
          Branch[Branch.size()-1].sort_idx=Branch[i].sort_Da_idx[j];
          Branch[Branch.size()-1].level=Branch[i].level+1;

          for(unsigned int k=0;k<Branch.size()-1;k++){  
            
          }
          
      }
    }
  }

}

//-------------------------- processTree_ print() -----------------------------

template<class T,int N> void McProcess<T,N>::processTree_::print_(int x) const{

   for(unsigned int i=0;i<Branch.size();i++){
      std::cout<<std::endl;
      Branch[i].printBranch_(x);
      std::cout<<std::endl;
   }
   std::cout<<std::endl;
   std::cout<<"____________________________________________"<<std::endl;

}

//-------------------------- processTree_ clearTree_() ------------------------

template<class T,int N> void McProcess<T,N>::processTree_::clearTree_() {

   for(unsigned int i=0;i<Branch.size();i++){
      Branch[i].clearBranch_();
   }

}

//----------------------- processBranch_ constructor --------------------------
template<class T,int N> McProcess<T,N>::processBranch_::processBranch_(){
}

//----------------------- processBranch_ constructor --------------------------
template<class T,int N> McProcess<T,N>::processBranch_::processBranch_(
  std::string & str){

  nDa=0;
  
  char* last;
  last=&str[str.size()-1];
  std::string::iterator it;

  sort_idx=NOVAL_I;

  Mo_name="";
  Mo_idx=NOVAL_I;
  sort_Mo_idx=NOVAL_I;
  Mo_level=NOVAL_I;

  idx=NOVAL_I;
  level=NOVAL_I;
  Da_level=NOVAL_I;
   
  for ( it=str.begin() ; it < str.end(); it++ )
    if(*it==')') nDa++;
  nDa--;

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

    if (i==0){
      name=ds;
     }else{
       Da_name[i-1]=ds;
       sort_Da_idx[i-1]=NOVAL_I;
    }

    it++;

    while (*it != ')'){ 
      if (*it != ','){
        di+=*it;
        it++;
      }else{
        it++;
	if (i==0){
          pdgId.resize(pdgId.size()+1);
	  pdgId[pdgId.size()-1]=string2int(di);
  	}else{
           Da_pdgId[i-1].resize(Da_pdgId[i-1].size()+1);
 	   Da_pdgId[i-1][Da_pdgId[i-1].size()-1]=string2int(di);
 	}
        di="";
      }
    }
    it++;
    if (i==0){
      pdgId.resize(pdgId.size()+1);
      pdgId[pdgId.size()-1]=string2int(di);
    }else{
      Da_pdgId[i-1].resize(Da_pdgId[i-1].size()+1);
      Da_pdgId[i-1][Da_pdgId[i-1].size()-1]=string2int(di);
   }
    ds="";
    di="";
    if(i!=nDa+1) it++;
  }
}

//----------------------- processBranch_ print() ------------------------------
template<class T,int N> void McProcess<T,N>::processBranch_::
  printBranch_(int x) const{

  if (x>=3){
    std::cout<<std::endl;
    std::cout<<"Mo_name="<<Mo_name<<std::endl;
    std::cout<<"Mo_pdgId=";
    for (unsigned int j=0;j<Mo_pdgId.size();j++){
      std::cout<<Mo_pdgId[j]<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Mo_idx="<<Mo_idx<<std::endl;
    std::cout<<"sort_Mo_idx="<<sort_Mo_idx<<std::endl;
    std::cout<<"Mo_level="<<Mo_level<<std::endl;
    std::cout<<std::endl;
  }
    
    std::cout<<"name="<<name<<std::endl;
  if (x>=1){
    std::cout<<"pdgId=";
    for (unsigned int i=0;i<pdgId.size();i++){
      std::cout<<pdgId[i]<<" ";
    }
    std::cout<<std::endl;
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
      std::cout<<"Da_pdgId["<<i+1<<"]=";
      for (unsigned int j=0;j<Da_pdgId[i].size();j++){
        std::cout<<Da_pdgId[i][j]<<" ";
      }
      std::cout<<std::endl;
      std::cout<<"Da_idx["<<i+1<<"]="<<Da_idx[i]<<std::endl;
      std::cout<<"sort_Da_idx["<<i+1<<"]="<<sort_Da_idx[i]<<std::endl;
    }
    std::cout<<std::endl;
  }
}

//----------------------- processBranch_ clearBranch() ------------------------
template<class T,int N> void McProcess<T,N>::processBranch_::clearBranch_() {

  Mo_name="";
  for (unsigned int i=0;i<Mo_pdgId.size();i++){
    Mo_pdgId[i]=NOVAL_I;
  }
  Mo_idx=NOVAL_I;
  sort_Mo_idx=NOVAL_I;
  Mo_level=NOVAL_I;

  name="";
  for (unsigned int i=0;i<pdgId.size();i++){
    pdgId[i]=NOVAL_I;
  }
  idx=NOVAL_I;
  sort_idx=NOVAL_I;
  level=NOVAL_I;

  matched_idx.resize(0);

  for (unsigned int i=0;i<nDa;i++){
    Da_name[i]="";    
    Da_idx[i]=NOVAL_I;
    sort_Da_idx[i]=NOVAL_I;
    for (unsigned int j=0;j<Da_pdgId[i].size();j++){
      Da_pdgId[i][j]=NOVAL_I;
    }
  }

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}
#endif
