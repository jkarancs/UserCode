#ifndef SusyAnalysis_debDataMaker_McProcessProducer_hh_
#define SusyAnalysis_debDataMaker_McProcessProducer_hh_
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
	mcProcessTag = cms.InputTag("genParticles","","HLT"),
	processTree  = cms.vstring(
	  'Mo(pdgId,pdgId,...),Da1(pdgId,pdgId,...),Da2(pdgId,pdgId,...)',
	  'Da1(pdgId,pdgId,...),Da3(pdgId,pdgId,...),Da4(pdgId,pdgId,...)',
	  'Da2(pdgId,pdgId,...),Da5(pdgId,...,pdgId,...)'
        )
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
// $Id: McProcessProducer.hh,v 1.1 2009/08/22 17:05:03 aranyi Exp $
//
//
//-----------------------------------------------------------------------------



#include "DataFormats/Common/interface/View.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SusyAnalysis/debDataMaker/interface/McProcess.hh"
#include "SusyAnalysis/debDataMaker/interface/Producer.hh"

namespace deb {

//----------------------------- Class Definition ------------------------------

template<class T,int N> class McProcessProducer : 
public Producer<McProcess<N> >{
						// D:=ParticleData

 public:
	 
  McProcessProducer(const edm::ParameterSet& iConfig);
  McProcessProducer() { stdErr("  Process<%s> configuration missing\n", 
		     typeid(T).name()); }

  // Inherited functions to be overloaded
  void set(const edm::Event&,unsigned int);

  // Introduce new variables and functions
  unsigned int findProcess(const edm::Event&);

 private:

   std::vector<std::string> processTreePara_;

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
     void clearBranch_();
     //void printBranch_(int) const;

   };


   struct processTree_ {
	   
     std::vector<processBranch_> Branch;

     processTree_();
     processTree_(std::vector<std::string> &);
     //void print_(int) const;
     void clearTree_();
     
   };

   processTree_ tree;
   std::vector<processTree_> trees;
   std::vector<std::string> particleNames;

    std::vector<int> findParticle(const edm::Event&,int,std::vector<int>);
    bool accepted(const edm::Event&,int,int);
    void findtrees(const edm::Event&,int,int,int);
    unsigned int getIncNum(processBranch_&,std::vector<int>);
    bool isEqualPdg(int,std::vector<int>);
    int getStoreNParticles(const edm::ParameterSet& iConfig);  
    std::vector<std::string> getParticleNames(const edm::ParameterSet& iConfig);

public:
    void printBranch_(processBranch_,int);
    void print_(processTree_,int);

};
    


//--------------------------------- Constructor -------------------------------

template<class T,int N> McProcessProducer<T,N>::
  McProcessProducer(const edm::ParameterSet& iConfig) : 
  Producer<McProcess<N> >(
	iConfig.getParameter<edm::InputTag>("mcProcessTag"), 
	iConfig.getParameter<std::string>("name"),
        iConfig.getParameter< std::vector<std::string> >("storeList")){
	//getStoreNParticles(iConfig)){         
        //getParticleNames(iConfig)){
  
  processTreePara_=
    iConfig.getParameter< std::vector<std::string> >("processTree");

    processBranch_ Branch(processTreePara_[0]);
    //Branch.printBranch_(3);
   processTree_ t(processTreePara_);
   particleNames=getParticleNames(iConfig);
   tree=t;
   //tree.print_(3);
}

//-----------------------------getParticleNames()------------------------------

template<class T,int N> std::vector<std::string> McProcessProducer<T,N>::
  getParticleNames(const edm::ParameterSet& iConfig) { 

  std::vector<std::string> brr;
  std::vector<std::string> particleNames;
  brr=
    iConfig.getParameter< std::vector<std::string> >("processTree");

  processTree_ tre(brr);

  particleNames.resize(particleNames.size()+1);
  particleNames[0]=tre.Branch[0].name;
  for(unsigned int i=0;i<tre.Branch.size();i++){
    for(unsigned int j=0;j<tre.Branch[i].nDa;j++){  
      particleNames.resize(particleNames.size()+1);
      particleNames[particleNames.size()-1]=tre.Branch[i].Da_name[j];     
    }
  }
  return particleNames;
}

