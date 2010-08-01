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
// $Id: Cut.hh,v 1.4 2010/07/27 09:45:41 veszpv Exp $
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

  // These functions are protected because they all need to know 'id_'
  inline ValueType          invalidValue() const;
  inline bool               isValid(ValueType value) const;
  std::string               valueToString(const ValueType& value) const;
  inline size_t             valueSize() const;
  inline std::string        valueTypeName() const { return valueTypeName(id_);}

  // a helper for operator+= in derived classes, 
  // asserts compatibility of 'c' with *this
  inline void               assert_equal_base(const CutBase& c);


 public:
  // Accessors and modifiers:
  const std::string&        name() const { return name_; }
  std::string               getName() const { return name_; }
  void                      setName(std::string name) { name_=name; }
  ValueTypeID               id() const { return id_; }

  // Static functions:
  template<class T> 
  static inline ValueTypeID valueTypeID();

  template<class T> 
  static inline ValueTypeID valueTypeID(T& t) { return valueTypeID<T>(); }


  template<class T> 
  static inline ValueType   valueType(T); //cast input to ValueType


  static const char*        valueTypeName(ValueTypeID id);
 
  template<class T> 
  static inline void        check(const T& t) { assert(t!=NOVAL<T>()); }

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


// ---------------------- CutBase::valueTypeName() ----------------------------

const char*  CutBase::valueTypeName(ValueTypeID id) {  
  switch (id) {
  case I: return ("I");
  case i: return ("i");
  case L: return ("L");
  case l: return ("l");
  case F: return ("F");
  case D: return ("D");
  default : return (NOVAL_S);
  }
}


// ---------------------- CutBase::valueToString ------------------------------
  
