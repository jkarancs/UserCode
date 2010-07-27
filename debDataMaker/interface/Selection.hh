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
// $Id: Selection.hh,v 1.3 2010/07/23 14:10:27 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/Cut.hh"
#include <limits>

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

  inline const std::string&     name() { return name_; }
  inline std::string            getName() { return name_; }
  inline void                   setName(std::string name) { name_=name; }

  inline const std::string&     object() { return object_; }
  inline std::string            getObject() { return object_; }
  inline void                   setObject(std::string object) {object_=object;}

  inline const std::vector<C>&  cuts() const { return cuts_; }
  inline const C&               cut(size_t i) const { return cuts_[i]; }

  inline unsigned int           entries() const { return entries_; }
  inline void                   increase_entries() { entries_++; }
  
  SelectionOp                   op() { return op_; }

  void                          add(const C& cut);

  void                          add(const SelectionBase<Cut>& sel);

  inline int                    passed();

  void                          print(size_t ncols=8);

  void                          analyze(SelectionBase& result, SelectionOp op);

  //void                          fill(Plot<TH1>& plot);

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
    cuts_[i].add(sel.cut(i).value<Cut::ValueType>(), sel.cut(i).passed());
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

template<> void SelectionBase<Cut>::print(size_t ncols) {
  std::cout<<"\nSelection report: "<<name_<<"\n";
  std::cout<<"Entries: "<<entries_<<std::endl;
  std::cout<<"Selection option: "<<op_<<std::endl;
  std::cout<<std::setw(20)<<"\t"<<object_<<"\n";
  for (size_t i=0; i<cuts_.size(); i++) {
    std::cout<<std::setw(20)<<cuts_[i].name()<<" :\t"<< cuts_[i].passed();
    if (entries_!=0) {
      std::cout << " (" << std::fixed << std::setprecision(2) 
		<< cuts_[i].passed()*100./entries_ << ") ";
    }
    #ifdef DEB_DEBUG
    if (entries_ < 2) std::cout << " (" << cuts_[i].value_str() << ") ";
    #endif
    std::cout<<std::endl;
  }
  std::cout<<std::endl;
}



template<> void SelectionBase<MultiCut>::print(size_t ncols) {

  std::cout<<"\nMultiSelection report: "<<name_<<"\n";
  std::cout<<"Entries: "<<entries_<<std::endl;
  std::cout<<"Selection option: "<<op_<<std::endl;
  if (cuts_.size()==0) {
    std::cout<<std::endl;
    return;
  }

  std::cout<<std::setw(20);
  for (size_t i=0; i<cuts_[0].size() && i<ncols; i++) {
    std::cout<<"\t";
    if (entries_!=0 && i!=0) std::cout<<"\t";
    std::cout<<object_<<"_"<<i;
  }
  std::cout<<std::endl;

  for (size_t i=0; i<cuts_.size(); i++) {
    std::cout<<std::setw(20)<<cuts_[i].name()<<" :";
    for (size_t j=0; j<cuts_[i].size() && j<ncols; j++) {
      std::cout << "\t" << cuts_[i].passed(j);
      if (entries_!=0) {
	std::cout << " (" << std::fixed << std::setprecision(2)
		  << cuts_[i].passed(j)*100./entries_ << ") ";
      }
      #ifdef DEB_DEBUG
      if (entries_ < 2) std::cout << " (" << cuts_[i].value_str(j) << ") ";
      #endif
      std::cout << " ";
    }
    std::cout<<std::endl;
  }
  std::cout<<std::endl;
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
      for (i++; i<cuts_.size(); i++) result.cuts_[i].passed_[j]=0;
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
      }
      if (i==cuts_.size()) {
	result.cuts_[i_passed].passed_[j]=1;
      } else {
	for (i++; i<cuts_.size(); i++) result.cuts_[i].passed_[j]=0;
      }
      for (i=0; i<i_passed; i++) result.cuts_[i].passed_[j]=0;
    }
    return;
  }

}


//------------------------------- plot() --------------------------------------

// template<class C> void SelectionBase<C>::fill(Plot<TH1>& plot) {

//   if (plot.size()==0) {

//     for (size_t i=0; i<cuts_.size(); i++) {
//       for (size_t j=0; j<cuts_[i].size(); j++) {
// 	TH1* h=cuts_[i].create_histogram(j);
	
//       }
//     }

//   } else {
//     #ifdef DEB_DEBUG
    
//     #endif
//   }

  
// }




//-----------------------------------------------------------------------------



typedef SelectionBase<Cut> Selection;

typedef SelectionBase<MultiCut> MultiSelection;



}
#endif