//-----------------------------getStoreNParticles()----------------------------

template<class T,int N> int McProcessProducer<T,N>::
  getStoreNParticles(const edm::ParameterSet& iConfig) { 

std::vector<std::string> brr;
  brr=
    iConfig.getParameter< std::vector<std::string> >("processTree");

  processTree_ tre(brr);

  int StoreNParticles=1;
  for(unsigned int i=0;i<tre.Branch.size();i++){
    for(unsigned int j=0;j<tre.Branch[i].nDa;j++){
      StoreNParticles++;
    }
  }
  return StoreNParticles;
}

//----------------------------------- set() -----------------------------------
template<class T,int N> void McProcessProducer<T,N>::set(const edm::Event& iEvent,
  unsigned int numProc) {

  if (!MContainer<std::string, McParticleData<N> >::isValid()) return;

  if (trees.size()==0){
    MContainer<std::string, McParticleData<N> >::stdErr("  No process found! \n");
    return;
  }

  edm::Handle<edm::View<T> > particleHandle;
  iEvent.getByLabel(Producer<McProcess<N> >::tag(), particleHandle );
  if (!particleHandle.isValid()){
    stdErr("set() : Invalid tag %s", Producer<McProcess<N> >::
      tag().label().data());
    return;
  }


  std::vector<const T *> Particles;
  typename std::vector<const T *>::const_iterator found;

      for(typename edm::View<T>::const_iterator p = particleHandle->begin();
	p != particleHandle->end(); ++ p ) {
	Particles.push_back( & * p );
      }

  int idx;
  int moidx=-1;
 // int ind;
  processBranch_ lastBranch(processTreePara_[0]);

  Producer<McProcess<N> >::clear();    
//   for(unsigned int i=0;i<trees[numProc].Branch.size();i++){   
//                                  
//   }

  //for(unsigned int i=0;i<trees[numProc].Branch.size();i++){ 

  for(unsigned int i=0;i<particleNames.size();i++){ 

      //std::string particleName=trees[numProc].Branch[i].name;
      std::string particleName=particleNames[i];
      McParticleData<N> new_obj;
      insert(particleName, new_obj);


   unsigned int nameind=0;
   for(unsigned int j=0;j<trees[numProc].Branch.size();j++){ 
     if (particleName==trees[numProc].Branch[j].name) nameind=j;
     
   }

      for(typename edm::View<T>::const_iterator p = particleHandle->begin();
	p != particleHandle->end(); ++ p ) {
	
	idx =  p - particleHandle->begin();

        if (idx==trees[numProc].Branch[nameind].matched_idx[0]){

//          ind=trees[numProc].Branch[i].sort_idx;

          Producer<McProcess<N> >::McParticle(particleName).e = p->energy();
	  Producer<McProcess<N> >::McParticle(particleName).px = p->px();
	  Producer<McProcess<N> >::McParticle(particleName).py = p->py();
	  Producer<McProcess<N> >::McParticle(particleName).pz = p->pz();
	  Producer<McProcess<N> >::McParticle(particleName).m = p->mass();
	  Producer<McProcess<N> >::McParticle(particleName).p = p->p();
	  Producer<McProcess<N> >::McParticle(particleName).et = p->et();
	  Producer<McProcess<N> >::McParticle(particleName).pt = p->pt();
	  Producer<McProcess<N> >::McParticle(particleName).phi = p->phi();
	  Producer<McProcess<N> >::McParticle(particleName).eta = p->eta();


          Producer<McProcess<N> >::McParticle(particleName).idx=idx;

          if (i==0){

	     const T * mo = p->mother(0);

            found = std::find(Particles.begin(), Particles.end(), mo);
	    if(found != Particles.end()) 
	      moidx = found - Particles.begin();                   
            
	    Producer<McProcess<N> >::McParticle(particleName).mo1 = moidx;
          }else{
            Producer<McProcess<N> >::McParticle(particleName).mo1 = trees[numProc].Branch[
              trees[numProc].Branch[nameind].Mo_idx].matched_idx[0];
          }
	  //McParticle(i).mo2 =trees[numProc].Branch[i].sort_Mo_idx;
          
          if(trees[numProc].Branch[nameind].Da_idx.size()!=0){ 

            for (unsigned int l=0;l<trees[numProc].Branch[nameind].Da_idx.size();l++){
  
              if (trees[numProc].Branch[nameind].Da_idx[l]!=NOVAL_I){
                Producer<McProcess<N> >::McParticle(particleName).da[l]=trees[numProc].Branch[
                  trees[numProc].Branch[nameind].Da_idx[l]].matched_idx[0];
              }else{               
                Producer<McProcess<N> >::McParticle(particleName).da[l]=NOVAL_I;
              }
                
            }
          }else{
            for(unsigned int ii = 0; ii < p->numberOfDaughters(); ++ii ) {
              const T * da = p->daughter(ii);

              found = std::find(Particles.begin(), Particles.end(), da);
	      if(found != Particles.end()) 
	      moidx = found - Particles.begin();

              Producer<McProcess<N> >::McParticle(particleName).da[ii]=moidx;
              if (ii>2) break;
            }

          }
          
          Producer<McProcess<N> >::McParticle(particleName).pdg=p->pdgId();
          Producer<McProcess<N> >::McParticle(particleName).stat = p->status();
        } 

      }
  }
}
  
