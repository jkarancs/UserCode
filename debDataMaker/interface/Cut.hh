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
// $Id: Cut.hh,v 1.1 2010/07/18 12:32:18 veszpv Exp $
//
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#include <string>
#include "CONST.hh"

namespace deb {

class CutBase {
 public:
  CutBase() { name_ = NOVAL_S; id_ = F; }
  CutBase(std::string name) { name_ = name; id_ = F; }
  CutBase(const CutBase& c) { *this=c; }
  ~CutBase() { }
  
  enum ValueTypeID { I, i, L, l, F, D };

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

//   bool operator!= (const CutBase &rhs) { return !((*this)==rhs); }
//   bool operator== (const CutBase &rhs) {
//     if (name_ != rhs.name_) return false;
//     return (id_ != rhs.id_) ? false : true;
//   }

 private:
  std::string name_;

 protected:
  ValueTypeID id_;

 public:
  const std::string& name() const { return name_; }
  std::string getName() { return name_; }
  void setName(std::string name) { name_=name; }

  ValueTypeID id() const { return id_; }

  inline std::string valueToString(const ValueType& value);

  template<class T> static inline void check(const T& t);

  template<class T> static inline ValueType castToValue(T);

  inline void assert_equal(const CutBase& c);

};

// ------------------------------- valueToString ------------------------------
  
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

// --------------------------------- check() ----------------------------------

template<> void CutBase::check(const int& t) { assert(t!=NOVAL_I); }
template<> void CutBase::check(const unsigned int& t) { assert(t!=NOVAL_i); }
template<> void CutBase::check(const long& t) { assert(t!=NOVAL_L); }
template<> void CutBase::check(const unsigned long& t) { assert(t!=NOVAL_l); }
template<> void CutBase::check(const float& t) { assert(t!=NOVAL_F); }
template<> void CutBase::check(const double& t) { assert(t!=NOVAL_D); }

// ------------------------------- castToValue() ------------------------------

template<> CutBase::ValueType CutBase::castToValue(int I) {
  ValueType v;
  v.I=I;
  return v;
}


template<> CutBase::ValueType CutBase::castToValue(unsigned int i) {
  ValueType v;
  v.i=i;
  return v;
}


template<> CutBase::ValueType CutBase::castToValue(long L) {
  ValueType v;
  v.L=L;
  return v;
}


template<> CutBase::ValueType CutBase::castToValue(unsigned long l) {
  ValueType v;
  v.l=l;
  return v;
}


template<> CutBase::ValueType CutBase::castToValue(float F) {
  ValueType v;
  v.F=F;
  return v;
}


template<> CutBase::ValueType CutBase::castToValue(double D) {
  ValueType v;
  v.D=D;
  return v;
}

// ------------------------------- assert_equal -------------------------------

inline void CutBase::assert_equal(const CutBase& c) {
  #ifdef DEB_DEBUG
  if (name_!=c.name_) {
    std::cout<<"MultiCut::operator+= : Trying to sum up two MultiCuts with "
      "different names (this function should be called from MultiSelection"
      "::operator+=)\n";
    assert(name_==c.name_);
  }
  #endif
  if (id_!=c.id_) {
    std::cout<<"MultiCut::operator+= : Trying to sum up two MultiCuts with "
      "different value types (this function should be called from "
      "MultiSelection::operator+=)\n";
    assert(id_==c.id_);
  }
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

  // should be a friend with Selection
  Cut& operator+= (const Cut& c) {    
    static_cast<CutBase*>(this)->assert_equal(c);
    int passed=passed_+c.passed_;
    init_();
    passed_=passed;
    return *this;
  }

 private:
  ValueType value_;
  int passed_;
  void init_();

 public:
  inline size_t size() const { return 1; }
  template<class T> inline T value() const;
  std::string value_str() { return valueToString(value_); }
  int passed() const { return passed_; }

  void print();
};

  
// --------------------------------- Constructor ------------------------------


template<> 
Cut::Cut(std::string name, int value, int passed) : CutBase(name) {
  assert(value!=NOVAL_I);
  value_.I = value;
  id_ = I;
  passed_ = passed;
}

template<> 
Cut::Cut(std::string name, unsigned int value, int passed) : CutBase(name) {
  assert(value!=NOVAL_i);
  value_.i = value;
  id_ = i;
  passed_ = passed;
}

template<> 
Cut::Cut(std::string name, long value, int passed) : CutBase(name) {
  assert(value!=NOVAL_L);
  value_.L = value;
  id_ = L;
  passed_ = passed;
}

template<> 
Cut::Cut(std::string name, unsigned long value, int passed) : CutBase(name) {
  assert(value!=NOVAL_l);
  value_.l = value;
  id_ = l;
  passed_ = passed;
}

template<> 
Cut::Cut(std::string name, float value, int passed) : CutBase(name) {
  assert(value!=NOVAL_F);
  value_.F = value;
  id_ = F;
  passed_ = passed;
}

template<> 
Cut::Cut(std::string name, double value, int passed) : CutBase(name) {
  assert(value!=NOVAL_D);
  value_.D = value;
  id_ = D;
  passed_ = passed;
}


// --------------------------------- init_() ----------------------------------

void Cut::init_() {
  switch (id_) {
  case I: value_.I = NOVAL_I; break;
  case i: value_.i = NOVAL_i; break;
  case L: value_.L = NOVAL_L; break;
  case l: value_.l = NOVAL_l; break;
  case F: value_.F = NOVAL_F; break;
  case D: value_.D = NOVAL_D; break;
  default : assert(0);
  }
  passed_ = NOVAL_I;
}
  

// --------------------------------- operator= --------------------------------

Cut& Cut::operator= (const Cut& c) {
  if (this==&c) return *this;
  *(static_cast<CutBase*> (this)) = c;
  value_ = c.value_;
  passed_ = c.passed_;
  return *this;
}


// --------------------------------- value() ----------------------------------

template<> Cut::ValueType Cut::value() const { return value_; }
template<> int Cut::value() const { return value_.I; }
template<> unsigned int Cut::value() const { return value_.i; }
template<> long Cut::value() const { return value_.L; }
template<> unsigned long Cut::value() const { return value_.l; }
template<> float Cut::value() const { return value_.F; }
template<> double Cut::value() const { return value_.D; }


// --------------------------------- print() ----------------------------------

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
  MultiCut(const Cut& c) : CutBase(c) {
    init_();
    value_.push_back(c.value<ValueType>());
    passed_.push_back(c.passed());
  }
  template<class T> MultiCut (std::string, T, int);
  ~MultiCut() { }

