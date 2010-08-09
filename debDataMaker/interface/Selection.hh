#ifndef SusyAnalysis_debDataMaker_Selection_hh_
#define SusyAnalysis_debDataMaker_Selection_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Selection
// 
/**\class Selection Selection.hh SusyAnalysis/debDataMaker/interface/Selection.hh

 Description: <one line class summary>

 Implementation:

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Mar 18 10:28:26 CET 2009
// $Id: Selection.hh,v 1.7 2010/08/03 09:31:51 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/Cut.hh"
#include "TFile.h"
#include "TTree.h"
#include <limits>

#define CUT_NAME_LENGTH 30

namespace deb {

template<class C>
class SelectionBase {
 public:
  enum  SelectionOp { individual=1, sequential=2, complementary=4 };

  SelectionBase() { init(); }

  SelectionBase(std::string name, 
		SelectionOp op=individual,
		std::string object=NOVAL_S)
    : name_(name), op_(op), object_(object) { clear(); }

  SelectionBase(const SelectionBase& s) { *this=s; }

  ~SelectionBase() { }
  
  template<class CC> friend class SelectionBase;
  template<class F> friend class SelectionTree;

  SelectionBase& operator= (const SelectionBase& s);

 private:
  std::string name_;
  SelectionOp op_;
  std::string object_;
  std::vector<C> cuts_;
  unsigned int entries_;


  void init();

 public:
  void                          clear();
  SelectionBase&                operator+= (const SelectionBase& s);

  inline const std::string&     name() const { return name_; }
  inline std::string            getName() const { return name_; }
  inline void                   setName(std::string name) { name_=name; }

  inline const std::string&     object() const { return object_; }
  inline std::string            getObject() const { return object_; }
  inline void                   setObject(std::string object) {object_=object;}

  inline const std::vector<C>&  cuts() const { return cuts_; }
  inline const C&               cut(size_t i) const { return cuts_[i]; }

  inline unsigned int           entries() const { return entries_; }
  inline void                   increase_entries() { entries_++; }
  
  SelectionOp                   op() const { return op_; }

  void                          add(const C& cut);

  void                          add(const SelectionBase<Cut>& sel);

  inline int                    passed();

  void                          print(size_t ncols=8, 
				      std::string prepend="",
				      std::string last="");

  void                          analyze(SelectionBase& result, SelectionOp op);

};


//------------------------------ operator= ------------------------------------

template<class C>
SelectionBase<C>& SelectionBase<C>::operator= (const SelectionBase<C>& s) {

  if (this==&s) return *this;
  name_ = s.name_;
  object_ = s.object_;
  op_ = s.op_;
  cuts_ = s.cuts_;
  entries_ = s.entries_;
  return *this;
}


//-------------------------------- init() -------------------------------------

template<class C>
void SelectionBase<C>::init() {
  name_=NOVAL_S;
  object_=NOVAL_S;
  op_=individual;
  clear();
}


//-------------------------------- clear() ------------------------------------

template<class C>
void SelectionBase<C>::clear() {
  cuts_.clear();
  entries_=0;
}



//----------------------------- operator+=  -----------------------------------

template<class C> 
SelectionBase<C>& SelectionBase<C>::operator+= (const SelectionBase<C>& s) {

  if ( name_ != s.name_ ||  object_ != s.object_ || op_ != s.op_ ) {
    std::cout<<"SelectionBase<C>::operator+= : trying to sum two selections"
      " together that have different selection or object names, or different"
      " representations.\n";
    assert(0);
  }

  if (cuts_.size()!=0 && entries_==0) entries_=1;
 
  entries_ += s.entries_;

  if (s.cuts_.size()==0) {
    return *this;
  } else {
    if (s.entries_==0) ++entries_;
  }
  
  if (cuts_.size()==0) {
    cuts_ = s.cuts_;
    return *this;
  }
  
  if (cuts_.size()!=s.cuts_.size()) {
    std::cout<<"SelectionBase"<<name_<<" operator+= : Trying to "
	     <<"sum up selections with different number of cuts ("
	     <<s.cuts_.size()<<"->"<<cuts_.size()<<")\n";
    assert(0);
  }
  
  for (size_t i=0; i<cuts_.size(); i++) cuts_[i]+=s.cuts_[i];

  return *this;
}



//-------------------------------- add(Cut) -----------------------------------

template<class C>
void SelectionBase<C>::add(const C& cut) {
  if (cuts_.size()!=0) {
    if (cuts_[cuts_.size()-1].size()!=cut.size()) {
      std::cout<<"SelectionBase "<<name_<<" : Trying to add a line of cuts"
	"with number of columns different from the cuts in the selection\n";
      assert(0);
    }
  }
  cuts_.push_back(cut); 
}


//-------------------------------- add(Selection) -----------------------------

template<> 
void SelectionBase<Cut>::add(const SelectionBase<Cut>& sel) {
  if ( op_ != individual || sel.op_ != individual ) {
    std::cout<<"Selection "<<name_<<" : Trying to add columns with wrong"
      "representations\n";
    assert(op_==individual);
    assert(sel.op_==individual);
  }

  if ( entries_!=sel.entries() && (entries_ > 1 || sel.entries_ > 1) ) {
    std::cout<<"Selection "<<name_<<" : Trying to add a "
      "selection column with a different number of entries\n";
    assert(0);
  }

  cuts_.insert(cuts_.end(), sel.cuts().begin(), sel.cuts().end());
  return;
}


template<> 
void SelectionBase<MultiCut>::add(const SelectionBase<Cut>& sel) {
  if ( op_ != individual || sel.op_ != SelectionBase<Cut>::individual ) {
    std::cout<<"Selection "<<name_<<" : Trying to add columns with wrong"
      "representations\n";
    assert(op_==individual);
    assert(sel.op_==SelectionBase<Cut>::individual);
  }

  if ( entries_!=sel.entries() && (entries_ > 1 || sel.entries_ > 1) ) {
    std::cout<<"MultiSelection "<<name_<<" : Trying to add a "
      "selection column with different number of entries\n";
    assert(0);
  }

  if (cuts_.size()==0) {
    for (size_t i=0; i<sel.cuts().size(); i++) {
      MultiCut cut(sel.cut(i));
      cuts_.push_back(cut);
    }
    return;
  }

  if (cuts_.size()!=sel.cuts().size()) {
    std::cout<<"SelectionBase<MultiCut> "<<name_<<" : Trying to add a "
	     <<"selection column with different number of cuts ("
	     <<sel.cuts().size()<<"->"<<cuts_.size()<<")\n";
    assert(0);
  }

  for (size_t i=0; i<cuts_.size(); i++) {
    #ifdef DEB_DEBUG
    if (cuts_[i].name()!=sel.cut(i).name()) {
      std::cout<<"SelectionBase<MultiCut> "<<name_<<" : Trying to add a "
	"selection column with a different set of cuts\n";
      assert(0);
    }
    #endif
    cuts_[i].add(sel.cuts_[i].value_, sel.cuts_[i].passed_);
  }

  return;
}


//------------------------------- passed()-------------------------------------

template<> int SelectionBase<Cut>::passed() {
  assert(entries_<2);
  assert(cuts_.size()!=0);

  if (op_ == sequential) return (cuts_[cuts_.size()-1].passed()==0) ? 0 : 1;

  if (op_ == individual) {
    for (size_t i=0; i<cuts_.size(); i++) if (cuts_[i].passed() == 0) return 0;
    return 1;
  }

  assert(0);
  return NOVAL_I;
}


template<> int SelectionBase<MultiCut>::passed() {
  std::cout << "SelectionBase<MulitCut>::passed() : call is ambiguous. \n";
  assert(0);
  return NOVAL_I;
}



//------------------------------- print()--------------------------------------

template<> 
void SelectionBase<Cut>::print(size_t ncols, std::string prepend, 
			       std::string last) {
  std::cout<<prepend<<"Selection report: "<<name_<<"\n";
  std::cout<<prepend<<"Entries: "<<entries_<<std::endl;
  std::cout<<prepend<<"Selection option: "<<op_<<std::endl;
  std::cout<<prepend<<std::setw(CUT_NAME_LENGTH)<<" "<<"\t"<<object_<<"\n";
  for (size_t i=0; i<cuts_.size(); i++) {
    std::cout<<prepend<<std::setw(CUT_NAME_LENGTH)
	     <<cuts_[i].name()<<" :\t"<< cuts_[i].passed();
    if (entries_!=0) {
      std::cout << " (" << std::fixed << std::setprecision(2) 
		<< cuts_[i].passed()*100./entries_ << ") ";
    }
    #ifdef DEB_DEBUG
    if (entries_<2) std::cout << " (" << cuts_[i].value_str() << ") ";
    #endif
    std::cout<<std::endl;
  }
  std::cout<<last;
}



template<> 
void SelectionBase<MultiCut>::print(size_t ncols, 
				    std::string prepend, std::string last) {

  std::cout<<prepend<<"MultiSelection report: "<<name_<<"\n";
  std::cout<<prepend<<"Entries: "<<entries_<<std::endl;
  std::cout<<prepend<<"Selection option: "<<op_<<std::endl;
  if (cuts_.size()==0) {
    std::cout<<prepend<<std::endl;
    return;
  }

  std::cout<<prepend<<std::setw(CUT_NAME_LENGTH)<<" "<<"  ";
  for (size_t i=0; i<cuts_[0].size() && i<ncols; i++) {
    std::cout<<"\t";
    if (entries_!=0 && i!=0) std::cout<<"\t";
    std::cout<<object_<<"_"<<i;
  }
  std::cout<<std::endl;

  for (size_t i=0; i<cuts_.size(); i++) {
    std::cout<<prepend<<std::setw(CUT_NAME_LENGTH);
    std::cout<<cuts_[i].name()<<" :";
    for (size_t j=0; j<cuts_[i].size() && j<ncols; j++) {
      std::cout << "\t" << cuts_[i].passed(j);
      if (entries_!=0) {
	std::cout << " (" << std::fixed << std::setprecision(2)
		  << cuts_[i].passed(j)*100./entries_ << ") ";
      }
      #ifdef DEB_DEBUG
      if (entries_<2) std::cout << " (" << cuts_[i].value_str(j) << ") ";
      #endif
      std::cout << " ";
    }
    std::cout<<std::endl;
  }

  std::cout<<last;
}



//------------------------------- analyze() -----------------------------------

template<class C> 
void SelectionBase<C>::analyze(SelectionBase<C>& result, SelectionOp op) {

  if (entries_ > 1) {
    std::cout << "(Multi)Selection::analyze() : cannot analyze a Selection"
      " containing the results of multiple events.";
    assert(entries_ > 1);
  }

  if (op_ != individual) {
    std::cout<<"(Multi)Selection::analyze() : cannot analyze this kind of "
	     <<"selection\n";
    assert(op_!=individual);
  }

  if (cuts_.size()==0) {
    result=*this;
    result.op_ = op;
    return;
  }

  if (op == op_) {
    result=*this;
    return;
  }

  if (op == sequential) {
    result=*this; // WARNING: result and this may be the same array
    result.op_=op;
    for (size_t j=0; j<cuts_[0].size(); j++) {
      size_t i=0;
      for ( ; i<cuts_.size(); i++) if (cuts_[i].passed_[j]==0) break;
      if (i==cuts_.size()) continue;
      for (i++; i<cuts_.size(); i++) {
	result.cuts_[i].passed_[j]=0;
	result.cuts_[i].setValueInvalid(j);
      }
    }
    return;
  }

  if (op == complementary) {
    result=*this; // WARNING: result and this may be the same array
    result.op_=op;
    for (size_t j=0; j<cuts_[0].size(); j++) {
      size_t i=0;
      for ( ; i<cuts_.size(); i++) if (cuts_[i].passed_[j]==0) break;
      if (i==cuts_.size()) continue;
      size_t i_passed=i;
      for (i++; i<cuts_.size(); i++) { 
	if (cuts_[i].passed_[j]==0) break; 
	result.cuts_[i].passed_[j]=0;
	result.cuts_[i].setValueInvalid(j);
      }
      if (i==cuts_.size()) {
	result.cuts_[i_passed].passed_[j]=1;
      } else {
	for (i++; i<cuts_.size(); i++) {
	  result.cuts_[i].passed_[j]=0;
	  result.cuts_[i].setValueInvalid(j);
	}
      }
      for (i=0; i<i_passed; i++) {
	result.cuts_[i].passed_[j]=0;
	result.cuts_[i].setValueInvalid(j);
      }
    }
    return;
  }

}





//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------





typedef SelectionBase<Cut> Selection;

typedef SelectionBase<MultiCut> MultiSelection;




//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

//class TFileService;

template<class F=TFile> class SelectionTree {
 public:

  SelectionTree() { f_ = NULL; name_ = object_ = NOVAL_S; clear_(); }
 

  SelectionTree(std::string name, std::string object)
    : name_(name), object_(object) { f_ = NULL; clear_(); }


  SelectionTree(std::string name, std::string object, F& f)
    : name_(name), object_(object) { f_ = &f; clear_(); }


  template<class C> 
  SelectionTree(const SelectionBase<C>& sel) 
    : name_(sel.name()), object_(sel.object()) { f_ =NULL; clear_(); }


  template<class C> 
  SelectionTree(const SelectionBase<C>& sel, F& f) 
    : name_(sel.name()), object_(sel.object()) { f_ = &f; clear_(); }


  SelectionTree(const SelectionTree& s) { *this=s; }


  ~SelectionTree() { }

  // Shallow copy, does not duplicate the tree. This is only for STL containers
  SelectionTree& operator= (const SelectionTree&);


 private:
  F* f_;
  std::string name_;            // name of selection
  std::string object_;          // name the object of selection

  std::vector<std::vector<TTree*> > tree_; // (iobj, icut) -> Tree

  void                          clear_() { tree_.clear(); }

  TTree*                        make_tree_(std::string);

  template<class C>
  void                          addTree_(const SelectionBase<C>&, size_t);

  template<class C>
  void                          fillTree_(const SelectionBase<C>&, size_t);


 public:

  inline F*                     file() { return f_; }

  inline const std::string&     name() { return name_; }
  inline std::string            getName() { return name_; }

  inline const std::string&     object() { return object_; }
  inline std::string            getObject() { return object_; }

  template<class C> void        fill(const SelectionBase<C>&);

  // Plot<TH1>*                 plot();
  // Where plot Name==this::object_, Title==this::name_, Index==[i_obj][i_cut]
  // the histos in the plot: Name= plot::Name_plot::Index, Title==cut::Name
 
};


//---------------------------- operator= () -----------------------------------
// Shallow copy, does not duplicate the tree. This is only for STL containers

template<class F>
SelectionTree<F>& SelectionTree<F>::operator= (const SelectionTree<F>& s) {
  if (this==&s) return *this;
  f_ = s.f_;
  name_ = s.name_;
  object_ = s.object_;
  tree_ = s.tree_;
  return *this;
}



//----------------------------- make_tree_() ----------------------------------

template<>
TTree* SelectionTree<TFile>::make_tree_(std::string tname) {
  TTree* ret = new TTree(tname.c_str(), "SelectionTree");
  assert(ret != NULL);
  return ret;
}


template<class F>
TTree* SelectionTree<F>::make_tree_(std::string tname) {
  assert( f_ != NULL);
  TTree* ret = f_->template make<TTree>(tname.c_str(), "SelectionTree");
  assert(ret != NULL);
  return ret;
}


//-------------------------------- addTree_ () -------------------------------

template<class F>
template<class C>
void SelectionTree<F>::addTree_(const SelectionBase<C>& sel, size_t iobj) {
  
  if (sel.cuts_.size()==0) return;

  #ifdef DEB_DEBUG
  assert( iobj <= sel.cuts_[0].size() );
  std::cout<< "SelectionTree::fill() : expanding tree with branches for "
	   << sel.object_ << "_" << iobj << std::endl;
  #endif

  std::vector<TTree*> tree;

  for (size_t icut=0; icut<sel.cuts_.size(); icut++) {
    std::ostringstream tname;
    tname << object_ << iobj << "_" << name_ << "_cut" << icut;
    TTree *t = make_tree_(tname.str());

    std::ostringstream vlist;
    vlist << "val/" << sel.cuts_[icut].valueTypeName();
    TBranch* br = t->Branch("val", NULL, vlist.str().c_str());
    assert(br != NULL);

    tree.push_back(t);
  }

  tree_.push_back(tree);

}


//------------------------------- fillTree () -------------------------------

template<class F>
template<class C>
void SelectionTree<F>::fillTree_(const SelectionBase<C>& sel, size_t iobj) {
  
  #ifdef DEB_DEBUG
  assert( iobj <= sel.cuts_[0].size() );
  assert( tree_.size() != 0 );

  std::cout<< "SelectionTree::fill() : filling branch for "
	   << sel.object_ << "_" << iobj << std::endl;
  #endif

  for (size_t icut=0; icut<sel.cuts_.size(); icut++) {

    #ifdef DEB_DEBUG
    if (icut!=0) std::cout << ", ";
    std::cout << sel.cuts_[icut].name()
	      << " (" << sel.cuts_[icut].value_str(iobj);
    #endif
    
    if (sel.cuts_[icut].isValid(iobj)) {
      #ifdef DEB_DEBUG
      assert( tree_[iobj][icut] != NULL ); // was checked in make_tree_()
      assert( tree_[iobj][icut]->GetListOfBranches()->GetEntriesFast() == 1 );
      std::cout<<" -> "<<tree_[iobj][icut]->GetName() << ")";
      #endif

      TBranch* b = 
	(TBranch*) tree_[iobj][icut]->GetListOfBranches()->UncheckedAt(0);

      Cut::ValueType* v = const_cast<Cut::ValueType*>
	(&sel.cuts_[icut].template value<Cut::ValueType>(iobj));

      b->SetAddress(v);
      tree_[iobj][icut]->Fill();
    }
    #ifdef DEB_DEBUG
    else {
      std::cout<<" not filled)";
    }
    #endif
  }
  
  #ifdef DEB_DEBUG
  std::cout<<std::endl;
  #endif
}



//------------------------------- fill() --------------------------------------

template<class F>
template<class C> 
void SelectionTree<F>::fill(const SelectionBase<C>& sel) {

  #ifdef DEB_DEBUG
  std::cout<<"SelectionTree::fill() : "<<name_<<" called.\n";
  #endif

  if (sel.cuts_.size()==0) return;

  size_t multi=sel.cuts_[0].size();
  
  if ( sel.cuts_[0].size() > tree_.size() ) {
    multi=tree_.size(); // Save before passed_ is enlarged!

    for (size_t iobj=tree_.size(); iobj<sel.cuts_[0].size(); iobj++) {
      addTree_(sel, iobj);
      fillTree_(sel, iobj);
    }
  }
  
  for (size_t iobj=0; iobj<multi; iobj++) fillTree_(sel, iobj);

  return;
}


}
#endif