//-----------------------------------findProcess()-----------------------------
template<class T,int N> unsigned int McProcessProducer<T,N>::findProcess(
  const edm::Event& iEvent) {
  

  //Producer<McParticleData<N> >::stdMesg("%s", "  findprocess");
  int level_size=tree.Branch[tree.Branch.size()-1].level+1;

  //tree.print_(3);
  MContainer<std::string, McParticleData<N> >::stdMesg("%s", "  findprocess");

  trees.resize(0);

  unsigned int axusize;

  findtrees(iEvent,0,0,0);

  if (trees.size()==0){
    stdMesg("  Number of process found: %d \n", trees.size());
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
  
  stdMesg("  Number of process found: %d", trees.size());  

  for(unsigned int i=0;i<trees.size();i++){
    //trees[i].print_(0);
    print_(trees[i],0);
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
template<class T,int N> void McProcessProducer<T,N>::findtrees(
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
        Producer<McProcess<N> >::stdErr("incorrect process declaration\n");
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

template<class T,int N> unsigned int McProcessProducer<T,N>::
  getIncNum(processBranch_& Branch,std::vector<int> pdg){

  unsigned int IncNum=0;

  for(unsigned int i=0;i<Branch.nDa;i++){
    if(Branch.Da_pdgId[i]==pdg)
      IncNum++;
  }

  return IncNum;
}
//-----------------------------------accepted()--------------------------------

template<class T,int N> bool McProcessProducer<T,N>::accepted(
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
template<class T,int N> bool McProcessProducer<T,N>::isEqualPdg(
  int pdg,std::vector<int> pdgId){


  for (unsigned int i=0;i<pdgId.size();i++){
    if (pdg==pdgId[i] || pdg==0 || pdgId[i]==0) return true;
  }
  return false;
}

//-----------------------------------findParticle()----------------------------
template<class T,int N> std::vector<int> McProcessProducer<T,N>::findParticle(
  const edm::Event& iEvent,int idx,std::vector<int> pdg){

  std::vector<int> pidx;

  if (!Producer<McProcess<N> >::isValid()) return pidx;

  edm::Handle<edm::View<T> > particleHandle;
  iEvent.getByLabel(Producer<McProcess<N> >::tag(), particleHandle );
  if (!particleHandle.isValid()){
    stdErr("set() : Invalid tag %s", Producer<McProcess<N> >::
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
            found = std::find(Particles.begin(), Particles.end(), da);
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
template<class T,int N> McProcessProducer<T,N>::processTree_::processTree_(){

}

//----------------------- processTree_ constructor ----------------------------
template<class T,int N> McProcessProducer<T,N>::processTree_::
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

          //for(unsigned int k=0;k<Branch.size()-1;k++){  
            
          //}
          
      }
    }
  }

  for(unsigned int i=0;i<Branch.size();i++){
    for(unsigned int j=0;j<Branch[i].nDa;j++){
      Branch[i].Da_idx[j]=NOVAL_I;
      for(unsigned int k=i;k<Branch.size();k++){
        if (Branch[i].Da_name[j]==Branch[k].name) Branch[i].Da_idx[j]=k;
      }
    }
  }

}

//-------------------------- processTree_ print() -----------------------------

template<class T,int N> void McProcessProducer<T,N>::print_(processTree_ tree,int x){

   for(unsigned int i=0;i<tree.Branch.size();i++){
      std::cout<<std::endl;
      //Branch[i].printBranch_(x);
      printBranch_(tree.Branch[i],x);
      std::cout<<std::endl;
   }
   std::cout<<std::endl;
   std::cout<<"____________________________________________"<<std::endl;

}

//-------------------------- processTree_ clearTree_() ------------------------

template<class T,int N> void McProcessProducer<T,N>::processTree_::clearTree_() {

   for(unsigned int i=0;i<Branch.size();i++){
      Branch[i].clearBranch_();
   }

}

//----------------------- processBranch_ constructor --------------------------
template<class T,int N> McProcessProducer<T,N>::processBranch_::processBranch_(){
}

//----------------------- processBranch_ constructor --------------------------
template<class T,int N> McProcessProducer<T,N>::processBranch_::processBranch_(
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
template<class T,int N> void McProcessProducer<T,N>::
  printBranch_(processBranch_ Branch,int x){

  //Data<McParticleData<N> > cout_(1);
  //Producer<McProcess<N> > cout_(1);

  if (x>=3){
    std::cout<<std::endl;
    std::cout<<"Mo_name="<<Branch.Mo_name<<std::endl;
    std::cout<<"Mo_pdgId=";
    for (unsigned int j=0;j<Branch.Mo_pdgId.size();j++){
      std::cout<<Branch.Mo_pdgId[j]<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Mo_idx="<<Branch.Mo_idx<<std::endl;
    std::cout<<"sort_Mo_idx="<<Branch.sort_Mo_idx<<std::endl;
    std::cout<<"Mo_level="<<Branch.Mo_level<<std::endl;
    std::cout<<std::endl;
  }

    //std::cout<<"name="<<name<<std::endl;

    //cout_.stdMesg("  name= %s", name.data());
   MContainer<std::string, McParticleData<N> >::stdMesg("  name= %s", Branch.name.data());
    
  if (x>=1){
    std::cout<<"pdgId=";
    for (unsigned int i=0;i<Branch.pdgId.size();i++){
      std::cout<<Branch.pdgId[i]<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"idx="<<Branch.idx<<std::endl;
    std::cout<<"sort_idx="<<Branch.sort_idx<<std::endl;
    std::cout<<"level="<<Branch.level<<std::endl;
    std::cout<<std::endl;
  }

  //std::cout<<"matched_idx=";
  //cout_.stdMesg("  matched_idx= %d", matched_idx[0]);
  MContainer<std::string, McParticleData<N> >::stdMesg("  matched_idx= %d", Branch.matched_idx[0]);
//   if (matched_idx.size()==0)
//     std::cout<<NOVAL_I;
//   for (unsigned int i=0;i<matched_idx.size();i++){      
//     std::cout<<matched_idx[i]<<" ";
//   }

  

  if(x>=2){
    std::cout<<std::endl;
    std::cout<<"Da_level="<<Branch.Da_level<<std::endl;
    for (unsigned int i=0;i<Branch.nDa;i++){
      std::cout<<"Da_name["<<i+1<<"]="<<Branch.Da_name[i]<<std::endl;
      std::cout<<"Da_pdgId["<<i+1<<"]=";
      for (unsigned int j=0;j<Branch.Da_pdgId[i].size();j++){
        std::cout<<Branch.Da_pdgId[i][j]<<" ";
      }
      std::cout<<std::endl;
      std::cout<<"Da_idx["<<i+1<<"]="<<Branch.Da_idx[i]<<std::endl;
      std::cout<<"sort_Da_idx["<<i+1<<"]="<<Branch.sort_Da_idx[i]<<std::endl;
    }
    std::cout<<std::endl;
  }

 //cout_.clear();
}

//----------------------- processBranch_ clearBranch() ------------------------
template<class T,int N> void McProcessProducer<T,N>::processBranch_::clearBranch_() {

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