std::string CutBase::valueToString(const ValueType& value) const {
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


// ---------------------- CutBase::valueSize ----------------------------------
  
size_t CutBase::valueSize() const {
  switch (id_) {
  case I: return (sizeof(int));
  case i: return (sizeof(unsigned int));
  case L: return (sizeof(long));
  case l: return (sizeof(unsigned long));
  case F: return (sizeof(float));
  case D: return (sizeof(double));
  default : assert(0);
  }
}


// ----------------------- CutBase::invalidValue() ----------------------------

CutBase::ValueType CutBase::invalidValue() const {
  ValueType value;
  switch (id_) {
  case I: value.I = NOVAL_I; break;
  case i: value.i = NOVAL_i; break;
  case L: value.L = NOVAL_L; break;
  case l: value.l = NOVAL_l; break;
  case F: value.F = NOVAL_F; break;
  case D: value.D = NOVAL_D; break;
  default : assert(0);
  }
  return value;
}
  


// ----------------------- CutBase::isValid() ---------------------------------

bool CutBase::isValid(ValueType value) const {
  switch (id_) {
  case I: return (value.I != NOVAL_I);
  case i: return (value.i != NOVAL_i);
  case L: return (value.L != NOVAL_L);
  case l: return (value.l != NOVAL_l);
  case F: return (value.F != NOVAL_F);
  case D: return (value.D != NOVAL_D);
  default : assert(0);
  }
  return false;
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

  inline void                 init_();

  Cut&                        operator+= (const Cut& c);

  template<class T> 
  inline T&                   get_value_();

  template<class C> friend class SelectionBase;
  template<class F> friend class SelectionTree;


 public:

  inline size_t               size() const { return 1; }

  inline void                 setValueInvalid() { value_=invalidValue(); }
  inline void                 setValueInvalid(size_t i) { setValueInvalid(); }

  inline bool                 isValid() { return CutBase::isValid(value_); }
  inline bool                 isValid(size_t i) { return isValid(); }

  template<class T> 
  inline const T&             value() const { return get_value_<T>(); }

  template<class T> 
  inline const T&             value(size_t i) const { return value<T>(); }

  template<class T> inline void value(T& t) const;
  template<class T> inline void value(size_t i, T& t) const { value(t);}

  std::string                 value_str() { return valueToString(value_); }

  int                         passed() const { return passed_; }

  void                        print() const;

};

  
// ---------------------------- Cut::Constructor ------------------------------


template<class T> Cut::Cut(std::string name, T value, int passed) 
  : CutBase(name, valueTypeID<T>()) {
  check(value);
  value_ = valueType(value);
  passed_ = passed;
}


// ---------------------------- Cut::init_() ----------------------------------

void Cut::init_() {
  setValueInvalid();
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
  passed_+=c.passed_;
  value_=c.value_;
  return *this;
}


// ---------------------------- Cut::value() ----------------------------------

template<class T> T& Cut::get_value_() {
  switch (id_) {
  case I: return (static_cast<T>(value_.I));
  case i: return (static_cast<T>(value_.i));
  case L: return (static_cast<T>(value_.L));
  case l: return (static_cast<T>(value_.l));
  case F: return (static_cast<T>(value_.F));
  case D: return (static_cast<T>(value_.D));
  default : assert(0);
  }
}

template<> Cut::ValueType& Cut::get_value_() { return value_; }


// ---------------------------- Cut::value() ----------------------------------

template<class T> void Cut::value(T& t) const {
  switch (id_) {
  case I: t=static_cast<T>(value_.I);break;
  case i: t=static_cast<T>(value_.i);break;
  case L: t=static_cast<T>(value_.L);break;
  case l: t=static_cast<T>(value_.l);break;
  case F: t=static_cast<T>(value_.F);break;
  case D: t=static_cast<T>(value_.D);break;
  default : assert(0);
  }
}

template<> void Cut::value(ValueType& t) const { t=value_; }


// ---------------------------- Cut::print() ----------------------------------

void Cut::print() const {
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

  template<class T> 
  inline T&            get_value_(size_t j);  

  template<class C> friend class SelectionBase;
  template<class F> friend class SelectionTree;


 public:

  void            add(ValueType value, int passed);

  inline void     setValueInvalid(size_t i) { value_[i]=invalidValue(); }

  inline bool     isValid(size_t i) const{ return CutBase::isValid(value_[i]);}

  inline size_t   size() const { return passed_.size(); }

  template<class T> 
  inline const T& value(size_t j) const { 
    return const_cast<MultiCut*>(this)->get_value_<T>(j); 
  }

  template<class T> 
  void            value(size_t j, T& t) const;

  std::string     value_str(size_t i) const{ return valueToString(value_[i]); }

  int             passed(size_t i) const { return passed_[i]; }

  void            print() const;
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
  //value_.push_back(c.value<ValueType>());
  ValueType v;
  c.value(v);
  value_.push_back(v);
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


template<class T> T& MultiCut::get_value_(size_t j) {
  switch (id_) {
  case I: return (static_cast<T>(value_[j].I));
  case i: return (static_cast<T>(value_[j].i));
  case L: return (static_cast<T>(value_[j].L));
  case l: return (static_cast<T>(value_[j].l));
  case F: return (static_cast<T>(value_[j].F));
  case D: return (static_cast<T>(value_[j].D));
  default : assert(0);
  }
}  


template<> 
MultiCut::ValueType& MultiCut::get_value_(size_t j) { return value_[j]; }


// ----------------------- MultiCut::value() ----------------------------------


template<class T> void MultiCut::value(size_t j, T& t) const {
  switch (id_) {
  case I: t=static_cast<T>(value_[j].I); break;
  case i: t=static_cast<T>(value_[j].i); break;
  case L: t=static_cast<T>(value_[j].L); break;
  case l: t=static_cast<T>(value_[j].l); break;
  case F: t=static_cast<T>(value_[j].F); break;
  case D: t=static_cast<T>(value_[j].D); break;
  default : assert(0);
  }
}  

template<> 
void MultiCut::value(size_t i, ValueType& v) const { v=value_[i]; }



// ----------------------- MultiCut::print() ----------------------------------

void MultiCut::print() const {
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
