#ifndef SusyAnalysis_debDataMaker_Cut_hh_
#define SusyAnalysis_debDataMaker_Cut_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Cut
// 
/**\class Cut Cut.hh SusyAnalysis/debDataMaker/interface/Cut.hh

 Description: <one line class summary>

 Cut eta("|eta|<2.4", jet(i).eta, jet(i).eta < 2.4);
 Cut eta(jet(i).eta, jet(i).eta < 2.4);

 Implementation: trying to avoid the use of virtual fuctions (less memory /
 faster running due to not having virtual function tables?) The cost is value 
 always using as much space as the largest type, plus a type id variable int

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Jul 18 10:28:26 CET 2010
// $Id: Cut.hh,v 1.3 2010/07/23 14:10:27 veszpv Exp $
//
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#include <string>
#include "CONST.hh"

namespace deb {

template<class C> class SelectionBase;

class CutBase {
 public:
  enum ValueTypeID { I=0, i, L, l, F, D, nan };

  CutBase() { name_ = NOVAL_S; id_ = nan; }
  CutBase(std::string name, ValueTypeID id=nan) { name_ = name; id_ = id; }
  CutBase(const CutBase& c) { *this=c; }
  ~CutBase() { }
  
  union ValueType {
    int I;
    unsigned int i;
    long L;
    unsigned long l;
    float F;
    double D;
  };
  
  CutBase& operator= (const CutBase& c) {
    if (this==&c) return *this;
    name_ = c.name_;
    id_ = c.id_;
    return *this;
  }

 private:
  std::string name_;

 protected:
  ValueTypeID id_;

  // a helper for operator+= in derived classes, 
  // asserts compatibility of 'c' with *this
  inline void               assert_equal_base(const CutBase& c);


 public:
  // Accessors and modifiers:
  const std::string&        name() const { return name_; }
  std::string               getName() { return name_; }
  void                      setName(std::string name) { name_=name; }
  ValueTypeID               id() const { return id_; }

  // Static functions:
  template<class T> 
  static inline ValueTypeID valueTypeID();

  template<class T> 
  static inline ValueTypeID valueTypeID(T& t) { return valueTypeID<T>(); }

  template<class T> 
  static inline ValueType   valueType(T);

  template<class T> 
  static inline void        check(const T& t); // assert that (t!=NOVAL)


  // Misc:
  std::string               valueToString(const ValueType& value);

  TH1*                      create_histogram();

};


// ---------------------- CutBase::assert_equal_base --------------------------

inline void CutBase::assert_equal_base(const CutBase& c) {
  #ifdef DEB_DEBUG
  if (name_!=c.name_) {
    std::cout<<"(Multi)Cut::operator+= : Trying to sum up two MultiCuts with "
      "different names (this function should be called from MultiSelection"
      "::operator+=)\n";
    assert(name_==c.name_);
  }
  #endif
  if (id_!=c.id_) {
    std::cout<<"(Multi)Cut::operator+= : Trying to sum up two MultiCuts with "
      "different value types (this function should be called from "
      "MultiSelection::operator+=)\n";
    assert(id_==c.id_);
  }
}


// ---------------------- CutBase::create_histogram() -------------------------

TH1* CutBase::create_histogram() {
  TH1* ret;

  switch (id_) {
  case I: ret = new TH1I(); break;
  case i: ret = new TH1D(); break;
  case L: ret = new TH1D(); break;
  case l: ret = new TH1D(); break;
  case F: ret = new TH1F(); break;
  case D: ret = new TH1D(); break;
  default : ret = NULL;
  }
  return ret;
}


// ---------------------- CutBase::valueTypeID --------------------------------

template<> 
CutBase::ValueTypeID CutBase::valueTypeID<int>() { return I; }

template<> 
CutBase::ValueTypeID CutBase::valueTypeID<unsigned int>() { return i; }

template<> 
CutBase::ValueTypeID CutBase::valueTypeID<long>() { return L; }

template<> 
CutBase::ValueTypeID CutBase::valueTypeID<unsigned long>() { return l; }

template<> 
CutBase::ValueTypeID CutBase::valueTypeID<float>() { return F; }

template<> 
CutBase::ValueTypeID CutBase::valueTypeID<double>() { return D; }


// ---------------------- CutBase::valueType() ------------------------------

template<> CutBase::ValueType CutBase::valueType(int I) {
  ValueType v;
  v.I=I;
  return v;
}


template<> CutBase::ValueType CutBase::valueType(unsigned int i) {
  ValueType v;
  v.i=i;
  return v;
}


template<> CutBase::ValueType CutBase::valueType(long L) {
  ValueType v;
  v.L=L;
  return v;
}


template<> CutBase::ValueType CutBase::valueType(unsigned long l) {
  ValueType v;
  v.l=l;
  return v;
}


template<> CutBase::ValueType CutBase::valueType(float F) {
  ValueType v;
  v.F=F;
  return v;
}


template<> CutBase::ValueType CutBase::valueType(double D) {
  ValueType v;
  v.D=D;
  return v;
}


// ------------------------ CutBase::check() ----------------------------------

template<> void CutBase::check(const int& t) { assert(t!=NOVAL_I); }
template<> void CutBase::check(const unsigned int& t) { assert(t!=NOVAL_i); }
template<> void CutBase::check(const long& t) { assert(t!=NOVAL_L); }
template<> void CutBase::check(const unsigned long& t) { assert(t!=NOVAL_l); }
template<> void CutBase::check(const float& t) { assert(t!=NOVAL_F); }
template<> void CutBase::check(const double& t) { assert(t!=NOVAL_D); }


// ---------------------- CutBase::valueToString ------------------------------
  
std::string CutBase::valueToString(const ValueType& value) {
  std::ostringstream ss;
  switch (id_) {
  case I: ss << value.I; break;
  case i: ss << value.i; break;
  case L: ss << value.L; break;
  case l: ss << value.l; break;
  case F: ss << value.F; break;
  case D: ss << value.D; break;
  default : ss << "N/A";
  }
  return ss.str();
}



//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------


class Cut : public CutBase{
 public:
  Cut() : CutBase() { init_(); }
  Cut(const Cut& c) : CutBase(c) { *this=c; }
  template<class T> Cut (std::string, T, int);
  ~Cut() { }

  Cut& operator= (const Cut& c);


 private:
  ValueType value_;
  int passed_;

  inline void                 init_id_();
  inline void                 init_();

  Cut&                        operator+= (const Cut& c);

  template<class C> friend class SelectionBase;


 public:

  inline size_t               size() const { return 1; }

  template<class T> inline T  value() const;

  std::string                 value_str() { return valueToString(value_); }

  int                         passed() const { return passed_; }

  void                        print();

  inline TH1*                 create_histogram(size_t i=0);
  
};

  
// ---------------------------- Cut::Constructor ------------------------------


template<class T> Cut::Cut(std::string name, T value, int passed) 
  : CutBase(name, valueTypeID<T>()) {
  check(value);
  value_ = valueType(value);
  passed_ = passed;
}


// ---------------------------- Cut::init_id_() -------------------------------

void Cut::init_id_() {
  switch (id_) {
  case I: value_.I = NOVAL_I; break;
  case i: value_.i = NOVAL_i; break;
  case L: value_.L = NOVAL_L; break;
  case l: value_.l = NOVAL_l; break;
  case F: value_.F = NOVAL_F; break;
  case D: value_.D = NOVAL_D; break;
  default : assert(0);
  }
}
  

// ---------------------------- Cut::init_() ----------------------------------

void Cut::init_() {
  init_id_();
  passed_ = NOVAL_I;
}
  

// ---------------------------- Cut::operator= --------------------------------

Cut& Cut::operator= (const Cut& c) {
  if (this==&c) return *this;
  *(static_cast<CutBase*> (this)) = c;
  value_ = c.value_;
  passed_ = c.passed_;
  return *this;
}


// ---------------------------- Cut::operator+= -------------------------------

Cut& Cut::operator+= (const Cut& c) {    
  assert_equal_base(c);
  init_id_();
  passed_+=c.passed_;
  value_=c.value_;
  return *this;
}


// ---------------------------- Cut::value() ----------------------------------

template<> Cut::ValueType Cut::value() const { return value_; }
template<> int Cut::value() const { return value_.I; }
template<> unsigned int Cut::value() const { return value_.i; }
template<> long Cut::value() const { return value_.L; }
template<> unsigned long Cut::value() const { return value_.l; }
template<> float Cut::value() const { return value_.F; }
template<> double Cut::value() const { return value_.D; }


// ---------------------------- Cut::print() ----------------------------------

void Cut::print() {
  std::cout<<std::setw(20)<<name()<<" :\t"<< passed_;
  #ifdef DEB_DEBUG
  std::cout << " (" << valueToString(value_) << ") ";
  #endif
  std::cout<<std::endl;
}




//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------


class MultiCut : public CutBase {
 public:
  MultiCut() : CutBase() { init_(); }
  MultiCut(const MultiCut& c) : CutBase(c) { *this=c; }
  MultiCut(const Cut& c);
  template<class T> MultiCut (std::string, T, int);
  ~MultiCut() { }

  MultiCut& operator= (const MultiCut& c);


 private:
  std::vector<ValueType> value_;
  std::vector<int> passed_;

  void                 init_() { value_.clear(); passed_.clear(); }

  MultiCut&            operator+= (const MultiCut& c);

  template<class C> friend class SelectionBase;


 public:

  void                 add(ValueType value, int passed);

  inline size_t        size() const { return passed_.size(); }

  template<class T> 
  inline T             value(size_t i) const;

  std::string          value_str(size_t i) { return valueToString(value_[i]); }

  int                  passed(size_t i) const { return passed_[i]; }

  void                 print();
};

  

// ----------------------- MultiCut::operator= --------------------------------

MultiCut& MultiCut::operator= (const MultiCut& c) {
  *(static_cast<CutBase*> (this)) = c;
  value_ = c.value_;
  passed_ = c.passed_;
  return *this;
}


// ----------------------- MultiCut::Constructors -----------------------------

MultiCut::MultiCut(const Cut& c) : CutBase(c) {
  init_();
  value_.push_back(c.value<ValueType>());
  passed_.push_back(c.passed());
}



template<class T> 
MultiCut::MultiCut(std::string name, T value, int passed) 
  : CutBase(name, valueTypeID<T>()) {
  check(value);
  value_.push_back(valueType(value));
  passed_.push_back(passed);
}



// ---------------------- MultiCut::add() -------------------------------------

void MultiCut::add(ValueType value, int passed) {
  value_.push_back(value);
  passed_.push_back(passed);
}



// ----------------------- MultiCut::operator+= -------------------------------

MultiCut& MultiCut::operator+= (const MultiCut& c) {
  assert_equal_base(c);
  size_t multi=c.size();
  
  if (c.size() > size()) {
    multi=size(); // Save before passed_ is enlarged!
    for (size_t i=size(); i<c.size(); i++) {
      passed_.push_back(c.passed_[i]);
      value_.push_back(c.value_[i]);
    }
  }
  
  for (size_t i=0; i<multi; i++) {
    passed_[i]+=c.passed_[i];
    value_[i]=c.value_[i];
  }

  return *this;
}


// ----------------------- MultiCut::value() ----------------------------------

template<> 
MultiCut::ValueType MultiCut::value(size_t i) const { return value_[i]; }

template<> 
int MultiCut::value(size_t i) const { return value_[i].I; }

template<> 
unsigned int MultiCut::value(size_t i) const { return value_[i].i; }

template<> 
long MultiCut::value(size_t i) const { return value_[i].L; }

template<> 
unsigned long MultiCut::value(size_t i) const { return value_[i].l; }

template<> 
float MultiCut::value(size_t i) const { return value_[i].F; }

template<> 
double MultiCut::value(size_t i) const { return value_[i].D; }


// ----------------------- MultiCut::print() ----------------------------------

void MultiCut::print() {
  std::cout<<std::setw(20)<<name()<<" :";
  for (size_t i=0; i<passed_.size(); i++) {
    std::cout << "\t" << passed_[i];
    #ifdef DEB_DEBUG
    std::cout << " (" << valueToString(value_[i]) << ") ";
    #endif
    std::cout << " ";
  }
  std::cout<<std::endl;
}


}
#endif
