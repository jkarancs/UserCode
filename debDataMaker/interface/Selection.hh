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
// $Id: Selection.hh,v 1.1 2010/07/18 12:32:18 veszpv Exp $
//
//
//-----------------------------------------------------------------------------

#include "SusyAnalysis/debDataMaker/interface/Cut.hh"
#include <limits>

namespace deb {

template<class C>
class SelectionBase {
 public:
  SelectionBase() { init(); }

  SelectionBase(std::string name, std::string object="") 
    : name_(name), object_(object) { clear(); }

  SelectionBase(const SelectionBase<C>& s) { *this=s; }

  ~SelectionBase() { }
  
  void init() {
    name_=NOVAL_S;
    object_=NOVAL_S;
    clear();
  }

  SelectionBase& operator= (const SelectionBase<C>& s) {
    if (this==&s) return *this;
    name_ = s.name_;
    object_ = s.object_;
    cuts_ = s.cuts_;
    entries_ = s.entries_;
    return *this;
  }

  SelectionBase& operator+= (const SelectionBase& s) {
    if ( name_ != s.name_ ||  object_ != s.object_ ) {
      std::cout<<"SelectionBase<C>::operator+= : trying to sum two selections"
	" together that have different selection or object names.\n";
      assert(0);
    }

    entries_ += s.entries_;

    if (s.cuts_.size()==0) return *this;

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

 private:
  std::string name_;
  std::string object_;
  std::vector<C> cuts_;
  unsigned int entries_;

 public:
  inline const std::string& name() { return name_; }
  inline std::string getName() { return name_; }
  inline void setName(std::string name) { name_=name; }

  inline const std::string& object() { return object_; }
  inline std::string getObject() { return object_; }
  inline void setObject(std::string object) { object_=object; }

  inline const std::vector<C>& cuts() const { return cuts_; }
  inline const C& cut(size_t i) const { return cuts_[i]; }

  inline unsigned int entries() const { return entries_; }
  inline void increase_entries() { entries_++; }

  void clear() {
    cuts_.clear();
    entries_=0;
  }
  
  void add(const C& cut);

  void add(const SelectionBase<Cut>& sel);

  inline int passed();

  void print(size_t ncols=8);

};


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
  if (entries_!=sel.entries()) {
    std::cout<<"Selection "<<name_<<" : Trying to add a "
      "selection column with a different number of entries\n";
    assert(0);
  }
  cuts_.insert(cuts_.end(), sel.cuts().begin(), sel.cuts().end());
  return;
}


template<> 
void SelectionBase<MultiCut>::add(const SelectionBase<Cut>& sel) {

  if (entries_!=sel.entries()) {
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
    if (cuts_[i].name()!=sel.cuts().name()) {
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
  for (size_t i=0; i<cuts_.size(); i++) if (cuts_[i].passed() == 0) return 0;
  return 1;
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
  std::cout<<std::setw(20)<<"\t"<<object_<<"\n";
  for (size_t i=0; i<cuts_.size(); i++) {
    std::cout<<std::setw(20)<<cuts_[i].name()<<" :\t"<< cuts_[i].passed();
    if (entries_!=0) {
      std::cout << " (" << std::fixed << std::setprecision(2) 
		<< cuts_[i].passed()*100./entries_ << ") ";
    }
    #ifdef DEB_DEBUG
    std::cout << " (" << valueToString(value_) << ") ";
    #endif
    std::cout<<std::endl;
  }
  std::cout<<std::endl;
}



template<> void SelectionBase<MultiCut>::print(size_t ncols) {

  std::cout<<"\nMultiSelection report: "<<name_<<"\n";
  std::cout<<"Entries: "<<entries_<<std::endl;
  if (cuts_.size()==0) return;

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
      std::cout << " (" << valueToString(value_[j]) << ") ";
      #endif
      std::cout << " ";
    }
    std::cout<<std::endl;
  }
  std::cout<<std::endl;
}


//-----------------------------------------------------------------------------




typedef SelectionBase<Cut> Selection;

typedef SelectionBase<MultiCut> MultiSelection;



}
#endif