  MultiCut& operator= (const MultiCut& c);

  // should be a friend with selection
  MultiCut& operator+= (const MultiCut& c) {

    static_cast<CutBase*>(this)->assert_equal(c);
    size_t multi=c.size();

    if (c.size() > size()) {
      for (size_t i=size(); i<c.size(); i++) passed_.push_back(c.passed(i));
      multi=size();
    }

    for (size_t i=0; i<multi; i++) passed_[i]+=c.passed_[i];

    value_.clear();
    return *this;
  }

 private:
  std::vector<ValueType> value_;
  std::vector<int> passed_;
  void init_();

 public:
  inline size_t size() const { return passed_.size(); }
  template<class T> inline T value(size_t i) const;
  std::string value_str(size_t i) { return valueToString(value_[i]); }
  int passed(size_t i) const { return passed_[i]; }

  void add(ValueType value, int passed) {
    value_.push_back(value);
    passed_.push_back(passed);
  }

  void print();
};

  
// --------------------------------- Constructor ------------------------------


template<> 
MultiCut::MultiCut(std::string name, int value, int passed) : CutBase(name) {
  assert(value!=NOVAL_I);
  ValueType v;
  v.I = value;
  id_ = I;
  value_.push_back(v);
  passed_.push_back(passed);
}

template<> 
MultiCut::MultiCut(std::string name, unsigned int value, int passed) 
  : CutBase(name) {
  assert(value!=NOVAL_i);
  ValueType v;
  v.i = value;
  id_ = i;
  value_.push_back(v);
  passed_.push_back(passed);
}

template<> 
MultiCut::MultiCut(std::string name, long value, int passed) : CutBase(name) {
  assert(value!=NOVAL_L);
  ValueType v;
  v.L = value;
  id_ = L;
  value_.push_back(v);
  passed_.push_back(passed);
}

template<> 
MultiCut::MultiCut(std::string name, unsigned long value, int passed) 
  : CutBase(name) {
  assert(value!=NOVAL_l);
  ValueType v;
  v.l = value;
  id_ = l;
  value_.push_back(v);
  passed_.push_back(passed);
}

template<> 
MultiCut::MultiCut(std::string name, float value, int passed) : CutBase(name) {
  assert(value!=NOVAL_F);
//   ValueType v;
//   v.F = value;
//   id_ = F;
//   value_.push_back(v);
  value_.push_back(castToValue(value));
  passed_.push_back(passed);
}

template<> 
MultiCut::MultiCut(std::string name, double value, int passed) 
  : CutBase(name) {
  assert(value!=NOVAL_D);
  ValueType v;
  v.D = value;
  id_ = D;
  value_.push_back(v);
  passed_.push_back(passed);
}


// --------------------------------- init_() ----------------------------------

void MultiCut::init_() {
  value_.clear();
  passed_.clear();
}
  

// --------------------------------- operator= --------------------------------

MultiCut& MultiCut::operator= (const MultiCut& c) {
  *(static_cast<CutBase*> (this)) = c;
  value_ = c.value_;
  passed_ = c.passed_;
  return *this;
}


// --------------------------------- value() ----------------------------------

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


// --------------------------------- print() ----------------------------------

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
