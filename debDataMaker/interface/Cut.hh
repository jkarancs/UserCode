#ifndef SusyAnalysis_debDataMaker_Cut_hh_
#define SusyAnalysis_debDataMaker_Cut_hh_
// -*- C++ -*-
//
// Package:    debDataMaker
// Class:      Cut
// 
/**\class Cut Cut.hh SusyAnalysis/debDataMaker/interface/Cut.hh

 Description: <one line class summary>

 Implementation:

*/
//
// Original Author:  Viktor VESZPREMI
//         Created:  Wed Jul 18 10:28:26 CET 2010
// $Id$
//
//
//-----------------------------------------------------------------------------

#include <string>
#include "CONST.hh"

namespace deb {

class Cut {
 public:
  Cut() { init(); }
  Cut(const Cut& c) { init(); *this=c; }
  template<class T> Cut(std::string, T, int);
  ~Cut() { }

  union ValueType {
    int I;
    unsigned int i;
    long L;
    unsigned long l;
    float F;
    double D;
  };
  
  void init() {
    name_ = NOVAL_S;
    value_.D = 0;
    result_ = NOVAL_I;
  }
  
  Cut& operator= (const Cut& c) {
    name_ = c.name_;
    value_ = c.value_;
    result_ = c.result_;
    return *this;
  }
  
 private:
  std::string name_;
  ValueType value_;
  int result_;
  
 public:
  inline std::string& name() { return name_; }
  template<class T> inline T value();
  inline int result() { return result_; }
  
  template<class T> static inline bool check(T& t);

};

  
// --------------------------------- Constructor ------------------------------


template<> Cut::Cut(std::string name, int value, int result) {
  name_ = name;
  value_.I = value;
  result_ = result;
}

template<> Cut::Cut(std::string name, unsigned int value, int result) {
  name_ = name;
  value_.i = value;
  result_ = result;
}

template<> Cut::Cut(std::string name, long value, int result) {
  name_ = name;
  value_.L = value;
  result_ = result;
}

template<> Cut::Cut(std::string name, unsigned long value, int result) {
  name_ = name;
  value_.l = value;
  result_ = result;
}

template<> Cut::Cut(std::string name, float value, int result) {
  name_ = name;
  value_.F = value;
  result_ = result;
}

template<> Cut::Cut(std::string name, double value, int result) {
  name_ = name;
  value_.D = value;
  result_ = result;
}


// --------------------------------- value() ----------------------------------

template<> int Cut::value() { return value_.I; }
template<> unsigned int Cut::value() { return value_.i; }
template<> long Cut::value() { return value_.L; }
template<> unsigned long Cut::value() { return value_.l; }
template<> float Cut::value() { return value_.F; }
template<> double Cut::value() { return value_.D; }


// --------------------------------- check() ----------------------------------

template<> bool Cut::check(int& t) { return t==NOVAL_I; }
template<> bool Cut::check(unsigned int& t) { return t==NOVAL_i; }
template<> bool Cut::check(long& t) { return t==NOVAL_L; }
template<> bool Cut::check(unsigned long& t) { return t==NOVAL_l; }
template<> bool Cut::check(float& t) { return t==NOVAL_F; }
template<> bool Cut::check(double& t) { return t==NOVAL_D; }


}
#endif
